/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eval_move.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/05 14:08:26 by tide-jon       #+#    #+#                */
/*   Updated: 2019/07/12 22:54:01 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void				check_touch_right(t_fillerlst *move, t_filler *data)
{
	int	i;
	int	j;

	j = 0;
	while (j < data->piece_y)
	{
		i = 0;
		while (i < data->piece_x)
		{
			if (data->piece[j][i] == '*')
			{
				if (move->x + i == data->map_x - 1 || (data->splitpoint_y ==
				data->map_y - 1 && move->y + j == data->map_y - 1) ||
				(data->splitpoint_y == 0 && move->y + j == 0))
				{
					move->x_touch = 1;
					move->weight -= 10000000;
				}
			}
			i++;
		}
		j++;
	}
}

void				check_touch_left(t_fillerlst *move, t_filler *data)
{
	int	i;
	int	j;

	j = 0;
	while (j < data->piece_y)
	{
		i = 0;
		while (i < data->piece_x)
		{
			if (data->piece[j][i] == '*')
			{
				if (move->x + i == 0 || (data->splitpoint_y ==
				data->map_y - 1 && move->y + j == data->map_y - 1) ||
				(data->splitpoint_y == 0 && move->y + j == 0))
				{
					move->x_touch = 1;
					move->weight -= 10000000;
				}
			}
			i++;
		}
		j++;
	}
}

void				check_touch_up(t_fillerlst *move, t_filler *data)
{
	int	i;
	int	j;

	j = 0;
	while (j < data->piece_y)
	{
		i = 0;
		while (i < data->piece_x)
		{
			if (data->piece[j][i] == '*')
			{
				if (move->y + j == 0 || (data->splitpoint_x ==
				data->map_x - 1 && move->x + i == data->map_x - 1) || // <-- zorgt voor problemen...
				(data->splitpoint_x == 0 && move->x + i == 0))
				{
					move->y_touch = 1;
					move->weight -= 10000000;
				}
			}
			i++;
		}
		j++;
	}
}

void				check_touch_down(t_fillerlst *move, t_filler *data)
{
	int	i;
	int	j;

	j = 0;
	while (j < data->piece_y)
	{
		i = 0;
		while (i < data->piece_x)
		{
			if (data->piece[j][i] == '*')
			{
				if (move->y + j == data->map_y - 1 || (data->splitpoint_x ==
				data->map_x - 1 && move->x + i == data->map_x - 1) ||
				(data->splitpoint_x == 0 && move->x + i == 0))
				{
					move->y_touch = 1;
					move->weight -= 10000000;
				}
			}
			i++;
		}
		j++;
	}
}

void			check_touch_x(t_filler *data, t_fillerlst *move)
{
	if (data->my_start_x < data->middle_x)
		check_touch_right(move, data);
	else
		check_touch_left(move, data);
}

void			check_touch_y(t_filler *data, t_fillerlst *move)
{
	if (data->my_start_y < data->middle_y)
		check_touch_down(move, data);
	else
		check_touch_up(move, data);
}

static void		distance_to_ypath(t_filler *data, t_fillerlst *move)
{
	int i;
	int j;
	int	distance_sum;

	j = 0;
	distance_sum = 0;
	while (j < data->piece_y)
	{
		i = 0;
		while (i < data->piece_x)
		{
			if (data->piece[j][i] == '*')
			{
				distance_sum += ft_abs(data->splitpoint_x - (move->x + i));
			}
			i++;
		}
		j++;
	}
	move->weight += distance_sum * 200 / data->movenum * data->movenum;
}

static void		distance_to_xpath(t_filler *data, t_fillerlst *move)
{
	int i;
	int j;
	int	distance_sum;

	j = 0;
	distance_sum = 0;
	while (j < data->piece_y)
	{
		i = 0;
		while (i < data->piece_x)
		{
			if (data->piece[j][i] == '*')
			{
				distance_sum += ft_abs(data->splitpoint_y - (move->y + j));
			}
			i++;
		}
		j++;
	}
	move->weight += distance_sum * 200 / data->movenum * data->movenum;
}

static void		to_xwall(t_filler *data, t_fillerlst *move)
{
	distance_to_xpath(data, move);
	if (data->my_start_x > data->middle_x)
		move->weight += move->x * 50;
	else
		move->weight += (data->map_x - move->x) * 50;
	if (data->my_start_y > data->middle_y)
		move->weight -= (data->map_y - move->y) * 5 - data->movenum * 10;
	else
		move->weight -= move->y * 5 - data->movenum * 10;
	check_touch_x(data, move);
}

static void		to_ywall(t_filler *data, t_fillerlst *move)
{
	distance_to_ypath(data, move);
	if (data->my_start_y > data->middle_y)
		move->weight += move->y * 50;
	else
		move->weight += (data->map_y - move->y) * 50;
	if (data->my_start_x > data->middle_x)
		move->weight -= (data->map_x - move->x) * 5 - data->movenum * 10;
	else
		move->weight -= move->x * 5 - data->movenum * 10;
	check_touch_y(data, move);
}

static void		to_walls(t_filler *data, t_fillerlst *move)
{
	move->weight = 0;
	if (data->x_wall_touch == 1)
		to_ywall(data, move);
	if (data->y_wall_touch == 1)
		to_xwall(data, move);
	else if (data->piecesize_x >= data->piecesize_y)
	{
		if (data->swap == 1)
			to_ywall(data, move);
		else
			to_xwall(data, move);
	}
	else
	{
		if (data->swap == 1)
			to_xwall(data, move);
		else
			to_ywall(data, move);
	}
	if (data->x_wall_touch == 1 && data->y_wall_touch == 1)
		data->phase = 3;
}

static void		to_middle(t_filler *data, t_fillerlst *move)
{
	int	i;
	int	j;
	int	closest;
	int	new;

	j = 0;
	closest = 10000000;
	while (j < data->piece_y)
	{
		i = 0;
		while (i < data->piece_x)
		{
			if (data->piece[j][i] == '*')
			{
				new = DISTANCE_TO_MID;
				if (new < closest)
					closest = new;
			}
			i++;
		}
		j++;
	}
	move->weight = closest;
}

void			invade_enemy(t_filler *data, t_fillerlst *move)
{
	move->weight = 0;
	if (data->my_start_x > data->middle_x)
		move->weight += move->x;
	else
		move->weight += (data->map_x - move->x);
	if (data->my_start_y > data->middle_y)
		move->weight += move->y;
	else
		move->weight += data->map_y - move->y;
}

void			eval_move(t_filler *data, t_fillerlst *move)
{
	if (data->phase == 1)
		to_middle(data, move);
	if (data->phase == 2)
	{
		get_piecesize(data);
		to_walls(data, move);
	}
	if (data->phase == 3)
		invade_enemy(data, move);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eval_move.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/05 14:08:26 by tide-jon       #+#    #+#                */
/*   Updated: 2019/07/07 17:32:35 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

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
	move->weight += distance_sum * 3000 - (data->movenum * 50);
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
	move->weight += distance_sum * 1000;
}

static void		to_xwall(t_filler *data, t_fillerlst *move)
{
	distance_to_xpath(data, move);
	if (data->my_start_x > data->middle_x)
		move->weight += move->x * 1000;
	else
		move->weight += (data->map_x - move->x) * 1000;
	if (data->my_start_y > data->middle_y)
		move->weight += move->y;
	else
		move->weight -= move->y; 
}

static void		to_ywall(t_filler *data, t_fillerlst *move)
{
	distance_to_ypath(data, move);
	if (data->my_start_y > data->middle_y)
		move->weight += move->y * 1000;
	else
		move->weight += (data->map_y - move->y) * 1000;
	if (data->my_start_x > data->middle_x)
		move->weight += move->x;
	else
		move->weight -= move->x; 
}

// dit bouwt nog niet naar de muren toe vanaf de split in het midden.
// oftewel: je moet 2 verschillende tracks gaan bijhouden

static void		to_walls(t_filler *data, t_fillerlst *move)
{
	move->weight = 0;
	if (data->piecesize_x >= data->piecesize_y)
		to_xwall(data, move);
	else
		to_ywall(data, move);
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

void			eval_move(t_filler *data, t_fillerlst *move)
{
	if (data->phase == 1)
		to_middle(data, move);
	if (data->phase == 2)
	{
		get_piecesize(data);
		to_walls(data, move);
	}
	// capture_enemy(data, move);
	// if (capture_enemy == 0)
	// fill_space(data, move);
}

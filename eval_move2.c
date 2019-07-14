/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eval_move2.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/14 16:47:02 by tide-jon       #+#    #+#                */
/*   Updated: 2019/07/14 21:07:43 by tide-jon      ########   odam.nl         */
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
	move->weight += distance_sum * PATH_WEIGHT / data->movenum * data->movenum;
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
	move->weight += distance_sum * PATH_WEIGHT / data->movenum * data->movenum;
}

static void		to_xwall(t_filler *data, t_fillerlst *move)
{
	distance_to_xpath(data, move);
	if (data->my_start_x > data->middle_x)
		move->weight += move->x * WALL_DIST_WEIGHT;
	else
		move->weight += (data->map_x - move->x) * WALL_DIST_WEIGHT;
	if (data->my_start_y > data->middle_y)
		move->weight -= (data->map_y - move->y) * CURVE - data->movenum * 10;
	else
		move->weight -= move->y * CURVE - data->movenum * 10;
}

static void		to_ywall(t_filler *data, t_fillerlst *move)
{
	distance_to_ypath(data, move);
	if (data->my_start_y > data->middle_y)
		move->weight += move->y * WALL_DIST_WEIGHT;
	else
		move->weight += (data->map_y - move->y) * WALL_DIST_WEIGHT;
	if (data->my_start_x > data->middle_x)
		move->weight -= (data->map_x - move->x) * CURVE - data->movenum * 10;
	else
		move->weight -= move->x * CURVE - data->movenum * 10;
}

void			to_walls(t_filler *data, t_fillerlst *move)
{
	move->weight = 0;
	if (data->x_wall_touch == 1)
		to_ywall(data, move);
	else if (data->y_wall_touch == 1)
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
	if (data->y_wall_touch != 1)
		check_touch_y(data, move);
	if (data->x_wall_touch != 1)
		check_touch_x(data, move);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eval_move.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/05 14:08:26 by tide-jon       #+#    #+#                */
/*   Updated: 2019/07/14 21:10:24 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

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
		if (data->gap_found == 1 && fill_gap(data, move) == 1)
			move->weight = -10000000;
		else
		{
			get_piecesize(data);
			to_walls(data, move);
		}
	}
	if (data->phase == 3)
	{
		if (data->gap_found == 1 && fill_gap(data, move) == 1)
			move->weight = -10000000;
		else
			invade_enemy(data, move);
	}
}

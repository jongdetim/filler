/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eval_move.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/05 14:08:26 by tide-jon       #+#    #+#                */
/*   Updated: 2019/07/06 20:50:54 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void		to_xwall(t_filler *data, t_fillerlst *move)
{
	if (data->my_start_x > data->middle_x)
		move->weight = move->x * 1000;
	else
		move->weight = (data->map_x - move->x) * 1000;
	if (data->my_start_y > data->middle_y)
		move->weight += move->y;
	else
		move->weight -= move->y; 
}

static void		to_ywall(t_filler *data, t_fillerlst *move)
{
	if (data->my_start_y > data->middle_y)
		move->weight = move->y * 1000;
	else
		move->weight = (data->map_y - move->y) * 1000;
	if (data->my_start_x > data->middle_x)
		move->weight += move->x;
	else
		move->weight -= move->x; 
}

// dit bouwt nog niet naar de muren toe vanaf de split in het midden.
// oftewel: je moet 2 verschillende tracks gaan bijhouden

static void		to_walls(t_filler *data, t_fillerlst *move)
{
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
				new = ft_pythagoras(data->middle_x - (move->x + i),
									data->middle_y - (move->y + j));
				if (new <= closest)
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
		to_walls(data, move);
	// capture_enemy(data, move);
	// if (capture_enemy == 0)
	// fill_space(data, move);
}

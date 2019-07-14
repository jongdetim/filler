/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   phase2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/14 16:33:48 by tide-jon       #+#    #+#                */
/*   Updated: 2019/07/14 17:00:29 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void		save_splitpoint(t_filler *data, t_fillerlst *best,
															int i, int j)
{
	data->splitpoint_x = best->x + i;
	data->splitpoint_y = best->y + j;
}

void			get_splitpoint(t_filler *data, t_fillerlst *move)
{
	int i;
	int j;
	int	new;
	int	closest;

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
				{
					closest = new;
					save_splitpoint(data, move, i, j);
				}
			}
			i++;
		}
		j++;
	}
}

int				check_enemy_x(t_filler *data)
{
	if (data->my_start_x < data->middle_x)
		return (check_enemy_right(data));
	else
		return (check_enemy_left(data));
}

int				check_enemy_y(t_filler *data)
{
	if (data->my_start_y < data->middle_y)
		return (check_enemy_down(data));
	else
		return (check_enemy_up(data));
}

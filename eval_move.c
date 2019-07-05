/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   eval_move.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/05 14:08:26 by tide-jon       #+#    #+#                */
/*   Updated: 2019/07/05 18:04:12 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int				ft_abs(int num)
{
	if (num < 0)
		num *= -1;
	return (num);
}

static void		to_middle(t_filler *data, t_fillerlst *move)
{
	int	i;
	int	j;
	int	closest;
	int	new;

	j = 0;
	closest = INFINITY;
	while (j < data->piece_y)
	{
		i = 0;
		while (i < data->piece_x)
		{
			if (data->piece[j][i] == '*')
			{
				new = ft_abs(data->middle_x - (move->x + i)) +
						ft_abs(data->middle_y - (move->y + j));
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
	to_middle(data, move);
	// to_enemy(data, move);
	// capture_enemy(data, move);
	// if (capture_enemy == 0)
	// 	fill_space(data, move);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_touch.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/14 16:44:42 by tide-jon       #+#    #+#                */
/*   Updated: 2019/07/14 20:40:21 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/*
**	checks if our player has reached a relevant wall
*/

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
					move->weight = -10000000;
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
					move->weight = -10000000;
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
				data->map_x - 1 && move->x + i == data->map_x - 1) ||
				(data->splitpoint_x == 0 && move->x + i == 0))
				{
					move->y_touch = 1;
					move->weight = -10000000;
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
					move->weight = -10000000;
				}
			}
			i++;
		}
		j++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_enemy.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/14 16:34:07 by tide-jon       #+#    #+#                */
/*   Updated: 2019/07/14 16:58:56 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/*
**	checks if out path is blocked by the enemy player
*/

int				check_enemy_down(t_filler *data)
{
	int y;
	int ret;

	ret = 0;
	y = 0;
	while (data->splitpoint_y + y < data->map_y && data->splitpoint_x != 0 &&
										data->splitpoint_x != data->map_x - 1)
	{
		if (data->map[data->splitpoint_y + y][data->splitpoint_x] ==
												ft_toupper(data->enemy))
		{
			if (data->my_start_x < data->middle_x)
				data->splitpoint_x--;
			else
				data->splitpoint_x++;
			y = -1;
			ret = 1;
		}
		y++;
	}
	return (ret);
}

int				check_enemy_up(t_filler *data)
{
	int y;
	int ret;

	ret = 0;
	y = 0;
	while (data->splitpoint_y - y >= 0 && data->splitpoint_x != 0 &&
										data->splitpoint_x != data->map_x - 1)
	{
		if (data->map[data->splitpoint_y - y][data->splitpoint_x] ==
												ft_toupper(data->enemy))
		{
			if (data->my_start_x < data->middle_x)
				data->splitpoint_x--;
			else
				data->splitpoint_x++;
			y = -1;
			ret = 1;
		}
		y++;
	}
	return (ret);
}

int				check_enemy_right(t_filler *data)
{
	int x;
	int ret;

	ret = 0;
	x = 0;
	while (data->splitpoint_x + x < data->map_x && data->splitpoint_y != 0 &&
										data->splitpoint_y != data->map_y - 1)
	{
		if (data->map[data->splitpoint_y][data->splitpoint_x + x] ==
												ft_toupper(data->enemy))
		{
			if (data->my_start_y < data->middle_y)
				data->splitpoint_y--;
			else
				data->splitpoint_y++;
			x = -1;
			ret = 1;
		}
		x++;
	}
	return (ret);
}

int				check_enemy_left(t_filler *data)
{
	int x;
	int ret;

	ret = 0;
	x = 0;
	while (data->splitpoint_x - x >= 0 && data->splitpoint_y != 0 &&
										data->splitpoint_y != data->map_y - 1)
	{
		if (data->map[data->splitpoint_y][data->splitpoint_x - x] ==
												ft_toupper(data->enemy))
		{
			if (data->my_start_y < data->middle_y)
				data->splitpoint_y--;
			else
				data->splitpoint_y++;
			x = -1;
			ret = 1;
		}
		x++;
	}
	return (ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   filler.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/03 16:41:33 by tide-jon       #+#    #+#                */
/*   Updated: 2019/07/12 22:55:53 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void	init_filler(t_filler *data)
{
	data->legal_moves = NULL;
	data->movenum = 1;
	data->gameover = 0;
	data->phase = 1;
	data->x_wall_touch = 0;
	data->y_wall_touch = 0;
}

void				save_splitpoint(t_filler *data, t_fillerlst *best, 
															int i, int j)
{
	data->splitpoint_x = best->x + i;
	data->splitpoint_y = best->y + j;
}

void				get_splitpoint(t_filler *data, t_fillerlst *move)
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

/*
**	retrieve the best evaluated move
*/

static t_fillerlst	*get_bestmove(t_fillerlst *lst, t_filler *data)
{
	t_fillerlst	*current;
	t_fillerlst	*best;

	current = lst;
	best = lst;
	while (current->next != NULL)
	{
		current = current->next;
		if (current->weight < best->weight)
			best = current;
	}
	if (data->phase == 1 && best->weight < ft_pythagoras(data->map_y,
					data->map_x) / 10 + (data->map_y * data->map_x) / 200)
		{
			data->phase = 2;
			get_splitpoint(data, best);
		}
	if (best->x_touch == 1)
		data->x_wall_touch = 1;
	if (best->y_touch == 1)
		data->y_wall_touch = 1;
	return (best);
}

/*
**	send a move to stdout
*/

static void	send_move(t_fillerlst *lst, t_filler *data)
{
	t_fillerlst *bestmove;

	if (lst != NULL)
	{
		bestmove = get_bestmove(lst, data);
		write(1, ft_itoa(bestmove->y), ft_digcount(bestmove->y));
		write(1, " ", 1);
		write(1, ft_itoa(bestmove->x), ft_digcount(bestmove->x));
		write(1, "\n", 1);
	}
	else
		write(1, "0 0\n", 4);
}

void		get_startpos(t_filler *data)
{
	int	i;
	int	j;

	j = 0;
	while (j < data->map_y)
	{
		i = 0;
		while (i < data->map_x)
		{
			if (data->map[j][i] == ft_toupper(data->player))
			{
				data->my_start_y = j;
				data->my_start_x = i;
			}
			if (data->map[j][i] == ft_toupper(data->enemy))
			{
				data->enemy_start_y = j;
				data->enemy_start_x = i;
			}
			i++;
		}
		j++;
	}
}

int				check_enemy_down(t_filler *data)
{
	int y;
	int ret;

	ret = 0;
	y = 0;
	while (data->splitpoint_y + y < data->map_y && data->splitpoint_x != 0 &&
										data->splitpoint_x != data->map_x - 1)
	{
		if (data->map[data->splitpoint_y + y][data->splitpoint_x] == ft_toupper(data->enemy))
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
		if (data->map[data->splitpoint_y - y][data->splitpoint_x] == ft_toupper(data->enemy))
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
		if (data->map[data->splitpoint_y][data->splitpoint_x + x] == ft_toupper(data->enemy))
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
		if (data->map[data->splitpoint_y][data->splitpoint_x - x] == ft_toupper(data->enemy))
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

int			main(void)
{
	char			*str;
	t_filler		*data;

	str = NULL;
	data = (t_filler*)malloc(sizeof(t_filler));
	init_filler(data);
	while (data->gameover == 0)
	{
		parse_filler(str, data);
		if (data->gameover == 1)
			break ;
		if (data->movenum == 1)
			get_startpos(data);
		get_piece_filler(str, data);
		data->swap = 0;
		if (data->phase == 2)
		{
			if (check_enemy_x(data) == 1 || check_enemy_y(data) == 1)
				data->swap = 1;
		}
		find_moves(data);
		send_move(data->legal_moves, data);
		data->movenum++;
	}
	return (0);
}

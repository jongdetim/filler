/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   filler.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/03 16:41:33 by tide-jon       #+#    #+#                */
/*   Updated: 2019/07/09 14:45:46 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void	init_filler(t_filler *data)
{
	data->legal_moves = NULL;
	data->movenum = 1;
	data->gameover = 0;
	data->phase = 1;
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
	if (data->phase == 1 && best->weight < ft_pythagoras(data->map_y / 10,
					data->map_x / 10) + (data->map_y * data->map_x) / 1)
		{
			data->phase = 2;
			get_splitpoint(data, best);
		}
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
		find_moves(data);
		send_move(data->legal_moves, data);
		data->movenum++;
	}
	return (0);
}

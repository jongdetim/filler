/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   filler.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/03 16:41:33 by tide-jon       #+#    #+#                */
/*   Updated: 2019/07/14 21:10:33 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void			init_filler(t_filler *data)
{
	data->legal_moves = NULL;
	data->movenum = 1;
	data->gameover = 0;
	data->phase = 1;
	data->x_wall_touch = 0;
	data->y_wall_touch = 0;
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
	if (data->phase == 1 && best->weight < (ft_pythagoras(data->map_y,
											data->map_x) * 8) / SPLIT_DELAY)
	{
		data->phase = 2;
		get_splitpoint(data, best);
	}
	if (best->x_touch == 1)
		data->x_wall_touch = 1;
	if (best->y_touch == 1)
		data->y_wall_touch = 1;
	if (data->x_wall_touch == 1 && data->y_wall_touch == 1)
		data->phase = 3;
	return (best);
}

/*
**	send a move to stdout
*/

static void			send_move(t_fillerlst *lst, t_filler *data)
{
	t_fillerlst *bestmove;
	char		*str;

	if (lst != NULL)
	{
		bestmove = get_bestmove(lst, data);
		str = ft_itoa(bestmove->y);
		write(1, str, ft_digcount(bestmove->y));
		write(1, " ", 1);
		free(str);
		str = ft_itoa(bestmove->x);
		write(1, str, ft_digcount(bestmove->x));
		write(1, "\n", 1);
		free(str);
	}
	else
		write(1, "0 0\n", 4);
	ft_chararrfree(&(data->piece));
}

int					main(void)
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

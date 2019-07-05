/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   filler.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/03 16:41:33 by tide-jon       #+#    #+#                */
/*   Updated: 2019/07/05 15:41:40 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void	init_filler(t_filler *data)
{
	data->legal_moves = NULL;
	data->movenum = 1;
	data->gameover = 0;
}

/*
**	retrieve the best evaluated move
*/

static t_fillerlst	*get_bestmove(t_fillerlst *lst)
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
	return (best);
}

/*
**	send a move to stdout
*/

static void	send_move(t_fillerlst *lst)
{
	t_fillerlst *bestmove;

	if (lst != NULL)
	{
		bestmove = get_bestmove(lst);
		write(1, ft_itoa(bestmove->y), ft_digcount(bestmove->y));
		write(1, " ", 1);
		write(1, ft_itoa(bestmove->x), ft_digcount(bestmove->x));
		write(1, "\n", 1);
	}
	else
		write(1, "0 0\n", 4);
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
		get_piece_filler(str, data);
		find_moves(data);
		send_move(data->legal_moves);
		data->movenum++;
	}
	return (0);
}

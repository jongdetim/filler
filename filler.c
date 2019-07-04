/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   filler.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/03 16:41:33 by tide-jon       #+#    #+#                */
/*   Updated: 2019/07/04 19:23:06 by tide-jon      ########   odam.nl         */
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
**	send a move to stdout
*/

static void	send_move(t_filler *data)
{
	t_fillerlst *current;

	if (data->legal_moves != NULL)
	{
		current = data->legal_moves;
		while (current->next != NULL)
			current = current->next;
		write(1, ft_itoa(current->y), ft_digcount(current->y));
		write(1, " ", 1);
		write(1, ft_itoa(current->x), ft_digcount(current->x));
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
		send_move(data);
		data->movenum++;
	}
	return (0);
}

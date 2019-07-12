/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   getmoves.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/04 17:41:05 by tide-jon       #+#    #+#                */
/*   Updated: 2019/07/12 22:55:16 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

static void	filler_lstdel(t_fillerlst **lst)
{
	t_fillerlst	*nextlink;
	t_fillerlst	*currentlink;

	if (lst)
	{
		currentlink = *lst;
		while (currentlink != NULL)
		{
			nextlink = currentlink->next;
			free(currentlink);
			currentlink = nextlink;
		}
		*lst = NULL;
	}
}

static void	add_move(t_filler *data, int x, int y)
{
	t_fillerlst	*current;

	current = data->legal_moves;
	if (current == NULL)
	{
		current = (t_fillerlst*)malloc(sizeof(t_fillerlst));
		current->next = NULL;
		data->legal_moves = current;
	}
	else
	{
		current = (t_fillerlst*)malloc(sizeof(t_fillerlst));
		current->next = data->legal_moves;
		data->legal_moves = current;
	}
	current->x = x;
	current->y = y;
	current->x_touch = 0;
	current->y_touch = 0;
	eval_move(data, current);
}

/*
**	checks if a given move is legal
*/

static int	check_legal(t_filler *data, int x, int y)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	j = 0;
	while (j < data->piece_y)
	{
		i = 0;
		while (i < data->piece_x)
		{
			if (data->piece[j][i] == '*' && POS != '.')
			{
				if (POS == data->player || POS == ft_toupper(data->player))
					count++;
				else
					return (0);
			}
			i++;
		}
		j++;
	}
	if (count == 1)
		return (1);
	return (0);
}

/*
**	find all legal moves
*/

void	find_moves(t_filler *data)
{
	int	y;
	int	x;

	if (data->movenum != 1)
		filler_lstdel(&(data->legal_moves));
	y = 0;
	while (y <= data->map_y - data->piece_y)
	{
		x = 0;
		while (x <= data->map_x - data->piece_x)
		{
			if (check_legal(data, x, y) == 1)
				add_move(data, x, y);
			x++;
		}
		y++;
	}
}

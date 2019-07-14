/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_piece.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/14 16:37:15 by tide-jon       #+#    #+#                */
/*   Updated: 2019/07/14 16:37:21 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/*
**	get dimensions of inner piece
*/

void		get_piecesize(t_filler *data)
{
	int i;
	int j;
	int	count;

	j = 0;
	data->piecesize_y = 0;
	data->piecesize_x = 0;
	while (j < data->piece_y)
	{
		i = 0;
		count = 0;
		while (i < data->piece_x)
		{
			if (data->piece[j][i] == '*')
				count++;
			i++;
		}
		if (count > 0)
			data->piecesize_y++;
		if (count > data->piecesize_x)
			data->piecesize_x = count;
		j++;
	}
}

/*
**	get piece dimensions and save piece
*/

void		get_piece_filler(char *str, t_filler *data)
{
	int i;

	get_next_line(0, &str);
	data->piece_y = ft_getnum(str, 1);
	data->piece_x = ft_getnum(str, 2);
	free(str);
	data->piece = (char**)malloc(sizeof(char*) * data->piece_y + 1);
	data->piece[data->piece_y] = NULL;
	i = 0;
	while (i < data->piece_y)
	{
		get_next_line(0, &str);
		data->piece[i] = ft_strsub(str, 0, data->piece_x);
		free(str);
		i++;
	}
}

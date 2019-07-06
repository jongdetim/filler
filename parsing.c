/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/04 17:39:11 by tide-jon       #+#    #+#                */
/*   Updated: 2019/07/06 20:46:40 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

/*
**	read player number
*/

static void	player_num(t_filler *data, char *str)
{
	while (str != '\0')
	{
		if (*str == '1' || *str == '2')
		{
			if (*str == '1')
				data->player = 'o';
			else
				data->player = 'x';
			break ;
		}
		str++;
	}
	if (data->player == 'o')
		data->enemy = 'x';
	else
		data->enemy = 'x';
}

/*
**	finds the middle of the map
*/

static void	get_middle(t_filler *data)
{
	data->middle_y = data->map_y / 2;
	data->middle_x = data->map_x / 2;
}

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

	if (data->movenum != 1)
		ft_chararrfree(&(data->piece));
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
	get_piecesize(data);
}

static void	parse_fillerhelper(int i, char *str, t_filler *data)
{
	if (i == 0 && data->movenum == 1)
		player_num(data, str);
	else if (i == 1 && data->movenum == 1)
	{
		data->map_y = ft_getnum(str, 1);
		data->map_x = ft_getnum(str, 2);
		data->map = (char**)malloc(sizeof(char*) * data->map_y + 1);
		data->map[data->map_y] = NULL;
		get_middle(data);
	}
}

/*
**	check the player number, map size, and read & store the map
*/

void		parse_filler(char *str, t_filler *data)
{
	int	i;
	int	j;

	i = 0;
	j = 3;
	if (data->movenum != 1)
		j = 2;
	while (i < j)
	{
		if (get_next_line(0, &str) == 0)
		{
			data->gameover = 1;
			break ;
		}
		parse_fillerhelper(i, str, data);
		if (i > 2 && data->movenum == 1)
			data->map[i - 3] = ft_strsub(str, 4, data->map_x);
		else if (i > 1 && data->movenum != 1)
			ft_strncpy(data->map[i - 2], str + 4, data->map_x);
		if (i == 1)
			j += data->map_y;
		i++;
		free(str);
	}
}

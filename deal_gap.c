/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   deal_gap.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/14 17:50:15 by tide-jon       #+#    #+#                */
/*   Updated: 2019/07/14 21:10:52 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int			fill_gap(t_filler *data, t_fillerlst *move)
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
				if ((move->y + j == data->gap_y[0] &&
				move->x + i == data->gap_x[0]) ||
				(move->y + j == data->gap_y[1] &&
				move->x + i == data->gap_x[1]))
					return (1);
			}
			i++;
		}
		j++;
	}
	return (0);
}

static int	check_pattern(t_filler *data, int j, int i)
{
	if (j < data->map_y - 1 && i < data->map_x - 1 &&
	data->map[j][i + 1] != ft_toupper(data->player) &&
	data->map[j + 1][i + 1] == ft_toupper(data->player) &&
	data->map[j + 1][i] != ft_toupper(data->player))
	{
		data->gap_x[0] = i + 1;
		data->gap_x[1] = i;
		data->gap_y[0] = j;
		data->gap_y[1] = j + 1;
		return (1);
	}
	if (j < data->map_y - 1 && i > 0 &&
	data->map[j][i - 1] != ft_toupper(data->player) &&
	data->map[j + 1][i - 1] == ft_toupper(data->player) &&
	data->map[j + 1][i] != ft_toupper(data->player))
	{
		data->gap_x[0] = i - 1;
		data->gap_x[1] = i;
		data->gap_y[0] = j;
		data->gap_y[1] = j + 1;
		return (1);
	}
	return (0);
}

int			find_gap(t_filler *data)
{
	int i;
	int j;

	j = 0;
	while (j < data->map_y)
	{
		i = 0;
		while (i < data->map_x)
		{
			if (data->map[j][i] == ft_toupper(data->player))
			{
				if (check_pattern(data, j, i) == 1)
					return (1);
			}
			i++;
		}
		j++;
	}
	return (0);
}

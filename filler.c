/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   filler.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/03 16:41:33 by tide-jon       #+#    #+#                */
/*   Updated: 2019/07/04 01:27:15 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>

#include "ft_printf/ft_printf.h"

# define POS data->map[y + j][x + i]

typedef struct	s_fillerlst
{
	struct s_fillerlst	*next;
	int					x;
	int					y;
}				t_fillerlst;


typedef struct	s_filler
{
	int			map_x;
	int			map_y;
	int			piece_x;
	int			piece_y;
	char		player;
	char		**piece;
	char		**map;
	t_fillerlst	*legal_moves;
}				t_filler;


void	add_move(t_filler *data, int x, int y)
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
}

int		check_legal(t_filler *data, int x, int y)
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

void	find_moves(t_filler *data)
{
	int	y;
	int	x;

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

void	player_num(t_filler *data, char *str)
{
	while (str != '\0')
	{
		if (*str == '1' || *str == '2')
		{
			if (*str == '1')
				data->player = 'o';
			else
				data->player = 'x';
			break;
		}
		str++;
	}
}

void	init_filler(t_filler *data)
{
	data->legal_moves = NULL;
}

int		main(void)
{
	char	*str;
	int		fd;
	int		fd2;
	int		i;
	int		j;
	t_filler	*data;

	data = (t_filler*)malloc(sizeof(t_filler));
	init_filler(data);
	i = 0;
	j = 2;
	fd = open("./test.txt", O_RDWR);
	fd2 = open("./input.txt", O_RDONLY);

//	check the player number, map size, and read & store the map 

	while (i < j)
	{
		get_next_line(fd2, &str);
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		if (i == 0)
			player_num(data, str);
		else if (i == 1)
		{
			data->map_y = ft_getnum(str, 1);
			data->map_x = ft_getnum(str, 2);
			j += data->map_y + 1;
			data->map = (char**)malloc(sizeof(char*) * data->map_y + 1);
			data->map[data->map_y] = NULL;
		}
		if (i > 2)
			(data->map[i - 3] = ft_strsub(str, 4, data->map_x));
		i++;
		free(str);
	}

//	check the piece size

	get_next_line(fd2, &str);
	write(fd, str, ft_strlen(str));
	write(fd, "\n", 1);
	data->piece_y = ft_getnum(str, 1);
	data->piece_x = ft_getnum(str, 2);
	free(str);
	j = data->piece_y;

//	allocate memory for to save the shape as 2d array

	data->piece = (char**)malloc(sizeof(char*) * data->piece_y + 1);
	data->piece[data->piece_y] = NULL; 

//	read the piece

	i = 0;

	while (i < j)
	{
		get_next_line(fd2, &str);
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		data->piece[i] = ft_strdup(str);
		free(str);
		i++;
	}

//	find all legal moves

	find_moves(data);

//	check if coordinates of correct moves have been found by printing to stdout

	// t_fillerlst	*current;
	// current = data->legal_moves;
	// while (current != NULL)
	// {
	// 	ft_putnbr(current->x);
	// 	ft_putnbr(current->y);
	// 	current = current->next;
	// }

//	check if map is correctly read by printing map to fd

	// i = 0;
	// while (i < data->map_y)
	// {
	// 	write(fd, data->map[i], data->map_x);
	// 	write(fd, "\n", 1);
	// 	i++;
	// }
//	write(1, "12 14\n", 6);

	return (0);
}

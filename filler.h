/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   filler.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/04 17:31:37 by tide-jon       #+#    #+#                */
/*   Updated: 2019/07/04 17:44:01 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft/ft_printf.h"

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
	int			movenum;
	char		player;
	char		**piece;
	char		**map;
	t_fillerlst	*legal_moves;
	id_t		gameover;
}				t_filler;

void		find_moves(t_filler *data);
void		parse_filler(char *str, t_filler *data);
void		get_piece_filler(char *str, t_filler *data);

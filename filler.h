/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   filler.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/04 17:31:37 by tide-jon       #+#    #+#                */
/*   Updated: 2019/07/07 17:28:36 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include <fcntl.h>
# include <math.h>
# include "libft/ft_printf.h"

# define POS data->map[y + j][x + i]
# define DISTANCE_TO_MID ft_pythagoras((data->middle_x - (move->x + i)) * 10, \
										(data->middle_y - (move->y + j)) * 10)

typedef struct	s_fillerlst
{
	struct s_fillerlst	*next;
	int					x;
	int					y;
	int					weight;
}				t_fillerlst;

typedef struct	s_filler
{
	int					map_x;
	int					map_y;
	int					piece_x;
	int					piece_y;
	int					movenum;
	char				player;
	char				enemy;
	char				**piece;
	int					piecesize_x;
	int					piecesize_y;
	char				**map;
	int					middle_x;
	int					middle_y;
	t_fillerlst			*legal_moves;
	int					gameover;
	int					phase;
	int					my_start_x;
	int					my_start_y;
	int					enemy_start_x;
	int					enemy_start_y;
	int					splitpoint_x;
	int					splitpoint_y;
}				t_filler;

void			get_piecesize(t_filler *data);
void			eval_move(t_filler *data, t_fillerlst *move);
void			find_moves(t_filler *data);
void			parse_filler(char *str, t_filler *data);
void			get_piece_filler(char *str, t_filler *data);

#endif

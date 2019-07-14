/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   filler.h                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/07/04 17:31:37 by tide-jon       #+#    #+#                */
/*   Updated: 2019/07/14 21:09:44 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H

# include <fcntl.h>
# include <math.h>
# include "libft/ft_printf.h"

# define POS data->map[y + j][x + i]
# define DIST_MID_X (data->middle_x - (move->x + i))
# define DIST_MID_Y (data->middle_y - (move->y + j))
# define DISTANCE_TO_MID ft_pythagoras(DIST_MID_X * 10, DIST_MID_Y * 10) / 10
# define PATH_WEIGHT 10
# define WALL_DIST_WEIGHT 50
# define CURVE 5
# define SPLIT_DELAY 25

typedef struct	s_fillerlst
{
	struct s_fillerlst	*next;
	int					x;
	int					y;
	int					weight;
	int					x_touch;
	int					y_touch;
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
	int					swap;
	int					x_wall_touch;
	int					y_wall_touch;
	int					gap_found;
	int					gap_x[2];
	int					gap_y[2];
}				t_filler;

int				find_gap(t_filler *data);
int				fill_gap(t_filler *data, t_fillerlst *move);
void			get_piecesize(t_filler *data);
void			eval_move(t_filler *data, t_fillerlst *move);
void			find_moves(t_filler *data);
void			parse_filler(char *str, t_filler *data);
void			get_piece_filler(char *str, t_filler *data);
void			get_startpos(t_filler *data);
void			check_touch_x(t_filler *data, t_fillerlst *move);
void			check_touch_y(t_filler *data, t_fillerlst *move);
void			invade_enemy(t_filler *data, t_fillerlst *move);
void			check_touch_right(t_fillerlst *move, t_filler *data);
void			check_touch_left(t_fillerlst *move, t_filler *data);
void			check_touch_up(t_fillerlst *move, t_filler *data);
void			check_touch_down(t_fillerlst *move, t_filler *data);
int				check_enemy_down(t_filler *data);
int				check_enemy_up(t_filler *data);
int				check_enemy_left(t_filler *data);
int				check_enemy_right(t_filler *data);
void			to_walls(t_filler *data, t_fillerlst *move);
void			get_splitpoint(t_filler *data, t_fillerlst *move);
int				check_enemy_x(t_filler *data);
int				check_enemy_y(t_filler *data);

#endif

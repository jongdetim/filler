/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: tide-jon <tide-jon@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/06/13 20:07:36 by tide-jon       #+#    #+#                */
/*   Updated: 2019/07/03 21:01:30 by tide-jon      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>

typedef struct		s_printf
{
	va_list	args;
	va_list	backup;
	int		precision;
	int		width;
	char	*format;
	char	type;
	int		ret;
	short	zero;
	short	dot;
	short	space;
	short	hash;
	short	minus;
	short	plus;
	char	length;
	void	(*arr[11])(struct s_printf*);
}					t_printf;

char				*ft_strjoinfree(char *s1, char *s2);
void				process_int(t_printf *data);
void				parser(t_printf *data);
void				lowestll(t_printf *data);
void				flaghandler_o(t_printf *data, int len, short hash,
												unsigned long long d);
void				flaghandler_x(t_printf *data, int len, short hash,
												unsigned long long d);
void				dispatcher(t_printf *data);
void				build_dispatcher(t_printf *data);
void				init_data(t_printf *data);
void				set_argnum(t_printf *data, int d);
int					ft_printf(const char *restrict format, ...);
void				conv_c(t_printf *data);
void				conv_s(t_printf *data);
void				conv_p(t_printf *data);
void				conv_d(t_printf *data);
void				conv_u(t_printf *data);
void				conv_o(t_printf *data);
void				conv_x(t_printf *data);
void				conv_f(t_printf *data);
void				conv_prcnt(t_printf *data);
unsigned long long	typecast_u(t_printf *data, unsigned long long d);
char				*ft_strtoupper(char *str);
char				*ft_ftoa(long double f, int afterpoint);

#endif

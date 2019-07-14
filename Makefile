# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: tide-jon <tide-jon@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/07/04 17:20:36 by tide-jon       #+#    #+#                 #
#    Updated: 2019/07/14 18:31:41 by tide-jon      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME =		tide-jon.filler

SRCS = 		filler.c parsing.c getmoves.c eval_move.c eval_move2.c get_piece.c \
			phase2.c check_enemy.c check_touch.c deal_gap.c

OBJECTS =	$(SRCS:.c=.o)

all :		$(NAME)

$(NAME) :	$(OBJECTS)
			@ cd libft && make && cd ..
			@ gcc -Wall -Wextra -Werror $(OBJECTS) -L ./libft/ -lftprintf \
			-o $(NAME)
			@ echo "tide-jon.filler executable compiled"

%.o : %.c
			@ gcc -c -Wall -Wextra -Werror $< -o $@ -I ./libft/

clean :
			@ cd libft && make clean && cd .. && rm -f $(OBJECTS)

fclean :
			@ cd libft && make fclean && cd .. && rm -f $(NAME) && \
			rm -f $(OBJECTS)

re :		fclean all

# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: tide-jon <tide-jon@student.codam.nl>         +#+                      #
#                                                    +#+                       #
#    Created: 2019/07/04 17:20:36 by tide-jon       #+#    #+#                 #
#    Updated: 2019/07/05 15:40:18 by tide-jon      ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME =		tide-jon.filler

SRCS = 		filler.c parsing.c getmoves.c eval_move.c

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

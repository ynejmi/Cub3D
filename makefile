# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ynejmi <ynejmi@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/03/04 17:34:04 by ynejmi            #+#    #+#              #
#    Updated: 2021/03/04 17:34:05 by ynejmi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC = get_next_line.c main.c pp.c readmap.c render.c rescol.c sprite.c strmods1.c screenie.c strmods2.c treatmap.c txtdraw.c walls.c

BONUS = $(SRC)

NAME = lib.a

all:	$(NAME)

$(NAME) : $(SRC:.c=.o)
	gcc -Wall -Werror -Wextra -c $(SRC)
	ar -rc  lib.a $(SRC:.c=.o)
	ranlib lib.a
	gcc -g -Wall -Werror -Wextra -lmlx -framework OpenGL -framework AppKit lib.a  -o cub3D -O3
	

bonus:
	gcc -Wall -Werror -Wextra -c $(SRC) $(BONUS)
	ar -rc  lib.a $(SRC:.c=.o)
	ranlib lib.a

clean:
	rm -f $(SRC:.c=.o) $(BONUS:.c=.o) 

fclean:	clean
	rm -f cub3D
	rm -f $(NAME) screenshot.bmp

re:		fclean all
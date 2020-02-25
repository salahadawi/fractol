# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/19 16:18:52 by sadawi            #+#    #+#              #
#    Updated: 2020/02/25 15:48:57 by sadawi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=fractol
SRCS=srcs/*.c
OBJS=$(notdir $(SRCS:.c=.o))
INCLUDES= -I includes -I libft
FLAGS=-Wall -Wextra -Werror
MLX=-I /usr/local/include -L /usr/local/lib/ -lmlx -framework OpenGL \
-framework Appkit
RUN_LIB=make -C libft/ fclean && make -C libft/

all: $(NAME)

$(NAME):
	@$(RUN_LIB)
	@echo Compiling $(NAME)...
	@gcc $(FLAGS) $(INCLUDES) -c $(SRCS)
	@gcc $(FLAGS) $(INCLUDES) $(MLX) -o $(NAME) $(OBJS) libft/libft.a
	@echo $(NAME) compiled succesfully!

clean:
	@/bin/rm -f $(OBJS)
	@make -C libft/ clean
	@echo Clean successful!

fclean: clean
	@/bin/rm -f $(NAME)
	@make -C libft/ fclean
	@echo Fclean successful!

re: fclean all

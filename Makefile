# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sadawi <sadawi@student.hive.fi>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/19 16:18:52 by sadawi            #+#    #+#              #
#    Updated: 2020/03/05 13:02:15 by sadawi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=fractol
CFILES=check_input.c draw_fractal.c fractals.c handle_error.c handle_gui.c \
handle_idle.c handle_julia_mouse.c handle_keys.c handle_mouse.c initialize.c \
main.c  multithreading.c palettes.c scale.c
SRCS=$(addprefix srcs/, $(CFILES))
OBJS=$(addprefix objs/, $(notdir $(SRCS:.c=.o)))
INCLUDES= -I includes -I libft
FLAGS=-Wall -Wextra -Werror -O3
MLX=-I /usr/local/include -L /usr/local/lib/ -lmlx -framework OpenGL \
-framework Appkit
RUN_LIB=make -C libft/ fclean && make -C libft/

all: $(NAME)

$(NAME):
	@$(RUN_LIB)
	@rm -rf objs
	@echo Compiling $(NAME)...
	@gcc $(FLAGS) $(INCLUDES) -c $(SRCS)
	@mkdir objs
	@mv $(notdir $(SRCS:.c=.o)) objs
	@gcc $(FLAGS) $(INCLUDES) $(MLX) -o $(NAME) $(OBJS) libft/libft.a
	@echo $(NAME) compiled succesfully!

clean:
	@/bin/rm -f $(OBJS)
	@rm -rf objs
	@make -C libft/ clean
	@echo Clean successful!

fclean: clean
	@/bin/rm -f $(NAME)
	@make -C libft/ fclean
	@echo Fclean successful!

re: fclean all

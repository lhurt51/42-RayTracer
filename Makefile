# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lhurt <marvin@42.fr>                       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/10/19 11:15:26 by lhurt             #+#    #+#              #
#    Updated: 2016/10/19 11:15:27 by lhurt            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC =		gcc

FLAG =		-Wall -Wextra -Werror

LX =		-lmlx

MINLX =		./minilibx

INC =		-I $(MINLX)

LIB =		-L $(MINLX)

OPENGL =	-framework OpenGl

APPKIT =	-framework AppKit

MLX =		$(INC) $(LIB) $(LX) $(OPENGL) $(APPKIT)

LFPFT = 	libftprintf/

LIBPF =		$(LFPFT)libftprintf.a

LFLAG =		-L libftprintf/ -lft

NAME =		RTv1

SRCS =		main.c \
			mlx.c \
			hook.c \
			color.c \
			vector.c \
			vector1.c \
			parser.c \
			parser_helpers.c \
			parser_helpers1.c \
			parser_setup.c \
			parser_setup1.c \
			parser_store.c \
			parser_store1.c \
			parser_store2.c \
			matfunc.c \
			matfunc1.c \
			matrot.c \
			ray_trace.c \
			rt_lighting.c \
			rt_check_lights.c \
			rt_set_cur.c \
			rt_set_cur1.c \
			rt_find_closest.c \
			intersections.c \
			intersections1.c \

FDIR = 		frame/

OBJS =		$(addprefix $(FDIR), $(SRCS:.c=.o))

all: 		$(NAME)

frame:
			@mkdir $(FDIR)
			@echo "$(FDIR): has been created"

$(NAME): $(OBJS) $(LIBPF)
			@$(CC) $(FLAG) $(OBJS) $(LIBPF) $(MLX) -o $(NAME)
			@echo "$(NAME): has been created"

frame/%.o: %.c | frame
			@$(CC) $(FLAG) -c $< -o $@

$(LIBPF):
			@make re -C $(LFPFT)
			@echo "$(LFPFT): has been created"

clean:
			@rm -f $(OBJS)
			@rm -rf $(FDIR)
			@echo "$(FDIR) & $(OBJS): have been cleaned"

fclean:	clean
			@/bin/rm -f $(NAME)
			@make fclean -C $(LFPFT)
			@echo "$(NAME) & $(LFPFT): have been cleaned"

re: fclean all

.PHONY: all clean fclean re

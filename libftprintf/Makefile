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

CC =	gcc

FLAG =	-Wall -Wextra -Werror

LFT = 	libft/

LIB =	$(LFT)libft.a

LFSRC =	$(LFT)ft_putchar.c \
		$(LFT)ft_putstr.c \
		$(LFT)ft_isalpha.c \
		$(LFT)ft_isdigit.c \
		$(LFT)ft_isalnum.c \
		$(LFT)ft_isascii.c \
		$(LFT)ft_isprint.c \
		$(LFT)ft_toupper.c \
		$(LFT)ft_tolower.c \
		$(LFT)ft_atoi.c \
		$(LFT)ft_itoa.c \
		$(LFT)ft_strnew.c \
		$(LFT)ft_strdel.c \
		$(LFT)ft_strclr.c \
		$(LFT)ft_strdup.c \
		$(LFT)ft_strlen.c \
		$(LFT)ft_strcpy.c \
		$(LFT)ft_strncpy.c \
		$(LFT)ft_strcat.c \
		$(LFT)ft_strncat.c \
		$(LFT)ft_strlcat.c \
		$(LFT)ft_strchr.c \
		$(LFT)ft_strrchr.c \
		$(LFT)ft_strstr.c \
		$(LFT)ft_strnstr.c \
		$(LFT)ft_strcmp.c \
		$(LFT)ft_strncmp.c \
		$(LFT)ft_memset.c \
		$(LFT)ft_bzero.c \
		$(LFT)ft_memcpy.c \
		$(LFT)ft_memccpy.c \
		$(LFT)ft_memmove.c \
		$(LFT)ft_memchr.c \
		$(LFT)ft_memcmp.c \
		$(LFT)ft_memalloc.c \
		$(LFT)ft_memdel.c \
		$(LFT)ft_striter.c \
		$(LFT)ft_striteri.c \
		$(LFT)ft_strmap.c \
		$(LFT)ft_strmapi.c \
		$(LFT)ft_strequ.c \
		$(LFT)ft_strnequ.c \
		$(LFT)ft_strsub.c \
		$(LFT)ft_strjoin.c \
		$(LFT)ft_strtrim.c \
		$(LFT)ft_strsplit.c \
		$(LFT)ft_putendl.c \
		$(LFT)ft_putnbr.c \
		$(LFT)ft_putchar_fd.c \
		$(LFT)ft_putstr_fd.c \
		$(LFT)ft_putendl_fd.c \
		$(LFT)ft_putnbr_fd.c \
		$(LFT)ft_lstnew.c \
		$(LFT)ft_lstdelone.c \
		$(LFT)ft_lstdel.c \
		$(LFT)ft_lstadd.c \
		$(LFT)ft_lstiter.c \
		$(LFT)ft_lstmap.c \
		$(LFT)ft_isupper.c \
		$(LFT)ft_islower.c \
		$(LFT)get_next_line.c \

LFTOB = $(LFSRC:.c=.o)

L =		ar rc

RLIB =	ranlib

LFLAG =	-L libft/ -lft

NAME =	libftprintf.a

SRCS =	main.c \
		printf_d.c \
		printf_u.c \
		printf_o.c \
		printf_x.c \
		printf_lx.c \
		printf_s.c \
		printf_extra.c \
		modifiers.c \
		conversions.c \
		flags.c \
		len.c \
		checks.c \
		errors.c \
		errors1.c \
		itoa_base.c \
		l_lltoa_base.c \
		u_ujtoa_base.c \
		ul_ulltoa_base.c \
		usc_usitoa_base.c \
		sc_sitoa_base.c \
		z_jtoa_base.c \
		tools.c \
		wstr_helpers.c \

FDIR = frame/

OBJS =	$(addprefix $(FDIR), $(SRCS:.c=.o))

all: 	$(NAME)

frame:
		@mkdir $(FDIR)
		@echo "$(FDIR): has been created"

$(NAME): $(OBJS) $(LIB)
		@$(L) $(NAME) $(OBJS) $(LFTOB)
		@$(RLIB) $(NAME)
		@echo "$(NAME): has been created"

frame/%.o: %.c | frame
		@$(CC) $(FLAG) -c $< -o $@

$(LIB):
		@make re -C $(LFT)
		@echo "$(LFT): has been created"

clean:
		@rm -f $(OBJS)
		@rm -rf $(FDIR)
		@echo "$(FDIR) & $(OBJS): have been cleaned"

fclean:	clean
		@/bin/rm -f $(NAME)
		@make fclean -C $(LFT)
		@echo "$(NAME) & $(LFT): have been cleaned"

re: fclean all

.PHONY: all clean fclean re

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: magouin <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/05/27 13:24:03 by magouin           #+#    #+#              #
#    Updated: 2016/10/17 13:56:42 by magouin          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= wolf3d
CC		= gcc
WFLAGS	= -Wall -Wextra -Werror -g
OPTI	= -I

LS		= ls -1
GREP	= grep
MKDIR	= mkdir -p
RM		= rm -rf

LFLAGS 		= -Llib/ -lft -lmlx
DSRC		= src
DLIB		= libft
DLIBX		= minilibx
DINC		= inc
DINCLIB		= inc \
		  		  $(DLIB)/inc
DINCLIBX	= inc \
		  		  $(DLIBX)/inc
DOBJ	= obj

FSRC		:= $(shell $(LS) $(DSRC) | $(GREP) \.c$)
FOBJ		:= $(FSRC:.c=.o)
LIBFT		:= libft.a
MINILIBX	:= libmlx.a

FSRC		:= $(addprefix $(DSRC)/, $(FSRC))
FOBJ		:= $(addprefix $(DOBJ)/, $(FOBJ))
FINCLIB		:= $(addprefix $(OPTI) , $(DINCLIB))
FINCLIBX	:= $(addprefix $(OPTI) , $(DINCLIBX))
LIBFT		:= $(addprefix $(DLIB)/, $(LIBFT))
MINILIBX	:= $(addprefix $(DLIBX)/, $(MINILIBX))
INC 		= $(addprefix -I,$(DINC))

all: libft minilibx $(FOBJ) $(NAME)

$(NAME): $(MINILIBX) $(LIBFT) $(FOBJ)
		$(CC) $(WFLAGS) $(INC) $(FOBJ) $(LIBFT) $(MINILIBX) -o $@ -framework OpenGL -framework AppKit

$(DOBJ)/%.o: $(DSRC)/%.c $(DINC)
		@$(MKDIR) $(DOBJ)
			$(CC) $(WFLAGS) -c $< $(FINCLIB) $(FINCLIBX) -o $@

libft:
		make -C $(DLIB)
		make -C $(DLIBX)

clean:
		make -C $(DLIBX) clean
		make -C $(DLIB) clean
			$(RM) $(DOBJ)

fclean: clean
		make -C $(DLIB) fclean
			$(RM) $(NAME)

re: fclean all

.PHONY: all libft clean fclean re

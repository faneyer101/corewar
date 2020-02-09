# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: faneyer <faneyer@student.le-101.fr>        +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2019/07/27 18:49:19 by nsalle       #+#   ##    ##    #+#        #
#    Updated: 2020/02/09 22:44:51 by faneyer     ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NAME	= 	asm

CC 		= 	gcc
CFLAGS 	+= 	-Wextra -Werror -Wall -g -flto -O3 -march=native -flto -ffast-math 

SRC		=	srcs/op.c						\
		 	srcs/asm/startasm.c				\
			srcs/asm/parser/parsing.c		\
			srcs/asm/parser/toolsparsing.c	\
			srcs/asm/writefile.c			\
			srcs/asm/free.c					\
			srcs/asm/lexer/main_lexer.c		\
			srcs/asm/lexer/token.c			\
			srcs/asm/lexer/gestion_token.c	\
			srcs/asm/print/print_error.c	\
			srcs/asm/print/print_token.c	\

OBJ		=	$(SRC:.c=.o)	# gerer la compilation des .o autrement pour inclure plusieurs header
							# car je pense qu'il ne recompile pas avec op.h

INC		=	-I./$(LFTDIR) -I.

LFTDIR	=	libft_nsalle
LFT		=	-L $(LFTDIR) -lft

RM		=	/bin/rm

all: LFTC $(NAME)

LFTC:
	@$(MAKE) -C $(LFTDIR)

$(NAME): $(OBJ) includes/asm.h includes/op.h $(LFTDIR)/libft.a
	@$(CC) $(CFLAGS) $(INC) $(LFT) $(OBJ) -o $(NAME)
	@printf "\n|-> \033[32m$(NAME) compiled\033[0m\n\n"

clean:
	@$(MAKE) -C $(LFTDIR) $@
	@$(RM) -rf $(OBJ)
	@printf "|-> \033[31mobjects removed\033[0m\n"

fclean: clean
	@$(MAKE) -C $(LFTDIR) $@
	@$(RM) -f $(NAME)
	@printf "|-> \033[31m$(NAME) deleted\033[0m\n"

re: fclean all

.SILENT: $(OBJ)
.PHONY: all clean fclean re

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/28 10:02:52 by faneyer           #+#    #+#              #
#    Updated: 2020/06/03 15:41:06 by user42           ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME		=		libft.a

CC 			=		gcc
CFLAGS		+= 		-Wall -Wextra -Werror -g3

SRCDIR		=		./
SRCFILE		=		ft_abs.c				\
					ft_atoi.c				\
					ft_atol.c				\
					ft_atoll.c				\
					ft_bzero.c				\
					ft_lstcreate.c			\
					ft_delret.c				\
					ft_intlen.c				\
					ft_isalnum.c			\
					ft_isalpha.c			\
					ft_isascii.c			\
					ft_isblank.c			\
					ft_iscntrl.c			\
					ft_isdigit.c			\
					ft_isgraph.c			\
					ft_islower.c			\
					ft_isprint.c			\
					ft_ispunct.c			\
					ft_isspace.c			\
					ft_isupper.c			\
					ft_isxdigit.c			\
					ft_itoa.c				\
					ft_itoa_base.c			\
					ft_lstat.c				\
					ft_lstclear.c			\
					ft_lstfind.c			\
					ft_lstforeach.c			\
					ft_lstforeach_if.c		\
					ft_lstlast.c			\
					ft_lstmerge.c			\
					ft_lstpush_back.c		\
					ft_lstpush_front.c		\
					ft_lstpush_params.c		\
					ft_lstremove_if.c		\
					ft_lstrev.c				\
					ft_lstsize.c			\
					ft_lstsort.c			\
					ft_llonglen.c			\
					ft_longlen.c			\
					ft_lstadd.c				\
					ft_lstdel.c				\
					ft_lstdelone.c			\
					ft_lstiter.c			\
					ft_lstmap.c				\
					ft_lstnew.c				\
					ft_memalloc.c			\
					ft_memccpy.c			\
					ft_memchr.c				\
					ft_memcmp.c				\
					ft_memcpy.c				\
					ft_memdel.c				\
					ft_memmove.c			\
					ft_memset.c				\
					ft_minmax.c				\
					ft_print_bits.c			\
					ft_putchar.c			\
					ft_putchar_fd.c			\
					ft_putendl.c			\
					ft_putendl_fd.c			\
					ft_puterr.c				\
					ft_putnbr.c				\
					ft_putnbr_fd.c			\
					ft_putstr.c				\
					ft_putstr_fd.c			\
					ft_realloc.c			\
					ft_reverse_bits.c		\
					ft_strcasecmp.c			\
					ft_strcasestr.c			\
					ft_strcat.c				\
					ft_strchr.c				\
					ft_strclr.c				\
					ft_strcmp.c				\
					ft_strcpy.c				\
					ft_strcspn.c			\
					ft_strspn.c				\
					ft_strdel.c				\
					ft_strdup.c				\
					ft_strequ.c				\
					ft_striter.c			\
					ft_striteri.c			\
					ft_strjoin.c			\
					ft_strlcat.c			\
					ft_strlen.c				\
					ft_strmap.c				\
					ft_strmapi.c			\
					ft_strncasecmp.c		\
					ft_strncat.c			\
					ft_strncmp.c			\
					ft_strncpy.c			\
					ft_strndup.c			\
					ft_strnequ.c			\
					ft_strnew.c				\
					ft_strnstr.c			\
					ft_stroccur.c			\
					ft_strpostpend.c		\
					ft_strprepend.c			\
					ft_strrchr.c			\
					ft_strrev.c				\
					ft_strsplit.c			\
					ft_strstr.c				\
					ft_strsub.c				\
					ft_strtoupper.c			\
					ft_strtrim.c			\
					ft_swap.c				\
					ft_swap_bits.c			\
					ft_tolower.c			\
					ft_toupper.c			\
					ft_ullonglen.c			\
					ft_ulonglen.c			\
					ft_wordcount.c			\
					ft_pow.c				\
					Printf/ft_printf.c		\
					Printf/handle_f.c		\
					Printf/handle_numbers.c \
					Printf/handle_others.c  \
					Printf/handle_text.c    \
					Printf/parsing.c        \
					Printf/tools_f.c        \
					Printf/tools_numbers.c  \
					Printf/tools_parsing.c  \
					Printf/tools.c          \
					Printf/tools_f2.c

OBJDIR		=		./objs/
OBJ			=		$(addprefix $(OBJDIR),$(SRCFILE:.c=.o))

INCDIR		=		./
INC			=		$(addprefix -I,$(INCDIR))

RM			=		/bin/rm

BAR			=		\033[32;7m

$(OBJDIR)%.o: $(SRCDIR)%.c $(INCDIR)libft.h
	@mkdir -p $(OBJDIR)
	@mkdir -p $(OBJDIR)/Printf
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $< && echo "${BAR} \c"

all: $(NAME)

$(NAME): $(OBJ)
	@printf "\n|-> \033[32mobjects created\033[0m\n\n"
	@ar rus $@ $^
	@printf "\n|-> \033[32m$(NAME) complete\033[0m\n"

clean:
	@$(RM) -rf $(OBJDIR)
	@printf "|-> \033[31mfichier .o de libft deleted\033[0m\n"

fclean: clean
	@$(RM) -f $(NAME)
	@printf "|-> \033[31m$(NAME) deleted\033[0m\n"

re: fclean all

.PHONY: all clean fclean re
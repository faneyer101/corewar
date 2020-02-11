# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    Makefile                                         .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: faneyer <faneyer@student.le-101.fr>        +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2019/07/27 18:49:19 by nsalle       #+#   ##    ##    #+#        #
#    Updated: 2020/02/11 05:49:49 by faneyer     ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

NAME_ASM		= 	asm
NAME_VM			=	corewar

CC 				= 	gcc
CFLAGS 			+= 	-Wextra -Werror -Wall
CFLAGS_OPTI		+=	-flto -O3 -march=native -flto -ffast-math
CFLAGS_DEBUG	+=	-g -fsanitize=address

#	SOURCE ASM
include ./config_makefile/config_asm.mak
#	SOURCE VM
include ./config_makefile/config_vm.mak

#	DOSSIER OU SON STOCKER LES SOURCES				
SRCDIR			=	./srcs/

#	GESTION DES INCLUDES
INCDIR			=	./includes/
INCLUDE			=	$(addprefix -I,$(INCDIR))

#	GESTION OBJ ASM
OBJDIR_ASM		=	./objs_asm/
OBJ_ASM			=	$(addprefix $(OBJDIR_ASM),$(SRCFILE_ASM:.c=.o))

#	GESTION OBJ VM
OBJDIR_VM		=	./objs_vm/
OBJ_VM			=	$(addprefix $(OBJDIR_VM),$(SRCFILE_VM:.c=.o))

#	GESTION LIBFT
LFTDIR			=	./libft_nsalle/
INC_LFT			=	-I $(LFTDIR)
LFT				=	-L $(LFTDIR) -lft

RM				=	/bin/rm

#	CREATION DES DOSSIERS OBJS POUR ASM ET COMPILATION DES .o
$(OBJDIR_ASM)%.o: $(SRCDIR)%.c $(INCDIR)asm.h $(INCDIR)op.h $(LFTDIR)libft.a
	@mkdir -p $(OBJDIR_ASM)
	@mkdir -p $(OBJDIR_ASM)/asm
	@mkdir -p $(OBJDIR_ASM)/asm/lexer
	@mkdir -p $(OBJDIR_ASM)/asm/parser
	@mkdir -p $(OBJDIR_ASM)/asm/print
	@mkdir -p $(OBJDIR_ASM)/asm/interpreteur
	$(CC) $(CFLAGS) $(INCLUDE) $(INC_LFT) -o $@ -c $<

#	CREATION DES DOSSIERS OBJS POUR VM ET COMPILATION DES .o
$(OBJDIR_VM)%.o: $(SRCDIR)%.c $(INCDIR)vm.h $(INCDIR)op.h $(LFTDIR)libft.a
	@mkdir -p $(OBJDIR_VM)
	@mkdir -p $(OBJDIR_VM)/vm
	$(CC) $(CFLAGS) $(INCLUDE) $(INC_LFT) -o $@ -c $<

all: LFTC $(NAME_ASM) $(NAME_VM)

#	CREATION EXE ASM
$(NAME_ASM): $(OBJ_ASM)
	$(CC) $(CFLAGS) -o $@ $(OBJ_ASM) $(LFT)
	@printf "\n|-> \033[32m$(NAME_ASM) complete\033[0m\n"

#	CREATION EXE VM
$(NAME_VM): $(OBJ_VM)
	$(CC) $(CFLAGS) -o $@ $(OBJ_VM) $(LFT)
	@printf "\n|-> \033[32m$(NAME_VM) complete\033[0m\n"

######################################	REGLE POUR ASM
#	COMPILER JUSTE ASM
ASM: LFTC $(NAME_ASM)

#	COMPILATION AVEC FLAGS FSANITIZE
debug: LFTC $(OBJ_ASM) $(INCDIR)asm.h $(INCDIR)op.h $(LFTDIR)libft.a
	$(CC) $(CFLAGS) $(CFLAGS_DEBUG) -o asm $(OBJ_ASM) $(LFT)
	@printf "\n|-> \033[32m$(NAME_ASM) complete avec flags fsanitize\033[0m\n"

#	EXE EN NORMAL
exec: LFTC $(OBJ_ASM) $(NAME_ASM)
	./asm zork.s

#	EXE AVEC FLAG DE DEBUG
dexec: debug
	./asm zork.s
#######################################	FIN DE REGLE ASM

#	COMPILER JUSTE VM
VM: LFTC $(NAME_VM)

LFTC:
	@make -C $(LFTDIR) all

clean:
	@$(MAKE) -C $(LFTDIR) $@
	@$(RM) -rf $(OBJDIR_VM)
	@$(RM) -rf $(OBJDIR_ASM)
	@printf "|-> \033[31mfile .o de $(NAME_VM) and $(NAME_ASM) deleted\033[0m\n"

fclean: clean
	@$(MAKE) -C $(LFTDIR) $@
	@$(RM) -f $(NAME_ASM)
	@$(RM) -f $(NAME_VM)
	@printf "|-> \033[31m$(NAME_VM) and $(NAME_ASM) deleted\033[0m\n"

re: fclean all

.SILENT: $(OBJ)
.PHONY: all clean fclean re

/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   vm.h                                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nsalle <nsalle@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/10 12:13:30 by nsalle       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/22 17:41:42 by nsalle      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef	VM_H
# define VM_H
# include "op.h"
# include "../libft_nsalle/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct      	s_proclist
{
	struct s_proclist	*next;
	uint16_t			cycle;
	uint16_t			index;
	uint8_t				opcode;
	uint16_t			pc;
	uint8_t				carry;
	uint8_t				reg[REG_NUMBER];
}                   	t_proclist;

typedef struct      	s_player
{
	unsigned char		magic[4];
	unsigned char		*code;
	char				*pname;
	char				name[PROG_NAME_LENGTH];
	char				comment[COMMENT_LENGTH];
	int					fd;
	int					size;
	int					start;
}                   	t_player;

typedef struct      	s_vm
{
	int					dump;
	unsigned char		booldump;
	unsigned char		arena[MEM_SIZE];
	int					nb_player;
	t_proclist			*proclist;
	t_proclist			*beginlist;
	t_player			players[MAX_PLAYERS];
	uint64_t			cycles;
	uint32_t			cyc_todie;
	uint8_t				game;
}                   	t_vm;

void    	all_checks(int argc, char **av, t_vm *vm);
void		usage(void);
int			get_size(t_vm *vm, int ip);
void		check_realsize(t_vm *vm, int ip);
void		get_code(t_vm *vm, int ip);


/* lst_tools.c */
t_proclist	*create_proc(uint8_t op, uint16_t pc);
void		push_proc(uint8_t op, uint16_t pc, t_vm *vm);

/* loop.c */
void		load_first(t_vm *vm);
void		loop(t_vm *vm);

void	init_arena(t_vm *vm);

#endif
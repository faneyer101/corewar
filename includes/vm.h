/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalle <nsalle@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 12:13:30 by nsalle            #+#    #+#             */
/*   Updated: 2020/03/04 06:46:52 by nsalle           ###   ########lyon.fr   */
/*                                                                            */
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
	char				*ocp;
	uint8_t				tomove;
	uint8_t				curs;
	uint32_t			start;
	uint16_t			cycle;
	uint16_t			index;
	uint8_t				opcode;
	uint16_t			pc;
	uint8_t				carry;
	uint32_t			reg[REG_NUMBER];
	uint8_t				param[4];
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
	uint8_t				lastalive;
}                   	t_vm;

void    	all_checks(int argc, char **av, t_vm *vm);
void		usage(void);
int			get_size(t_vm *vm, int ip);
void		check_realsize(t_vm *vm, int ip);
void		get_code(t_vm *vm, int ip);

/* init_arena.c */
void	dump_arena(t_vm *vm);

/* lst_tools.c */
t_proclist	*create_proc(t_proclist *proc, uint16_t pc, uint8_t op);
void		push_proc(t_vm *vm, t_proclist *proc, uint16_t pc, uint8_t op);
uint16_t	get_cycle(uint8_t op);

/* loop.c */
void		load_first(t_vm *vm);
void		loop(t_vm *vm);

/* instruct1.c */
void		exec_proc(t_proclist *proc, t_vm *vm);
void		carryhandler(t_proclist *proc, uint32_t val);
int			get_paramval(t_vm *vm, t_proclist *proc, uint8_t code, int dsize);
uint8_t		get_param(uint8_t c1, uint8_t c2);
uint8_t		compute_params(t_proclist *proc, uint8_t nbp, uint8_t dsize);

/* digitools.c */
char		*binstring(uint8_t toparse);
uint32_t	maptoi(t_vm *vm, int i, uint8_t size);
void		write_onmap(t_vm *vm, int adress, uint32_t val);

void		init_arena(t_vm *vm);

/* Instructions */
void    	ld(t_proclist *proc, t_vm *vm);
void    	lld(t_proclist *proc, t_vm *vm);
void		sti(t_proclist *proc, t_vm *vm);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 12:13:30 by nsalle            #+#    #+#             */
/*   Updated: 2020/06/02 15:45:45 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_H
# define VM_H
# include "op.h"
# include "../libft_nsalle/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct			s_proclist
{
	struct s_proclist	*next;
	struct s_proclist	*activenext;
	char				*ocp;
	uint32_t			id;
	uint8_t				tomove;
	uint8_t				curs;
	uint32_t			start;
	uint16_t			cycle;
	uint16_t			index;
	uint8_t				opcode;
	uint16_t			pc;
	uint8_t				carry;
	uint8_t				alive;
	uint8_t				param[4];
	long long			last_alive;
	int					reg[REG_NUMBER];
}						t_proclist;

typedef struct			s_live
{
	short				todie;
	uint64_t			liv_since_last;
	short				cyc_since_last;
	uint8_t				lastalive;
	uint8_t				checks;
}						t_live;

typedef struct			s_player
{
	unsigned char		magic[4];
	unsigned char		*code;
	char				*pname;
	char				name[PROG_NAME_LENGTH];
	char				comment[COMMENT_LENGTH];
	int					fd;
	int					size;
	int					start;
}						t_player;

typedef struct			s_vm
{
	t_live				linf;
	int					dump;
	unsigned char		booldump;
	unsigned char		option_n;
	unsigned char		verbose;
	unsigned char		arena[MEM_SIZE];
	uint8_t				nb_player;
	uint8_t				lastalive;
	t_proclist			*proclist;
	t_proclist			*beginlist;
	t_proclist			*beginactive;
	uint32_t			pid_tracker;
	t_player			players[MAX_PLAYERS];
	long long			cycles;
	uint8_t				game;
}						t_vm;

void					exit_corewar(t_vm *vm);
void					all_checks(int argc, char **av, t_vm *vm);
void					usage(void);
int						get_size(t_vm *vm, int ip);
void					check_realsize(t_vm *vm, int ip);
void					get_code(t_vm *vm, int ip);

/*
** init_arena.c
*/

void					dump_arena(t_vm *vm);

/*
** lst_tools.c
*/

t_proclist				*create_proc(t_vm *vm, t_proclist *proc, uint16_t pc,
							uint8_t op);
void					push_proc(t_vm *vm, t_proclist *proc, uint16_t pc,
							uint8_t op);
uint16_t				get_cycle(uint8_t op);

/*
** loop.c
*/

void					load_first(t_vm *vm);
void					loop(t_vm *vm);

/*
** instructools.c
*/

void					exec_proc(t_proclist *proc, t_vm *vm);
void					carryhandler(t_vm *vm, t_proclist *proc, uint32_t val);
int						get_paramval(t_vm *vm, t_proclist *proc, uint8_t code,
							int dsize);
uint8_t					get_param(uint8_t c1, uint8_t c2);
uint8_t					compute_params(t_proclist *proc, uint8_t nbp,
							uint8_t dsize);
short					get_reach(int val);

/*
** digitools.c
*/
char					*binstring(uint8_t toparse);
uint32_t				maptoi(t_vm *vm, int i, uint8_t size);
void					write_onmap(t_vm *vm, int adress, uint32_t val);

/*
** deathcheck.c
*/

void					deathcheck(t_vm *vm);
void					init_arena(t_vm *vm);

/*
** active_tools.c
*/
void					get_opcode(t_vm *vm, t_proclist *proc);
void					push_active(t_proclist *proc, t_vm *vm);
void					negative_ctd(t_vm *vm);

/*
** verbose_tools.c
*/
void					death_verbose(t_vm *vm, t_proclist *proc);
void					print_map_part(t_vm *vm, t_proclist *proc);
void					cycle_verbose(t_vm *vm);
void					fork_verbose(t_vm *vm, t_proclist *proc,
							uint8_t lfork, short target);

/*
** Instructions
*/
void					ld(t_proclist *proc, t_vm *vm);
void					lld(t_proclist *proc, t_vm *vm);
void					st(t_proclist *proc, t_vm *vm);
void					sti(t_proclist *proc, t_vm *vm);
void					add(t_proclist *proc, t_vm *vm);
void					sub(t_proclist *proc, t_vm *vm);
void					ldi(t_proclist *proc, t_vm *vm);
void					lldi(t_proclist *proc, t_vm *vm);
void					xor(t_proclist *proc, t_vm *vm);
void					and(t_proclist *proc, t_vm *vm);
void					or(t_proclist *proc, t_vm *vm);
void					aff(t_proclist *proc, t_vm *vm);
void					zjmp(t_proclist *proc, t_vm *vm);

#endif

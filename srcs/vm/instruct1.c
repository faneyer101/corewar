/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruct1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 19:33:20 by nsalle            #+#    #+#             */
/*   Updated: 2020/05/24 00:53:15 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/vm.h"

void		fork_(t_proclist *proc, t_vm *vm, uint8_t lfork)
{
	short	target;

	target = maptoi(vm, get_reach(proc->pc + 1), 2);
	if (vm->verbose)
		fork_verbose(vm, proc, lfork, target);
	if (!lfork)
		target %= IDX_MOD;
	push_proc(vm, proc, get_reach(target + proc->pc),
		vm->arena[get_reach(target + proc->pc)]);
	print_map_part(vm, proc);
}

static void	live_verbose(t_vm *vm, t_proclist *proc, uint32_t player)
{
	if (vm->verbose == 2)
		ft_printf("{CYAN}");
	ft_printf("P%5d ", proc->id);
	if (vm->verbose == 2)
		ft_printf("{END}");
	ft_printf("| live %d\n", player);
	proc->tomove = 5;
}

void		live(t_proclist *proc, t_vm *vm)
{
	uint32_t	player;

	proc->alive = 1;
	proc->last_alive = vm->cycles;
	vm->linf.liv_since_last++;
	player = maptoi(vm, get_reach(proc->pc + 1), 4);
	if (vm->verbose)
		live_verbose(vm, proc, player);
	if (player * -1 <= vm->nb_player && player * -1 > 0)
	{
		if (vm->verbose)
			ft_printf("Player %d (%s) is said to be alive\n",
				player * -1, vm->players[(player * -1) - 1].name);
		vm->lastalive = player * -1;
	}
	proc->tomove = 5;
	print_map_part(vm, proc);
}

void		exec_more(t_proclist *proc, t_vm *vm)
{
	if (proc->opcode == 0x0b)
		sti(proc, vm);
	else if (proc->opcode == 0x0c)
		fork_(proc, vm, 0);
	else if (proc->opcode == 0x0d)
		lld(proc, vm);
	else if (proc->opcode == 0x0e)
		lldi(proc, vm);
	else if (proc->opcode == 0x0f)
		fork_(proc, vm, 1);
	else if (proc->opcode == 0x10)
		aff(proc, vm);
	else
		proc->pc = get_reach(proc->pc + 1);
}

void		exec_proc(t_proclist *proc, t_vm *vm)
{
    if (proc->opcode == 1)
	 	live(proc, vm);
	else if (proc->opcode == 2)
		ld(proc, vm);
	else if (proc->opcode == 3)
		st(proc, vm);
	else if (proc->opcode == 4)
		add(proc, vm);
	else if (proc->opcode == 5)
		sub(proc, vm);
	else if (proc->opcode == 6)
		and(proc, vm);
	else if (proc->opcode == 7)
		or(proc, vm);
	else if (proc->opcode == 8)
		xor(proc, vm);
	else if (proc->opcode == 9)
		zjmp(proc, vm);
	else if (proc->opcode == 0x0a)
		ldi(proc, vm);
	else
		exec_more(proc, vm);
	push_active(proc, vm);
}

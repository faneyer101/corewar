/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruct1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 19:33:20 by nsalle            #+#    #+#             */
/*   Updated: 2020/05/07 11:50:29 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/vm.h"

void	fork_(t_proclist *proc, t_vm *vm, uint8_t lfork)
{
	short	target;

	target = maptoi(vm, get_reach(proc->pc + 1), 2);
	if (!lfork)
		target %= IDX_MOD;
	ft_printf("{CYAN}P\t%d{END} Forking at adress %d\n", get_reach(proc->id + proc->pc), target);
	push_proc(vm, proc, get_reach(target + proc->pc), vm->arena[get_reach(target + proc->pc)]);
	proc->pc = get_reach(proc->pc + 3);
}

void	live(t_proclist *proc, t_vm *vm)
{
	uint32_t	player;

	proc->alive = 1;
	vm->linf.liv_since_last++;
	player = maptoi(vm, get_reach(proc->pc + 1), 4);
	ft_printf("{CYAN}P\t%d{END} I performed a live %.4x (%d live since last ctd, ctd = %d)\n", proc->id, player, vm->linf.liv_since_last, vm->linf.todie);
	ft_printf("My PC is %d and my carry is %d\n", proc->pc, proc->carry);
	if (player * -1 <= vm->nb_player)
	{
		ft_printf("Player %d said he is alive\n", player * -1);
		vm->lastalive = player * -1;
	}
	proc->pc = get_reach(proc->pc + 5);
}

void	exec_more(t_proclist *proc, t_vm *vm)
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

void	exec_proc(t_proclist *proc, t_vm *vm)
{
/* 	int	i = 0;
	if (proc->opcode > 0 && proc->opcode < 17)
	{
		while (i < 10)
			ft_printf("%.2x ", vm->arena[get_reach(proc->pc + i++)]);
		ft_putendl("");
	} */
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

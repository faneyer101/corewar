/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruct1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalle <nsalle@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 19:33:20 by nsalle            #+#    #+#             */
/*   Updated: 2020/03/06 22:29:24 by nsalle           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/vm.h"

void	fork_l(t_proclist *proc, t_vm *vm)
{
	short	target;

	target = maptoi(vm, proc->pc + 1, 2) + proc->pc;
	target %= IDX_MOD;
	ft_printf("Forking at adress %d\n", target);
	push_proc(vm, proc, target, vm->arena[target]);
	vm->beginlist->cycle--;
	proc->pc += 3;
}

void	live(t_proclist *proc, t_vm *vm)
{
	uint32_t	player;

	proc->alive = 1;
	player = maptoi(vm, proc->pc + 1, 4);
	ft_printf("I performed a live\n");
	if (player * -1 <= vm->nb_player)
	{
		ft_printf("Player %d said he is alive\n", player * -1);
		vm->lastalive = player * -1;
	}
	proc->pc += 5;
}

void	zjmp(t_proclist *proc, t_vm *vm)
{
	short		tojump;
	short		tmp;

	tojump = 0;
	tmp = 0;
	if (proc->carry)
	{
		tojump = maptoi(vm, proc->pc + 1, 2);
		ft_printf("adress before jump: %d\n", proc->pc);
		tojump %= IDX_MOD;
		tmp = proc->pc;
		if (proc->pc + tojump < 0)
			proc->pc += MEM_SIZE;
		proc->pc += tojump;
		ft_printf("adress after jump: %d\n", proc->pc);
		ft_printf("tojump = %d\n", tojump);
	}
	else
	{
		proc->pc += 3;
		ft_printf("Jump failed because carry 0\n");
	}
	ft_printf("zjmp: adress->%d so i jumped %d\n", proc->pc, proc->pc - tmp);
}

// void	exec_more(t_proclist *proc, t_vm *vm)
// {
	
// }

void	exec_proc(t_proclist *proc, t_vm *vm)
{
	int	i = 0;
	if (proc->opcode > 0 && proc->opcode < 17)
	{
		while (i < 10)
			ft_printf("%.2x ", vm->arena[proc->pc + i++]);
		ft_putendl("");
	}
    if (proc->opcode == 1)
	 	live(proc, vm);
	else if (proc->opcode == 2)
		ld(proc, vm);
	else if (proc->opcode == 4)
		add(proc, vm);
	else if (proc->opcode == 5)
		sub(proc, vm);
	else if (proc->opcode == 9)
		zjmp(proc, vm);
	else if (proc->opcode == 0x0a)
		ldi(proc, vm);
	else if (proc->opcode == 0x0b)
		sti(proc, vm);
	else if (proc->opcode == 0x0c)
		fork_l(proc, vm);
	else
		proc->pc++;
	proc->opcode = vm->arena[proc->pc];
	proc->cycle = get_cycle(proc->opcode);
	//ft_printf("\nMy new opcode is: %.2x\n", proc->opcode);
}

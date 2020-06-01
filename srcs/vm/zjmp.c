/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 11:50:04 by user42            #+#    #+#             */
/*   Updated: 2020/06/01 17:37:24 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

static void	verbose(t_vm *vm, t_proclist *proc, short tojump, uint8_t succes)
{
	proc->tomove = 3;
	if (vm->verbose == 2)
		ft_printf("{CYAN}");
	ft_printf("P%5d ", proc->id);
	if (vm->verbose == 2)
		ft_printf("{END}");
	if (succes)
	{
		ft_printf("| zjmp %d OK\n", tojump);
		if (vm->verbose == 2)
			ft_printf("{YELL}From %#.4x to %#.4x{END}\n", proc->pc,
				get_reach(proc->pc + tojump % IDX_MOD));
	}
	else
	{
		ft_printf("| zjmp %d FAILED\n", tojump);
		print_map_part(vm, proc);
	}
}

void		zjmp(t_proclist *proc, t_vm *vm)
{
	short		tojump;

	proc->tomove = 3;
	tojump = 0;
	tojump = maptoi(vm, get_reach(proc->pc + 1), 2);
	if (vm->verbose)
		verbose(vm, proc, tojump, proc->carry);
	if (proc->carry)
		proc->pc = get_reach(proc->pc + tojump % IDX_MOD);
	else
	{
		if (!vm->verbose)
			proc->pc = get_reach(proc->pc + 3);
	}
}

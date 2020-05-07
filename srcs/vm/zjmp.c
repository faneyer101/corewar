/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zjmp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/07 11:50:04 by user42            #+#    #+#             */
/*   Updated: 2020/05/07 23:16:39 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"


static void	verbose(t_vm *vm, t_proclist *proc, short tojump, uint8_t succes)
{
	if (vm->verbose == 2)
		ft_printf("{CYAN}");
	ft_printf("P%5d ", proc->id);
	if (vm->verbose == 2)
		ft_printf("{END}");
	if (succes)
		ft_printf("| zjmp %d OK\n", tojump);
	else
	{
		ft_printf("| zjmp %d FAILED\n", tojump);
		ft_printf("ADV 3 (%#.4x -> %#.4x) ", proc->pc,
			get_reach(proc->pc + 3));
		print_map_part(vm, proc);
	}
}

void		zjmp(t_proclist *proc, t_vm *vm)
{
	short		tojump;

	proc->tomove = 3;
	tojump = 0;
	tojump = maptoi(vm, get_reach(proc->pc + 1), 2);
	//tojump %= IDX_MOD;
	if (vm->verbose)
		verbose(vm, proc, tojump, proc->carry);
	if (proc->carry)
		proc->pc = get_reach(proc->pc + tojump);
	else
		proc->pc = get_reach(proc->pc + 3);
}
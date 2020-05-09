/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 12:39:19 by user42            #+#    #+#             */
/*   Updated: 2020/05/09 14:16:03 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void	fork_verbose(t_vm *vm, t_proclist *proc, uint8_t lfork, short target)
{
	if (vm->verbose == 2)
		ft_printf("{CYAN}");
	ft_printf("P%5d ", proc->id);
	if (vm->verbose == 2)
		ft_printf("{END}");
	if (lfork)
		ft_printf("| lfork %d (%d)\n", target, proc->pc + target);
	else
		ft_printf("| fork %d (%d)\n", target,
			get_reach(proc->pc + target % IDX_MOD));
	proc->tomove = 3;
	print_map_part(vm, proc);
}

void	cycle_verbose(t_vm *vm)
{
	if (vm->verbose == 2)
		ft_printf("{RED}");
	ft_printf("It is now cycle %d\n", vm->cycles + 1);
	if (vm->verbose == 2)
		ft_printf("{END}");
}

void	print_map_part(t_vm *vm, t_proclist *proc)
{
	int i;

	i = 0;
	if (vm->verbose)
	{
		ft_printf("ADV %d (0x%.4x -> 0x%.4x) ", proc->tomove, proc->pc,
			get_reach(proc->pc + proc->tomove));
		if (vm->verbose == 2)
			ft_printf("{INV}");
		while (i < proc->tomove)
		{
			ft_printf("%.2x ", vm->arena[get_reach(proc->pc + i)]);
			i++;
		}
		if (vm->verbose == 2)
			ft_printf("{END}");
		ft_putendl("");
	}
}

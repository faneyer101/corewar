/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 12:39:19 by user42            #+#    #+#             */
/*   Updated: 2020/06/05 14:15:06 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void	verbose_lldi(t_vm *vm, t_proclist *proc, int val[4], int ldi)
{
	int	target;

	if (vm->verbose)
	{
		if (val[2] > 0 && val[2] < 17 && val[3] != -1)
		{
			target = val[0] + val[1];
			if (ldi)
				target %= IDX_MOD;
			if (vm->verbose == 2)
				ft_printf("{CYAN}");
			ft_printf("P %4d ", proc->id);
			if (vm->verbose == 2)
				ft_printf("{END}");
			if (ldi)
				ft_printf("| ldi %d %d r%d\n", val[0], val[1], val[2]);
			else
				ft_printf("| lldi %d %d r%d\n", val[0], val[1], val[2]);
			ft_printf("%7c| -> load from %d + %d = %d (with pc %d)\n",
						' ', val[0], val[1], val[0] + val[1],
						proc->pc + target);
		}
	}
}

void	death_verbose(t_vm *vm, t_proclist *proc)
{
	if (vm->cycles - proc->last_alive > vm->linf.todie)
	{
		if (vm->verbose)
		{
			ft_printf("Process %d hasn't lived ", proc->id);
			ft_printf("for %d cycles ", vm->cycles - proc->last_alive - 1);
			ft_printf("(CTD %d)\n", vm->linf.todie);
		}
	}
}

void	fork_verbose(t_vm *vm, t_proclist *proc, uint8_t lfork, short target)
{
	if (vm->verbose)
	{
		if (vm->verbose == 2)
			ft_printf("{CYAN}");
		ft_printf("P %4d ", proc->id);
		if (vm->verbose == 2)
			ft_printf("{END}");
		if (lfork)
			ft_printf("| lfork %d (%d)\n", target, proc->pc + target);
		else
			ft_printf("| fork %d (%d)\n", target,
				proc->pc + target % IDX_MOD);
	}
	proc->tomove = 3;
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
			proc->pc + proc->tomove);
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
	proc->pc = get_reach(proc->pc + proc->tomove);
}

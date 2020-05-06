/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verbose_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 12:39:19 by user42            #+#    #+#             */
/*   Updated: 2020/05/06 12:59:59 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

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

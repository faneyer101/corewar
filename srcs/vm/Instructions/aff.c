/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 13:36:39 by nsalle            #+#    #+#             */
/*   Updated: 2020/06/02 14:30:37 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/vm.h"

static uint8_t	check_ocp(t_proclist *proc, t_vm *vm)
{
	uint8_t	i;
	uint8_t	j;

	proc->ocp = binstring(vm->arena[get_reach(proc->pc + 1)]);
	proc->tomove = 2;
	i = 0;
	j = 0;
	while (i < 4)
	{
		proc->param[i++] = get_param(proc->ocp[j], proc->ocp[j + 1]);
		j += 2;
	}
	proc->tomove += compute_params(proc, 1, 4);
	return (1);
}

void			aff(t_proclist *proc, t_vm *vm)
{
	uint8_t		reg;
	uint32_t	toaff;

	reg = maptoi(vm, get_reach(proc->pc + 1), 1);
	check_ocp(proc, vm);
	if (reg > 0 && reg < 17)
	{
		toaff = proc->reg[reg] % 256;
		if (vm->verbose == 2)
			ft_printf("{YELL}P%d\t AFF: %u\n{END}", proc->id, toaff);
	}
	print_map_part(vm, proc);
}

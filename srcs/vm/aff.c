/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalle <nsalle@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 13:36:39 by nsalle            #+#    #+#             */
/*   Updated: 2020/03/11 13:44:14 by nsalle           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void	aff(t_proclist *proc, t_vm *vm)
{
	uint8_t		reg;
	uint32_t	toaff;

	reg = maptoi(vm, get_reach(proc->pc + 1), 1);
	if (reg > 0 && reg < 17)
	{
		toaff = proc->reg[reg] % 256;
		ft_printf("{YELL}P%d\t AFF: %u\n{END}", proc->id, toaff);
	}
	proc->pc = get_reach(proc->pc + 2);
}

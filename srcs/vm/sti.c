/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalle <nsalle@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 02:23:03 by nsalle            #+#    #+#             */
/*   Updated: 2020/03/04 06:54:20 by nsalle           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

static uint8_t	check_ocp(t_proclist *proc, t_vm *vm)
{
	uint8_t	i;
	uint8_t	j;

	proc->ocp = binstring(vm->arena[proc->pc + 1]);
	proc->tomove = 2;
	i = 0;
	j = 0;
	while (i < 4)
	{
		proc->param[i++] = get_param(proc->ocp[j], proc->ocp[j + 1]);
		j += 2;
	}
	proc->tomove += compute_params(proc, 3, 2);
	if (proc->param[0] != REG_CODE)
		return (0);
	if (proc->param[2] == IND_CODE)
		return (0);
	return (1);
}

void	sti(t_proclist *proc, t_vm *vm)
{
	uint8_t	reg;
	short	toput;

	proc->curs = 3;
	reg = 0;
	toput = 0;
	if (check_ocp(proc, vm))
	{
		reg = vm->arena[proc->pc + 2];
		if (proc->param[1] == DIR_CODE)
			toput = get_paramval(vm, proc, DIR_CODE, 2);
		if (proc->param[1] == IND_CODE)
			toput = get_paramval(vm, proc, IND_CODE, 2);
		if (proc->param[1] == REG_CODE)
			toput = get_paramval(vm, proc, REG_CODE, 2);
		ft_printf("Reg value is %d, so reg[reg] = %x\n", reg, proc->reg[reg]);
		if (proc->param[2] == DIR_CODE)
			toput += get_paramval(vm, proc, DIR_CODE, 2);
		if (proc->param[2] == REG_CODE)
			toput += get_paramval(vm, proc, REG_CODE, 2);
		write_onmap(vm, proc->pc + toput % IDX_MOD, proc->reg[reg]);
	}
	ft_printf("I have to put the value %d (%x), to the adress %d", proc->reg[reg], proc->reg[reg], proc->pc + toput % IDX_MOD);
	proc->pc += proc->tomove;
}
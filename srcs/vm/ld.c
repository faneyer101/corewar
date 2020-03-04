/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalle <nsalle@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 20:17:42 by nsalle            #+#    #+#             */
/*   Updated: 2020/03/04 05:20:15 by nsalle           ###   ########lyon.fr   */
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
	proc->tomove += compute_params(proc, 2, 4);
	if (proc->param[0] != DIR_CODE && proc->param[0] != IND_CODE)
		return (0);
	if (proc->param[1] != REG_CODE)
		return (0);
	return (1);
}

void    		lld(t_proclist *proc, t_vm *vm)
{
	uint8_t toreach;
	uint8_t	reg;
	
	reg = 0;
	if (check_ocp(proc, vm))
	{
		if (proc->param[0] == DIR_CODE)
		{
			reg = vm->arena[proc->pc + 6];
			if (reg > 0 && reg < 17)
				proc->reg[reg] = maptoi(vm, proc->pc + 2, 4);
			ft_printf("Loading the value %d in my r%d\n", proc->reg[reg], reg);
		}
		else if (proc->param[0] == IND_CODE)
		{
			reg = vm->arena[proc->pc] + 4;
			if (reg > 0 && reg < 17)
				proc->reg[reg] = maptoi(vm, proc->pc + 2, 4);
			toreach = maptoi(vm, proc->pc + 2, 2);
			proc->reg[reg] = maptoi(vm, toreach, 4);
			ft_printf("Loading the value %d in my r%d\n", proc->reg[reg], reg);
		}
	}
	proc->pc += proc->tomove;
	carryhandler(proc, proc->reg[reg]);
}

void    		ld(t_proclist *proc, t_vm *vm)
{
	uint8_t toreach;
	uint8_t	reg;
	
	reg = 0;
	if (check_ocp(proc, vm))
	{
		if (proc->param[0] == DIR_CODE)
		{
			reg = vm->arena[proc->pc + 6];
			if (reg > 0 && reg < 17)
				proc->reg[reg] = maptoi(vm, proc->pc + 2, 4) % IDX_MOD;
			ft_printf("Loading the value %d in my r%d\n", proc->reg[reg], reg);
		}
		else if (proc->param[0] == IND_CODE)
		{
			reg = vm->arena[proc->pc] + 4;
			if (reg > 0 && reg < 17)
				proc->reg[reg] = maptoi(vm, proc->pc + 2, 4);
			toreach = maptoi(vm, proc->pc , 2) % IDX_MOD;
			proc->reg[reg] = maptoi(vm, toreach, 4);
			ft_printf("Loading the value %d in my r%d\n", proc->reg[reg], reg);
		}
	}
	proc->pc += proc->tomove;
	carryhandler(proc, proc->reg[reg]);
}
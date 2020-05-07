/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 20:17:42 by nsalle            #+#    #+#             */
/*   Updated: 2020/05/07 05:17:02 by user42           ###   ########lyon.fr   */
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

static void		verbose(t_vm *vm, t_proclist *proc, uint8_t val, int mode)
{
	if (vm->verbose == 2)
		ft_printf("{CYAN}");
	ft_printf("P\t%d ", proc->id);
	if (vm->verbose == 2)
		ft_printf("{END}");
	if (mode)
		ft_printf("| lld %d r%d\n", proc->reg[val], val);
	else
		ft_printf("| ld %d r%d\n", proc->reg[val], val);
	ft_printf("ADV %d (0x%.4x -> 0x%.4x) ", proc->tomove, proc->pc,
		get_reach(proc->pc + proc->tomove));
	print_map_part(vm, proc);
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
		}
		else if (proc->param[0] == IND_CODE)
		{
			reg = vm->arena[proc->pc] + 4;
			if (reg > 0 && reg < 17)
				proc->reg[reg] = maptoi(vm, get_reach(proc->pc + 2), 4);
			toreach = maptoi(vm, get_reach(proc->pc + 2), 2);
			proc->reg[reg] = maptoi(vm, toreach, 4);
		}
		if (vm->verbose)
			verbose(vm, proc, reg, 1);
		carryhandler(vm, proc, proc->reg[reg]);
	}
	proc->pc += proc->tomove;
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
			reg = vm->arena[get_reach(proc->pc + 6)];
			if (reg > 0 && reg < 17)
				proc->reg[reg] = maptoi(vm, get_reach(proc->pc + 2), 4);
		}
		else if (proc->param[0] == IND_CODE)
		{
			reg = vm->arena[get_reach(proc->pc + 4)];
			if (reg > 0 && reg < 17)
				proc->reg[reg] = maptoi(vm, get_reach(proc->pc + 2), 4);
			toreach = maptoi(vm, get_reach(proc->pc), 2) % IDX_MOD;
			proc->reg[reg] = maptoi(vm, get_reach(toreach), 4);
		}
		if (vm->verbose)
			verbose(vm, proc, reg, 0);
		carryhandler(vm, proc, proc->reg[reg]);
	}
	proc->pc = get_reach(proc->pc + proc->tomove);
}

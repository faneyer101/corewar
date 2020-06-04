/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ld.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 20:17:42 by nsalle            #+#    #+#             */
/*   Updated: 2020/06/04 19:46:14 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/vm.h"

static uint8_t	check_ocp(t_proclist *proc, t_vm *vm)
{
	uint8_t	i;
	uint8_t	j;

	binstring(proc, vm->arena[get_reach(proc->pc + 1)]);
	proc->tomove = 2;
	i = 0;
	j = 0;
	while (i < 4)
	{
		proc->param[i++] = get_param(proc->ocp[j], proc->ocp[j + 1]);
		j += 2;
	}
	proc->tomove += compute_params(proc, 2, 4);
	if (proc->param[0] == 0 || proc->param[1] == 0)
		return (0);
	if (proc->param[0] != DIR_CODE && proc->param[0] != IND_CODE)
		return (0);
	if (proc->param[1] != REG_CODE)
		return (0);
	return (1);
}

static void		verbose(t_vm *vm, t_proclist *proc, uint8_t val, int mode)
{
	if (vm->verbose)
	{
		if (val > 0 && val < 17)
		{
			if (vm->verbose == 2)
				ft_printf("{CYAN}");
			ft_printf("P %4d ", proc->id);
			if (vm->verbose == 2)
				ft_printf("{END}");
			if (mode)
				ft_printf("| lld %d r%d\n", proc->reg[val], val);
			else
				ft_printf("| ld %d r%d\n", proc->reg[val], val);
		}
	}
}

void			lld(t_proclist *proc, t_vm *vm)
{
	short	toreach;
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
			reg = vm->arena[proc->pc + 4];
			toreach = maptoi(vm, get_reach(proc->pc + 2), 2);
			if (reg > 0 && reg < 17)
				proc->reg[reg] =
				(short)maptoi(vm, get_reach(toreach + proc->pc), 2);
		}
		verbose(vm, proc, reg, 1);
		if (reg > 0 && reg < 17)
			carryhandler(vm, proc, proc->reg[reg]);
	}
	print_map_part(vm, proc);
}

void			ld(t_proclist *proc, t_vm *vm)
{
	short	toreach;
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
			toreach = maptoi(vm, get_reach(proc->pc + 2), 2);
			if (reg > 0 && reg < 17)
				proc->reg[reg] = maptoi(vm,
				get_reach(proc->pc + toreach % IDX_MOD), 4);
		}
		verbose(vm, proc, reg, 0);
		if (reg > 0 && reg < 17)
			carryhandler(vm, proc, proc->reg[reg]);
	}
	print_map_part(vm, proc);
}

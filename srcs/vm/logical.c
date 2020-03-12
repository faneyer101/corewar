/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   logical.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalle <nsalle@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 19:42:18 by nsalle            #+#    #+#             */
/*   Updated: 2020/03/11 16:21:09 by nsalle           ###   ########lyon.fr   */
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
	proc->tomove += compute_params(proc, 3, 4);
	if (proc->param[2] != REG_CODE)
		return (0);
	return (1);
}

uint8_t	regcheck(t_proclist *proc, t_vm *vm)
{
	uint8_t	p;
	uint8_t	i;

	i = 0;
	proc->curs = 2;
	while (i < 3)
	{
		if (proc->param[i] == REG_CODE)
			p = get_paramval(vm, proc, REG_CODE, 4);
		else if (proc->param[i] == DIR_CODE)
			p = get_paramval(vm, proc, DIR_CODE, 4);
		else
			p = get_paramval(vm, proc, IND_CODE, 4);
		if (proc->param[i] == REG_CODE && (p < 1 || p > 16))
		{
			ft_printf("{YELL} P%d\tWrong reg r%d i = %d{END}\n", proc->id, p, i);
			return (0);
		}
		i++;
	}
	return (1);
}

void	xor(t_proclist *proc, t_vm *vm)
{
	int	param1;
	int	param2;
	int	reg;

	proc->curs = 2;
	if (check_ocp(proc, vm))
	{
		if (proc->param[0] == REG_CODE)
			param1 = proc->reg[get_paramval(vm, proc, REG_CODE, 4)];
		else if (proc->param[0] == DIR_CODE)
			param1 = get_paramval(vm, proc, DIR_CODE, 4);
		else
			param1 = get_paramval(vm, proc, DIR_CODE, 4);
		if (proc->param[1] == REG_CODE)
			param2 = proc->reg[get_paramval(vm, proc, REG_CODE, 4)];
		else if (proc->param[1] == DIR_CODE)
			param2 = get_paramval(vm, proc, DIR_CODE, 4);
		else
			param2 = get_paramval(vm, proc, DIR_CODE, 4);
		reg = get_paramval(vm, proc, REG_CODE, 4);
		if (regcheck(proc, vm))
		{
			proc->reg[reg] = param1 ^ param2;
			ft_printf("{CYAN}P\t%d{END} AND r%d = %d ^ %d", proc->id, reg, param1, param2);
			carryhandler(proc, proc->reg[reg]);
		}
	}
	proc->pc = get_reach(proc->pc + proc->tomove);
}

void	or(t_proclist *proc, t_vm *vm)
{
	int	param1;
	int	param2;
	int	reg;

	proc->curs = 2;
	if (check_ocp(proc, vm))
	{
		if (proc->param[0] == REG_CODE)
			param1 = proc->reg[get_paramval(vm, proc, REG_CODE, 4)];
		else if (proc->param[0] == DIR_CODE)
			param1 = get_paramval(vm, proc, DIR_CODE, 4);
		else
			param1 = get_paramval(vm, proc, DIR_CODE, 4);
		if (proc->param[1] == REG_CODE)
			param2 = proc->reg[get_paramval(vm, proc, REG_CODE, 4)];
		else if (proc->param[1] == DIR_CODE)
			param2 = get_paramval(vm, proc, DIR_CODE, 4);
		else
			param2 = get_paramval(vm, proc, DIR_CODE, 4);
		reg = get_paramval(vm, proc, REG_CODE, 4);
		if (regcheck(proc, vm))
		{
			proc->reg[reg] = param1 | param2;
			ft_printf("{CYAN}P\t%d{END} AND r%d = %d | %d", proc->id, reg, param1, param2);
			carryhandler(proc, proc->reg[reg]);
		}
	}
	proc->pc = get_reach(proc->pc + proc->tomove);
}

void	and(t_proclist *proc, t_vm *vm)
{
	int	param1;
	int	param2;
	int	reg;

	proc->curs = 2;
	if (check_ocp(proc, vm))
	{
		if (proc->param[0] == REG_CODE)
			param1 = proc->reg[get_paramval(vm, proc, REG_CODE, 4)];
		else if (proc->param[0] == DIR_CODE)
			param1 = get_paramval(vm, proc, DIR_CODE, 4);
		else
			param1 = get_paramval(vm, proc, IND_CODE, 4);
		if (proc->param[1] == REG_CODE)
			param2 = proc->reg[get_paramval(vm, proc, REG_CODE, 4)];
		else if (proc->param[1] == DIR_CODE)
			param2 = get_paramval(vm, proc, DIR_CODE, 4);
		else
			param2 = get_paramval(vm, proc, IND_CODE, 4);
		reg = get_paramval(vm, proc, REG_CODE, 4);
		if (regcheck(proc, vm))
		{
			proc->reg[reg] = param1 & param2;
			ft_printf("{CYAN}P\t%d{END} AND r%d = %d & %d", proc->id, reg, param1, param2);
			carryhandler(proc, proc->reg[reg]);
		}
	}
	proc->pc = get_reach(proc->pc + proc->tomove);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 15:38:02 by nsalle            #+#    #+#             */
/*   Updated: 2020/06/04 16:45:29 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/vm.h"

static void		regcheck(t_vm *vm, t_proclist *proc, int var[4])
{
	int	reg;

	reg = get_paramval(vm, proc, REG_CODE, 2);
	var[1] = proc->reg[reg];
	if (reg > 0 && reg < 17)
		var[3] = 1;
	else
		var[3] = -1;
}

static uint8_t	check_ocp(t_proclist *proc, t_vm *vm)
{
	uint8_t i;
	uint8_t j;

	binstring(proc, vm->arena[get_reach(proc->pc + 1)]);
	proc->tomove = 2;
	i = 0;
	j = 0;
	while (i < 4)
	{
		proc->param[i++] = get_param(proc->ocp[j], proc->ocp[j + 1]);
		j += 2;
	}
	proc->tomove += compute_params(proc, 3, 2);
	if (proc->param[0] == 0 || proc->param[1] == 0 || proc->param[2] == 0)
		return (0);
	else if (proc->param[1] == IND_CODE || proc->param[2] != REG_CODE)
		return (0);
	return (1);
}

static void		verbose(t_vm *vm, t_proclist *proc, int val[4], int ldi)
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
			ft_printf("%7c| -> load from %d + %d = %d (with pc and mod %d)\n",
						' ', val[0], val[1], val[0] + val[1],
						get_reach(proc->pc + target));
		}
	}
}

void			lldi(t_proclist *proc, t_vm *vm)
{
	int		var[4];
	short	sum;

	proc->curs = 2;
	var[3] = 0;
	if (check_ocp(proc, vm))
	{
		if (proc->param[0] == REG_CODE)
			var[0] = proc->reg[get_paramval(vm, proc, REG_CODE, 2)];
		else if (proc->param[0] == DIR_CODE)
			var[0] = (short)get_paramval(vm, proc, DIR_CODE, 2);
		else if (proc->param[0] == IND_CODE)
			var[0] = (short)get_paramval(vm, proc, IND_CODE, 2);
		if (proc->param[1] == REG_CODE)
			regcheck(vm, proc, var);
		else if (proc->param[1] == DIR_CODE)
			var[1] = (short)get_paramval(vm, proc, DIR_CODE, 2);
		sum = var[0] + var[1];
		var[2] = get_paramval(vm, proc, REG_CODE, 2);
		if (var[2] > 0 && var[2] < 17 && var[3] != -1)
			proc->reg[var[2]] = maptoi(vm, get_reach(sum + proc->pc), 4);
		verbose(vm, proc, var, 0);
	}
	print_map_part(vm, proc);
}

void			ldi(t_proclist *proc, t_vm *vm)
{
	int		var[4];
	short	sum;

	proc->curs = 2;
	var[3] = 0;
	if (check_ocp(proc, vm))
	{
		if (proc->param[0] == REG_CODE)
			var[0] = proc->reg[get_paramval(vm, proc, REG_CODE, 2)];
		else if (proc->param[0] == DIR_CODE)
			var[0] = (short)get_paramval(vm, proc, DIR_CODE, 2);
		else if (proc->param[0] == IND_CODE)
			var[0] = (short)get_paramval(vm, proc, IND_CODE, 2);
		if (proc->param[1] == REG_CODE)
			regcheck(vm, proc, var);
		else if (proc->param[1] == DIR_CODE)
			var[1] = (short)get_paramval(vm, proc, DIR_CODE, 2);
		sum = (var[0] + var[1]) % IDX_MOD;
		var[2] = get_paramval(vm, proc, REG_CODE, 2);
		if (var[2] > 0 && var[2] < 17 && var[3] != -1)
			proc->reg[var[2]] = maptoi(vm, get_reach(sum + proc->pc), 4);
		verbose(vm, proc, var, 1);
	}
	print_map_part(vm, proc);
}

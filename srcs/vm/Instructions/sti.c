/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 02:23:03 by nsalle            #+#    #+#             */
/*   Updated: 2020/06/05 00:24:04 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/vm.h"

static int		index_sti(t_vm *vm, t_proclist *proc)
{
	short	toreach;

	toreach = maptoi(vm, get_reach(proc->pc + proc->curs), 2);
	toreach %= IDX_MOD;
	proc->curs += 2;
	return (maptoi(vm, get_reach(proc->pc + toreach), 4));
}

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
	proc->tomove += compute_params(proc, 3, 2);
	if (proc->param[0] == 0 || proc->param[1] == 0 || proc->param[2] == 0)
		return (0);
	if (proc->param[0] != REG_CODE)
		return (0);
	if (proc->param[2] == IND_CODE)
		return (0);
	return (1);
}

static int		regcheck(t_vm *vm, t_proclist *proc, int reg)
{
	int	reg2;

	reg2 = 0;
	if (reg < 1 || reg > REG_NUMBER)
		return (0);
	if (proc->param[1] == REG_CODE)
	{
		reg2 = vm->arena[get_reach(proc->pc + 3)];
		if (reg2 < 1 || reg2 > REG_NUMBER)
			return (0);
	}
	if (proc->param[2] == REG_CODE)
	{
		proc->curs -= 1;
		reg2 = get_paramval(vm, proc, REG_CODE, 2);
		if (reg2 < 1 || reg2 > REG_NUMBER)
			return (0);
	}
	return (1);
}

static void		verbose(int t[2], int reg, t_proclist *proc, t_vm *vm)
{
	if (regcheck(vm, proc, reg))
	{
		if (vm->verbose == 2)
			ft_printf("{CYAN}");
		ft_printf("P %4d | sti r%d %d %d\n", proc->id, reg, t[0], t[1]);
		if (vm->verbose == 2)
			ft_printf("{END}");
		ft_printf("%7c| -> store to %d + %d = %d ",
			' ', t[0], t[1], t[0] + t[1]);
		ft_printf("(with pc and mod %d)\n", proc->pc + (t[0] + t[1]) % IDX_MOD);
	}
}

void			sti(t_proclist *proc, t_vm *vm)
{
	int		reg;
	int		toput[2];

	proc->curs = 3;
	if (check_ocp(proc, vm))
	{
		reg = vm->arena[get_reach(proc->pc + 2)];
		if (proc->param[1] == DIR_CODE)
			toput[0] = (short)get_paramval(vm, proc, DIR_CODE, 2);
		else if (proc->param[1] == IND_CODE)
			toput[0] = index_sti(vm, proc);
		else if (proc->param[1] == REG_CODE)
			toput[0] = proc->reg[get_paramval(vm, proc, REG_CODE, 2)];
		if (proc->param[2] == DIR_CODE)
			toput[1] = (short)get_paramval(vm, proc, DIR_CODE, 2);
		else if (proc->param[2] == REG_CODE)
			toput[1] = proc->reg[get_paramval(vm, proc, REG_CODE, 2)];
		if (vm->verbose)
			verbose(toput, reg, proc, vm);
		if (regcheck(vm, proc, reg))
			write_onmap(vm, proc->pc + (toput[0] + toput[1]) %
				IDX_MOD, proc->reg[reg]);
	}
	print_map_part(vm, proc);
}

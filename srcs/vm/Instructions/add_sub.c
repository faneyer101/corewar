/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_sub.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 12:25:23 by nsalle            #+#    #+#             */
/*   Updated: 2020/06/04 16:12:40 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/vm.h"

static uint8_t	check_regvalue(t_proclist *proc, t_vm *vm)
{
	uint8_t	i;

	proc->curs = 2;
	i = 0;
	while (i < 3)
	{
		if (vm->arena[get_reach(proc->pc + proc->curs)] > 16 ||
			vm->arena[get_reach(proc->pc + proc->curs)] < 1)
			return (1);
		i++;
		proc->curs++;
	}
	return (0);
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
	proc->tomove += compute_params(proc, 3, 4);
	if (proc->param[0] != REG_CODE || proc->param[1] != REG_CODE ||
		proc->param[2] != REG_CODE)
		return (0);
	if (check_regvalue(proc, vm))
		return (0);
	return (1);
}

static void		verbose(t_vm *vm, t_proclist *proc, uint8_t val[3], int mode)
{
	if (vm->verbose == 2)
		ft_printf("{CYAN}");
	ft_printf("P%5d ", proc->id);
	if (vm->verbose == 2)
		ft_printf("{END}");
	if (mode)
		ft_printf("| sub r%d r%d r%d\n", val[0], val[1], val[2]);
	else
		ft_printf("| add r%d r%d r%d\n", val[0], val[1], val[2]);
}

void			add(t_proclist *proc, t_vm *vm)
{
	uint8_t	reg[3];

	if (check_ocp(proc, vm))
	{
		reg[0] = vm->arena[get_reach(proc->pc + 2)];
		reg[1] = vm->arena[get_reach(proc->pc + 3)];
		reg[2] = vm->arena[get_reach(proc->pc + 4)];
		proc->reg[reg[2]] = proc->reg[reg[0]] + proc->reg[reg[1]];
		if (vm->verbose)
			verbose(vm, proc, reg, 0);
		carryhandler(vm, proc, proc->reg[reg[2]]);
	}
	print_map_part(vm, proc);
}

void			sub(t_proclist *proc, t_vm *vm)
{
	uint8_t	reg[3];

	if (check_ocp(proc, vm))
	{
		reg[0] = vm->arena[get_reach(proc->pc + 2)];
		reg[1] = vm->arena[get_reach(proc->pc + 3)];
		reg[2] = vm->arena[get_reach(proc->pc + 4)];
		proc->reg[reg[2]] = proc->reg[reg[0]] - proc->reg[reg[1]];
		if (vm->verbose)
			verbose(vm, proc, reg, 1);
		carryhandler(vm, proc, proc->reg[reg[2]]);
	}
	print_map_part(vm, proc);
}

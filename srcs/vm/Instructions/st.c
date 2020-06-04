/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 20:56:23 by nsalle            #+#    #+#             */
/*   Updated: 2020/06/04 15:29:53 by user42           ###   ########lyon.fr   */
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
	proc->tomove += compute_params(proc, 2, 4);
	if (proc->param[0] == 0 || proc->param[1] == 0)
		return (0);
	if (proc->param[0] != REG_CODE)
		return (0);
	if (proc->param[1] == DIR_CODE)
		return (0);
	return (1);
}

static void		verbose(t_vm *vm, t_proclist *proc, uint8_t reg, short val)
{
	if (vm->verbose)
	{
		if (vm->verbose == 2)
			ft_printf("{CYAN}");
		ft_printf("P%5d ", proc->id);
		if (vm->verbose == 2)
			ft_printf("{END}");
		ft_printf("| st r%u %d\n", reg, val);
	}
}

void			st(t_proclist *proc, t_vm *vm)
{
	uint8_t	reg;
	short	param;

	if (check_ocp(proc, vm))
	{
		reg = vm->arena[get_reach(proc->pc + 2)];
		if (proc->param[1] == REG_CODE && reg > 0 && reg < 17)
		{
			param = vm->arena[get_reach(proc->pc + 3)];
			proc->reg[param] = proc->reg[reg];
			verbose(vm, proc, reg, param);
		}
		else if (reg > 0 && reg < 17)
		{
			param = maptoi(vm, get_reach(proc->pc + 3), 2);
			verbose(vm, proc, reg, param);
			param %= IDX_MOD;
			write_onmap(vm, proc->pc + param, proc->reg[reg]);
		}
	}
	print_map_part(vm, proc);
}

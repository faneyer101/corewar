/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   st.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalle <nsalle@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 20:56:23 by nsalle            #+#    #+#             */
/*   Updated: 2020/03/09 21:29:27 by nsalle           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

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
	if (proc->param[0] != REG_CODE)
		return (0);
	if (proc->param[1] == DIR_CODE)
		return (0);
	return (1);
}

void	st(t_proclist *proc, t_vm *vm)
{
	uint8_t	reg;
	int		param;

	if (check_ocp(proc, vm))
	{
		reg = vm->arena[get_reach(proc->pc + 2)];
		if (proc->param[1] == REG_CODE)
		{
			param = vm->arena[get_reach(proc->pc + 3)];
			proc->reg[param] = proc->reg[reg];
			ft_printf("{CYAN}P\t%d{END} Writing r%hhd in r%hhd\n", reg, param);
		}
		else
		{
			param = maptoi(vm, get_reach(proc->pc + 3), 2);
			param %= IDX_MOD;
			ft_printf("{CYAN}P\t%d{END} Writing %d at adress %d\n", proc->reg[reg], get_reach(proc->pc + param));
			write_onmap(vm, proc->pc + param, proc->reg[reg]);
		}
	}
	proc->pc = get_reach(proc->pc + proc->tomove);
}

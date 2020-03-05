/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_sub.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalle <nsalle@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 12:25:23 by nsalle            #+#    #+#             */
/*   Updated: 2020/03/05 18:05:33 by nsalle           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

static uint8_t check_regvalue(t_proclist *proc, t_vm *vm)
{
	uint8_t	i;

	proc->curs = 2;
	i = 0;
	while (i < 3)
	{
		if (vm->arena[proc->pc + proc->curs] > 16 ||
			vm->arena[proc->pc + proc->curs] < 1)
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
	if (proc->param[0] != REG_CODE || proc->param[1] != REG_CODE ||
		proc->param[2] != REG_CODE)
		return (0);
	if (check_regvalue(proc, vm))
		return (0);
	return (1);
}

void	add(t_proclist *proc, t_vm *vm)
{
	uint8_t	reg1;
	uint8_t	reg2;
	uint8_t	reg3;

	if (check_ocp(proc, vm))
	{
		reg1 = vm->arena[proc->pc + 2];
		reg2 = vm->arena[proc->pc + 3];
		reg3 = vm->arena[proc->pc + 4];
		proc->reg[reg3] = proc->reg[reg1] + proc->reg[reg2];
		ft_printf("Adding r%d (%d) to r%d (%d)\n", reg1, proc->reg[reg1], reg2, proc->reg[reg2]);
		ft_printf("Storing the value %d in my r%d\n", proc->reg[reg1] + proc->reg[reg2], reg3);
		carryhandler(proc, proc->reg[reg1] + proc->reg[reg2]);
	}
	proc->pc += proc->tomove;
}

void	sub(t_proclist *proc, t_vm *vm)
{
	uint8_t	reg1;
	uint8_t	reg2;
	uint8_t	reg3;

	if (check_ocp(proc, vm))
	{
		reg1 = vm->arena[proc->pc + 2];
		reg2 = vm->arena[proc->pc + 3];
		reg3 = vm->arena[proc->pc + 4];
		proc->reg[reg3] = proc->reg[reg2] - proc->reg[reg1];
		ft_printf("Substracting r%d (%d) to r%d (%d)\n", reg2, proc->reg[reg2], reg1, proc->reg[reg1]);
		ft_printf("Storing the value %d in my r%d\n", proc->reg[reg2] - proc->reg[reg1], reg3);
		carryhandler(proc, proc->reg[reg1] + proc->reg[reg2]);
	}
	proc->pc += proc->tomove;
}

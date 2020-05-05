/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ldi.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalle <nsalle@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 15:38:02 by nsalle            #+#    #+#             */
/*   Updated: 2020/03/11 18:19:39 by nsalle           ###   ########lyon.fr   */
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
	proc->tomove += compute_params(proc, 3, 2);
	if (proc->param[1] == REG_CODE || proc->param[2] != REG_CODE)
		return (0);
	return (1);
}

void	lldi(t_proclist *proc, t_vm *vm)
{
	short	toadd;
    short	toadd2;
	short	sum;
    int		reg;

    toadd = 0;
    toadd2 = 0;
    reg = 0;
    proc->curs = 2;
	sum = 0;
    if (check_ocp(proc, vm))
    {
        if (proc->param[0] == REG_CODE)
            toadd = proc->reg[get_paramval(vm, proc, REG_CODE, 2)];
        else if (proc->param[0] == DIR_CODE)
            toadd = get_paramval(vm, proc, DIR_CODE, 2);
        else if (proc->param[0] == IND_CODE)
            toadd = get_paramval(vm, proc, IND_CODE, 2);
        if (proc->param[0] == REG_CODE)
            toadd2 = proc->reg[get_paramval(vm, proc, REG_CODE, 2)];
        else if (proc->param[0] == DIR_CODE)
            toadd2 = get_paramval(vm, proc, DIR_CODE, 2);
		sum = toadd + toadd2;
		reg = get_paramval(vm, proc, REG_CODE, 2);
		if (reg > 0 && reg < 17)
		{
			proc->reg[reg] = maptoi(vm, get_reach(sum + proc->pc), 4);
			ft_printf("{CYAN}P\t%d{END} LLDI Loading the value from %d and %d to my r%d", proc->id, toadd, toadd2, reg);
			ft_printf(" (Source with pc: %d)\n", sum + proc->pc);
			carryhandler(proc, sum);
        }
    }
	proc->pc = get_reach(proc->pc + proc->tomove);
}

void    ldi(t_proclist *proc, t_vm *vm)
{
    short	toadd;
    short	toadd2;
	short	sum;
    int		reg;

    toadd = 0;
    toadd2 = 0;
    reg = 0;
    proc->curs = 2;
    if (check_ocp(proc, vm))
    {
        if (proc->param[0] == REG_CODE)
            toadd = proc->reg[get_paramval(vm, proc, REG_CODE, 2)];
        else if (proc->param[0] == DIR_CODE)
            toadd = get_paramval(vm, proc, DIR_CODE, 2);
        else if (proc->param[0] == IND_CODE)
            toadd = get_paramval(vm, proc, IND_CODE, 2);
        if (proc->param[0] == REG_CODE)
            toadd2 = proc->reg[get_paramval(vm, proc, REG_CODE, 2)];
        else if (proc->param[0] == DIR_CODE)
            toadd2 = get_paramval(vm, proc, DIR_CODE, 2);
		sum = toadd % IDX_MOD + toadd2 % IDX_MOD;
		reg = get_paramval(vm, proc, REG_CODE, 2);
		if (reg > 0 && reg < 17)
		{
			proc->reg[reg] = maptoi(vm, get_reach(sum + proc->pc), 4);
			ft_printf("{CYAN}P\t%d{END} LDI Loading the value from %d and %d to my r%d", proc->id, toadd, toadd2, reg);
			ft_printf(" (Source with pc: %d)\n", sum + proc->pc);
        }
    }
	//proc->pc += proc->tomove;
    proc->pc = get_reach(proc->pc + proc->tomove);
}
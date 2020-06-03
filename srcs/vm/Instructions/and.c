/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/06 13:42:31 by user42            #+#    #+#             */
/*   Updated: 2020/06/02 14:30:42 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/vm.h"

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

static void		verbose(t_vm *vm, t_proclist *proc, int par[3])
{
	if (vm->verbose == 2)
		ft_printf("{CYAN}");
	ft_printf("P%5d ", proc->id);
	if (vm->verbose == 2)
		ft_printf("{END}");
	ft_printf("| and %d %d r%d\n", par[0], par[1], par[2]);
}

static uint8_t	regcheck(t_proclist *proc, t_vm *vm, int par[3])
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
			return (0);
		i++;
	}
	proc->reg[par[2]] = par[0] & par[1];
	if (vm->verbose)
		verbose(vm, proc, par);
	carryhandler(vm, proc, proc->reg[par[2]]);
	return (1);
}

void			and(t_proclist *proc, t_vm *vm)
{
	int	par[3];

	proc->curs = 2;
	if (check_ocp(proc, vm))
	{
		if (proc->param[0] == REG_CODE)
			par[0] = proc->reg[get_paramval(vm, proc, REG_CODE, 4)];
		else if (proc->param[0] == DIR_CODE)
			par[0] = get_paramval(vm, proc, DIR_CODE, 4);
		else
			par[0] = get_paramval(vm, proc, IND_CODE, 4);
		if (proc->param[1] == REG_CODE)
			par[1] = proc->reg[get_paramval(vm, proc, REG_CODE, 4)];
		else if (proc->param[1] == DIR_CODE)
			par[1] = get_paramval(vm, proc, DIR_CODE, 4);
		else
			par[1] = get_paramval(vm, proc, IND_CODE, 4);
		par[2] = get_paramval(vm, proc, REG_CODE, 4);
		regcheck(proc, vm, par);
	}
	print_map_part(vm, proc);
}

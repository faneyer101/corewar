/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sti.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 02:23:03 by nsalle            #+#    #+#             */
/*   Updated: 2020/05/06 11:46:45 by user42           ###   ########lyon.fr   */
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
	proc->tomove += compute_params(proc, 3, 2);
	if (proc->param[0] != REG_CODE)
		return (0);
	if (proc->param[2] == IND_CODE)
		return (0);
	return (1);
}

static void	verbose(short t[2], short reg, t_proclist *proc, t_vm *vm)
{
	int	i;

	i = 0;
	ft_printf("{CYAN}P\t%d{END} | sti r%d %d %d\n", proc->id, reg, t[0], t[1]);
	ft_printf("\t  | -> Store to %d + %d = %d ", t[0], t[1], t[0] + t[1]);
	ft_printf("(with pc and mod %d)\n", proc->pc + (t[0] + t[1]) % IDX_MOD);
	ft_printf("ADV %d (0x%.4x -> 0x%.4x) ", proc->tomove, proc->pc,
		get_reach(proc->pc + proc->tomove));
	while (i < proc->tomove)
	{
		ft_printf("%.2x ", vm->arena[get_reach(proc->pc + i)]);
		i++;
	}
	ft_putendl("");
}

void		sti(t_proclist *proc, t_vm *vm)
{
	uint8_t	reg;
	short	toput[2];
	//short	toput;
	//short	toput2;

	proc->curs = 3;
	reg = 0;
	//toput = 0;
	if (check_ocp(proc, vm))
	{
		reg = vm->arena[get_reach(proc->pc + 2)];
		if (proc->param[1] == DIR_CODE)
			toput[0] = get_paramval(vm, proc, DIR_CODE, 2);
		else if (proc->param[1] == IND_CODE)
			toput[0] = get_paramval(vm, proc, IND_CODE, 2);
		else if (proc->param[1] == REG_CODE)
			toput[0] = proc->reg[get_paramval(vm, proc, REG_CODE, 2)];
		//ft_printf("Toput first adress = %d\n", toput);
		if (proc->param[2] == DIR_CODE)
		{
			toput[1] = get_paramval(vm, proc, DIR_CODE, 2);
			//ft_printf("2nd adress = %d DIRECT\n", toput2);
		}
		else if (proc->param[2] == REG_CODE)
		{
			toput[1] = proc->reg[get_paramval(vm, proc, REG_CODE, 2)];
			//ft_printf("2nd adress = %d REG\n", proc->reg[get_paramval(vm, proc, REG_CODE, 2)]);
		}
		write_onmap(vm, proc->pc + (toput[0] + toput[1]) % IDX_MOD, proc->reg[reg]);
	}
	if (vm->verbose)
		verbose(toput, reg, proc, vm);
	//ft_printf("STI: I have to put the value %d (%.8x), to the adress %d\n", proc->reg[reg], proc->reg[reg], proc->pc + toput % IDX_MOD);
	//carryhandler(proc, toput)
	//proc->pc += proc->tomove;
	proc->pc = get_reach(proc->pc + proc->tomove);
}
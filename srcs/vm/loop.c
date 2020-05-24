/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 15:44:59 by nsalle            #+#    #+#             */
/*   Updated: 2020/05/24 19:56:21 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/vm.h"

void	carryhandler(t_vm *vm, t_proclist *proc, uint32_t val)
{
	if (!val)
		proc->carry = 1;
	else
		proc->carry = 0;
	if (vm->verbose == 2)
		ft_printf("{RED}My carry is now: %d (P%d){END}\n",
			proc->carry, proc->id);
}

void	check_proc(t_proclist *lst, t_vm *vm)
{
	t_proclist	*curs;

	curs = lst;
	while (curs)
	{
		//ft_printf("passage cycle: %d\n", vm->cycles);
		if (curs->cycle == 0)
			get_opcode(vm, curs);
		if (curs->cycle > 0)
			curs->cycle--;
		if (curs->cycle == 0)
			exec_proc(curs, vm);
		curs = curs->next;
	}
}

int		get_nbproc(t_proclist *lst)
{
	t_proclist	*curs;
	int			count;

	curs = lst;
	count = 0;
	while (curs)
	{
		if (curs)
			count++;
		curs = curs->next;
	}
	//ft_printf("There are %d processes running\n", count);
	return (count);
}

void	load_first(t_vm *vm)
{
	int			i;
	t_proclist	*dummy;
	t_proclist	*curs;

	i = 0;
	if (!(dummy = (t_proclist*)malloc(sizeof(t_proclist))))
		exit(0);
	while (i < REG_NUMBER)
		dummy->reg[i++] = 0;
	dummy->carry = 0;
	i = 0;
	while (i < vm->nb_player)
	{
		dummy->reg[1] = (i + 1) * -1;
		push_proc(vm, dummy, vm->players[i].start, vm->players[i].code[0]);
		i++;
	}
	curs = vm->beginlist;
	while (curs)
	{
		curs->start = curs->pc;
		curs = curs->next;
	}
}

void	loop(t_vm *vm)
{
	while (vm->game)
	{
		if (vm->verbose)
			cycle_verbose(vm);
		check_proc(vm->beginlist, vm);
		if (vm->linf.todie <= 0)
			negative_ctd(vm);
		vm->cycles++;
		vm->linf.cyc_since_last++;
		if (vm->linf.cyc_since_last == vm->linf.todie)
			deathcheck(vm);
		if (vm->booldump)
		{
			//ft_printf("Passage\n");
			vm->dump--;
			if (!vm->dump)
			{
				dump_arena(vm);
				exit (0);
			}
		}
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalle <nsalle@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 15:44:59 by nsalle            #+#    #+#             */
/*   Updated: 2020/03/05 17:37:56 by nsalle           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/vm.h"

void	carryhandler(t_proclist *proc, uint32_t val)
{
	if (!val)
		proc->carry = 1;
	else
		proc->carry = 0;
	ft_printf("My carry is now: %d\n", proc->carry);
}

void	check_proc(t_proclist *lst, t_vm *vm)
{
	t_proclist	*curs;

	curs = lst;
	while (curs)
	{
		if (curs->cycle > 0)
		{
			curs->cycle--;
			if (curs->cycle == 0)
				exec_proc(curs, vm);
		}
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
		if (curs->cycle)
			count++;
		curs = curs->next;
	}
	ft_printf("There are %d processes running\n", count);
	return (count);
}

void	load_first(t_vm *vm)
{
	int			i;
	t_proclist *dummy;
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
		check_proc(vm->beginlist, vm);
		ft_printf("Cycle %d:\t", vm->cycles + 1);
		if (get_nbproc(vm->beginlist) == 0)
			vm->game = 0;
		vm->cycles++;
		vm->linf.cyc_since_last++;
		if (vm->booldump)
		{
			vm->dump--;
			if (!vm->dump)
			{
				dump_arena(vm);
				exit (0);
			}
		}
	}
	//check_winner();
}
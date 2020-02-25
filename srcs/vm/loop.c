/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalle <nsalle@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 15:44:59 by nsalle            #+#    #+#             */
/*   Updated: 2020/02/25 21:10:21 by nsalle           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/vm.h"

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
		dummy->reg[0] = i;
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
		ft_printf("Cycle %d:\t", vm->cycles);
		if (get_nbproc(vm->beginlist) == 0)
			vm->game = 0;
		vm->cycles++;
	}
	//check_winner();
}
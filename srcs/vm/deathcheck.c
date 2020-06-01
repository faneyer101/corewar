/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deathcheck.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 17:33:42 by nsalle            #+#    #+#             */
/*   Updated: 2020/06/01 16:53:13 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void		endofgame(t_vm *vm)
{
	if (vm->verbose == 2)
		ft_printf("{UND}{GREEN}");
	ft_printf("Contestant %d, ", vm->lastalive);
	ft_printf("\"%s\", has won !\n", vm->players[vm->lastalive - 1].name);
	if (vm->verbose == 2)
		ft_printf("{END}");
	exit(0);
}

void		reduce_ctc(t_vm *vm)
{
	if (vm->verbose == 2)
		ft_printf("{YELL}%d live since last check\n{END}",
			vm->linf.liv_since_last);
	if (vm->verbose == 2)
		ft_printf("{YELL}");
	if (vm->verbose)
		ft_printf("Cycle to die is now %d\n", vm->linf.todie - CYCLE_DELTA);
	if (vm->verbose == 2)
		ft_printf("{END}");
	vm->linf.todie -= CYCLE_DELTA;
	vm->linf.liv_since_last = 0;
}

t_proclist	*kill_this(t_vm *vm, t_proclist *curr, t_proclist *prev)
{
	if (vm->cycles - curr->last_alive > vm->linf.todie)
	{
		if (!prev)
			vm->beginlist = curr->next;
		else
			prev->next = curr->next;
		ft_strdel(&curr->ocp);
		free(curr);
		if (!prev)
			return (vm->beginlist);
		else
			return (prev);
	}
	return (0);
}

void		refresh_ctd(t_vm *vm)
{
	if (vm->linf.liv_since_last > NBR_LIVE)
		reduce_ctc(vm);
	else
		vm->linf.checks++;
	if (vm->linf.checks == MAX_CHECKS)
	{
		reduce_ctc(vm);
		vm->linf.checks = 0;
	}
	vm->linf.liv_since_last = 0;
	vm->linf.cyc_since_last = 0;
}

void		deathcheck(t_vm *vm)
{
	t_proclist	*curr;
	t_proclist	*prev;

	curr = vm->beginlist;
	prev = NULL;
	while (curr)
	{
		if (!curr->alive && vm->cycles - curr->last_alive > vm->linf.todie)
		{
			death_verbose(vm, curr);
			curr = kill_this(vm, curr, prev);
			if (prev == NULL)
				continue;
		}
		else
			curr->alive = 0;
		prev = curr;
		curr = curr->next;
	}
	refresh_ctd(vm);
	if (!vm->beginlist)
		endofgame(vm);
}

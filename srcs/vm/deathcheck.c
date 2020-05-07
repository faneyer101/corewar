/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deathcheck.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 17:33:42 by nsalle            #+#    #+#             */
/*   Updated: 2020/05/07 22:39:01 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void		endofgame(t_vm *vm)
{
	ft_printf("Contestant %d has won !\n", vm->lastalive);
	exit (0);
}

void		reduce_ctc(t_vm *vm)
{
	if (vm->verbose == 2)
		ft_printf("{YELL}%d live since last check\n{END}",
			vm->linf.liv_since_last);
	if (vm->verbose == 2)
		ft_printf("{YELL}");
	ft_printf("Cycle to die is now %d\n", vm->linf.todie - CYCLE_DELTA);
	if (vm->verbose == 2)
		ft_printf("{END}");
	vm->linf.todie -= CYCLE_DELTA;
	vm->linf.liv_since_last = 0;
}

t_proclist	*kill_this(t_vm *vm, t_proclist *curr, t_proclist *prev)
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
	return (0);
}

void		deathcheck(t_vm *vm)
{
	t_proclist	*curr;
	t_proclist	*prev;

	curr = vm->beginlist;
	prev = NULL;
	if (vm->linf.liv_since_last > NBR_LIVE)
		reduce_ctc(vm);
	while (curr)
	{
		if (!curr->alive)
		{
			ft_printf("\n\n\n\n\n\nOne process must die now (P\t%d)\n\n\n\n\n\n", curr->id);
			curr = kill_this(vm, curr, prev);
			if (prev == NULL)
				continue;
		}
		else
			curr->alive = 0;
		prev = curr;
		curr = curr->next;
	}
	vm->linf.liv_since_last = 0;
	vm->linf.cyc_since_last = 0;
	if (!vm->beginlist)
		endofgame(vm);
}

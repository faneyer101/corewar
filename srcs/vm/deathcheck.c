/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deathcheck.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalle <nsalle@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 17:33:42 by nsalle            #+#    #+#             */
/*   Updated: 2020/03/12 16:27:48 by nsalle           ###   ########lyon.fr   */
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
	ft_printf("%d live since last check, CTC is reduced to %d",
		vm->linf.liv_since_last, vm->linf.todie - CYCLE_DELTA);
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
	ft_printf("\n\n\n\nIt is now time to kill some processes (CTC = %hd)\n\n\n\n",
		vm->linf.todie);
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

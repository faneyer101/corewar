/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   active_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 13:02:21 by nsalle            #+#    #+#             */
/*   Updated: 2020/05/24 11:46:29 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void	negative_ctd(t_vm *vm)
{
	t_proclist	*proc;

	proc = vm->beginlist;
	while (proc)
	{
		proc->alive = 0;
		proc->last_alive--;
		proc = proc->next;
	}
	deathcheck(vm);
}

void	get_opcode(t_vm *vm, t_proclist *proc)
{
	proc->opcode = vm->arena[proc->pc];
	proc->cycle = get_cycle(proc->opcode);
}

void	push_active(t_proclist *proc, t_vm *vm)
{
	if (!vm->beginactive)
		vm->beginactive = proc;
	else
	{
		proc->activenext = vm->beginactive;
		vm->beginactive = proc;
	}
}

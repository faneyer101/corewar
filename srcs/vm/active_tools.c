/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   active_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalle <nsalle@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 13:02:21 by nsalle            #+#    #+#             */
/*   Updated: 2020/03/12 13:12:17 by nsalle           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void	get_opcode(t_vm *vm)
{
	t_proclist	*proc;
	t_proclist	*prev;

	proc = vm->beginactive;
	while (proc)
	{
		proc->opcode = vm->arena[proc->pc];
		proc->cycle = get_cycle(proc->opcode);
		prev = proc;
		proc = proc->activenext;
		prev->activenext = NULL;
	}
	vm->beginactive = NULL;
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
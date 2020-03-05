/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalle <nsalle@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/05 10:51:26 by nsalle            #+#    #+#             */
/*   Updated: 2020/03/05 16:02:15 by nsalle           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

int		get_paramval(t_vm *vm, t_proclist *proc, uint8_t code, int dsize)
{
	int	rep;
	int	toreach;

	rep = 0;
	if (code == REG_CODE)
	{
		rep = vm->arena[proc->pc + proc->curs];
		proc->curs += 1;
	}
	if (code == IND_CODE)
	{
		toreach = maptoi(vm, proc->pc + proc->curs, 2);
		rep = maptoi(vm, toreach, 4);
		proc->curs += 2;
	}
	if (code == DIR_CODE)
	{
		rep = maptoi(vm, proc->pc + proc->curs, dsize);
		proc->curs += dsize;
	}
	return (rep);
}

uint8_t	compute_params(t_proclist *proc, uint8_t nbp, uint8_t dsize)
{
	uint8_t	i;
	uint8_t	rep;

	i = 0;
	rep = 0;
	while (i < nbp)
	{
		if (proc->param[i] == REG_CODE)
			rep += 1;
		if (proc->param[i] == DIR_CODE)
			rep += dsize;
		if (proc->param[i] == IND_CODE)
			rep += 2;
		i++;
	}
	return (rep);
}

uint8_t	get_param(uint8_t c1, uint8_t c2)
{
	uint8_t	rep;

	rep = 0;
	if (c1 == 0 && c2 == 0)
		return (0);
	if (c1 == 0 && c2 == 1)
		return (REG_CODE);
	if (c1 == 1 && c2 == 0)
		return (DIR_CODE);
	if (c1 == 1 && c2 == 1)
		return (IND_CODE);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digitools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 16:32:18 by nsalle            #+#    #+#             */
/*   Updated: 2020/06/04 16:12:20 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void		write_onmap(t_vm *vm, int adress, uint32_t val)
{
	while (adress < 0)
		adress += MEM_SIZE;
	if (adress >= MEM_SIZE)
		adress %= MEM_SIZE;
	vm->arena[get_reach(adress + 3)] = val;
	vm->arena[get_reach(adress + 2)] = val >> 8;
	vm->arena[get_reach(adress + 1)] = val >> 16;
	vm->arena[adress] = val >> 24;
	if (vm->verbose == 2)
		ft_printf("{YELL}Writing %.4x to adress %d{END}\n", val, adress);
}

uint32_t	maptoi(t_vm *vm, int i, uint8_t size)
{
	int	rep;
	int	bit;

	i = get_reach(i);
	rep = 0;
	bit = 0;
	while (bit < size)
	{
		rep *= 256;
		rep += vm->arena[get_reach(i)];
		i++;
		bit++;
	}
	return (rep);
}

void		binstring(t_proclist *proc, uint8_t toparse)
{
	int		j;

	j = 0;
	while (j < 8)
		proc->ocp[j++] = 0;
	j = 7;
	while (j > -1)
	{
		proc->ocp[j--] = toparse % 2;
		toparse /= 2;
	}
}

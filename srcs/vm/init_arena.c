/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_arena.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 18:01:58 by nsalle            #+#    #+#             */
/*   Updated: 2020/06/05 11:10:24 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void	dump_arena(t_vm *vm)
{
	int	i;

	i = 0;
	ft_printf("0x0000 : ");
	while (i < MEM_SIZE)
	{
		if (!vm->arena[i])
			ft_printf("%.2x ", vm->arena[i]);
		else
		{
			if (vm->verbose == 2)
				ft_printf("{RED}");
			ft_printf("%.2x ", vm->arena[i]);
			if (vm->verbose == 2)
				ft_printf("{END}");
		}
		i++;
		if (i % DUMP_SIZE == 0 && i < MEM_SIZE)
			ft_printf("\n0x%.4x : ", i);
	}
	ft_putendl("");
	exit(0);
}

void	init_arena(t_vm *vm)
{
	int	ip;
	int	ic;
	int	i;

	ip = 0;
	i = 0;
	while (i < MEM_SIZE)
	{
		vm->arena[i] = 0;
		i++;
	}
	while (ip < vm->nb_player)
	{
		i = vm->players[ip].start;
		ic = 0;
		while (ic < vm->players[ip].size)
		{
			vm->arena[i] = vm->players[ip].code[ic];
			i++;
			ic++;
		}
		ip++;
	}
	vm->lastalive = vm->nb_player;
}

/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init_arena.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nsalle <nsalle@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/12 18:01:58 by nsalle       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/19 13:51:50 by nsalle      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/vm.h"

void	dump_arena(t_vm *vm)
{
	int	i;

	i = 0;
	while (i < MEM_SIZE)
	{
		if (!vm->arena[i])
			ft_printf("%.2x ", vm->arena[i]);
		else
			ft_printf("{RED}%.2x{END} ", vm->arena[i]);
		i++;
		if (i % 64 == 0)
			ft_putchar ('\n');
	}
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
	dump_arena(vm);
}
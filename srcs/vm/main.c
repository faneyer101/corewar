/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalle <nsalle@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 21:45:58 by nsalle            #+#    #+#             */
/*   Updated: 2020/03/07 17:33:47 by nsalle           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void	usage(void)
{
	ft_printf("Usage:\n./vm [player1] ... [playerMAX_PLAYERS]\n");
	ft_printf("-n N\t: Changes the player number of the next .cor file\n");
	ft_printf("-dump N\t: Dumps memory after N cycles then exits\n");
	exit(0);
}

void	vm_init(t_vm *vm)
{
	vm->nb_player = 0;
	vm->booldump = 0;
	vm->dump = 0;
	vm->cycles = 0;
	vm->linf.cyc_since_last = 0;
	vm->linf.liv_since_last = 0;
	vm->linf.todie = CYCLE_TO_DIE;
}

void	introducing(t_vm *vm)
{
	int	i;

	i = 0;
	ft_printf("Introducing contestants...\n");
	while (i < vm->nb_player)
	{
		ft_printf("* Player %d, wheighing %d bytes,",
			i + 1, vm->players[i].size);
		ft_printf(" \"%s\" ", vm->players[i].name);
		ft_printf("(\"%s\")\n", vm->players[i].comment);
		i++;
	}
}

int		main(int argc, char **argv)
{
	t_vm	vm;

	vm_init(&vm);
	all_checks(argc, argv, &vm);
	introducing(&vm);
	init_arena(&vm);
	load_first(&vm);
	loop(&vm);
}

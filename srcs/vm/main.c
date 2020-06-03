/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faneyer <faneyer@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 21:45:58 by nsalle            #+#    #+#             */
/*   Updated: 2020/06/03 15:31:56 by faneyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void	exit_corewar(t_vm *vm)
{
	t_proclist	*curs;
	t_proclist	*cursnext;
	int			i;

	i = 0;
	while (i < vm->nb_player)
	{
		close(vm->players[i].fd);
		free(vm->players[i].code);
		i++;
	}
	curs = vm->beginlist;
	cursnext = vm->beginlist;
	while (cursnext)
	{
		cursnext = cursnext->next;
		ft_strdel(&curs->ocp);
		free(curs);
		curs = cursnext;
	}
	exit(0);
}

void	usage(void)
{
	ft_printf("Usage:\n./vm [player1] ... [playerMAX_PLAYERS]\n");
	ft_printf("-n N\t: Changes the player number of the next .cor file\n");
	ft_printf("-dump N\t: Dumps memory after N cycles then exits\n");
	exit(0);
}

void	vm_init(t_vm *vm)
{
	ft_bzero(vm, sizeof(t_vm));
	vm->nb_player = 0;
	vm->booldump = 0;
	vm->dump = 0;
	vm->cycles = 0;
	vm->pid_tracker = 1;
	vm->linf.cyc_since_last = 0;
	vm->linf.liv_since_last = 0;
	vm->linf.checks = 0;
	vm->game = 1;
	vm->linf.todie = CYCLE_TO_DIE;
	vm->verbose = 2;
}

void	introducing(t_vm *vm)
{
	int	i;

	i = 0;
	ft_printf("Introducing contestants...\n");
	while (i < vm->nb_player)
	{
		ft_printf("* Player %d, weighing %d bytes,",
			i + 1, vm->players[i].size);
		ft_printf(" \"%s\" ", vm->players[i].name);
		ft_printf("(\"%s\") !\n", vm->players[i].comment);
		i++;
	}
}

int		main(int argc, char **argv)
{
	t_vm	vm;

	vm_init(&vm);
	parsing_cmd(argc, argv, &vm);
	introducing(&vm);
	init_arena(&vm);
	load_first(&vm);
	if (vm.booldump && !vm.dump)
		dump_arena(&vm);
	loop(&vm);
}

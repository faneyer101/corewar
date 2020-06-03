/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faneyer <faneyer@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 12:03:05 by nsalle            #+#    #+#             */
/*   Updated: 2020/06/03 15:31:27 by faneyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void	swap_player(char *name_player, t_vm *vm, int player)
{
	int		i;
	char	*tmp;

	i = 0;
	while (i < vm->nb_player && vm->players[i].pname != NULL)
		i++;
	tmp = vm->players[player].pname;
	vm->players[player].pname = name_player;
	vm->players[i].pname = tmp;
}

void	stock_option_n(int argc, char **av, t_vm *vm, int i)
{
	int player;

	while (i < argc)
	{
		player = 0;
		if (!ft_strcmp(av[i], "-n"))
		{
			if ((player = ft_atoi(av[i + 1])) > vm->nb_player)
				print_with_exit("Max players wait:", vm->nb_player);
			else if (player <= 0)
				print_with_exit("Please select a num player correct:", player);
			else if (vm->players[player - 1].pname != NULL)
				swap_player(av[i + 2], vm, player - 1);
			else
				vm->players[player - 1].pname = av[i + 2];
			i += 2;
		}
		else
		{
			while (player < vm->nb_player && vm->players[player].pname != NULL)
				player++;
			vm->players[player].pname = av[i];
		}
		i++;
	}
}

void	parsing_cmd(int argc, char **av, t_vm *vm)
{
	int i;

	if (argc < 2)
		usage();
	i = -1;
	while (++i < MAX_PLAYERS)
		vm->players[i].pname = NULL;
	vm->verbose = 0;
	check_verbos(av, vm);
	check_dump(argc, av, vm);
	i = (vm->verbose) ? 2 : 1;
	i += (vm->booldump) ? 2 : 0;
	check_bad_option(argc, av, vm, i);
	stock_option_n(argc, av, vm, i);
	check_magic(vm);
}

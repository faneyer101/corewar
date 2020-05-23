/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faneyer <faneyer@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 12:03:05 by nsalle            #+#    #+#             */
/*   Updated: 2020/05/23 23:25:30 by faneyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"
#include <stdio.h>

void	check_verbos(char **av, t_vm *vm)
{
	if (!(ft_strcmp(av[1], "-v")))
		vm->verbose = 1;
	else if (!(ft_strcmp(av[1], "-vc")))
		vm->verbose = 2;
}

void	check_dump(int argc, char **av, t_vm *vm)
{
	int	j;
	int	i;

	i = (vm->verbose) ? 2 : 1;
	if (argc > i && !(ft_strcmp(av[i], "-dump")))
	{
		j = 0;
		if (argc > i + 1)
		{
			while (av[i + 1][j])
			{
				if (!ft_isdigit(av[i + 1][j]))
					usage();
				j++;
			}
			vm->dump = ft_atoi(av[i + 1]);
			vm->booldump = 1;
		}
		else
			usage();
	}
}

void	check_nullbytes(t_vm *vm, int ip)
{
	int		i;
	char	check[4];

	i = 0;
	read(vm->players[ip].fd, check, 4);
	while (i < 4)
	{
		if (check[i] != 0)
		{
			ft_printf("Some bytes were supposed to be NULL\n");
			exit(0);
		}
		i++;
	}
}

void	check_magic(t_vm *vm)
{
	int	i;
	int	ip;

	ip = 0;
	i = (vm->verbose) ? 2 : 1;
	i += (vm->booldump) ? 2 : 0;
	while (ip < vm->nb_player)
	{
		vm->players[ip].fd = open(vm->players[ip].pname, O_RDONLY);
		read(vm->players[ip].fd, vm->players[ip].magic, 4);
		read(vm->players[ip].fd, vm->players[ip].name, PROG_NAME_LENGTH);
		check_nullbytes(vm, ip);
		vm->players[ip].size = get_size(vm, ip);
		read(vm->players[ip].fd, vm->players[ip].comment, COMMENT_LENGTH);
		check_nullbytes(vm, ip);
		check_realsize(vm, ip);
		get_code(vm, ip);
		vm->players[ip].start = MEM_SIZE / vm->nb_player * (ip);
		ip++;
		i++;
	}
}

void	print_with_exit(char *msg, int i)
{
	ft_printf("%s %d\n", msg, i);
	exit(1);
}

void	print_with_usage(char *msg, char *av)
{
	ft_printf("%s %s\n", msg, av);
	usage();
}

void	check_bad_option_n(char **av, int *i, int j, t_vm *vm)
{
	if (!ft_isdigit(av[*i + 1][j]))
		usage();
	else if ((ft_strcmp(".cor", av[*i + 2] + ft_strlen(av[*i + 2]) - 4)))
		print_with_usage("Wrong file", av[*i]);
	while (ft_isdigit(av[*i + 1][j]))
		j++;
	if (av[*i + 1][j] != '\0' && ft_isalpha(av[*i + 1][j]))
		usage();
	*i += 3;
	vm->nb_player++;
}

void	check_bad_option(int ac, char **av, t_vm *vm, int i)
{
	int	j;

	while (ac > i)
	{
		j = 0;
		if (!(ft_strcmp(av[i], "-n")) && ac > i + 2)
		{
			check_bad_option_n(av, &i, j, vm);
			continue ;
		}
		else if (!(ft_strcmp(".cor", av[i] + ft_strlen(av[i]) - 4)))
		{
			i++;
			vm->nb_player++;
			continue ;
		}
		else if ((ft_strcmp(".cor", av[i] + ft_strlen(av[i]) - 4)))
			print_with_usage("Wrong file", av[i]);
		else
			usage();
	}
	if (vm->nb_player > MAX_PLAYERS)
		print_with_exit("Max players wait:", MAX_PLAYERS);
}

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

void	all_checks(int argc, char **av, t_vm *vm)
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
	if (vm->verbose == 2)
	{
		printf("verbose %d | dump %d ==> %d\n", vm->verbose, vm->booldump, vm->dump);
		i = 1;
		while (i < vm->nb_player + 1)
		{
			printf("joueur numero %d ==> %s\n", i, vm->players[i - 1].pname);
			i++;
		}
	}
}

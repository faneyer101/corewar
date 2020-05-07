/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   all_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faneyer <faneyer@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 12:03:05 by nsalle            #+#    #+#             */
/*   Updated: 2020/05/07 17:58:48 by faneyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/vm.h"
#include <stdio.h>
/*
void	check_filenames(int ac, char **av, t_vm *vm)
{
	int				i;
	unsigned char	error;

	error = 0;
	i = (vm->verbose) ? 2 : 1;
	i += (vm->booldump) ? 2 : 0;
	printf("position index i %d | %s\n", i, av[i]);
	while (i < ac)
	{
		if (av[i][0] != '-'
			&& (ft_strcmp(".cor", av[i] + ft_strlen(av[i]) - 4)))
		{
			ft_printf("Wrong file %s\n", av[i]);
			error = 1;
		}
		else if (av[i][0] != '-')
		{
			vm->players[vm->nb_player].pname = av[i];
			vm->nb_player++;
		}
		i++;
	}
	if (error)
	{
		ft_printf("\nThe champions must be .cor files to be able to");
		ft_printf(" play the game\n");
		exit(1);
	}
}
*/
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
	//printf("test dump %d|%s\n", i, av[i]);
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
		{
			printf("error dump\n");
			usage();
		}
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

void	check_magic(char **av, t_vm *vm)
{
	int	i;
	int	ip;

	ip = 0;
	i = (vm->verbose) ? 2 : 1;
	i += (vm->booldump) ? 2 : 0;
	while (ip < vm->nb_player)
	{
		if (av[i][0] == '-')
			i += 2;
		vm->players[ip].fd = open(av[i], O_RDONLY);
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

void	check_bad_option(int ac, char **av, t_vm *vm)
{
	int	i;
	int	j;

	i = (vm->verbose) ? 2 : 1;
	i += (vm->booldump) ? 2 : 0;
	while (ac > i)
	{
		j = 0;
		if (!(ft_strcmp(av[i], "-n")) && ac > i + 2)
		{
			if (!ft_isdigit (av[i + 1][j]))
				usage ();
			else if ((ft_strcmp(".cor", av[i + 2] + ft_strlen(av[i + 2]) - 4)))
			{
				ft_printf("Wrong file %s\n", av[i]);
				usage ();
			}
			while (ft_isdigit(av[i + 1][j]))
				j++;
			if (av[i + 1][j] != '\0' && ft_isalpha(av[i + 1][j]))
				usage ();
			i += 3;
			continue ;
		}
		else if (!(ft_strcmp(".cor", av[i] + ft_strlen(av[i]) - 4)))
		{
			i++;
			continue ;
		}
		else if ((ft_strcmp(".cor", av[i] + ft_strlen(av[i]) - 4)))
		{
			ft_printf("Wrong file %s\n", av[i]);
			usage ();
		}
		else
			usage();
	}
}

void	swap_player(char *name_player, t_vm *vm, int player)
{
	int 	i;
	char	tmp[PROG_NAME_LENGTH];

	i = 0;
	while (i < MAX_PLAYERS && vm->players[i].name[0] != '\0')
	{
	
		i++;
	}
//	printf ("player %d existe. On deplace en joueur %d\n", player, i);
	ft_strcpy(tmp, vm->players[player].name);
	ft_strcpy(vm->players[player].name, name_player);
	ft_strcpy(vm->players[i].name, tmp);
	
}

void	stock_option_n(int argc, char **av, t_vm *vm)
{
	int	i;
	int player;

	i = (vm->verbose) ? 2 : 1;
	i += (vm->booldump) ? 2 : 0;
	while (i < argc)
	{
		player = 0;
		if (!ft_strcmp(av[i], "-n"))
		{
			if ((player = ft_atoi(av[i + 1])) > MAX_PLAYERS)
			{
				ft_printf("Max players wait: %d\n", MAX_PLAYERS);
				exit (1);
			}
			else if (player <= 0)
			{
				ft_printf("Please select a num player correct: %d\n", player);
				exit (1);
			}
			else if (vm->players[player - 1].name[0] != '\0')
			{
			//	printf ("avant swap %s ==> %s\n", vm->players[player - 1].name, av[i + 2]);
				swap_player(av[i + 2], vm, player - 1);
			}
			else
			{
			//	while (player < MAX_PLAYERS && vm->players[player].name[0] != '\0')
			//		player++;
				ft_strcpy(vm->players[player - 1].name, av[i + 2]);
			}
			i += 2;
		}
		else
		{
			while (player < MAX_PLAYERS && vm->players[player].name[0] != '\0')
				player++;
			ft_strcpy(vm->players[player].name, av[i]);
		}
		i++;
	}
}

void	all_checks(int argc, char **av, t_vm *vm)
{
	int i = 1;
	
	if (argc < 2)
		usage();
	vm->verbose = 0;
	check_verbos(av, vm);
	check_dump(argc, av, vm);
	check_bad_option(argc, av, vm);
	stock_option_n(argc, av, vm);
	//check_filenames(argc, av, vm);
	check_magic(av, vm);
	printf("verbose %d | dump %d ==> %d\n", vm->verbose, vm->booldump, vm->dump);
	while (i < MAX_PLAYERS + 1)
	{
		printf ("joueur numero %d ==> %s\n", i, vm->players[i - 1].name);
		i++;
	}
	//exit (0);
}
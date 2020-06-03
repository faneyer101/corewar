/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faneyer <faneyer@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 15:17:27 by faneyer           #+#    #+#             */
/*   Updated: 2020/06/03 15:21:37 by faneyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

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

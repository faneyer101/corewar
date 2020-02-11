/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   all_checks.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nsalle <nsalle@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/10 12:03:05 by nsalle       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/10 21:10:46 by nsalle      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/vm.h"

void	check_filenames(int ac, char **av, t_vm *vm)
{
	int				i;
	unsigned char	error;

	error = 0;
	if (vm->booldump)
		i = 3;
	else
		i = 1;
	while (i < ac)
	{
		if (av[i][0] != '-'
			&& (ft_strcmp(".cor", av[i] + ft_strlen(av[i]) - 4)))
		{
			ft_printf("Wrong file %s\n", av[i]);
			error = 1;
		}
		else if (av[i][0] != '-')
			vm->nb_player++;
		i++;
	}
	if (error)
	{
		ft_printf("\nThe champions must be .cor files to be able to");
		ft_printf(" play the game\n");
		exit(1);
	}
}

void	check_dump(int argc, char **av, t_vm *vm)
{
	int	j;

	if (!(ft_strcmp(av[1], "-dump")))
	{
		j = 0;
		if (argc > 2)
		{
			while (av[2][j])
			{
				if (!ft_isdigit(av[2][j]))
					usage();
				j++;
			}
			vm->dump = ft_atoi(av[2]);
			vm->booldump = 1;
		}
		else
			usage();
	}
}

void	check_magic(char **av, t_vm *vm)
{
	int	i;
	int	ip;

	ip = 0;
	i = (vm->booldump) ? 3 : 1;
	while (ip < vm->nb_player)
	{
		if (av[i][0] == '-')
			i += 2;
		ft_printf("openning : %s \n", av[i]);
		vm->players[ip].fd = open(av[i], O_RDONLY);
		unsigned char *test = malloc(5);
		test[5] = '\0';
		read(vm->players[ip].fd, test, 4);

		int	j = -1;
		while (++j < 4)
			ft_printf("%b16 ", test[j]);

		ft_printf("\n\nmagic: %b16 \n", COREWAR_EXEC_MAGIC);
		ft_putchar('\n');
		ip++;
	}
}

void	all_checks(int argc, char **av, t_vm *vm)
{
	if (argc < 2)
		usage();
	check_dump(argc, av, vm);
	check_filenames(argc, av, vm);
	check_magic(av, vm);
}

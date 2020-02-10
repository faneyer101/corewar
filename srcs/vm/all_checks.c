/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   all_checks.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nsalle <nsalle@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/10 12:03:05 by nsalle       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/10 12:55:32 by nsalle      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/vm.h"

void	check_filenames(int ac, char **av)
{
	int				i;
	unsigned char	error;

	i = 1;
	error = 0;
	while (i < ac)
	{
		if (av[i][0] != '-'
			&& (ft_strcmp(".cor", av[i] + ft_strlen(av[i]) - 4)))
		{
			ft_printf("Wrong file %s\n", av[i]);
			error = 1;
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

void	all_checks(int argc, char **av)
{
	if (argc < 2)
	{
		ft_printf("Usage:\n./vm [player1] ... [playerMAX_PLAYERS]\n");
		ft_printf("-n to change the player number of the next .cor file\n");
	}
	check_filenames(argc, av);

}

/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parser.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: faneyer <marvin@le-101.fr>                 +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/04 12:08:14 by faneyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/06 07:12:12 by faneyer     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

# include "../../includes/corewar.h"

int	main(int ac, char **av)
{
	/*
	 *
	 *	gerer le nombre d'arguments inferieur a 1 || superieur a 2 error
	 *
	*/
	if (ac < 2)
		write (1, "salut\n", 6);
	else
		write (1, av[1], ft_strlen(av[1]) + 1);
	return (0);
}

/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_tools.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nsalle <nsalle@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/11 14:39:38 by nsalle       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/11 16:42:20 by nsalle      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/vm.h"

void	check_realsize(t_vm *vm, int ip)
{
	int readc = 0;
	char dump[1];

	while (read(vm->players[ip].fd, dump, 1))
		readc++;
	if (readc != vm->players[ip].size)
	{
		ft_printf("Champion %s ", vm->players[ip].name);
		ft_printf("has a code size that differ from what its header says\n");
		exit (0);
	}
}

int		get_size(t_vm *vm, int ip)
{
	int				rep;
	unsigned char	tab[4];

	read(vm->players[ip].fd, tab, 4);
	rep = 0;
	rep += tab[3];
	rep += tab[2] * 256;
	rep += tab[1] * 256 * 256;
	rep += tab[0] * 256 * 256 * 256;
	if (rep > CHAMP_MAX_SIZE)
	{
		ft_printf("Champion %s is too heavy:", vm->players[ip].name);
		ft_printf(" %d bytes, limit is: %d\n", rep, CHAMP_MAX_SIZE);
		exit(0);
	}
	return (rep);
}
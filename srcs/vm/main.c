/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nsalle <nsalle@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/09 21:45:58 by nsalle       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/10 18:31:35 by nsalle      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/vm.h"


#include "../../includes/vm.h"

void	usage(void)
{
	ft_printf("Usage:\n./vm [player1] ... [playerMAX_PLAYERS]\n");
	ft_printf("-n N\t: Changes the player number of the next .cor file\n");
	ft_printf("-dump N\t: Dumps memory after N cycles then exits\n");
	exit(0);
}

void    vm_init(t_vm *vm)
{
    vm->nb_player = 0;
    vm->booldump = 0;
    vm->dump = 0;
}

int     main(int argc, char **argv)
{
    t_vm    vm;

    vm_init(&vm);
    all_checks(argc, argv, &vm);
    ft_printf("\nWe have %d champions today\n\n", vm.nb_player);
	ft_printf("Dump after %d cycles\n", vm.dump);
	int i = 0;
	while (i < vm.nb_player)
	{
		ft_printf("fd of p%d: %d\n", i + 1, vm.players[i].fd);
		i++;
	}
}
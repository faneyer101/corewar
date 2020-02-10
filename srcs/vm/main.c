/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nsalle <nsalle@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/09 21:45:58 by nsalle       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/10 15:50:38 by nsalle      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/vm.h"


#include "../../includes/vm.h"

void    vm_init(t_vm *vm)
{
    vm->nb_player = 0;
}

int     main(int argc, char **argv)
{
    t_vm    vm;

    vm_init(&vm);
    all_checks(argc, argv, &vm);
    ft_printf("\nWe have %d champions today\n\n", vm.nb_player);

}
/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   loop.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nsalle <nsalle@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/20 15:44:59 by nsalle       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/22 18:16:30 by nsalle      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/vm.h"

void	exec_proc(t_proclist *proc, t_vm *vm)
{
	ft_printf("I am supposed to execute my code which looks like: ");
	int	i = 0;
	while (i < 10)
		ft_printf("%.2x ", vm->arena[proc->pc + i++]);
	ft_putendl("");
}

void	check_proc(t_proclist *lst, t_vm *vm)
{
	t_proclist	*curs;

	curs = lst;
	while (curs)
	{
		if (curs->cycle > 0)
		{
			curs->cycle--;
			if (curs->cycle == 0)
				exec_proc(curs, vm);
		}
		curs = curs->next;
	}
}

int		get_nbproc(t_proclist *lst)
{
	t_proclist	*curs;
	int			count;

	curs = lst;
	count = 0;
	while (curs)
	{
		if (curs->cycle)
			count++;
		curs = curs->next;
	}
	ft_printf("There are %d processes running\n", count);
	return (count);
}

void	load_first(t_vm *vm)
{
	int	i;

	i = 0;
	while (i < vm->nb_player)
	{
		push_proc(vm->players[i].code[0], vm->players[i].start, vm);
		i++;
	}
}

void	loop(t_vm *vm)
{
	while (vm->game)
	{
		check_proc(vm->beginlist, vm);
		if (get_nbproc(vm->beginlist) == 0)
			vm->game = 0;
		vm->cycles++;
	}
	//check_winner();
}
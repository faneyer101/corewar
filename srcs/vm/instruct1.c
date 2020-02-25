/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instruct1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalle <nsalle@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 19:33:20 by nsalle            #+#    #+#             */
/*   Updated: 2020/02/25 22:17:15 by nsalle           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/vm.h"

// void	live(t_proclist *proc, t_vm *vm)
// {
    
// }

void	carryhandler(t_proclist *proc, uint32_t val)
{
	if (!val)
		proc->carry = 1;
	else
		proc->carry = 0;
	ft_printf("My carry is now: %d\n", proc->carry);
}

void    ld(t_proclist *proc, t_vm *vm)
{
	uint8_t	tomove;
	uint8_t toreach;
	uint8_t	reg;
	

	proc->ocp = binstring(vm->arena[proc->pc + 1]);
	tomove = 2;
	reg = 0;
	if (proc->ocp[0] == 1 && proc->ocp[1]  == 0)
	{
		tomove += 5;
		reg = vm->arena[proc->pc + 6];
		proc->reg[reg] = maptoi(vm, proc->pc + 2, 4);
		ft_printf("Loading the value %d in my r%d\n", proc->reg[reg], reg);
	}
	else if (proc->ocp[0] == 1 && proc->ocp[1]  == 1)
	{
		tomove += 3;
		reg = vm->arena[proc->pc] + 4;
		toreach = maptoi(vm, proc->pc , 2);
		proc->reg[reg] = maptoi(vm, toreach, 4);
		ft_printf("Loading the value %d in my r%d\n", proc->reg[reg], reg);
	}
	proc->pc += tomove;
	carryhandler(proc, proc->reg[reg]);
}

void	zjmp(t_proclist *proc, t_vm *vm)
{
	int	tojump;

	tojump = 0;
	if (proc->carry)
	{
		tojump = maptoi(vm, proc->pc + 1, 2) % IDX_MOD;
		proc->pc += tojump;
	}
	ft_printf("I made a %d long jump to the relative adress->%d\n\n", tojump, proc->pc);
	ft_printf("ADRESSE DU STI : %.2x case numero %d\n", vm->arena[proc->pc - 73], proc->pc - 73);
}

void	exec_proc(t_proclist *proc, t_vm *vm)
{
	int	i = 0;
	while (i < 10)
		ft_printf("%.2x ", vm->arena[proc->pc + i++]);
	ft_putendl("");
    // if (proc->opcode == 1)
	// 	live(proc, vm);
	if (proc->opcode == 2)
		ld(proc, vm);
	if (proc->opcode == 9)
		zjmp(proc, vm);
	if ()
	proc->opcode = vm->arena[proc->pc];
	proc->cycle = get_cycle(proc->opcode);
	ft_printf("\nMy new opcode is: %.2x\n", proc->opcode);
}

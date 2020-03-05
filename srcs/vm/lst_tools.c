/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalle <nsalle@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:14:27 by nsalle            #+#    #+#             */
/*   Updated: 2020/03/05 14:09:14 by nsalle           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/vm.h"

uint16_t	more_opcodes(uint8_t op)
{
	if (op == 12)
		return (800);
	else if (op == 13)
		return (10);
	else if (op == 14)
		return (50);
	else if (op == 15)
		return (1000);
	else if (op == 16)
		return (2);
	else
		return (1);
	return (0);
}

uint16_t	get_cycle(uint8_t op)
{
	if (op == 1)
		return (10);
	else if (op == 2)
		return (5);
	else if (op == 3)
		return (5);
	else if (op == 4)
		return (10);
	else if (op == 5)
		return (10);
	else if (op == 6)
		return (6);
	else if (op == 7)
		return (6);
	else if (op == 8)
		return (6);
	else if (op == 9)
		return (20);
	else if (op == 10)
		return (25);
	else if (op == 11)
		return (25);
	else
		return (more_opcodes(op));
}

t_proclist	*create_proc(t_proclist *proc, uint16_t pc, uint8_t op)
{
	t_proclist	*new;
	uint8_t		i;

	i = 0;
	new = NULL;
	if (!(new = (t_proclist*)malloc(sizeof(t_proclist))))
		exit(0);
	while (i < REG_NUMBER)
	{
		new->reg[i] = proc->reg[i];
		i++;
	}
	new->carry = proc->carry;
	new->opcode = op;
	new->pc = pc;
	new->alive = 0;
	new->cycle = get_cycle(op);
	new->next = NULL;
	return (new);
}

void		push_proc(t_vm *vm, t_proclist *proc, uint16_t pc, uint8_t op)
{
	t_proclist *new;

	new = create_proc(proc, pc, op);
	if (vm->beginlist)
		new->next = vm->beginlist;
	vm->beginlist = new;
	ft_printf("Pushed a proc, opcode: %.2x pc = %d, %d cycles cooldown\n", op, pc, new->cycle);
}

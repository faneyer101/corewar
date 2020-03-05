/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   digitools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nsalle <nsalle@student.le-101.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 16:32:18 by nsalle            #+#    #+#             */
/*   Updated: 2020/03/05 18:52:18 by nsalle           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#include "../../includes/vm.h"

void		write_onmap(t_vm *vm, int adress, uint32_t val)
{
	vm->arena[adress + 3] = val;
	vm->arena[adress + 2] = val >> 8;
	vm->arena[adress + 1] = val >> 16;
	vm->arena[adress] = val >> 24;
	ft_printf("Writing %x to adress %d\n", val, adress);
}

uint32_t	maptoi(t_vm *vm, int i, uint8_t size)
{
	int	rep;
	int	bit;

	rep = 0;
	bit = 0;
	while (bit < size)
	{
		rep *= 256;
		rep += vm->arena[i];
		i++;
		bit++;
	}
	return (rep);
}

char		*binstring(uint8_t toparse)
{
	char	*binary;
	int		j;

	binary = (char*)malloc(sizeof(char) * 8);
	j = 0;
	while (j < 8)
		binary[j++] = 0;
	j = 7;
	while (j > -1)
	{
		binary[j--] = toparse % 2;
		toparse /= 2;
	}
	return (binary);
}

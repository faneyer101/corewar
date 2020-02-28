/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reverse_bits.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faneyer <faneyer@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 14:47:18 by jde-la-m          #+#    #+#             */
/*   Updated: 2020/02/28 09:58:23 by faneyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned char	ft_reverse_bits(unsigned char bit)
{
	int				i;
	unsigned char	last;
	unsigned char	reversed;

	i = 0;
	reversed = 0;
	while (i < 7)
	{
		last = bit & 1;
		bit >>= 1;
		reversed += last;
		reversed <<= 1;
		i++;
	}
	return (reversed);
}

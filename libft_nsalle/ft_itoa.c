/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faneyer <faneyer@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 14:04:49 by jde-la-m          #+#    #+#             */
/*   Updated: 2020/02/28 09:53:49 by faneyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

/*
**		DESCRIPTION
**	Allocate (with malloc(3)) and returns a “fresh” string ending
**	with ’\0’ representing the integer n given as argument.
**	Negative numbers must be supported. If the allocation fails,
**	the function returns NULL.
**
**		RETURN VALUE
**	The string representing the integer passed as argument.
*/

#include "libft.h"

char	*ft_itoa(int n)
{
	char			*str;
	int				i;
	unsigned int	nb;

	if (!(str = (char *)malloc(sizeof(*str) * ft_intlen(n) + 1)))
		return (NULL);
	i = 0;
	nb = n < 0 ? -n : n;
	while (nb && (str[i++] = (nb % 10) + '0'))
		nb /= 10;
	if (n <= 0)
		str[i++] = n == 0 ? '0' : '-';
	str[i] = '\0';
	return (ft_strrev(str));
}

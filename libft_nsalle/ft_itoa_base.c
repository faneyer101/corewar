/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faneyer <faneyer@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 18:16:56 by jde-la-m          #+#    #+#             */
/*   Updated: 2020/02/28 09:53:43 by faneyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa_base(int n, int base)
{
	char			*str;
	int				i;
	int				digit;
	unsigned int	nb;

	if (!(str = (char *)malloc(sizeof(*str) * 64)))
		return (NULL);
	i = 0;
	nb = n < 0 ? -n : n;
	while (nb)
	{
		digit = nb % base;
		str[i++] = (digit > 9) ? (digit - 10) + 'a' : digit + '0';
		nb /= base;
	}
	if (n < 0 && base == 10)
		str[i++] = '-';
	else if (n == 0)
		str[i++] = '0';
	str[i] = '\0';
	return (ft_strrev((char *)ft_realloc(str, ft_strlen(str))));
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faneyer <faneyer@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 13:48:03 by jde-la-m          #+#    #+#             */
/*   Updated: 2020/06/03 14:54:15 by faneyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long	ft_atol(const char *str)
{
	long res;
	long sign;

	res = 0;
	while (ft_isspace(*str))
		str++;
	sign = (*str == '-' ? -1 : 1);
	*str == '-' || *str == '+' ? str++ : str;
	while (ft_isdigit(*str))
		res = (res * 10) + (*str++ - '0');
	return (res * sign);
}

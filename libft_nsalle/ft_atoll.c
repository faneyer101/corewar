/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faneyer <faneyer@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 13:49:06 by jde-la-m          #+#    #+#             */
/*   Updated: 2020/06/04 20:01:05 by faneyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long	ft_atoll(const char *str)
{
	long long res;
	long long sign;

	res = 0;
	while (ft_isspace(*str))
		str++;
	sign = (*str == '-' ? -1 : 1);
	*str == '-' || *str == '+' ? str++ : str;
	while (ft_isdigit(*str))
	{
		if (((res * 10) + (*str - '0')) < 0)
			return (LONG_MAX);
		res = (res * 10) + (*str++ - '0');
	}
	return (res * sign);
}

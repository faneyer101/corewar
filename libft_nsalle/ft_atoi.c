/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faneyer <faneyer@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 13:45:05 by jde-la-m          #+#    #+#             */
/*   Updated: 2020/06/03 14:55:02 by faneyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long long int	ft_atoi(const char *str)
{
	long long int	res;
	int				sign;

	res = 0;
	while (ft_isspace(*str))
		str++;
	sign = (*str == '-' ? -1 : 1);
	*str == '-' || *str == '+' ? str++ : str;
	while (ft_isdigit(*str))
		res = (res * 10) + (*str++ - '0');
	return (res * sign);
}

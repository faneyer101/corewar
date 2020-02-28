/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faneyer <faneyer@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/09 17:44:31 by jde-la-m          #+#    #+#             */
/*   Updated: 2020/02/28 10:00:15 by faneyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncpy(char *dst, const char *src, size_t n)
{
	char	*d;

	if (!n)
		return (dst);
	d = dst;
	while (n && *src)
	{
		*dst++ = *src++;
		n--;
	}
	while (n)
	{
		*dst++ = '\0';
		n--;
	}
	return (d);
}

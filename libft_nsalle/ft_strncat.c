/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faneyer <faneyer@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/10 06:07:57 by jde-la-m          #+#    #+#             */
/*   Updated: 2020/02/28 10:00:06 by faneyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t n)
{
	char	*str1;

	if (!n)
		return (s1);
	str1 = s1;
	while (*str1)
		str1++;
	while (n && *s2)
	{
		*str1++ = *s2++;
		n--;
	}
	*str1 = '\0';
	return (s1);
}

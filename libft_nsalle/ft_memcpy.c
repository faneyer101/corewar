/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faneyer <faneyer@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 14:20:26 by jde-la-m          #+#    #+#             */
/*   Updated: 2020/02/28 09:56:39 by faneyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

/*
**		DESCRIPTION
**	The memcpy() function copies n bytes from memory area src to memory area
**	dest.  The memory areas must not overlap.  Use memmove(3) if the memory
**	areas do overlap.
**
**		RETURN VALUE
**	The memcpy() function returns a pointer to dest.
*/

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*dp;
	const char	*sp;

	dp = (char*)dest;
	sp = (const char*)src;
	while (n--)
		*dp++ = *sp++;
	return (dest);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcasestr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faneyer <faneyer@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/11 23:47:43 by jde-la-m          #+#    #+#             */
/*   Updated: 2020/02/28 09:58:32 by faneyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

/*
**		DESCRIPTION
**	The strstr() function locates the first occurrence of the null-terminated
**	string needle in the null-terminated string haystack.
**	The strcasestr() function is similar to strstr(), but ignores the case of
**	both strings.
**	While the strcasestr() function uses the current locale, the
**	strcasestr_l() function may be passed a locale directly. See xlocale(3)
**	for more information.
**
**		RETURN VALUE
**	If needle is an empty string, haystack is returned; if needle occurs nowhere
**	in haystack, NULL is returned; otherwise a pointer to the first character of
** the first occurrence of needle is returned.
*/

#include "libft.h"

char	*ft_strcasestr(const char *haystack, const char *needle)
{
	size_t	len;

	if (*needle == '\0')
		return ((char *)haystack);
	len = ft_strlen(needle);
	while (*haystack)
	{
		if (!ft_strncasecmp(haystack, needle, len))
			return ((char *)haystack);
		haystack++;
	}
	return (NULL);
}

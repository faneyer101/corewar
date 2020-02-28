/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isspace.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faneyer <faneyer@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 14:00:38 by jde-la-m          #+#    #+#             */
/*   Updated: 2020/02/28 09:53:27 by faneyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

/*
**		DESCRIPTION
**	Checks for white-space characters.
**	In the "C" and "POSIX" locales, these are:
**	space, form-feed ('\f'), newline ('\n'), carriage return ('\r'), horizontal
**	tab('\t'), and vertical tab ('\v').
*/

#include "libft.h"

int	ft_isspace(int c)
{
	return (c == 32 || (9 <= c && c <= 13));
}

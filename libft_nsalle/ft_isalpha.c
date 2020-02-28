/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faneyer <faneyer@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/03 13:54:50 by jde-la-m          #+#    #+#             */
/*   Updated: 2020/02/28 09:52:25 by faneyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

/*
**		DESCRIPTION
**	Checks for an alphabetic character; in the standard "C" locale, it is
**	equivalent to (isupper(c) || islower(c)).  In some locales, there may be
**	additional characters for which isalpha()  is  true—letters which are
**	neither uppercase nor lowercase.
*/

#include "libft.h"

int	ft_isalpha(int c)
{
	return (ft_isupper(c) || ft_islower(c));
}

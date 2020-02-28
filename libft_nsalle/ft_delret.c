/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_delret.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faneyer <faneyer@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/02 16:44:02 by jde-la-m          #+#    #+#             */
/*   Updated: 2020/02/28 09:52:09 by faneyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

/*
**		DESCRIPTION
**	The function ft_delret frees and sets a previously allocated ptr to NULL,
**	then returns the set ret value.
*/

#include "libft.h"

int	ft_delret(void *ptr, int ret)
{
	ft_memdel((void **)ptr);
	return (ret);
}

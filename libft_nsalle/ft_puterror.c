/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puterror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faneyer <faneyer@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/12 17:18:07 by jde-la-m          #+#    #+#             */
/*   Updated: 2020/02/28 09:57:49 by faneyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

/*
**		DESCRIPTION
**	Outputs an error message as a string to the error output followed by a ’\n’
**	and followed exits program with a custom return value (defined by ret).
*/

#include "libft.h"

void	ft_puterror(const char *msg, int ret)
{
	ft_putendl_fd(msg, 2);
	exit(ret);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strpostpend.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faneyer <faneyer@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/27 00:27:32 by jde-la-m          #+#    #+#             */
/*   Updated: 2020/02/28 10:00:47 by faneyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_strpostpend(char *str, int nb, char c)
{
	int	i;

	i = ft_strlen(str);
	while (nb--)
		str[i++] = c;
	str[i] = '\0';
	return (str);
}

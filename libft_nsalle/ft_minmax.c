/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minmax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 15:06:31 by user42            #+#    #+#             */
/*   Updated: 2020/06/03 15:09:51 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_min(size_t a, size_t b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

size_t		ft_max(size_t a, size_t b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faneyer <faneyer@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/18 03:38:38 by jde-la-m          #+#    #+#             */
/*   Updated: 2020/02/28 09:54:19 by faneyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

/*
**		DESCRIPTION
**	The function ft_lstat returns the Nth element of the list.
**	In case of error, it returns a null pointer.
*/

#include "libft.h"

t_list	*ft_lstat(t_list *lst, unsigned int nbr)
{
	if (!lst)
		return (NULL);
	while (nbr-- && lst)
		lst = lst->next;
	return (lst);
}

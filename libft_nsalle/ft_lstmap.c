/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faneyer <faneyer@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 20:03:34 by jde-la-m          #+#    #+#             */
/*   Updated: 2020/02/28 09:55:25 by faneyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

/*
**		DESCRIPTION
**	Iterates a list lst and applies the function f to each link to create a
**	“fresh” list (using malloc(3)) resulting from the successive applications of
**	f. If the allocation fails, the function returns NULL.
**
**		RETURN VALUE
**	The new list.
*/

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list *nlst;

	if (lst)
	{
		nlst = f(lst);
		nlst->next = ft_lstmap(lst->next, f);
		return (nlst);
	}
	return (NULL);
}

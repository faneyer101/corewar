/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faneyer <faneyer@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 20:35:52 by jde-la-m          #+#    #+#             */
/*   Updated: 2020/02/28 09:56:13 by faneyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

/*
**		DESCRIPTION
**	The function ft_lstsort sorts the list's contents by ascending order by
**	comparing two links thanks to a function that can compare the data held in
**	those two links.
*/

#include "libft.h"

t_list	*ft_lstsort(t_list *lst, int (*cmp)())
{
	void	*tmp;
	t_list	*nav;

	nav = lst;
	while (lst->next)
	{
		if (((*cmp)(lst->content, lst->next->content)) == 0)
		{
			tmp = lst->content;
			lst->content = lst->next->content;
			lst->next->content = tmp;
			lst = nav;
		}
		else
			lst = lst->next;
	}
	lst = nav;
	return (lst);
}

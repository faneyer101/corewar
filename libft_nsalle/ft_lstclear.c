/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faneyer <faneyer@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/01 20:34:57 by jde-la-m          #+#    #+#             */
/*   Updated: 2020/02/28 09:54:30 by faneyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

/*
**		DESCRIPTION
**	The function ft_lstclear which clears all links from the list.
**	It then assigns the list's pointer to null
*/

#include "libft.h"

void	ft_lstclear(t_list **alst)
{
	if (*alst != NULL)
	{
		ft_lstclear(&((*alst)->next));
		free(*alst);
		*alst = NULL;
	}
}

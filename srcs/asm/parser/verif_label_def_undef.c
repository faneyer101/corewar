/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_label_def_undef.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faneyer <faneyer@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 17:01:23 by faneyer           #+#    #+#             */
/*   Updated: 2020/02/28 19:13:39 by faneyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/asm.h"

int		search_label_undefine(t_list_label *begin_undefine, t_token *data)
{
	t_list_label *undefine;

	undefine = begin_undefine;
	while (undefine)
	{
		if (ft_strcmp(undefine->name, data->data) == 0 &&
		ft_strlen(undefine->name) == ft_strlen(data->data))
			return (TRUE);
		undefine = undefine->unext;
	}
	return (FALSE);
}

int		search_label_define(t_list_label *begin_define, t_token *data)
{
	t_list_label *define;

	define = begin_define;
	while (define)
	{
		if (ft_strcmp(define->name, data->data) == 0 &&
		ft_strlen(define->name) == ft_strlen(data->data))
			return (TRUE);
		define = define->dnext;
	}
	return (FALSE);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_labbel_undefine.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faneyer <faneyer@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 14:29:53 by faneyer           #+#    #+#             */
/*   Updated: 2020/05/24 14:34:52 by faneyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/asm.h"

void	norme_push_label_undefine(t_asm *master, t_token *t)
{
	master->interpretor.wait_label = t;
	master->interpretor.wait_label->index_tab_op =
	master->interpretor.function.index_tab;
	master->interpretor.wait_label->direct =
	master->interpretor.function.direct;
	master->interpretor.wait_label->index_function =
	master->interpretor.function.index_declaration;
	master->interpretor.wait_label->call_index =
	master->interpretor.index;
	master->interpretor.wait_label->unext = NULL;
}

void	push_label_undefine(t_asm *master, t_token *token)
{
	t_token	*ltoken;

	ltoken = master->interpretor.wait_label;
	if (ltoken)
	{
		while (ltoken->unext != NULL)
			ltoken = ltoken->unext;
		ltoken->unext = token;
		ltoken = ltoken->unext;
		ltoken->direct = master->interpretor.function.direct;
		ltoken->index_tab_op = master->interpretor.function.index_tab;
		ltoken->index_function =
		master->interpretor.function.index_declaration;
		ltoken->call_index = master->interpretor.index;
		ltoken->unext = NULL;
	}
	else
		norme_push_label_undefine(master, token);
}

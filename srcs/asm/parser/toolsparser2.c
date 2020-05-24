/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolsparser2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faneyer <faneyer@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 20:59:44 by faneyer           #+#    #+#             */
/*   Updated: 2020/05/24 15:02:18 by faneyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/asm.h"

void	verif_declaration_label(t_asm *master, t_list_label *label)
{
	t_list_label	*list;

	list = label;
	while (list)
	{
		if (list->define_parser == 0)
			print_error_parser_label(master, "label don't declared",
			list->name, list);
		list = list->unext;
	}
}

int		verif_separator(t_asm *m, t_op function, t_token *verif, int i)
{
	t_token *l;

	l = verif;
	while (verif)
	{
		if (verif->kind == SEPARATOR)
			i++;
		verif = verif->next;
	}
	if (i == function.nb_arg - 1 && function.nb_arg >= 1)
		return (TRUE);
	if (nb_param(l->next) < function.nb_arg)
		print_error_parser(m, "missing declared parameters in function",
		l->data, l);
	else if (nb_param(l->next) >= function.nb_arg)
		print_error_parser(m, "too many parameters declared in function",
		l->data, l);
	else
		print_error_parser(m, "need to ',' to separate param on function",
		l->data, l);
	return (FALSE);
}

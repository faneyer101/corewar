/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolsparser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faneyer <faneyer@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 18:03:31 by faneyer           #+#    #+#             */
/*   Updated: 2020/06/04 14:33:27 by faneyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/asm.h"

int	search_label(t_list_label *label, char *str)
{
	while (label)
	{
		if (label->defaut)
		{
			label = label->dnext;
			continue ;
		}
		if (ft_strcmp(label->name, str) == 0 &&
		ft_strlen(str) == ft_strlen(label->name))
		{
			if (label->define_parser)
				return (TRUE);
		}
		label = label->dnext;
	}
	return (FALSE);
}

int	norme_verif_type_param(t_asm *m, t_op function, t_token *list)
{
	return (print_error_parser(m, "error type param in function",
		function.name, list));
}

int	verif_type_param(t_asm *m, t_token *list, t_op function, int i)
{
	while (list)
	{
		if (list->kind == BAD)
			return (norme_verif_type_param(m, function, list));
		while (++i < function.nb_arg)
		{
			if ((list->kind == LABEL_INDIRECT || list->kind == NUM_INDIRECT) &&
			function.args[i] >= 4)
				break ;
			else if ((list->kind == LABEL_DIRECT || list->kind == NUM_DIRECT) &&
			(function.args[i] == 2 || function.args[i] == 3 ||
			function.args[i] == 6 || function.args[i] == 7))
				break ;
			else if (list->kind == REGISTRE && (function.args[i] == 1 ||
			function.args[i] == 3 || function.args[i] == 5 ||
			function.args[i] == 7))
				break ;
			else if (list->kind != SEPARATOR)
				return (print_error_parser(m, "error type of param",
				list->data, list));
		}
		list = list->next;
	}
	return (1);
}

int	nb_param(t_token *list)
{
	int	i;

	i = 0;
	while (list)
	{
		if (list->kind != SEPARATOR && list->kind != COMMENT)
			i++;
		list = list->next;
	}
	return (i);
}

int	verif_kind_bad(t_asm *master, t_token *list)
{
	while (list)
	{
		if (list->kind == BAD)
		{
			print_error_parser(master, "error syntax param on function",
			list->data, list);
			return (TRUE);
		}
		list = list->next;
	}
	return (FALSE);
}

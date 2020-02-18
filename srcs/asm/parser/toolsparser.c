/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   toolsparser.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: faneyer <faneyer@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/17 18:03:31 by faneyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/18 18:56:58 by faneyer     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../../includes/asm.h"

int		search_label(t_list_label *label, char *str)
{
	while (label)
	{
		if (ft_strncmp(label->name, str, ft_strlen(str)) == 0)
		{
			if (label->define_parser)
				return (TRUE);
		}
		label = label->next;
	}
	return (FALSE);
}

int	verif_type_param(t_asm *master, t_token *list, t_op function, int i)
{
	while (list)
	{
		if (list->kind == BAD)
			return (print_error_parser_param(master, "error type of param in function", function.name, list));
		if (list->kind == LABEL_INDIRECT || list->kind == LABEL_DIRECT)
			declare_label_param(master, list);
		while (++i < function.nb_arg)
		{
			if ((list->kind == LABEL_INDIRECT || list->kind == NUM_INDIRECT) && function.args[i] >= 4)
				break;
			else if ((list->kind == LABEL_DIRECT || list->kind == NUM_DIRECT) &&
				(function.args[i] == 2 || function.args[i] == 3 || function.args[i] == 6 || function.args[i] == 7))
				break;
			else if (list->kind == REGISTRE && (function.args[i] == 1 || function.args[i] == 3 || function.args[i] == 5 || function.args[i] == 7))
				break;
			else if (list->kind != SEPARATOR)
				return (print_error_parser_param(master, "error type of param", list->data, list));
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

int	verif_bad(t_asm *master, t_token *list)
{
	while (list)
	{
		if (list->kind == BAD)
		{
			print_error_parser_param(master, "error syntax param on function", list->data, list);
			return (TRUE);
		}
		list = list->next;
	}
	return (FALSE);
}

int		verif_separator(t_asm *master, t_op function, t_token *verif)
{
	t_token *list;
	int		i;

	list = verif;
	i = 0;
	while (verif)
	{
		if (verif->kind == SEPARATOR)
			i++;
		verif = verif->next;
	}
	if (i == function.nb_arg - 1 && function.nb_arg >= 1)
		return (TRUE);
	else if (function.nb_arg == 1 && i > 0)
	{	
		print_error_parser_param(master, "too many ',' for separate param on function", list->data, list);
		return (FALSE);
	}
	if (nb_param(list->next) < function.nb_arg)
	{
		ft_printf("|%d|%d|\n", nb_param(list->next), function.nb_arg);
		print_error_parser_param(master, "missing declared parameters in function", list->data, list);
	}
	else if (nb_param(list->next) > function.nb_arg)
		print_error_parser_param(master, "too many parameters declared in function", list->data, list);
	else
		print_error_parser_param(master, "need separator ',' for separate param on function", list->data, list);
	return (FALSE);
}
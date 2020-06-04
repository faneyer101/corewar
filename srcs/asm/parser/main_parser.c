/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faneyer <faneyer@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 23:23:14 by faneyer           #+#    #+#             */
/*   Updated: 2020/06/04 15:52:31 by faneyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/asm.h"

void	parser_function_and_param(t_asm *master, t_token *list, int i)
{
	if (list->kind == FONCTION)
	{
		i = -1;
		while (++i < 17)
			if (ft_strncmp(master->tab_op[i].name, list->data,
			ft_strlen(list->data)) == 0)
				break ;
		if (!verif_kind_bad(master, list) &&
		verif_separator(master, master->tab_op[i], list, 0))
		{
			if (list->next == NULL ||
			master->tab_op[i].nb_arg > nb_param(list->next))
				print_error_parser(master,
				"missing declared parameters in function", list->data, list);
			else if (master->tab_op[i].nb_arg != nb_param(list->next))
				print_error_parser(master,
				"too many parameters declared in function", list->data, list);
			if (verif_type_param(master, list->next, master->tab_op[i], -1))
				create_token_label(master, list);
		}
	}
	else if (list->kind == BAD)
		print_error_parser(master, "error name function", list->data, list);
}

void	parser_label_or_function(t_asm *m, t_token **token, t_token *l)
{
	l = token[0];
	while (l)
	{
		if (l->kind == LABEL_DECLARATION)
		{
			if (m->parser.curent_label && !m->parser.curent_label->defaut &&
			l->column == 1 && search_label(m->parser.define_label, l->data))
				print_error_parser(m, "labbel already declared", l->data, l);
			else if (l->column > 1)
			{
				print_error_parser(m, "just declared one labbel per line",
				l->data, l);
			}
			else
				declare_label_define(m, l);
		}
		else if (l->kind != COMMENT)
		{
			parser_function_and_param(m, l, 0);
			break ;
		}
		if (l)
			l = l->next;
	}
}

void	main_parser_norme(t_asm *master)
{
	verif_declaration_label(master, master->parser.undefine_label);
	if (master->error_parser == 1)
		ft_printf("{RED}%d{END} error detected\n", master->error_parser);
	else if (master->error_parser > 1)
		ft_printf("{RED}%d{END} errors detected\n", master->error_parser);
}

void	norme_main_print_bad(t_asm *m, t_token *l)
{
	print_error_parser(m, "Error of syntax on start instruction", l->data, l);
}

void	main_parser(t_asm *m, t_token *list, int i)
{
	while (++i < m->maxline)
	{
		if (m->tab_token[i])
			list = m->tab_token[i];
		else
			continue ;
		while (list && list->kind != COMMENT)
		{
			if (list->kind == HEADER_NAME || list->kind == HEADER_COMMENT)
				parser_header(m, &list);
			else if (list->kind == BAD)
			{
				norme_main_print_bad(m, list);
				break ;
			}
			else if (list->kind == LABEL_DECLARATION || list->kind == FONCTION)
			{
				parser_label_or_function(m, &list, NULL);
				break ;
			}
			if (list)
				list = list->next;
		}
	}
	main_parser_norme(m);
}

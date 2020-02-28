/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faneyer <faneyer@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/16 23:23:14 by faneyer           #+#    #+#             */
/*   Updated: 2020/02/28 18:28:13 by faneyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/asm.h"

static void	create_label_token(t_token *list, t_token **label)
{
	t_token	*box;

	box = label[0];
	if (box)
	{
		while (box->lnext)
			box = box->lnext;
		box->lnext = list;
	}
	else
		label[0] = list;
}

void	push_back_token_on_label(t_list_label *label, t_token *token)
{
	t_token	*llist;

	llist = label->info;
	if (llist)
	{
		while (llist->lnext)
			llist = llist->lnext;
		create_label_token(token, &llist);
	}
	else
		create_label_token(token, &label->info);
}

static t_list_label	*create_label_defaut(int define, t_token *data)
{
	t_list_label	*box;

	if (!(box = (t_list_label*)malloc(sizeof(t_list_label))))
		return (NULL);
	ft_bzero(box, sizeof(t_list_label));
	box->define_parser = define;
	box->info = data;
	box->defaut = 1;
	return (box);
}

void	norme_create_token_label(t_asm *master, t_token *tlist)
{
	if (tlist->kind == REGISTRE && ft_atoi(tlist->data) > REG_NUMBER)
	{
		ft_printf("parser[{GREEN}line:%d{END}][{GREEN}column:%d{END}]",
		tlist->numline, tlist->column);
		ft_printf("the maximum number of registre is %d|{RED}%s{END}|",
		REG_NUMBER, tlist->data);
		ft_printf("\n");
		master->error_parser++;
	}
	else if (master->parser.curent_label)
		push_back_token_on_label(master->parser.curent_label, tlist);
	else
	{
		master->parser.define_label = create_label_defaut(0, tlist);
		master->parser.curent_label = master->parser.define_label;
	}
}

void	create_token_label(t_asm *master, t_token *tlist)
{
	while (tlist)
	{
		if (tlist->kind != SEPARATOR && tlist->kind != BAD &&
		tlist->kind != COMMENT)
		{
			if ((tlist->kind == LABEL_DIRECT ||
			tlist->kind == LABEL_INDIRECT) && ((master->parser.define_label &&
			master->parser.define_label->defaut == 1 &&
			master->parser.define_label->dnext == NULL) ||
			master->parser.define_label == NULL ||
			(master->parser.define_label->name &&
			!search_label_define(master->parser.define_label, tlist))))
				push_undefine_label(master, tlist);
			norme_create_token_label(master, tlist);
		}
		else if (tlist->kind == BAD)
			print_error_parser(master, "bad syntax in function",
			tlist->data, tlist);
		tlist = tlist->next;
	}
}

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

void	parser_label_or_function(t_asm *m, t_token **token)
{
	t_token			*l;

	l = token[0];
	while (l)
	{
		if (l->kind == LABEL_DECLARATION)
		{
			if (m->parser.curent_label && !m->parser.curent_label->defaut &&
			m->parser.define_label->name && l->column == 1 &&
			search_label(m->parser.define_label, l->data))
				print_error_parser(m, "labbel already declared", l->data, l);
			else if (l->column > 1)
				print_error_parser(m, "just declared one labbel per line",
				l->data, l);
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
				parser_label_or_function(m, &list);
				break ;
			}
			if (list)
				list = list->next;
		}
	}
	main_parser_norme(m);
}

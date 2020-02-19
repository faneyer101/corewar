/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main_parser.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: faneyer <faneyer@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/16 23:23:14 by faneyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/19 19:04:04 by faneyer     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
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
	//box->name = ft_strnew(1);
	box->define_parser = define;
	box->info = data;
	box->defaut = 1;
	return (box);
}

void	create_token_label(t_asm *master, t_token *tlist)
{
	while (tlist)
	{
		if (tlist->kind != SEPARATOR && tlist->kind != BAD && tlist->kind != COMMENT)
		{
			if ((tlist->kind == LABEL_DIRECT || tlist->kind == LABEL_INDIRECT) && master->parser.define_label->name && !search_label_define(master->parser.define_label, tlist))
				push_undefine_label(master, tlist);
			if (master->parser.curent_label)
				push_back_token_on_label(master->parser.curent_label, tlist);
			else
			{
				master->parser.define_label = create_label_defaut(0, tlist);
				master->parser.curent_label = master->parser.define_label;
			}
		}
		tlist = tlist->next;
	}
}

void	parser_function_and_param(t_asm *master, t_token *list, int i)
{
	if (list->kind == FONCTION)
	{
		i = -1;
		while (++i < 17)
			if (ft_strncmp(master->tab_op[i].name, list->data, ft_strlen(list->data)) == 0)
				break;
		if (!verif_kind_bad(master, list) && verif_separator(master, master->tab_op[i], list))
		{
			if (list->next == NULL || master->tab_op[i].nb_arg > nb_param(list->next))
				print_error_parser_param(master, "missing declared parameters in function", list->data, list);
			else if (master->tab_op[i].nb_arg != nb_param(list->next))
				print_error_parser_param(master, "too many parameters declared in function", list->data, list);
			if (verif_type_param(master, list->next, master->tab_op[i], -1))
			{
				create_token_label(master, list);
			}
		}
	}
	else if (list->kind == BAD)
		print_error_parser_param(master, "error name function", list->data, list);
}

void	parser_label_or_function(t_asm *master, t_token **token)
{
	t_token			*list;

	list = token[0];
	while (list)
	{
		if (list->kind == LABEL_DECLARATION)
		{
			if (master->parser.curent_label && !master->parser.curent_label->defaut && search_label(master->parser.define_label, list->data) && list->column == 1)
				print_error_parser_param(master, "label deja declarer", list->data, list);
			else if (list->column > 1)
				print_error_parser_param(master, "just one label declaration on line", list->data, list);
			else
			{
				printf("DECLARE LABEL|%s|\n", list->data);
				declare_label_define(master, list);
			}
		}
		else if (list->kind != COMMENT || list->kind == BAD)
		{
			parser_function_and_param(master, list, 0);
			break;
		}
		if (list)
			list = list->next;
	}
}

int     main_parser(t_asm *master, t_token *list, int i)
{
	while (++i < master->numline)
	{	
		if (master->tab_token[i])
    		list = master->tab_token[i];
		else
			continue;
		while (list && list->kind != COMMENT)
    	{
			if (list->kind == HEADER_NAME || list->kind == HEADER_COMMENT)
				parser_header(master, &list);
			else if (list->kind == BAD)
			{
				print_error_parser_param(master, "Error of syntax", list->data, list);
				break;
			}
			else if (list->kind == LABEL_DECLARATION || list->kind == FONCTION)
			{
				parser_label_or_function(master, &list);
				break;
			}
			if (list)
        		list = list->next;
    	}
	}
	verif_declaration_label(master, master->parser.undefine_label);
	if (master->error_parser == 1)
		ft_printf("{RED}%d{END} error detected\n", master->error_parser);
    else if (master->error_parser > 1)
		ft_printf("{RED}%d{END} errors detected\n", master->error_parser);
	return (0);
}
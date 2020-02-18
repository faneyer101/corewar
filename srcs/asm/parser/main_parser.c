/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main_parser.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: faneyer <faneyer@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/16 23:23:14 by faneyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/18 19:34:38 by faneyer     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../../includes/asm.h"

void	declare_label_param(t_asm *master, t_token *list)
{
	t_list_label *label;
	
	label = master->parser.define_label;
	if (label && label->defaut == 1)
		label = label->next;
	while (label)
	{
		if (ft_strncmp(label->name, list->data, ft_strlen(list->data)) == 0)
			return ;
		label = label->next;
	}
	push_label(master, list, 0);
}

void	create_label_null(t_asm *master, t_token *info)
{
	if ((master->parser.define_label = (t_list_label*)malloc(sizeof(t_list_label))))
	{
		ft_printf("CRASH a securiser et free tout le reste ici"); //icicicicicici
		exit (0);
	}
	ft_bzero(master->parser.define_label, sizeof(t_list_label));
	master->parser.define_label->defaut = 1;
	master->parser.define_label->info = info;
	//master->parser.begin_label = master->parser.define_label;
}

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

void	push_front_token_on_label(t_asm *master, t_token *data)
{
	t_list_label	*front_list;

	front_list = create_label_defaut(1, data);
	if (master->parser.define_label)
	{
		front_list->next = master->parser.define_label;
		master->parser.define_label = front_list;
	}
	else
		master->parser.define_label = front_list;
	front_list->info = data;
}

void	push_info(t_asm *master, t_token *data)
{
	t_list_label	*label;
	t_list_label	*save;

	label = master->parser.define_label;
	save = master->parser.define_label;
	while (label)
	{
		if (label->define_parser == 1)
			save = label;
		label = label->next;
	}
	label = save;
	if (label->define_parser == 1)
		push_back_token_on_label(label, data);
	else
		push_front_token_on_label(master, data);
}

void	create_token_label(t_asm *master, t_token *list)
{
	while (list)
	{
		if (list->kind != SEPARATOR && list->kind != BAD && list->kind != COMMENT)
		{
			if (master->parser.define_label)
				push_info(master, list);
			else
				push_front_token_on_label(master, list);
		}
		list = list->next;
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
		if (!verif_bad(master, list) && verif_separator(master, master->tab_op[i], list))
		{
			if (list->next == NULL || master->tab_op[i].nb_arg > nb_param(list->next))
				print_error_parser_param(master, "missing declared parameters in function", list->data, list);
			else if (master->tab_op[i].nb_arg != nb_param(list->next))
				print_error_parser_param(master, "too many parameters declared in function", list->data, list);
			if (verif_type_param(master, list->next, master->tab_op[i], -1))
				create_token_label(master, list);
		}
	}
	else if (list->kind == BAD)
		print_error_parser_param(master, "error name function", list->data, list);
}

void	parser_label_or_function(t_asm *master, t_token **token)
{
	t_token			*list;
	t_list_label	*begin_label;

	list = token[0];
	begin_label = master->parser.define_label;
	if (begin_label && begin_label->defaut == 1)
		begin_label = begin_label->next;
	while (list)
	{
		if (list->kind == LABEL_DECLARATION)
		{
			if (search_label(begin_label, list->data) && list->column == 1)
				print_error_parser_param(master, "label deja declarer", list->data, list);
			else if (list->column > 1)
				print_error_parser_param(master, "just one label declaration on line", list->data, list);
			else
				push_label(master, list, 1);
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
		while (list)
    	{
			if (list->kind == COMMENT)
				break;
			else if (list->kind == HEADER_NAME || list->kind == HEADER_COMMENT)
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
	if (master->parser.define_label->defaut == 1)
		verif_declaration_label(master, master->parser.define_label->next);
	else
		verif_declaration_label(master, master->parser.define_label);
	if (master->error_parser == 1)
		ft_printf("{RED}%d{END} error detected\n", master->error_parser);
    else if (master->error_parser > 1)
		ft_printf("{RED}%d{END} errors detected\n", master->error_parser);
	return (0);
}
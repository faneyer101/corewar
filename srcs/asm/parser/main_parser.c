/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main_parser.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: faneyer <faneyer@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/16 23:23:14 by faneyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/18 08:19:29 by faneyer     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../../includes/asm.h"

void	declare_label_param(t_asm *master, t_token *list)
{
	t_list_label *label;
	
	label = master->parser.define_label;
	while (label)
	{
		if (ft_strncmp(label->name, list->data, ft_strlen(list->data)) == 0)
			return ;
		label = label->next;
	}
	push_label(master, list, 0);
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
			verif_type_param(master, list->next, master->tab_op[i], -1);
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
	while (list)
	{
		if (list->kind == LABEL_DECLARATION)
		{
			if (search_label(master->parser.define_label, list->data) && list->column == 1)
				print_error_parser_param(master, "label deja declarer", list->data, list);
			else if (list->column > 1)
				print_error_parser_param(master, "just one label declaration on line", list->data, list);
			else
				push_label(master, list, 1);
		}
		else if (list->kind == FONCTION || list->kind == BAD)
		{
			parser_function_and_param(master, list, 0);
			break;
		}
		if (list)
			list=list->next;
	}
}

int     main_parser(t_asm *master)
{
	int		i;
	t_token	*list;

	i = -1;
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
	verif_declaration_label(master, master->parser.define_label);
	if (master->error_parser == 1)
		ft_printf("{RED}%d{END} error detected\n", master->error_parser);
    else if (master->error_parser > 1)
		ft_printf("{RED}%d{END} errors detected\n", master->error_parser);
	return (0);
}
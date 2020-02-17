/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main_parser.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: faneyer <faneyer@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/16 23:23:14 by faneyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/17 20:51:15 by faneyer     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../../includes/asm.h"

void	print_error_parser_param(t_asm *master, char *msg_error, char *error, t_token *list)
{	
	ft_printf("parser[{GREEN}line:%d{END}][{GREEN}column:%d{END}]%s|{RED}%s{END}|\n", list->numline, list->column, msg_error, error);
	master->error_parser++;
}

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

static t_list_label	*create_label(t_asm *master, t_token *list, int define)
{
	t_list_label	*box;
	(void)master;

	if (!(box = (t_list_label*)malloc(sizeof(t_list_label))))
		return (NULL);
	ft_bzero(box, sizeof(t_list_label));
	if (!(box->name = ft_strndup(list->data, ft_strlen(list->data))))
		return (NULL);

	box->info = list;
	box->define_parser = define;
	return (box);
}

void	push_label(t_asm *master, t_token *token, int define)
{
	t_list_label	*list;

	list = master->parser.define_label;
	if (list)
	{
		while (list->next)
		{
			if (ft_strncmp(list->name, token->data, ft_strlen(token->data)) == 0 && ft_strlen(token->data) == ft_strlen(list->name) && define == 1)
			{
				list->define_parser = define;
				return ;
			}
			list = list->next;
		}
		if (ft_strncmp(list->name, token->data, ft_strlen(token->data)) == 0 && ft_strlen(token->data) == ft_strlen(list->name) && define == 1)
		{
			list->define_parser = define;
			return ;
		}
		if (!(list->next = create_label(master, token, define)))
            printf_error_lexer(master, "Crash allocate for memory\n"); //voir pour changer fonction
	}
	else
		if (!(master->parser.define_label = create_label(master, token, define)))
            printf_error_lexer(master, "Crash allocate for memory\n"); //voir pour changer fonction
}

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

void	verif_type_param(t_asm *master, t_token *list, t_op function, int i)
{
	while (list)
	{
		if (list->kind == BAD)
		{
			print_error_parser_param(master, "error type of param in function", function.name, list);
			break;
		}
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
				print_error_parser_param(master, "error type of param", list->data, list);
		}
		list = list->next;
	}
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
		print_error_parser_param(master, "missing declared parameters in function", list->data, list);
	else if (nb_param(list->next) > function.nb_arg)
		print_error_parser_param(master, "too many parameters declared in function", list->data, list);
	else
		print_error_parser_param(master, "need separator ',' for separate param on function", list->data, list);
	return (FALSE);
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
			if (search_label(master->parser.define_label, list->data))
				print_error_parser_param(master, "label deja declarer", list->data, list);
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

void	verif_declaration_label(t_asm *master, t_list_label *label)
{
	t_list_label	*list;

	list = label;
	while (list)
	{
		if (list->define_parser == 0)
				print_error_parser_param(master, "label don't declared", list->info->data, list->info);
		list = list->next;
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
			else
			{
				ft_printf("parser|il manque quelques choses?????[%s][%d][%d][{CYAN}%d{END}]\n", list->data, list->numline, list->column, list->kind);
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
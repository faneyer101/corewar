/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main_parser.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: faneyer <faneyer@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/16 23:23:14 by faneyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/17 17:02:53 by faneyer     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../../includes/asm.h"

int		search_label(t_list_label *label, char *str)
{
	while (label)
	{
		if (ft_strncmp(label->name, str, ft_strlen(str) - 1) == 0)
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
	if (!(box->name = ft_strndup(list->data, ft_strlen(list->data) - 1)))
		return (NULL);
	box->define_parser = define;
	return (box);
}

void	push_label(t_asm *master, t_token *token, int define)
{
	t_list_label	*list;

	list = master->define_label;
	if (list)
	{
		while (list->next != NULL)
			list = list->next;
		if (!(list->next = create_label(master, token, define)))
            printf_error_lexer(master, "Crash allocate for memory\n");
		list = list->next;
	}
	else
		if (!(master->define_label = create_label(master, token, define)))
            printf_error_lexer(master, "Crash allocate for memory\n");
}

void	parser_function_and_param(t_asm *master, t_token *list)
{
	(void)master;
	while (list)
	{
		list = list->next;
	}
}

void	parser_label_or_function(t_asm *master, t_token **token)
{
	t_token			*list;
	t_list_label	*begin_label;

	list = token[0];
	begin_label = master->define_label;
	while (list)
	{
		if (list->kind == LABEL_DECLARATION)
		{
			if (search_label(master->define_label, list->data))
			{
				ft_printf("parser[{GREEN}line:%d{END}][{GREEN}column:%d{END}]label deja declarer|{RED}%s{END}|\n", list->numline, list->column, list->data);
				master->error_parser++;
			}
			else
				push_label(master, list, 1);
		}
		else if (list->kind == FONCTION)
		{
			parser_function_and_param(master, list);
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
				ft_printf("parser[{GREEN}line:%d{END}][{GREEN}column:%d{END}]Error of syntax|{RED}%s{END}|\n", list->numline, list->column, list->data);
				master->error_parser++;
			}
			else if (list->kind == LABEL_DECLARATION || list->kind == FONCTION)
				parser_label_or_function(master, &list);
			else
			{
				ft_printf("parser|il manque quelques choses?????[%s][%d][%d][{CYAN}%d{END}]\n", list->data, list->numline, list->column, list->kind);
			}
			if (list)
        		list = list->next;
    	}
	}
	if (master->error_parser == 1)
		ft_printf("{RED}%d{END} error detected\n", master->error_parser);
    else if (master->error_parser > 1)
		ft_printf("{RED}%d{END} errors detected\n", master->error_parser);
	return (0);
}
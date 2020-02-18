/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   toolsparser2.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: faneyer <faneyer@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/17 20:59:44 by faneyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/18 19:52:17 by faneyer     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../../includes/asm.h"

void	verif_declaration_label(t_asm *master, t_list_label *label)
{
	t_list_label	*list;

	list = label;
	while (list)
	{
		if (list->define_parser == 0)
			print_error_parser_label(master, "label don't declared", list->name, list);
		list = list->next;
	}
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
	box->define_parser = define;
	box->numline = list->numline;
	box->column = list->column;
	return (box);
}

void	push_label(t_asm *master, t_token *token, int define)
{
	t_list_label	*list;

	list = master->parser.define_label;
	if (list && list->defaut == 1)
		list = list->next;
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
	{
		if (!(master->parser.define_label = create_label(master, token, define)))
            printf_error_lexer(master, "Crash allocate for memory\n"); //voir pour changer fonction
	//	master->parser.begin_label = master->parser.define_label;
	}
}

int	print_error_parser_param(t_asm *master, char *msg_error, char *error, t_token *list)
{	
	ft_printf("parser[{GREEN}line:%d{END}][{GREEN}column:%d{END}]%s|{RED}%s{END}|\n", list->numline, list->column, msg_error, error);
	master->error_parser++;
	return(0);
}

int	print_error_parser_label(t_asm *master, char *msg_error, char *error, t_list_label *list)
{	
	ft_printf("parser[{GREEN}line:%d{END}][{GREEN}column:%d{END}]%s|{RED}%s{END}|\n", list->numline, list->column, msg_error, error);
	master->error_parser++;
	return(0);
}
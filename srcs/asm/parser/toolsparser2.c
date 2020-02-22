/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   toolsparser2.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: faneyer <faneyer@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/17 20:59:44 by faneyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/23 04:18:49 by faneyer     ###    #+. /#+    ###.fr     */
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
	//	ft_printf("{RED}Verif undefine{END}|label: %s|define: %d|\n", list->name, list->define_parser);
		if (list->define_parser == 0)
			print_error_parser_label(master, "label don't declared", list->name, list);
		list = list->unext;
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
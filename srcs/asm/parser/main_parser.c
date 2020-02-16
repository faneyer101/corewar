/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main_parser.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: faneyer <faneyer@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/16 23:23:14 by faneyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/17 03:53:01 by faneyer     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../../includes/asm.h"

void	parser_label_function(t_asm *master, t_token *list)
{
	int	label;
	int	function;

	label = 0;
	function = 0;
	while (list)
	{
		if (list->kind == BAD && label == 0 && function == 0)
		{
			ft_printf("Error of syntax label or name function[line:%d][column:%d]|{RED}%s{END}|\n", list->numline, list->column, list->data);
			master->error_parser++;
			break;
		}
		else if (list->kind == BAD && label == 1 && function == 0)
		{
			ft_printf("Error of syntax name function[line:%d][column:%d]|{RED}%s{END}|\n", list->numline, list->column, list->data);
			master->error_parser++;
			break;
		}
		else if (list->kind == LABEL_DECLARATION)
			label++;
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
			{
				parser_header(master, list);
				break;
			}	
		//	else if (list->kind == BAD)
		//	{
		//		ft_printf("Error of syntax label or name function[line:%d][column:%d]|%s|\n", list->numline, list->column, list->data[0], list->data);
		//		master->error_parser++;
		//		break;
		//	}
			else
			{
				parser_label_function(master, list);
				break;
			}	
			//else if (list->kind == LABEL_DECLARATION)
			//verif labbel
			//verif op code
        	list = list->next;
    	}
	}
	if (master->error_parser > 0)
		ft_printf("nomber error: {RED}%d{END}\n", master->error_parser);
//	write(0, &master->header, sizeof(t_header));
//	write(0, "\n", 1);
//	printf("header|%s|\n", master->header.prog_name);
    return (0);
}
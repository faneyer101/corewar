/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main_parser.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: faneyer <faneyer@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/16 23:23:14 by faneyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/17 02:07:37 by faneyer     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../../includes/asm.h"

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
			if (list->kind == HEADER_NAME || list->kind == HEADER_COMMENT)
				parser_header(master, list);
 			
			//verif header
			//verif labbel
			//verif op code
        	list = list->next;
    	}
	}
//	write(0, &master->header, sizeof(t_header));
//	write(0, "\n", 1);
//	printf("header|%s|\n", master->header.prog_name);
    return (0);
}
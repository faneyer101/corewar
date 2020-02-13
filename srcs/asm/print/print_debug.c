/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print_debug.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: faneyer <faneyer@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/09 01:23:48 by faneyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/13 18:49:22 by faneyer     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../../includes/asm.h"

void    print_token(t_asm *master)
{
    int		i;
    t_token	*list;

	i = 0;
	while (i < master->numline)
	{	
		if (master->tab_token[i])
    		list = master->tab_token[i];
		else
		{
			i++;
			continue;
		}
		while (list)
    	{
        	ft_printf("[%d]Valeur LEXEME ==> %d | ", i, list->kind);
        	ft_printf("{RED}Data: |%s|{END} Line %d | column %d\n", list->data,
				list->numline, list->column);
        	list = list->next;
    	}
		i++;
	}
}

void    print_buff_read(t_asm *master)
{
    int i;

    i = -1;
    while (++i < master->size_read_total)
    {
        if (master->buff_read[i] && master->buff_read[i] == '\n' && ++master->numline)
            continue;
        else if (delimiter(master->buff_read[i], "s"))
			ft_printf("{CYAN}|%c|C'est un space{END}\n", master->buff_read[i]);
		else if (ft_isdigit(master->buff_read[i]))
			ft_printf("{BLUE}|%c|C'est un chiffre{END}\n", master->buff_read[i]);
		else if (ft_isalpha(master->buff_read[i]))
			ft_printf("{RED}|%c|C'est un char{END}\n", master->buff_read[i]);
		else
			ft_printf("{GREEN}|%c|C'est un delimiteur{END}\n", master->buff_read[i]);
    }
}
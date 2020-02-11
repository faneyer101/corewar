/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print_token.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: faneyer <faneyer@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/09 01:23:48 by faneyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/11 19:58:28 by faneyer     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../../includes/asm.h"
/*
void    print_token(t_asm *master)
{
    t_lexer *list;

    list = master->lexer;
    while (list)
    {
        ft_printf("String or digit or delimiter: %c|%c|%c ==> ",
            list->string, list->digit, list->delimiter);
        ft_printf("Data: %s\n", list->data);
        list = list->next;
    }
}*/

void    print_lexeme(t_asm *master)
{
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
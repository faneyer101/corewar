/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print_token.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: faneyer <faneyer@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/09 01:23:48 by faneyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/09 04:59:26 by faneyer     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../../includes/asm.h"

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
}
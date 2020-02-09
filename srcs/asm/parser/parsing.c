/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parsing.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: faneyer <faneyer@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/06 08:20:27 by faneyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/09 21:45:16 by faneyer     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../../includes/asm.h"

int     main_parser(t_asm *master)
{
    t_lexer *list;

    list = master->lexer;
	while (list)
    {
        if (delimiter(list->data[0], "#") && list->data[1] == '\0')
            list = list->next->next;
        else
            break;
    }
    return (0);
}
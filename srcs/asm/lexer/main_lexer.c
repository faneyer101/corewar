/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main_lexer.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: faneyer <faneyer@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/10 16:33:44 by faneyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/10 19:04:59 by faneyer     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../../includes/asm.h"

int main_lexer2(t_asm *master, int i) // i = -1
{
    t_token token;

    ft_bzero(&token, sizeof(t_token));
    while (++i < master->size_read_total)
    {
        //ft_printf("------DEPART LEXER/TOKEN-----\n|%s|\n|%c|\n|%d|\n", master->buff_read, master->buff_read[i], i);
        if (master->buff_read[i] == '\n' && ++master->numline)
            continue;
        if (delimiter(master->buff_read[i], "s"))
            continue;
        //ft_printf("------MAIN APRES SPACE/\n-----\n|%s|\n|%c|\n|index chaine: %d|Numero de ligne: %d|\n", master->buff_read, master->buff_read[i], i, master->numline);
        
        
    }
    return (0);
}
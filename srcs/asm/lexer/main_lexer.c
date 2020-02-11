/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main_lexer.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: faneyer <faneyer@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/10 16:33:44 by faneyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/11 11:12:30 by faneyer     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../../includes/asm.h"

int main_lexer2(t_asm *master, int i) // i = -1
{
    t_token token;

    ft_bzero(&token, sizeof(t_token));
    ft_printf("%d\n", master->size_read_total);
    while (++i < master->size_read_total)
    {
      //  ft_printf("------DEPART LEXER/TOKEN-----\n|%s|\n|%c|\n|%d|\n", master->buff_read, master->buff_read[i], i);
        if (master->buff_read[i] && master->buff_read[i] == '\n' && ++master->numline)
            continue;
        else if (delimiter(master->buff_read[i], "s"))
            continue;
		else if (ft_isdigit(master->buff_read[i]))
			ft_printf("|%c|C'est un chiffre\n", master->buff_read[i]);
		else if (ft_isalpha(master->buff_read[i]))
			ft_printf("|%c|C'est un char\n", master->buff_read[i]);
		else
			ft_printf("|%c|C'est autre\n", master->buff_read[i]);
    }
    return (0);
}
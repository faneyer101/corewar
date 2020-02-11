/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main_lexer.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: faneyer <faneyer@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/10 16:33:44 by faneyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/11 20:02:21 by faneyer     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../../includes/asm.h"
/*
static void		push_token(t_asm *master, char *type, char *data)
{
	
}

void	token_space(char *lexeme, int i)
{
	push_token(master);
}
*/
int 	main_lexer2(t_asm *master, int i) // i = -1
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
           // token_space(master->buff_read, i);
			ft_printf("{CYAN}|%c|C'est un space{END}\n", master->buff_read[i]);
            //continue;
		else if (ft_isdigit(master->buff_read[i]))
			ft_printf("{BLUE}|%c|C'est un chiffre{END}\n", master->buff_read[i]);
		else if (ft_isalpha(master->buff_read[i]))
			ft_printf("{RED}|%c|C'est un char{END}\n", master->buff_read[i]);
		else
			ft_printf("{GREEN}|%c|C'est un delimiteur{END}\n", master->buff_read[i]);
    }
    return (0);
}
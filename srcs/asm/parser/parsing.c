/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parsing.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: faneyer <faneyer@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/06 08:20:27 by faneyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/11 19:42:26 by faneyer     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../../includes/asm.h"

/*
int    gestion_token_comment(t_lexer **list)
{
	if (delimiter(list[0]->data[0], "#") && list[0]->data[1] == '\0')
	{
		list[0] = list[0]->next->next;
		return (TRUE);
	}
    return (FALSE);
}

int     main_parser(t_asm *master)
{
    t_lexer *list;

    list = master->lexer;
    while (list)
    {
		printf("DEBUT BOUCLE |%s|\n", list->data);
        if (gestion_token_comment(&list))
		{
			printf("COMMENT passer |%s|\n", list->data);
            continue;
		}
       // else if (gestion_token_comment)
        //header
        //code asm
        list = list->next;
    }
    return (0);
}*/
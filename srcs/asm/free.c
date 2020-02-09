/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   free.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: faneyer <faneyer@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/09 04:45:56 by faneyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/09 12:57:01 by faneyer     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/asm.h"

void    free_list_lexer(t_asm *master)
{
    t_lexer *next_list;

	next_list = master->lexer->next;
	while (master->lexer != NULL)
	{
		free(master->lexer->data);
		master->lexer->next = NULL;
		free(master->lexer);
		master->lexer = next_list;
		if (next_list != NULL)
			next_list = next_list->next;
		else
			next_list = NULL;
	}
}

void	free_split(t_asm *master, int i)
{
	while (master->split_read[i])
	{
		ft_strdel(&master->split_read[i]);
		i++;
	}
	ft_strdel(&master->split_read[i]);
	master->split_read = NULL;
	free(master->split_read);
}
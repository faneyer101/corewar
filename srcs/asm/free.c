/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   free.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: faneyer <faneyer@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/09 04:45:56 by faneyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/11 19:53:56 by faneyer     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/asm.h"

void    free_list_lexer(t_asm *master)
{
    t_token *next_list;

	next_list = master->bigin_token->next;
	while (master->bigin_token != NULL)
	{
		free(master->bigin_token->data);
		master->bigin_token->next = NULL;
		free(master->bigin_token);
		master->bigin_token = next_list;
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
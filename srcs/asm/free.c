/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   free.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: faneyer <faneyer@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/09 04:45:56 by faneyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/13 07:21:28 by faneyer     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/asm.h"

void    free_tab_token(t_asm *master)
{
	int		i;
    t_token *next_list;

	i = -1;
	while (++i < master->numline)
	{
		next_list = master->tab_token[i]->next;
		while (master->tab_token[i] != NULL)
		{
			free(master->tab_token[i]->data);
			master->tab_token[i]->next = NULL;
			free(master->tab_token[i]);
			master->tab_token[i] = next_list;
			if (next_list != NULL)
				next_list = next_list->next;
			else
				next_list = NULL;
		}
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
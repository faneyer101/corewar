/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   free.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: faneyer <faneyer@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/09 04:45:56 by faneyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/25 12:06:32 by faneyer     ###    #+. /#+    ###.fr     */
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
		if (master->tab_token[i] == NULL)
			continue;
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
	free(master->tab_token);
}

void	free_undefine_label(t_asm *master)
{
	t_list_label	*next_label;

	if (master->parser.define_label->unext)
		next_label = master->parser.define_label->unext;
	while (master->parser.define_label)
	{
		if (master->parser.define_label->define_parser == 0)
		{
			ft_strdel(&master->parser.define_label->name);
			master->parser.define_label->unext = NULL;
			free(master->parser.define_label);
		}
			master->parser.define_label = next_label;
			if (next_label)
				next_label = next_label->unext;
			else
				next_label = NULL;
	}
}

void	free_define_label(t_asm *master)
{
	t_list_label	*next_label;

	if (master->parser.define_label && master->parser.define_label->dnext)
		next_label = master->parser.define_label->dnext;
	while (master->parser.define_label)
	{
		ft_strdel(&master->parser.define_label->name);
		master->parser.define_label->dnext = NULL;
		free(master->parser.define_label);
		master->parser.define_label = next_label;
		if (next_label)
			next_label = next_label->dnext;
		else
			next_label = NULL;
	}
}
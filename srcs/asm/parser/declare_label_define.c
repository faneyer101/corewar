/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   declare_label_define.c                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: faneyer <faneyer@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/19 16:39:45 by faneyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/26 19:19:19 by faneyer     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../../includes/asm.h"

static t_list_label	*create_label_define(t_token *list)
{
	t_list_label	*box;

	if (!(box = (t_list_label*)malloc(sizeof(t_list_label))))
		return (NULL);
	ft_bzero(box, sizeof(t_list_label));
	if (!(box->name = ft_strndup(list->data, ft_strlen(list->data))))
		return (NULL);
	box->define_parser = 1;
	box->numline = list->numline;
	box->column = list->column;
	return (box);
}

static void	    push_back_label_define(t_asm *master, t_token *data, t_list_label *undefine)
{
	t_list_label *define;

	define = master->parser.define_label;
	if (define)
	{
		while (define->dnext)
			define = define->dnext;
		if (undefine == NULL)
			define->dnext = create_label_define(data);
		else
			define->dnext = undefine;
		define->dnext->define_parser = 1;
		master->parser.curent_label = define->dnext;
	}
	else
	{
		if (undefine == NULL)
			master->parser.define_label = create_label_define(data);
		else
		{
			undefine->define_parser = 1;
			master->parser.define_label = undefine;
		}
		master->parser.curent_label = master->parser.define_label;
	}
}

void			declare_label_define(t_asm *master, t_token *token)
{
	t_list_label *undefine;

	undefine = master->parser.undefine_label;
	while (undefine)
	{
		if (ft_strcmp(undefine->name, token->data) == 0 && ft_strlen(undefine->name) == ft_strlen(token->data))
			break;
		undefine = undefine->unext;
	}
	if (undefine)
	{
		push_back_label_define(master, token, undefine);
	}
	else
	{
		push_back_label_define(master, token, NULL);
	}
}

t_list_label	*create_label_undefine(t_token *data)
{
	t_list_label	*box;

	if (!(box = (t_list_label*)malloc(sizeof(t_list_label))))
		return (NULL);	////////icidiicicicicicicicicic
	ft_bzero(box, sizeof(t_list_label));
	if (!(box->name = ft_strndup(data->data, ft_strlen(data->data))))
		return (NULL);
	return (box);
}

void	push_undefine_label(t_asm *master, t_token *data)
{
	t_list_label *undefine;

	undefine = master->parser.undefine_label;
	if (master->parser.undefine_label)
	{
		if(!search_label_undefine(master->parser.undefine_label, data))
		{
			while (undefine->unext)
				undefine = undefine->unext;
			undefine->unext = create_label_undefine(data);
		}
	}	
	else
		master->parser.undefine_label = create_label_undefine(data);
}
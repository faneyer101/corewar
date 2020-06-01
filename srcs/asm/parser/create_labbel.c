/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_labbel.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faneyer <faneyer@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 15:03:35 by faneyer           #+#    #+#             */
/*   Updated: 2020/05/24 15:07:47 by faneyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/asm.h"

static void			create_label_token(t_token *list, t_token **label)
{
	t_token	*box;

	box = label[0];
	if (box)
	{
		while (box->lnext)
			box = box->lnext;
		box->lnext = list;
	}
	else
		label[0] = list;
}

void				push_back_token_on_label(t_list_label *label,
t_token *token)
{
	t_token	*llist;

	llist = label->info;
	if (llist)
	{
		while (llist->lnext)
			llist = llist->lnext;
		create_label_token(token, &llist);
	}
	else
		create_label_token(token, &label->info);
}

static t_list_label	*create_label_defaut(int define, t_token *data)
{
	t_list_label	*box;

	if (!(box = (t_list_label*)malloc(sizeof(t_list_label))))
		return (NULL);
	ft_bzero(box, sizeof(t_list_label));
	box->define_parser = define;
	box->info = data;
	box->defaut = 1;
	return (box);
}

static void			norme_create_token_label(t_asm *master, t_token *tlist)
{
	if (tlist->kind == REGISTRE && ft_atoi(tlist->data) > REG_NUMBER)
	{
		ft_printf("parser[{GREEN}line:%d{END}][{GREEN}column:%d{END}]",
		tlist->numline, tlist->column);
		ft_printf("the maximum number of registre is %d|{RED}%s{END}|",
		REG_NUMBER, tlist->data);
		ft_printf("\n");
		master->error_parser++;
	}
	else if (master->parser.curent_label)
		push_back_token_on_label(master->parser.curent_label, tlist);
	else
	{
		master->parser.define_label = create_label_defaut(0, tlist);
		master->parser.curent_label = master->parser.define_label;
	}
}

void				create_token_label(t_asm *master, t_token *tlist)
{
	while (tlist)
	{
		if (tlist->kind != SEPARATOR && tlist->kind != BAD &&
		tlist->kind != COMMENT)
		{
			if ((tlist->kind == LABEL_DIRECT ||
			tlist->kind == LABEL_INDIRECT) && ((master->parser.define_label &&
			master->parser.define_label->defaut == 1 &&
			master->parser.define_label->dnext == NULL) ||
			master->parser.define_label == NULL ||
			(master->parser.define_label->name &&
			!search_label_define(master->parser.define_label, tlist))))
				push_undefine_label(master, tlist);
			norme_create_token_label(master, tlist);
		}
		else if (tlist->kind == BAD)
			print_error_parser(master, "bad syntax in function",
			tlist->data, tlist);
		tlist = tlist->next;
	}
}

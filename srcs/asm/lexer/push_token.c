/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_token.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faneyer <faneyer@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 01:47:54 by faneyer           #+#    #+#             */
/*   Updated: 2020/06/04 22:21:15 by faneyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/asm.h"

static t_token	*create_token(t_asm *master, t_lexeme lex, int index, int size)
{
	t_token	*box;

	if (!(box = (t_token*)malloc(sizeof(t_token))))
		return (NULL);
	ft_bzero(box, sizeof(t_token));
	if (!(box->data = ft_strndup(&master->buff_read[index], size)))
	{
		free(box);
		return (NULL);
	}
	box->kind = lex;
	box->column = master->column;
	box->numline = master->numline;
	box->next = NULL;
	master->current = box;
	return (box);
}

void			push_token(t_asm *master, t_lexeme lexeme, int index, int size)
{
	t_token	*list;

	list = master->tab_token[master->numline - 1];
	if (list)
	{
		while (list->next != NULL)
			list = list->next;
		if (!(list->next = create_token(master, lexeme, index, size)))
			printf_error_lexer(master, "Crash allocate for memory\n");
		list = list->next;
	}
	else
	{
		if (!(master->tab_token[master->numline - 1] = create_token(master,
		lexeme, index, size)))
			printf_error_lexer(master, "Crash allocate for memory\n");
	}
}

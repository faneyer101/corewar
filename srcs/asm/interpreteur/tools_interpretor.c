/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_interpretor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faneyer <faneyer@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 14:40:47 by faneyer           #+#    #+#             */
/*   Updated: 2020/06/04 15:49:12 by faneyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/asm.h"

void	search_define_label(t_asm *master, t_token *token, int *index_define,
t_list_label *curent)
{
	t_list_label	*lab;

	lab = master->parser.define_label;
	if (curent)
	{
		while (lab && lab != curent->dnext)
		{
			if (lab->name && ft_strcmp(token->data, lab->name) == 0 &&
			ft_strlen(token->data) == ft_strlen(lab->name))
			{
				index_define[0] = lab->index_define;
				break ;
			}
			lab = lab->dnext;
		}
	}
}

void	init_struct_function(t_asm *master)
{
	master->interpretor.function.octet = 0;
	master->interpretor.function.direct = 0;
	master->interpretor.function.index_declaration = -1;
	master->interpretor.function.index_tab = 16;
	master->interpretor.function.opcode = 16;
}

int		verif_once_define(t_list_label *define, t_list_label *undefine,
		t_token *data, char type)
{
	if (type == 'a')
	{
		if (ft_strcmp(define->name, data->data) == 0 || (undefine != NULL &&
				ft_strcmp(define->name, undefine->name) == 0))
		{
			define->define_parser += 1;
			return (TRUE);
		}
	}
	else if (type == 'b')
	{
		if (define->defaut != 1 && !ft_strcmp(define->name, undefine->name))
		{
			define->define_parser += 1;
			return (TRUE);
		}
	}
	return (FALSE);
}

void	push_back_define_first(t_asm *master, t_list_label *undefine,
		t_token *data)
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

void	define_parser(t_asm *master, t_list_label *define)
{
	define->dnext->define_parser = 1;
	master->parser.curent_label = define->dnext;
}

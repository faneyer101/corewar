/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_interpretor.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faneyer <faneyer@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 14:40:47 by faneyer           #+#    #+#             */
/*   Updated: 2020/05/24 14:43:40 by faneyer          ###   ########lyon.fr   */
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

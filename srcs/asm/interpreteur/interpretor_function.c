/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interpretor_function.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faneyer <faneyer@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 15:29:10 by faneyer           #+#    #+#             */
/*   Updated: 2020/05/24 14:44:22 by faneyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/asm.h"

static void	stock_octet_codage(t_asm *master, t_op tab_op, t_token *token)
{
	t_token			*data;
	int				i;
	unsigned char	octet;

	i = 0;
	data = token;
	octet = 0;
	data = data->lnext;
	while (i < tab_op.nb_arg)
	{
		if (data->kind == LABEL_DIRECT || data->kind == NUM_DIRECT)
			octet += (0b10000000 >> (2 * i)) & 0xFF;
		else if (data->kind == LABEL_INDIRECT || data->kind == NUM_INDIRECT)
			octet += (0b11000000 >> (2 * i)) & 0xFF;
		else if (data->kind == REGISTRE)
			octet += (0b01000000 >> (2 * i)) & 0xFF;
		data = data->lnext;
		i++;
	}
	master->interpretor.code_champ[master->interpretor.index] = octet;
}

static void	stock_opcode(t_asm *master, t_token *token)
{
	master->interpretor.code_champ[master->interpretor.index] =
	master->interpretor.function.opcode;
	master->interpretor.function.index_declaration =
	master->interpretor.index;
	master->interpretor.index++;
	if (master->interpretor.function.octet == 1)
	{
		stock_octet_codage(master,
		master->tab_op[master->interpretor.function.index_tab], token);
		master->interpretor.index++;
	}
}

void		interpretor_function(t_asm *master, t_token *token)
{
	int	i;

	i = 0;
	while (ft_strcmp(master->tab_op[i].name, token->data))
		i++;
	if (master->tab_op[i].octet == 1)
		master->interpretor.function.octet = 1;
	if (master->tab_op[i].size_octet_dir == 1)
		master->interpretor.function.direct = 1;
	master->interpretor.function.index_tab = i;
	master->interpretor.function.opcode = master->tab_op[i].numop;
	stock_opcode(master, token);
}

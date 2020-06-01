/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_interpreteur.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faneyer <faneyer@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 04:09:47 by faneyer           #+#    #+#             */
/*   Updated: 2020/05/24 14:43:27 by faneyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/asm.h"

/*
**	REGISTRE:01	//	DIRECT:10	//	INDIRECT:11
*/

void	interpretor_param(t_asm *master, t_token *token, t_list_label *label)
{
	int long long	calcul;

	calcul = 0;
	if (token->kind == REGISTRE)
		registre(master, &calcul, token);
	else if ((token->kind == NUM_DIRECT &&
	master->interpretor.function.direct == 1) || token->kind == NUM_INDIRECT)
		num_two_octets(master, &calcul, token);
	else if ((token->kind == NUM_DIRECT &&
	master->interpretor.function.direct == 0))
		num_four_octets(master, &calcul, token);
	else if ((token->kind == LABEL_DIRECT &&
	master->interpretor.function.direct == 1) ||
	token->kind == LABEL_INDIRECT)
		labbel_two_octets(master, &calcul, token, label);
	else if (token->kind == LABEL_DIRECT &&
	master->interpretor.function.direct == 0)
		labbel_four_octets(master, &calcul, token, label);
	if (master->interpretor.index > CHAMP_MAX_SIZE)
		size_champ_max(master);
}

void	norme_label_before_dec(t_asm *master, t_token *analyse,
unsigned *calcul, t_list_label *def)
{
	calcul[0] = def->index_define - analyse->index_function;
	master->interpretor.code_champ[analyse->call_index] =
	(calcul[0] >> 24) & 0xFF;
	master->interpretor.code_champ[analyse->call_index + 1] =
	(calcul[0] >> 16) & 0xFF;
	master->interpretor.code_champ[analyse->call_index + 2] =
	(calcul[0] >> 8) & 0xFF;
	master->interpretor.code_champ[analyse->call_index + 3] =
	(calcul[0] >> 0) & 0xFF;
}

void	label_before_declaration(t_asm *master, t_token *analyse,
t_list_label *define)
{
	t_list_label	*def;
	unsigned		calcul;

	def = define;
	while (def)
	{
		if (ft_strcmp(def->name, analyse->data) == 0 &&
		ft_strlen(def->name) == ft_strlen(analyse->data))
			break ;
		def = def->dnext;
	}
	if (def)
	{
		if (master->tab_op[analyse->index_tab_op].size_octet_dir == 1 ||
		analyse->kind == LABEL_INDIRECT)
		{
			calcul = def->index_define - analyse->index_function;
			master->interpretor.code_champ[analyse->call_index] =
			(calcul >> 8) & 0xFF;
			master->interpretor.code_champ[analyse->call_index + 1] =
			(calcul >> 0) & 0xFF;
		}
		else
			norme_label_before_dec(master, analyse, &calcul, def);
	}
}

void	controle(t_asm *master)
{
	t_token	*label;

	label = master->interpretor.wait_label;
	if (master->interpretor.index >= CHAMP_MAX_SIZE)
		print_msg_error_interpretor(master, "Champion program too long");
	else if (ft_strlen(master->interpretor.code_champ) == 0)
		print_msg_error_interpretor(master, "Champion program is null");
	while (label)
	{
		if (master->parser.define_label->defaut == 1)
			label_before_declaration(master, label,
			master->parser.define_label->dnext);
		else
			label_before_declaration(master, label,
			master->parser.define_label);
		label = label->unext;
	}
}

void	main_interpreteur(t_asm *master, t_token *token)
{
	t_list_label	*label;

	label = master->parser.define_label;
	while (label && master->interpretor.index < CHAMP_MAX_SIZE)
	{
		if (label->defaut != 1)
			label->index_define = master->interpretor.index;
		token = label->info;
		while (token && master->interpretor.index < CHAMP_MAX_SIZE)
		{
			if (token->kind == FONCTION)
			{
				init_struct_function(master);
				interpretor_function(master, token);
			}
			else if (token->kind == LABEL_DIRECT ||
			token->kind == LABEL_INDIRECT || token->kind == NUM_DIRECT ||
			token->kind == NUM_INDIRECT || token->kind == REGISTRE)
				interpretor_param(master, token, label);
			if (token)
				token = token->lnext;
		}
		label = label->dnext;
	}
	controle(master);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_interpreteur.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faneyer <faneyer@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 04:09:47 by faneyer           #+#    #+#             */
/*   Updated: 2020/02/28 20:39:13 by faneyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/asm.h"

/*
**	REGISTRE:01	//	DIRECT:10	//	INDIRECT:11
*/

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

void	norme_push_label_undefine(t_asm *master, t_token *t)
{
	master->interpretor.wait_label = t;
	master->interpretor.wait_label->index_tab_op =
	master->interpretor.function.index_tab;
	master->interpretor.wait_label->direct =
	master->interpretor.function.direct;
	master->interpretor.wait_label->index_function =
	master->interpretor.function.index_declaration;
	master->interpretor.wait_label->call_index =
	master->interpretor.index;
	master->interpretor.wait_label->unext = NULL;
}

void	push_label_undefine(t_asm *master, t_token *token)
{
	t_token	*ltoken;

	ltoken = master->interpretor.wait_label;
	if (ltoken)
	{
		while (ltoken->unext != NULL)
			ltoken = ltoken->unext;
		ltoken->unext = token;
		ltoken = ltoken->unext;
		ltoken->direct = master->interpretor.function.direct;
		ltoken->index_tab_op = master->interpretor.function.index_tab;
		ltoken->index_function =
		master->interpretor.function.index_declaration;
		ltoken->call_index = master->interpretor.index;
		ltoken->unext = NULL;
	}
	else
		norme_push_label_undefine(master, token);
}

void	print_error_overflow(t_asm *master, int index, t_token *token,
char *msg)
{
	ft_printf("interpretor[{GREEN}line:%d{END}]", token->numline);
	ft_printf("[{GREEN}column:%d{END}]%s", token->column, msg);
	ft_printf("|{RED}%s{END}|\n", token->data);
	master->interpretor.index += index;
	master->error_traitment++;
}

void	norme_registre(t_asm *master, int long long *calcul, t_token *t)
{
	calcul[0] = ft_atoi(t->data);
	master->interpretor.code_champ[master->interpretor.index] =
	(calcul[0] >> 0) & 0xFF;
	master->interpretor.index++;
}

void	norme_num_two_octets(t_asm *master, int long long *calcul,
t_token *token)
{
	if ((calcul[0] = ft_atoi(token->data)) > UINT_MAX ||
	(token->data[0] == '-' && ft_atoi(&token->data[1]) > UINT_MAX))
		print_error_overflow(master, 2, token,
		"Value max: 4294967295. Size max on the param");
	else
	{
		master->interpretor.code_champ[master->interpretor.index] =
		(calcul[0] >> 8) & 0xFF;
		master->interpretor.code_champ[master->interpretor.index + 1] =
		(calcul[0] >> 0) & 0xFF;
		master->interpretor.index += 2;
	}
}

void	norme_num_four_octets(t_asm *master, long long int *calcul,
t_token *token)
{
	if ((calcul[0] = ft_atoi(token->data)) > UINT_MAX ||
	(token->data[0] == '-' && ft_atoi(&token->data[1]) > UINT_MAX))
		print_error_overflow(master, 4, token,
		"Value max: 4294967295. Size max on the param");
	else
	{
		master->interpretor.code_champ[master->interpretor.index] =
		(calcul[0] >> 24) & 0xFF;
		master->interpretor.code_champ[master->interpretor.index + 1] =
		(calcul[0] >> 16) & 0xFF;
		master->interpretor.code_champ[master->interpretor.index + 2] =
		(calcul[0] >> 8) & 0xFF;
		master->interpretor.code_champ[master->interpretor.index + 3] =
		(calcul[0] >> 0) & 0xFF;
		master->interpretor.index += 4;
	}
}

void	nornme_labbel_two_octets(t_asm *master, long long int *calcul,
t_token *token, t_list_label *label)
{
	int	index_define;

	index_define = -1;
	search_define_label(master, token, &index_define, label);
	if (index_define >= 0)
	{
		calcul[0] =
		index_define - master->interpretor.function.index_declaration;
		master->interpretor.code_champ[master->interpretor.index] =
		((calcul[0] >> 8) & 0xFF);
		master->interpretor.code_champ[master->interpretor.index + 1] =
		((calcul[0] >> 0) & 0xFF);
	}
	else
		push_label_undefine(master, token);
	master->interpretor.index += 2;
}

void	nornme_labbel_four_octets(t_asm *master, long long int *calcul,
t_token *token, t_list_label *label)
{
	int	index_define;

	index_define = -1;
	search_define_label(master, token, &index_define, label);
	if (index_define >= 0)
	{
		calcul[0] =
		index_define - master->interpretor.function.index_declaration;
		master->interpretor.code_champ[master->interpretor.index] =
		(calcul[0] >> 24) & 0xFF;
		master->interpretor.code_champ[master->interpretor.index + 1] =
		(calcul[0] >> 16) & 0xFF;
		master->interpretor.code_champ[master->interpretor.index + 2] =
		(calcul[0] >> 8) & 0xFF;
		master->interpretor.code_champ[master->interpretor.index + 3] =
		(calcul[0] >> 0) & 0xFF;
	}
	else
		push_label_undefine(master, token);
	master->interpretor.index += 4;
}

void	size_champ_max(t_asm *master)
{
	ft_printf("{RED}SIZE TOO LONG{END} %d. Size Max: %d\nA FREEEEEEEEEEEE!!!!!!!!!!!!!!!!!!!!!\n",
	master->interpretor.index, CHAMP_MAX_SIZE);
	exit(0);
}

void	interpretor_param(t_asm *master, t_token *token, t_list_label *label)
{
	int				index_define;
	int long long	calcul;

	index_define = -1;
	calcul = 0;
	if (token->kind == REGISTRE)
		norme_registre(master, &calcul, token);
	else if ((token->kind == NUM_DIRECT &&
	master->interpretor.function.direct == 1) || token->kind == NUM_INDIRECT)
		norme_num_two_octets(master, &calcul, token);
	else if ((token->kind == NUM_DIRECT &&
	master->interpretor.function.direct == 0))
		norme_num_four_octets(master, &calcul, token);
	else if ((token->kind == LABEL_DIRECT &&
	master->interpretor.function.direct == 1) ||
	token->kind == LABEL_INDIRECT)
		nornme_labbel_two_octets(master, &calcul, token, label);
	else if (token->kind == LABEL_DIRECT &&
	master->interpretor.function.direct == 0)
		nornme_labbel_four_octets(master, &calcul, token, label);
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
	{
		ft_printf("FREE ET EXIT 0 CAR PROG TROP GRAND\n");
		exit(0);
	}
	else if (ft_strlen(master->interpretor.code_champ) == 0)
	{
		ft_printf("FREE ET EXIT 0 CAR PROG TROP PETIT\n");
		exit(0);
	}
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

static void	init_struct_function(t_asm *master)
{
	master->interpretor.function.octet = 0;
	master->interpretor.function.direct = 0;
	master->interpretor.function.index_declaration = -1;
	master->interpretor.function.index_tab = 16;
	master->interpretor.function.opcode = 16;
}

void		main_interpreteur(t_asm *master, t_token *token)
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

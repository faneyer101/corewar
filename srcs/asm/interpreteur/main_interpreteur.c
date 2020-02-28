/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_interpreteur.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faneyer <faneyer@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 04:09:47 by faneyer           #+#    #+#             */
/*   Updated: 2020/02/28 09:45:15 by faneyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */


#include "../../../includes/asm.h"

/*
**	REGISTRE:01	//	DIRECT:10	//	INDIRECT:11
*/

void	search_define_label(t_asm *master, t_token *token, int *index_define, t_list_label *curent)
{
	t_list_label	*lab;

	lab = master->parser.define_label;
	if (curent)
	{
		while (lab && lab != curent->dnext)
		{
			if (lab->name && ft_strcmp(token->data, lab->name) == 0 && ft_strlen(token->data) == ft_strlen(lab->name))
			{
			//	ft_printf("icicicic|%s|%s|%d|\n", token->data, lab->name, lab->index_define), fflush(stdout);
				index_define[0] = lab->index_define;
				break;
			}
			lab = lab->dnext;
		}
	}
}

void	push_label_undefine(t_asm *master, t_token *token)
{
	t_token	*ltoken;

	ltoken = master->interpretor.wait_label;
	//printf("START Push undefine |%p|%p|%d|\n", ltoken, master->interpretor.wait_label, master->parser.size_prog), fflush(stdout);
	if (ltoken)
	{
		while (ltoken->unext != NULL)
		{
			ltoken = ltoken->unext;
		}
		//ft_printf("{GREEN}PUSH 1 UNDEFINE {END}|%s|%d|\n", token->data, master->interpretor.function.index_tab);
		ltoken->unext = token;
		ltoken = ltoken->unext;
		ltoken->direct = master->interpretor.function.direct;
		ltoken->index_tab_op = master->interpretor.function.index_tab;
		ltoken->index_function = master->interpretor.function.index_declaration;
		ltoken->call_index = master->interpretor.index;
		ltoken->unext = NULL;
	}
	else
	{
		//ft_printf("{GREEN}PUSH 2 UNDEFINE {END}|%s|%d|\n", token->data, master->interpretor.function.index_tab);
		master->interpretor.wait_label = token;
		master->interpretor.wait_label->index_tab_op = master->interpretor.function.index_tab;
		master->interpretor.wait_label->direct = master->interpretor.function.direct;
		master->interpretor.wait_label->index_function = master->interpretor.function.index_declaration;
		master->interpretor.wait_label->call_index = master->interpretor.index;
		master->interpretor.wait_label->unext = NULL;
	}
	//printf("FIN Push undefine |%p|\n", master->interpretor.wait_label), fflush(stdout);

}

void	print_error_overflow(t_asm *master, char *msg, int index, t_token *token)
{
	ft_printf("interpretor[{GREEN}line:%d{END}][{GREEN}column:%d{END}]%s|{RED}%s{END}|\n", token->numline, token->column, msg, token->data);
	master->interpretor.index += index;
	master->error_traitment++;
}

void	interpretor_param(t_asm *master, t_token *token, t_list_label *label)
{
	int			index_define;
	int long long	calcul;

	index_define = -1;
	calcul = 0;
	if (token->kind == REGISTRE)
	{
		calcul = ft_atoi(token->data);
		master->interpretor.code_champ[master->interpretor.index] = (calcul >> 0) & 0xFF;
		master->interpretor.index++;
	}
	else if ((token->kind == NUM_DIRECT && master->interpretor.function.direct == 1) || token->kind == NUM_INDIRECT)
	{
		if ((calcul = ft_atoi(token->data)) > UINT_MAX || (token->data[0] == '-' && ft_atoi(&token->data[1]) > UINT_MAX))
		{
			print_error_overflow(master, "Value max: 4294967295. Size max on the param", 2, token);
		}
		else
		{
			master->interpretor.code_champ[master->interpretor.index] = (calcul >> 8) & 0xFF;
			master->interpretor.code_champ[master->interpretor.index + 1] = (calcul >> 0) & 0xFF;
			master->interpretor.index += 2;
		}
	}
	else if ((token->kind == NUM_DIRECT && master->interpretor.function.direct == 0))
	{
		if ((calcul = ft_atoi(token->data)) > UINT_MAX || (token->data[0] == '-' && ft_atoi(&token->data[1]) > UINT_MAX))
		{
			print_error_overflow(master, "Value max: 4294967295. Size max on the param", 4, token);
		}
		else
		{
			master->interpretor.code_champ[master->interpretor.index] = (calcul >> 24) & 0xFF;
			master->interpretor.code_champ[master->interpretor.index + 1] = (calcul >> 16) & 0xFF;
			master->interpretor.code_champ[master->interpretor.index + 2] = (calcul >> 8) & 0xFF;
			master->interpretor.code_champ[master->interpretor.index + 3] = (calcul >> 0) & 0xFF;
			master->interpretor.index += 4;
		}
	}
	else if ((token->kind == LABEL_DIRECT && master->interpretor.function.direct == 1) || token->kind == LABEL_INDIRECT)
	{
		search_define_label(master, token, &index_define, label);
		if (index_define >= 0)
		{
			calcul = index_define - master->interpretor.function.index_declaration;
			master->interpretor.code_champ[master->interpretor.index] = ((calcul >> 8) & 0xFF);
			master->interpretor.code_champ[master->interpretor.index + 1] = ((calcul >> 0) & 0xFF);
		}
		else
			push_label_undefine(master, token);
		master->interpretor.index += 2;
	}
	else if (token->kind == LABEL_DIRECT && master->interpretor.function.direct == 0)
	{
		search_define_label(master, token, &index_define, label);
		if (index_define >= 0)
		{
			calcul = index_define - master->interpretor.function.index_declaration;
			master->interpretor.code_champ[master->interpretor.index] = (calcul >> 24) & 0xFF;
			master->interpretor.code_champ[master->interpretor.index + 1] = (calcul >> 16) & 0xFF;
			master->interpretor.code_champ[master->interpretor.index + 2] = (calcul >> 8) & 0xFF;
			master->interpretor.code_champ[master->interpretor.index + 3] = (calcul >> 0) & 0xFF;
		}
		else
			push_label_undefine(master, token);
		master->interpretor.index += 4;
	}
	if (master->interpretor.index > CHAMP_MAX_SIZE)
	{
		ft_printf("{RED}SIZE TOO LONG{END} %d. Size Max: %d\n", master->interpretor.index, CHAMP_MAX_SIZE);
		exit (0);
	}
//ft_printf("{RED}FIN   PARAM{END}|%p|%d|%s|\n", master->interpretor.wait_label, token->kind, token->data);

}

void	label_before_declaration(t_asm *master, t_token *analyse, t_list_label *define)
{
	t_list_label	*def;
	unsigned		calcul;

	def = define;
	while (def)
	{
		if (ft_strcmp(def->name, analyse->data) == 0 && ft_strlen(def->name) == ft_strlen(analyse->data))
			break;
		def = def->dnext;
	}
	if (def)
	{
		if (master->tab_op[analyse->index_tab_op].size_octet_dir == 1 || analyse->kind == LABEL_INDIRECT)
		{
			//calcul = index_define - master->interpretor.function.index_declaration;
			//ft_printf("{YELL}REPRISE LABEL NON DEC |%s| 2 octets {END}|%d|%d|%d|\n", analyse->data, def->index_define, analyse->index_tab_op, def->index_define - analyse->index_function);
	//		ft_printf("{BLUE}REPRISE LABEL NON DEC |%s| 2 octets {YELL} fonction |%s|{END}\n", analyse->data, master->tab_op[analyse->index_tab_op].name);
			calcul = def->index_define - analyse->index_function;
			master->interpretor.code_champ[analyse->call_index] = (calcul >> 8) & 0xFF;
			master->interpretor.code_champ[analyse->call_index + 1] = (calcul >> 0) & 0xFF;
		}
		else
		{
		//	ft_printf("{BLUE}REPRISE LABEL NON DEC |%s| 4 octets {YELL} fonction |%s|{END}\n", analyse->data, master->tab_op[analyse->index_tab_op].name);
			calcul = def->index_define - analyse->index_function;
			//calcul = def->index_define /*- analyse->call_index) + 3*/;
			master->interpretor.code_champ[analyse->call_index] = (calcul >> 24) & 0xFF;
			master->interpretor.code_champ[analyse->call_index + 1] = (calcul >> 16) & 0xFF;
			master->interpretor.code_champ[analyse->call_index + 2] = (calcul >> 8) & 0xFF;
			master->interpretor.code_champ[analyse->call_index + 3] = (calcul >> 0) & 0xFF;
		}
	}
}

void	controle(t_asm *master)
{
	t_token	*label;

	label = master->interpretor.wait_label;
	while (label)
	{
		if (master->parser.define_label->defaut == 1)
		{
		//	ft_printf("{BLUE}LABEL NON DECLARER{END}|%s|%d|\n", label->data, label->index_tab_op);
			label_before_declaration(master, label, master->parser.define_label->dnext);
		}
		else
		{
		//	ft_printf("{BLUE}LABEL NON DECLARER{END}|%s|%d|\n", label->data, label->index_tab_op);
			label_before_declaration(master, label, master->parser.define_label);
		}
		
		label = label->unext;
	}
}

static void	init_struct_function(t_asm *master)
{
	master->interpretor.function.octet = 0;
	master->interpretor.function.direct = 0;
	master->interpretor.function.index_declaration = -1;
	master->interpretor.function.index_tab = 16;	//null de optab
	master->interpretor.function.opcode = 16;		//null de optab
}	
/*
int		verif_undefine_label(t_asm *master)
{
	t_list_label	*undefine;

	undefine = master->parser.undefine_label;
	while (undefine)
	{
		if (undefine->index_define == -1)
			return (TRUE);
		undefine = undefine->unext;
	}
	return (FALSE);
}
*/
void    main_interpreteur(t_asm *master)
{
    t_list_label    *label;
    t_token			*token;

    label = master->parser.define_label;
//	master->interpretor.wait_label = NULL;
    while (label && master->interpretor.index < CHAMP_MAX_SIZE)
    {
		
		if (label->defaut != 1)
            label->index_define = master->interpretor.index;
        token = label->info;
		while (token && master->interpretor.index < CHAMP_MAX_SIZE)
		{
	//	printf("START MAIN |%p|%d|%s|\n", master->interpretor.wait_label, token->kind, token->data);
			if (token->kind == FONCTION)
			{
	//	printf("START Mfun |%p|%d|%s|\n", master->interpretor.wait_label, token->kind, token->data);
				init_struct_function(master);
				interpretor_function(master, label, token);
	//	printf("fin   Mfun |%p|%d|%s|\n", master->interpretor.wait_label, token->kind, token->data);
			}
			else if (token->kind == LABEL_DIRECT || token->kind == LABEL_INDIRECT ||
				token->kind == NUM_DIRECT || token->kind == NUM_INDIRECT || token->kind == REGISTRE)
			{
		//		ft_printf("{GREEN}START Mpar {END}|%p|%d|%s|\n", master->interpretor.wait_label, token->kind, token->data);
				interpretor_param(master, token, label);
		//		ft_printf("{RED}FIN   Mpar {END}|%p|%d|%s|\n", master->interpretor.wait_label, token->kind, token->data);
			}
		//	printf("fin  MAIN |%p|\n", master->interpretor.wait_label);
			if (token)
				token = token->lnext;
		}
    	label = label->dnext;
    }
	if (master->interpretor.index >= CHAMP_MAX_SIZE)
	{
		ft_printf("FREE ET EXIT 0 CAR PROG TROP GRAND\n");
		exit (0);
	}
	else if (ft_strlen(master->interpretor.code_champ) == 0)
	{
		ft_printf("FREE ET EXIT 0 CAR PROG TROP PETIT\n");
		exit (0);
	}
	//if (verif_undefine_label(master))	
	//	ft_printf("TA mere la chauve\n");
	controle(master);
}
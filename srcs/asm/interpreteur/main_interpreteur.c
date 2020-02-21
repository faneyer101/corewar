/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main_interpreteur.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: faneyer <faneyer@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/20 04:09:47 by faneyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/21 22:36:00 by faneyer     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
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
			if (ft_strcmp(token->data, lab->name) == 0 && ft_strlen(token->data) == ft_strlen(lab->name))
			{
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
	if (ltoken)
	{
		while (ltoken->unext)
			ltoken = ltoken->unext;
		ltoken->unext = token;
		ltoken->unext->call_index = master->interpretor.index;
	}
	else
	{
		master->interpretor.wait_label = token;
		master->interpretor.wait_label->call_index = master->interpretor.index;
	}
}

void	interpretor_param(t_asm *master, t_token *token, t_list_label *label)
{
	int				index_define;

	index_define = -1;
	if (token->kind == REGISTRE)
	{
		master->interpretor.code_champ[master->interpretor.index] = ft_atoi(token->data);
		master->interpretor.index++;
	}
	else if (token->kind == NUM_DIRECT)
	{
		if (master->interpretor.function.direct == 1)
		{
			master->interpretor.code_champ[master->interpretor.index] = (ft_atoi(token->data) >> 8) & 0xFF;
			master->interpretor.code_champ[master->interpretor.index + 1] = (ft_atoi(token->data) >> 0) & 0xFF;
		}
		else if (master->interpretor.function.direct == 0)
		{
			master->interpretor.code_champ[master->interpretor.index] = (ft_atoi(token->data) >> 24) & 0xFF;
			master->interpretor.code_champ[master->interpretor.index + 1] = (ft_atoi(token->data) >> 16) & 0xFF;
			master->interpretor.code_champ[master->interpretor.index + 2] = (ft_atoi(token->data) >> 8) & 0xFF;
			master->interpretor.code_champ[master->interpretor.index + 3] = (ft_atoi(token->data) >> 0) & 0xFF;
		}
		if (master->interpretor.function.direct == 0)
			master->interpretor.index += 4;
		else
			master->interpretor.index += 2;
	}
	else if (token->kind == NUM_INDIRECT)
	{
		master->interpretor.code_champ[master->interpretor.index] = (ft_atoi(token->data) >> 24) & 0xFF;
		master->interpretor.code_champ[master->interpretor.index + 1] = (ft_atoi(token->data) >> 16) & 0xFF;
		master->interpretor.code_champ[master->interpretor.index + 2] = (ft_atoi(token->data) >> 8) & 0xFF;
		master->interpretor.code_champ[master->interpretor.index + 3] = (ft_atoi(token->data) >> 0) & 0xFF;
		master->interpretor.index += 4;
	}
	else if (token->kind == LABEL_DIRECT)
	{
		search_define_label(master, token, &index_define, label);
		if (index_define >= 0)
		{
			if (master->interpretor.function.direct == 1)
			{
				master->interpretor.code_champ[master->interpretor.index] = (((index_define >> 8) - (master->interpretor.index >> 8)) & 0xFF);
				master->interpretor.code_champ[master->interpretor.index + 1] = (((index_define >> 0) - (master->interpretor.index >> 0)) & 0xFF);
		//		ft_printf("|{GREEN}%d|{RED}%d{END}|{YELL}%d{END}|\n", index_define, master->interpretor.index, index_define - master->interpretor.index);
				// ft_print_bits((((index_define >> 8) - (master->interpretor.index >> 8)) & 0xFF));
				// printf("\n");
				 //ft_print_bits((((index_define >> 0) - (master->interpretor.index >> 0)) & 0xFF));
				// printf("\n");

		//		ft_print_bits(((master->interpretor.index >> 0) & 0xFF));
		//		printf("\n");
		//		ft_print_bits(((index_define >> 0) & 0xFF));
		//		printf("\n");
		//		if (index_define > master->interpretor.index)
		//			ft_print_bits((((index_define >> 0) - (master->interpretor.index >> 0)) & 0xFF));
		//		else
		//			ft_print_bits(((master->interpretor.index >> 0) - (index_define >> 0)) & 0xFF);
		//		 printf("\n");
				

			}
			else if (master->interpretor.function.direct == 0)
			{
				master->interpretor.code_champ[master->interpretor.index] = ((index_define >> 24) & 0xFF) + 0xFF;
				master->interpretor.code_champ[master->interpretor.index + 1] = ((index_define >> 16) & 0xFF) + 0xFF;
				master->interpretor.code_champ[master->interpretor.index + 2] = ((index_define >> 8) & 0xFF) + 0xFF;
				master->interpretor.code_champ[master->interpretor.index + 3] = ((index_define >> 0) & 0xFF) + 0xFF;
			}
		}
		else
			push_label_undefine(master, token);
		if (master->interpretor.function.direct == 0)
			master->interpretor.index += 4;
		else
			master->interpretor.index += 2;
	}
	else if (token->kind == LABEL_INDIRECT)
	{
		search_define_label(master, token, &index_define, label);
		if (index_define >= 0)
		{
			master->interpretor.code_champ[master->interpretor.index] = (index_define >> 24) & 0xFF;
			master->interpretor.code_champ[master->interpretor.index + 1] = (index_define >> 16) & 0xFF;
			master->interpretor.code_champ[master->interpretor.index + 2] = (index_define >> 8) & 0xFF;
			master->interpretor.code_champ[master->interpretor.index + 3] = (index_define >> 0) & 0xFF;
		}
		else
			push_label_undefine(master, token);
		master->interpretor.index += 4;
	}
}
/*
void	controle(t_asm *master)
{
	t_list_label	*label;

	label = master->interpretor.wait_label;
	if (label)
	{
		while (label)
		{
			
			label = label->unext;
		}
	}
}
*/
static void	init_struct_function(t_asm *master)
{
	master->interpretor.function.octet = 0;
	master->interpretor.function.direct = 0;
	master->interpretor.function.index_tab = 16;	//null de optab
	master->interpretor.function.opcode = 16;		//null de optab
}	

void    main_interpreteur(t_asm *master)
{
    t_list_label    *label;
    t_token			*token;

    label = master->parser.define_label;
    while (label && master->interpretor.index < CHAMP_MAX_SIZE)
    {
		if (label->defaut != 1)
            label->index_define = master->interpretor.index;
        token = label->info;
		while (token)
		{
			if (token->kind == FONCTION)
			{
				init_struct_function(master);
				interpretor_function(master, label, token);
			}
			else if (token->kind == LABEL_DIRECT || token->kind == LABEL_INDIRECT ||
				token->kind == NUM_DIRECT || token->kind == NUM_INDIRECT || token->kind == REGISTRE)
				interpretor_param(master, token, label);
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
//	controle(master);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion_params.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faneyer <faneyer@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 14:30:56 by faneyer           #+#    #+#             */
/*   Updated: 2020/05/24 14:39:37 by faneyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/asm.h"

void	registre(t_asm *master, int long long *calcul, t_token *t)
{
	calcul[0] = ft_atoi(t->data);
	master->interpretor.code_champ[master->interpretor.index] =
	(calcul[0] >> 0) & 0xFF;
	master->interpretor.index++;
}

void	num_two_octets(t_asm *master, int long long *calcul,
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

void	num_four_octets(t_asm *master, long long int *calcul,
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

void	labbel_two_octets(t_asm *master, long long int *calcul,
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

void	labbel_four_octets(t_asm *master, long long int *calcul,
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

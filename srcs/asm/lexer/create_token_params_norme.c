/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_params_norme.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faneyer <faneyer@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 14:47:49 by faneyer           #+#    #+#             */
/*   Updated: 2020/05/24 14:48:17 by faneyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/asm.h"

void		cheack_label(int *i, char *str, int *direct)
{
	if (str[*i] == DIRECT_CHAR)
	{
		i[0] += 2;
		direct[0] = 1;
	}
	else
		i[0]++;
}

void		lexer_registre(t_asm *master, int *i, char *str, int start)
{
	i[0]++;
	start = *i;
	while (ft_isdigit(str[i[0]]))
		i[0]++;
	push_token(master, REGISTRE, start, i[0] - start);
	master->column++;
}

void		lexer_num_direct(t_asm *master, int *i, char *str, int start)
{
	i[0]++;
	start = *i;
	if (str[i[0]] == '-')
		i[0]++;
	while (ft_isdigit(str[i[0]]))
		i[0]++;
	push_token(master, NUM_DIRECT, start, i[0] - start);
	master->column++;
}

void		lexer_num_indirect(t_asm *master, int *i, char *str, int start)
{
	start = *i;
	if (str[i[0]] == '-')
		i[0]++;
	while (ft_isdigit(str[i[0]]))
		i[0]++;
	push_token(master, NUM_INDIRECT, start, i[0] - start);
	master->column++;
}

void		lexer_bad(t_asm *master, int *i, char *str)
{
	create_token_bad(master, i, str, 0);
	i[0]++;
}

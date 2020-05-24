/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error_interpreteur.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faneyer <faneyer@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 14:16:54 by faneyer           #+#    #+#             */
/*   Updated: 2020/05/24 15:49:44 by faneyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/asm.h"

void	print_error_overflow(t_asm *master, int index, t_token *token,
char *msg)
{
	ft_printf("interpretor[{GREEN}line:%d{END}]", token->numline);
	ft_printf("[{GREEN}column:%d{END}]%s", token->column, msg);
	ft_printf("|{RED}%s{END}|\n", token->data);
	master->interpretor.index += index;
	master->error_traitment++;
}

void	size_champ_max(t_asm *master)
{
	ft_printf("{RED}SIZE TOO LONG{END} %d. Size Max: %d\n",
	master->interpretor.index, CHAMP_MAX_SIZE);
	free_undefine_label(master);
	free_define_label(master);
	free_token_and_buff(master);
	exit(0);
}

void	print_msg_error_interpretor(t_asm *master, char *msg)
{
	free_undefine_label(master);
	free_define_label(master);
	free_token_and_buff(master);
	ft_printf("%s\n", msg);
	exit(0);
}

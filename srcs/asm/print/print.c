/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faneyer <faneyer@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 18:52:42 by faneyer           #+#    #+#             */
/*   Updated: 2020/06/03 15:53:58 by faneyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/asm.h"

void	print_usage(void)
{
	ft_printf("{UND}Usage:{END}\n./asm [{YELL}opion{END}][{RED}file{END}]\n");
	ft_printf("{YELL}Option{END}:\n	l: print lexer\n");
	ft_printf("	p: print parser\n");
	ft_printf("{YELL}{UND}Exemple option: -p or -l or -lp or -pl{END}\n");
	ft_printf("{RED}Extension file .s{END}\n\n");
	exit(0);
}

int		print_error_parser(t_asm *master, char *msg_error, char *error,
t_token *list)
{
	ft_printf("parser[{GREEN}line:%d{END}][{GREEN}column:%d{END}]%s|{RED}%s",
		list->numline, list->column, msg_error, error);
	ft_printf("{END}|\n");
	master->error_parser++;
	return (0);
}

int		print_error_parser_label(t_asm *master, char *msg_error, char *error,
t_list_label *list)
{
	ft_printf("parser[{GREEN}line:%d{END}][{GREEN}column:%d{END}]%s|{RED}%s",
		list->numline, list->column, msg_error, error);
	ft_printf("{END}|\n");
	master->error_parser++;
	return (0);
}

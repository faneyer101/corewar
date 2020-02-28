/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faneyer <faneyer@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 18:52:42 by faneyer           #+#    #+#             */
/*   Updated: 2020/02/28 09:47:22 by faneyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/asm.h"

void 	print_usage(void)
{
	ft_printf("{UND}Usage:{END}\n./asm [{YELL}opion{END}][{RED}file{END}]\n");
    ft_printf("{YELL}Option{END}:\n	t: print token\n");
    ft_printf("	p: print parser\n{RED}Extension file .s{END}\n\n");
	exit(0);
}

int	print_error_parser_param(t_asm *master, char *msg_error, char *error, t_token *list)
{	
	ft_printf("parser[{GREEN}line:%d{END}][{GREEN}column:%d{END}]%s|{RED}%s{END}|\n", list->numline, list->column, msg_error, error);
	master->error_parser++;
	return(0);
}

int	print_error_parser_label(t_asm *master, char *msg_error, char *error, t_list_label *list)
{	
	ft_printf("parser[{GREEN}line:%d{END}][{GREEN}column:%d{END}]%s|{RED}%s{END}|\n", list->numline, list->column, msg_error, error);
	master->error_parser++;
	return(0);
}
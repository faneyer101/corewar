/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faneyer <faneyer@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 01:05:17 by faneyer           #+#    #+#             */
/*   Updated: 2020/05/24 15:49:02 by faneyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/asm.h"

void	print_error_before_read(char *msg_error, int fd, char *buff, char *line)
{
	if (line)
		ft_strdel(&line);
	if (buff)
		ft_strdel(&buff);
	if (fd > 0)
		close(fd);
	ft_printf("%s", msg_error);
	exit(1);
}

void	printf_error_lexer(t_asm *master, char *msg_error)
{
	ft_strdel(&master->buff_read);
	if (master->tab_token)
		free_tab_token(master);
	ft_printf("{RED}{BOLD}%s on line %d{BLUE}\n\n",
		msg_error, master->numline);
	exit(0);
}

void	print_error_allocation(t_asm *master, char *function)
{
	ft_strdel(&master->buff_read);
	ft_printf("Problem to allocate memory in the function: {RED}%s{END}\n",
		function);
	exit(1);
}

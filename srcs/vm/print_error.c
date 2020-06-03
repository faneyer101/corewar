/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faneyer <faneyer@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 15:11:56 by faneyer           #+#    #+#             */
/*   Updated: 2020/06/03 15:12:07 by faneyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/vm.h"

void	print_with_exit(char *msg, int i)
{
	ft_printf("%s %d\n", msg, i);
	exit(1);
}

void	print_with_usage(char *msg, char *av)
{
	ft_printf("%s %s\n", msg, av);
	usage();
}

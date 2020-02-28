/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   toolsparser2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faneyer <faneyer@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 20:59:44 by faneyer           #+#    #+#             */
/*   Updated: 2020/02/28 09:46:50 by faneyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/asm.h"

void	verif_declaration_label(t_asm *master, t_list_label *label)
{
	t_list_label	*list;

	list = label;
	//	printf("%s|%d|\n", list->name, list->define_parser);
	while (list)
	{
		if (list->define_parser == 0)
			print_error_parser_label(master, "label don't declared", list->name, list); //revoir le print erreur
		list = list->unext;
	}
}


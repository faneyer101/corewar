/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faneyer <faneyer@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 16:33:44 by faneyer           #+#    #+#             */
/*   Updated: 2020/05/24 14:59:22 by faneyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/asm.h"

int		control_label_declaration(char *str)
{
	int i;

	i = 0;
	while (str[i] && !delimiter(str[i], "s") && str[i] != LABEL_CHAR)
		i++;
	if ((cmp_label_chars(str[i - 1], 0) && str[i] == LABEL_CHAR))
		return (TRUE);
	return (FALSE);
}

int		check_param(t_asm *master, char *str, int i)
{
	while (i < 17)
	{
		if (ft_strncmp(master->tab_op[i].name, str,
		ft_strlen(master->tab_op[i].name)) == 0)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

void	create_labbel_declaration(t_asm *master, int *i, char *str)
{
	int	start;

	start = *i;
	while (str[*i] && str[*i] != LABEL_CHAR && cmp_label_chars(str[*i], 0))
		i[0]++;
	if (str[*i] == LABEL_CHAR)
	{
		push_token(master, LABEL_DECLARATION, start, *i - start);
		master->column++;
	}
	else
	{
		i[0] = start;
		create_token_bad(master, i, str, 0);
	}
}

void	init_token(t_asm *master)
{
	int	i;

	if (!(master->tab_token = (t_token**)malloc(sizeof(t_token*) *
	(master->maxline + 1))))
		print_error_allocation(master, "master->tab_token");
	i = -1;
	while (++i <= master->maxline)
		master->tab_token[i] = NULL;
	master->numline = 1;
	master->column = 1;
}

int		main_lexer(t_asm *master, int i)
{
	init_token(master);
	while (++i < master->size_read_total && master->buff_read[i])
	{
		if (master->buff_read[i] && master->buff_read[i] == '\n')
		{
			master->numline++;
			master->column = 1;
			continue;
		}
		else if (delimiter(master->buff_read[i], "s"))
			continue;
		else if (delimiter(master->buff_read[i], "#"))
			create_token_comment(master, &i, master->buff_read, 0);
		else if (delimiter(master->buff_read[i], "nc"))
			create_token_header(master, &i, master->buff_read, i);
		else if (control_label_declaration(&master->buff_read[i]))
			create_labbel_declaration(master, &i, master->buff_read);
		else if (check_param(master, &master->buff_read[i], 0))
			create_token_name_funtion(master, &i, master->buff_read, -1);
		else if (!delimiter(master->buff_read[i], "s#") &&
		master->buff_read[i] != SEPARATOR_CHAR)
			create_token_bad(master, &i, master->buff_read, 0);
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_token_params.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faneyer <faneyer@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 18:03:43 by faneyer           #+#    #+#             */
/*   Updated: 2020/06/04 22:20:55 by faneyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/asm.h"

static void	create_ind_dir_label(t_asm *master, int *i, char *str, int start)
{
	int	direct;

	direct = 0;
	cheack_label(i, str, &direct);
	start = *i;
	while (cmp_label_chars(str[i[0]], 0))
		i[0]++;
	if (str[i[0]] == '\0' || str[*i] == SEPARATOR_CHAR ||
		delimiter(str[*i], "s"))
	{
		if (direct)
			push_token(master, LABEL_DIRECT, start, i[0] - start);
		else
			push_token(master, LABEL_INDIRECT, start, i[0] - start);
	}
	else
	{
		i[0] = start;
		return (create_token_bad(master, i, str, 0));
	}
	master->column++;
}

static void	norme_create_token_param(t_asm *m, int *i, char *str, int start)
{
	if (str[i[0]] && str[i[0]] == DIRECT_CHAR &&
	(ft_isdigit(str[i[0] + 1]) || (str[i[0] + 1] == '-' &&
	ft_isdigit(str[i[0] + 2]))))
		lexer_num_direct(m, i, str, start);
	else if (str[i[0]] && (ft_isdigit(str[i[0]]) || (str[i[0]] == '-' &&
	ft_isdigit(str[i[0] + 1]))))
		lexer_num_indirect(m, i, str, start);
	else if (str[i[0]] && !delimiter(str[i[0]], "s") && ft_isprint(str[i[0]]))
		lexer_bad(m, i, str);
	else
		i[0]++;
}

static void	create_token_param(t_asm *master, int *i, char *str, int start)
{
	while (str[*i] && str[*i] != '\n')
	{
		if (str[i[0]] && delimiter(str[i[0]], "#"))
			return (create_token_comment(master, i, str, 0));
		else if (str[i[0]] && str[i[0]] == SEPARATOR_CHAR && (i[0] = i[0] + 1))
			push_token(master, SEPARATOR, i[0] - 1, 1);
		else if ((str[*i] && str[*i] == LABEL_CHAR && str[i[0] + 1] &&
		cmp_label_chars(str[i[0] + 1], 0)) || (str[i[0] + 1] &&
		str[i[0] + 1] == LABEL_CHAR && str[*i] == DIRECT_CHAR &&
		str[i[0] + 2] && cmp_label_chars(str[i[0] + 2], 0)))
			create_ind_dir_label(master, i, str, 0);
		else if (str[i[0]] && str[i[0]] == 'r' && str[i[0] + 1] &&
		ft_isdigit(str[i[0] + 1]))
			lexer_registre(master, i, str, start);
		else
			norme_create_token_param(master, i, str, start);
	}
	if (str[*i] && str[*i] == '\n' && *i != master->size_read_total)
		i[0]--;
}

void		create_token_name_funtion(t_asm *master, int *i, char *str, int j)
{
	while (++j < 17)
	{
		if (ft_strncmp(master->tab_op[j].name, &str[*i],
			ft_strlen(master->tab_op[j].name)) == 0 &&
			delimiter(str[*i + ft_strlen(master->tab_op[j].name)], "sPN") &&
			ft_strlen(master->tab_op[j].name) > 0)
		{
			push_token(master, FONCTION, i[0],
			ft_strlen(master->tab_op[j].name));
			i[0] += (ft_strlen(master->tab_op[j].name));
			master->column++;
			break ;
		}
	}
	if (j >= 17)
		return (create_token_bad(master, i, str, 0));
	while (str[*i] && str[*i] != '\n' && delimiter(str[*i], "s"))
		i[0]++;
	if (str[*i] && str[*i] != '\n')
		create_token_param(master, i, str, 0);
	else if (str[*i])
		i[0]--;
}

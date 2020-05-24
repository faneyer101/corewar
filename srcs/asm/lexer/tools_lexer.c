/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_lexer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faneyer <faneyer@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 14:58:13 by faneyer           #+#    #+#             */
/*   Updated: 2020/05/24 14:58:47 by faneyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/asm.h"

int		cmp_label_chars(char c, int i)
{
	while (LABEL_CHARS[i])
	{
		if (LABEL_CHARS[i] == c)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int		norme_delimiter(char c, char *analyse)
{
	if (ft_strchr(analyse, '*'))
		if (c == DSTRING)
			return (TRUE);
	if (ft_strchr(analyse, 'A'))
		if (ft_isalpha(c) != 0)
			return (TRUE);
	if (ft_strchr(analyse, 'N'))
		if (ft_isdigit(c) != 0)
			return (TRUE);
	if (ft_strchr(analyse, '-'))
		if (c == DNEGATIF)
			return (TRUE);
	return (FALSE);
}

int		delimiter(char c, char *analyse)
{
	if (c != '\0')
	{
		if (ft_strchr(analyse, 'P'))
			if (c == LABEL_CHAR || c == DIRECT_CHAR || c == 'r' || c == '-')
				return (TRUE);
		if (ft_strchr(analyse, 's'))
			if (ft_isspace(c))
				return (TRUE);
		if (norme_delimiter(c, analyse))
			return (TRUE);
		if (ft_strchr(analyse, 'd'))
			if (c == LABEL_CHAR || c == DIRECT_CHAR || c == SEPARATOR_CHAR)
				return (TRUE);
		if (ft_strchr(analyse, '#'))
			if (c == COMMENT_CHAR || c == ALT_COMMENT_CHAR)
				return (TRUE);
		if (ft_strcmp("nc", analyse) == 0)
			if (c == COMMENT_CMD_STRING[0] || c == NAME_CMD_STRING[0])
				return (TRUE);
	}
	return (FALSE);
}

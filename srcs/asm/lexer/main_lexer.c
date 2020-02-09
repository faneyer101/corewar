/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main_lexer.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: faneyer <faneyer@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/08 21:13:26 by faneyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/10 00:04:52 by faneyer     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../../includes/asm.h"
#include "../../../includes/op.h"

int		cmp_header_oph(char c, int i, char bole)
{
	if (bole == 'c')
		while (COMMENT_CMD_STRING[i])
		{
			if (c != COMMENT_CMD_STRING[i])
				return (FALSE);
			i++;
		}
	else if (bole == 'n')
	{
		i = 0;
		while (NAME_CMD_STRING[i])
		{
			if (c != NAME_CMD_STRING[i])
				return (FALSE);
			i++;
		}
	}
	return (TRUE);
}

int		delimiter(char c, char *analyse)
{
	if (c != '\0')
	{
		if (ft_strchr(analyse, 'd'))
			if (c == LABEL_CHAR || c == DIRECT_CHAR || c == SEPARATOR_CHAR || c == '-')
				return (TRUE);
		if (ft_strchr(analyse, 's'))
			if (ft_isspace(c))
				return (TRUE);
		if (ft_strchr(analyse, '"'))
			if (c == '"')
				return (TRUE);
		if (ft_strchr(analyse, '_'))
			if (c == '_')
				return (TRUE);
		if (ft_strchr(analyse, '#'))
			if (c == COMMENT_CHAR || c == ALT_COMMENT_CHAR)
				return (TRUE);
		if (ft_strchr(analyse, 'a'))
			if (ft_isprint(c) && delimiter(c, "ds._#""") == 0)
				return (TRUE);
		/*		GESTION HEADER 					*/		
		if (ft_strcmp("nc", analyse) == 0)
		{
			if (c == COMMENT_CMD_STRING[0] || c == NAME_CMD_STRING[0])
				return (TRUE);
		}
		else 
		{
			if (ft_strchr(analyse, 'n'))
				if (cmp_header_oph(c, 0, 'n'))
					return (TRUE);
			if (ft_strchr(analyse, 'c'))
				if (cmp_header_oph(c, 0, 'c'))
					return (TRUE);
		}
	}
	return (FALSE);
}

void	init_token(t_token *token, t_asm *master)
{
	token->index = -1;
	master->numline++;
}

int	main_lexer(t_asm *master, int i)
{	
	t_token	token;

	printf("%d|%d|%s|\n", i, master->numline, master->split_read[i]);
	init_token(&token, master);
	if (master->split_read[i] == NULL) // a gerer pour compter le nombre de ligne or stack
		return (0);
	while (master->split_read[i][++token.index])
		if (delimiter(master->split_read[i][token.index], "s"))
			continue;
		else
			break;
	if (delimiter(master->split_read[i][token.index], "nc") && cheak_header(master->split_read[i]))
		create_token_for_header(master, master->split_read[i], &token);
	else if (delimiter(master->split_read[i][token.index], "#"))
		create_token_comment(master, master->split_read[i], &token);
	else if (ft_isdigit(master->split_read[i][token.index]) || ft_isalpha(master->split_read[i][token.index]) ||
			delimiter(master->split_read[i][token.index], "_"))
		create_token_champion(master, master->split_read[i], &token);
	else if (master->split_read[i][token.index] != '\0')
		printf_error_lexer(master, "Bad syntax");
	return (main_lexer(master, i + 1));
}
/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main_lexer.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: faneyer <faneyer@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/08 21:13:26 by faneyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/09 13:22:55 by faneyer     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../../includes/asm.h"

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
		if (ft_strchr(analyse, '.'))
			if (c == '.')
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
	}
	return (FALSE);
}

void	init_token(t_token *token)
{
	token->index = -1;
//	token->nbligne = 0;
//	token->size = 0;
//	token->type = '\0';
//	token->digit = 0;
//	token->string = NULL;
}

int	main_lexer(t_asm *master, int i)
{	
	t_token	token;

	init_token(&token);
	master->numline++; 
	if (master->split_read[i] == NULL)
	{
		// a gerer pour compter le nombre de ligne or stack
		return (0);
	}
	while (master->split_read[i][++token.index])
		if (delimiter(master->split_read[i][token.index], "s"))
			continue;
		else
			break;
	if (delimiter(master->split_read[i][token.index], "."))
		create_token_for_header(master, master->split_read[i], &token);
	else if (delimiter(master->split_read[i][token.index], "#"))
		create_token_comment(master, master->split_read[i], &token);
	else if (ft_isdigit(master->split_read[i][token.index]) || ft_isalpha(master->split_read[i][token.index]) ||
			delimiter(master->split_read[i][token.index], "_"))
		create_token_champion(master, master->split_read[i], &token);
	else if (master->split_read[i][token.index] == '\0')
		return (main_lexer(master, i + 1));
	else
		printf_error_lexer(master, "Bad syntax");
	return (main_lexer(master, i + 1));
}
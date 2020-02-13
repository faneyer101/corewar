/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main_lexer3.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: faneyer <faneyer@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/08 21:13:26 by faneyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/13 07:23:35 by faneyer     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../../includes/asm.h"
/*
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
*/
/*
int		delimiter(char c, char *analyse)
{
	if (c != '\0')
	{
//		printf("DELIMITEUR |%c|%s|\n", c, analyse);
		if (ft_strchr(analyse, 'd'))
			if (c == LABEL_CHAR || c == DIRECT_CHAR || c == SEPARATOR_CHAR || c == DNEGATIF)
				return (TRUE);
		if (ft_strchr(analyse, 's'))
			if (ft_isspace(c))
				return (TRUE);
		if (ft_strchr(analyse, '*'))
			if (c == DSTRING)
				return (TRUE);
		if (ft_strchr(analyse, 'N'))
			if (ft_isdigit(c) != 0 || ft_isalpha(c) != 0)
				return (TRUE);
		if (ft_strchr(analyse, '#'))
			if (c == COMMENT_CHAR || c == ALT_COMMENT_CHAR)
				return (TRUE);
		if (ft_strchr(analyse, 'a'))
			if (ft_isprint(c) && delimiter(c, "dsL#*") == 0)
				return (TRUE);
		
	//	if (ft_strchr(analyse, 'L'))
	//		if (cmp_label_chars(c, 0))
	//			return (TRUE);
		
		if (ft_strcmp("nc", analyse) == 0)
		{
			if (c == COMMENT_CMD_STRING[0] || c == NAME_CMD_STRING[0])
				return (TRUE);
		}
	//	else 
	//	{
	//		if (ft_strchr(analyse, 'n'))
	//			if (cmp_header_oph(c, 0, 'n'))
	//				return (TRUE);
	//		if (ft_strchr(analyse, 'c'))
	//			if (cmp_header_oph(c, 0, 'c'))
	//				return (TRUE);
	//	}
	}
	return (FALSE);
}*/
/*
void	init_token(t_token *token, t_asm *master)
{
	token->index = 0;
	master->numline++;
}






int	main_lexer(t_asm *master, int i)
{	
	t_token	token;

	init_token(&token, master);
	ft_printf("{RED}%d|%d|%d|%s|{END}\n", i, token.index, master->numline, master->split_read[i]);
	if (master->split_read[i] == NULL) // a gerer pour compter le nombre de ligne or stack
		return (0);
	while (delimiter(master->split_read[i][token.index], "s"))
			token.index++;
	if (delimiter(master->split_read[i][token.index], "#"))
		create_token_comment(master, master->split_read[i], &token);
	else if (cheak_header(master->split_read[i]))
	{
		printf("%d|%d|%s|\n", i, master->numline, master->split_read[i]);
		create_token_for_header(master, master->split_read[i], &token);
	}
	else if (ft_isalpha(master->split_read[i][token.index]) || delimiter(master->split_read[i][token.index], "Ld"))
	{
		create_token_champion(master, master->split_read[i], &token);
	}
	else if (master->split_read[i][token.index] != '\0')
		printf_error_lexer(master, "Bad syntax");
	return (main_lexer(master, i + 1));
*/
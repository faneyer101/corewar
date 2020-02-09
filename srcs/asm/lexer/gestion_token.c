/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   gestion_token.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: faneyer <faneyer@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/09 04:48:01 by faneyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/10 00:02:52 by faneyer     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../../includes/asm.h"

void    create_token_comment(t_asm *master, char *comment, t_token *token)
{
	int	start;

	token->index++;
	start = token->index;
	while (comment[token->index])
	{	
		if (delimiter(comment[token->index], "s#"))
			token->index++;
		else
			break;
	}
	if (comment[token->index])
	{
		push_token(master, &comment[start - 1], 1, 'D');
		push_token(master, &comment[start], ft_strlen(&comment[start]), 'S');
	}
	else
		return ;
}

void    header_string(t_asm *master, char *header, t_token *token)
{
    int start;

    token->index = 1;
    push_token(master, &header[0], 1, 'D');
    start = 1;
    while (header[token->index] && header[token->index] != '"')
        token->index++;
	if (header[token->index] == '\0')
		printf_error_lexer(master, "File Bad Syntax header");
    push_token(master, &header[start], token->index - start, 'S');
    push_token(master, &header[token->index], 1, 'D');
    while (header[++token->index])
    {
        if (delimiter(header[token->index], "s"))
            continue;
		else if (delimiter(header[token->index], "#"))
		{
			create_token_comment(master, &header[token->index], token);		
			return ;		
		}
		else
			printf_error_lexer(master, "File Bad Syntax header");    
    }
}

int		cheak_header(char *str)
{
	if (*str)
	{
		if (ft_strncmp(str, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)) == 0)
			return (TRUE);
		if (ft_strncmp(str, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING)) == 0)
			return (TRUE);
	}
		return (FALSE);
}

void    create_token_for_header(t_asm *master, char *header, t_token *token)
{
    if (cheak_header(header) == FALSE)
		printf_error_lexer(master, "File Bad Syntax header name or comment");
    push_token(master, &header[token->index], 1, 'D');
    if (header[token->index + 1] == NAME_CMD_STRING[1])
    {
        push_token(master, &header[token->index + 1], ft_strlen(NAME_CMD_STRING) - 1, 'S');
        token->index += ft_strlen(NAME_CMD_STRING);
    }
    else
    {
        push_token(master, &header[token->index + 1], ft_strlen(COMMENT_CMD_STRING) - 1, 'S');
        token->index += ft_strlen(COMMENT_CMD_STRING);
    }
    while (header[token->index] && delimiter(header[token->index], "s"))
        token->index++;
    if (header[token->index] != '"')
	    printf_error_lexer(master, "File Bad Syntax header");
    else
        header_string(master, &header[token->index], token);
}

void	token_champion_param(t_asm *master, char *code, t_token *token, int start)
{
	while (code[token->index++])
	{
		if (delimiter(code[token->index], "s"))
			continue;
		if (ft_isdigit(code[token->index]) || ft_isalpha(code[token->index]) || code[token->index] == '_')
		{
			start = token->index;
			while (code[token->index] && (ft_isdigit(code[token->index]) || ft_isalpha(code[token->index]) || code[token->index] == '_'))
				token->index++;
        	push_token(master, &code[start], token->index - start, 'S');
			if (delimiter(code[token->index], "d"))
	        	push_token(master, &code[token->index], 1, 'D');
			if (delimiter(code[token->index], "a"))
			    printf_error_lexer(master, "File Bad Syntax setting commande champion");
		}
		else if (delimiter(code[token->index], "d"))
        	push_token(master, &code[token->index], 1, 'D');
		else if (delimiter(code[token->index], "#"))
		{
			create_token_comment(master, code, token);		
			return ;
		}
		else if (code[token->index] == '\0')
			return ;
		else 
		    printf_error_lexer(master, "File Bad Syntax setting commande champion");
	}
}

void    create_token_champion(t_asm *master, char *code, t_token *token)
{
	int	start;

	while (code[token->index])
	{
		if (delimiter(code[token->index], "s"))
			token->index++;
		else
			break;
	}
	if (ft_isdigit(code[token->index]) != 0 || ft_isalpha(code[token->index]) != 0 || delimiter(code[token->index], "_"))
	{
		start = token->index;
		while (code[token->index])
			if (ft_isdigit(code[token->index]) != 0 || ft_isalpha(code[token->index]) != 0 || delimiter(code[token->index], "_"))
				token->index++;
			else
				break;
        push_token(master, &code[start], token->index - start, 'S');
	}
	else
	    printf_error_lexer(master, "File Bad Syntax setting labbel champion");
	if (delimiter(code[token->index], "d"))
        push_token(master, &code[token->index], 1, 'D');
	token_champion_param(master, code, token, 0);
}

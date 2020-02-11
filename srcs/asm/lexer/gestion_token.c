/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   gestion_token.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: faneyer <faneyer@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/09 04:48:01 by faneyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/11 19:40:20 by faneyer     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../../includes/asm.h"

/*
int		cheak_header(char *str)
{
	if (*str)
	{
		//printf("|%c|\n", str[ft_strlen(NAME_CMD_STRING)]);
		if (ft_strncmp(str, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)) == 0 && delimiter(str[ft_strlen(NAME_CMD_STRING)], "s*"))
			return (TRUE);
		if (ft_strncmp(str, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING)) == 0 && delimiter(str[ft_strlen(COMMENT_CMD_STRING)], "s*"))
			return (TRUE);
	}
		return (FALSE);
}

void    create_token_comment(t_asm *master, char *comment, t_token *token)
{
	int	start;

	//printf("CREATE TOKEN COMMENT |%s|%c|%d|\n", comment, comment[token->index], token->index);
	if (cheak_header(comment))
		create_token_for_header(master, comment, token);
	else
	{
		token->index++;
		start = token->index;
		while (delimiter(comment[token->index], "s#"))
				token->index++;
		if (comment[token->index])
		{
			push_token(master, &comment[start - 1], 1, 'D');
			push_token(master, &comment[start], ft_strlen(&comment[start]), 'S');
		}
		else
			return ;
	}
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
			return (create_token_comment(master, header, token));		
		else
			printf_error_lexer(master, "File Bad Syntax header");    
    }
}


void    create_token_for_header(t_asm *master, char *header, t_token *token)
{
	printf("TOKEN HEADER|%s|%c|%d|\n", header, header[token->index], token->index);
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
    while (delimiter(header[token->index], "s"))
        token->index++;
    if (header[token->index] != '"')
	    printf_error_lexer(master, "File Bad Syntax header. Miss String [\" \"]");
    else
        header_string(master, &header[token->index], token);
}

void	token_champion_param(t_asm *master, char *code, t_token *token, int start)
{
	while (code[token->index])
	{
		//printf("PARCOUR PARAM CHAMPION: |%s|%c|%d-%d|\n", code, code[token->index], token->index, start);
		while (delimiter(code[token->index], "s"))
			token->index++;
		if (delimiter(code[token->index], "L")) //N
		{
			start = token->index;
			while (delimiter(code[token->index], "L")) //N
				token->index++;
        	push_token(master, &code[start], token->index - start, 'S');
			if (code[token->index] == '\0')
				break;
			else
				continue;
		}
		else if (delimiter(code[token->index], "d"))
        	push_token(master, &code[token->index], 1, 'D');
		else if (delimiter(code[token->index], "#"))
			return (create_token_comment(master, code, token));
		else if (code[token->index])
		    printf_error_lexer(master, "File Bad Syntax setting commande champion");
		token->index++;
	}
}

int		labbel_or_param(char *code)
{
	int	i;

	i = 0;
	while (code[i] && cmp_label_chars(code[i], 0))
		i++;
	if (code[i] && code[i] == LABEL_CHAR)
		return (TRUE);
	return (FALSE);
}
void    create_token_champion(t_asm *master, char *code, t_token *token)
{
	int	start;

	//printf("DEPAR CHAMPION|%d|%c|%s|\n", token->index, code[token->index], code);
	if (labbel_or_param(&code[token->index]))
	{
		start = token->index;
		while (delimiter(code[token->index], "L"))
				token->index++;
        push_token(master, &code[start], token->index - start, 'S');
        push_token(master, &code[token->index], 1, 'D');
		token->index++;
	}
	while (delimiter(code[token->index], "s"))
		token->index++;
	if (delimiter(code[token->index], "N"))
		return (token_champion_param(master, code, token, 0));
	else if (delimiter(code[token->index], "#"))
		return (create_token_comment(master, code, token));
	if (code[token->index])
		return (printf_error_lexer(master, "FILE bad syntax on the start prog champions"));
}
*/
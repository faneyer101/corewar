/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   create_token.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: faneyer <faneyer@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/15 20:36:00 by faneyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/23 05:19:13 by faneyer     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../../includes/asm.h"

void	create_token_bad(t_asm *master, int *i, char *str, int start)
{
	start = i[0];
	while (str[i[0]] && str[i[0]] != '\n')
		i[0]++;
    
   // printf("[%d][%d]CREATE BAD |%c|%c|%c|\n", master->numline, master->column, str[i[0]], str[i[0] + 1], str[i[0] + 2]);
	push_token(master, BAD, start, i[0] - start);
    i[0]--;
    master->error_lexer++;
//	master->column = 1;
//	master->numline++;
}

void	create_token_comment(t_asm *master, int *i, char *str, int start)
{
	start = *i;
	while (str[*i] && delimiter(str[*i], "s") && str[*i] != '\n')
		i[0]++;
	if (str[*i] && str[*i] == '\n')
	{
		master->numline++;
		master->column = 1;
		return ;
	}
	else if (str[*i])
	{
		while (str[*i] && str[*i] != '\n')
			i[0]++;
		master->column++;
		push_token(master, COMMENT, start, *i - start);
		if (str[*i] && str[*i] == '\n')
		{
			master->column = 1;
			master->numline++;
		}
	}
}

static void    create_token_string_header(t_asm *master, int *i, int start, char* str)
{
    i[0]++;
	while (str[*i] /*&& str[*i] != '\n'*/ && str[*i] != DSTRING)
		i[0]++;
    if (str[*i] && str[*i] == DSTRING)
	{
		push_token(master, HEADER_STRING, start, *i - start + 1);
		master->column++;
	}
	else
	{
		push_token(master, BAD, start, *i - start + 1);
		master->numline++;
		master->column = 1;
	}
}

void    create_token_header(t_asm *master, int *i, char *str, int start)
{
	if (ft_strncmp(&str[*i], COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING)) == 0)
	{
		i[0] += ft_strlen(COMMENT_CMD_STRING);
		push_token(master, HEADER_COMMENT, start, *i - start);
		master->column++;
	}
	else if (ft_strncmp(&str[*i], NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)) == 0)
	{
		i[0] += ft_strlen(NAME_CMD_STRING);
		push_token(master, HEADER_NAME, start, *i - start);
		master->column++;
	}
	while (str[i[0]] && str[i[0]] != '\n' && delimiter(str[i[0]], "s"))
		i[0]++;
    start = *i;
	if (str[i[0]] ==  '"')
       create_token_string_header(master, i, start, str);
	else if (str[i[0]] && str[i[0]] == '\n')
	{
			master->numline++;
			master->column = 1;	
	}
    else
    	create_token_bad(master, i, str, start);
}
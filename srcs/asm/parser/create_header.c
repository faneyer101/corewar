/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   create_header.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: faneyer <faneyer@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/17 01:39:22 by faneyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/17 02:48:38 by faneyer     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../../includes/asm.h"

static void	parser_header_name(t_asm *master, t_token *token)
{
	master->parser.name = 1;
	token = token->next;
	if (token && token->kind == HEADER_STRING && (token->next == NULL || token->next->kind == COMMENT))
	{
		if ((ft_strlen(token->data) - 2) < PROG_NAME_LENGTH && (ft_strlen(token->data) - 2) > 0)
			ft_strncpy(master->header.prog_name, &token->data[1], (ft_strlen(&token->data[1]) - 1));
		else
        {
			ft_printf("Name too long or this name is bad (\"\"). Please give him the good name.\n");
            master->error_parser++;
        }
    }
	else
	{
		master->error_parser++;
        if (token != NULL)
		{
            while (token->next != NULL)
		    	token = token->next;
		    ft_printf("[%d][%d] problem syntax ==> {RED}%s{END}\n", token->numline, token->column, token->data);
        }
        else
            ft_printf("Need one name\n");
    }
}

static void	parser_header_comment(t_asm *master, t_token *token)
{
	master->parser.comment = 1;
	token = token->next;
	if (token && token->kind == HEADER_STRING && (token->next == NULL || token->next->kind == COMMENT))
	{
		if ((ft_strlen(token->data) - 2) < COMMENT_LENGTH)
			ft_strncpy(master->header.comment, &token->data[1], ft_strlen(&token->data[1]) - 1);
		else
        {
			ft_printf("Comment too long\n");
            master->error_parser++;
        }
    }
	else
	{
		master->error_parser++;
        if (token != NULL)
		{
            while (token->next != NULL)
		    	token = token->next;
		    ft_printf("[%d][%d] problem syntax ==> {RED}%s{END}\n", token->numline, token->column, token->data);
        }
        else
            ft_printf("Need comment\n");
    }
}

void	parser_header(t_asm *master, t_token *token)
{
	if (token->kind == HEADER_NAME)
	{
		if (master->parser.name == 0)
			parser_header_name(master, token);
		else
        {
			ft_printf("This champion need juste one .name\n");
            master->error_parser++;
        }
    }
	else if (token->kind == HEADER_COMMENT)
	{
		if (master->parser.comment == 0)
			parser_header_comment(master, token);
		else
        {
			ft_printf("Faire fonction pour free et exit. Fichier peu contenir qu'un comment\n");
            master->error_parser++;
        }
    }
}
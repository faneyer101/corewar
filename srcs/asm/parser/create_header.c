/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   create_header.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: faneyer <faneyer@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/17 01:39:22 by faneyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/17 16:56:53 by faneyer     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../../includes/asm.h"

static void	parser_header_name(t_asm *master, t_token **token)
{
	master->parser.name = 1;
	token[0] = token[0]->next;
	if (token && token[0]->kind == HEADER_STRING && (token[0]->next == NULL || token[0]->next->kind == COMMENT))
	{
		if ((ft_strlen(token[0]->data) - 2) < PROG_NAME_LENGTH && (ft_strlen(token[0]->data) - 2) > 0)
			ft_strncpy(master->header.prog_name, &token[0]->data[1], (ft_strlen(&token[0]->data[1]) - 1));
		else
        {
			ft_printf("Name too long or this name is bad (\"\"). Please give him the good name.\n");
            master->error_parser++;
        }
    }
	else
	{
		master->error_parser++;
        if (token[0] != NULL)
		{
            while (token[0]->next != NULL)
		    	token[0] = token[0]->next;
		    ft_printf("parser[{GREEN}line:%d{END}][{GREEN}column:%d{END}]Error of syntax{RED}|%s|{END}\n", token[0]->numline, token[0]->column, token[0]->data);
        }
        else
            ft_printf("Need one name\n");
    }
}

static void	parser_header_comment(t_asm *master, t_token **token)
{
	master->parser.comment = 1;
	token[0] = token[0]->next;
	if (token[0] && token[0]->kind == HEADER_STRING && (token[0]->next == NULL || token[0]->next->kind == COMMENT))
	{
		if ((ft_strlen(token[0]->data) - 2) < COMMENT_LENGTH)
			ft_strncpy(master->header.comment, &token[0]->data[1], ft_strlen(&token[0]->data[1]) - 1);
		else
        {
			ft_printf("Comment too long\n");
            master->error_parser++;
        }
    }
	else
	{
		master->error_parser++;
        if (token[0] != NULL)
		{
            while (token[0]->next != NULL)
		    	token[0] = token[0]->next;
		    ft_printf("parser[{GREEN}line:%d{END}][{GREEN}column:%d{END}]error of syntax{RED}|%s|{END}\n", token[0]->numline, token[0]->column, token[0]->data);
        }
        else
            ft_printf("Need comment\n");
    }
}

void	parser_header(t_asm *master, t_token **token)
{
	if (token[0]->kind == HEADER_NAME)
	{
		if (master->parser.name == 0)
			parser_header_name(master, token);
		else
        {
			ft_printf("This champion need juste one .name\n");
            master->error_parser++;
        }
    }
	else if (token[0]->kind == HEADER_COMMENT)
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_header.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faneyer <faneyer@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 01:39:22 by faneyer           #+#    #+#             */
/*   Updated: 2020/06/04 23:24:46 by faneyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/asm.h"

void		norme_parser_header_comment(t_asm *master, t_token **token)
{
	master->error_parser++;
	if (token[0] != NULL)
	{
		while (token[0]->next != NULL)
			token[0] = token[0]->next;
		ft_printf("parser[{GREEN}line:%d{END}][{GREEN}column:%d{END}]",
			token[0]->numline, token[0]->column);
		ft_printf("Error of syntax{RED}|%s|{END}\n", token[0]->data);
	}
	else
		ft_printf("Need one comment\n");
}

void		norme_parser_header_name(t_asm *master, t_token **token)
{
	master->error_parser++;
	if (token[0] != NULL)
	{
		while (token[0]->next != NULL)
			token[0] = token[0]->next;
		ft_printf("parser[{GREEN}line:%d{END}][{GREEN}column:%d{END}]",
			token[0]->numline, token[0]->column);
		ft_printf("Error of syntax{RED}|%s|{END}\n", token[0]->data);
	}
	else
		ft_printf("Need one name\n");
}

static void	parser_header_name(t_asm *master, t_token **token)
{
	master->parser.name = 1;
	token[0] = token[0]->next;
	if (token[0] && token[0]->kind == HEADER_STRING &&
	(token[0]->next == NULL || token[0]->next->kind == COMMENT))
	{
		if ((ft_strlen(token[0]->data) - 2) <= PROG_NAME_LENGTH &&
		(ft_strlen(token[0]->data) - 2) > 0)
			ft_strncpy(master->header.prog_name, &token[0]->data[1],
			(ft_strlen(&token[0]->data[1]) - 1));
		else if ((ft_strlen(token[0]->data) - 2) == 0)
		{
			ft_printf("Name is empty (\"\"). Please give him the good name.\n");
			master->error_parser++;
		}
		else
		{
			ft_printf("Champion name too long (Max length %d)\n",
			PROG_NAME_LENGTH);
			master->error_parser++;
		}
	}
	else
		norme_parser_header_name(master, token);
}

static void	parser_header_comment(t_asm *master, t_token **token)
{
	master->parser.comment = 1;
	token[0] = token[0]->next;
	if (token[0] && token[0]->kind == HEADER_STRING &&
	(token[0]->next == NULL || token[0]->next->kind == COMMENT))
	{
		if ((ft_strlen(token[0]->data) - 2) <= COMMENT_LENGTH)
			ft_strncpy(master->header.comment, &token[0]->data[1],
			ft_strlen(&token[0]->data[1]) - 1);
		else
		{
			ft_printf("Champion comment too long (Max length %d)\n",
			COMMENT_LENGTH);
			master->error_parser++;
		}
	}
	else
		norme_parser_header_comment(master, token);
}

void		parser_header(t_asm *master, t_token **token)
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
			ft_printf("This champion need just one .comment\n");
			master->error_parser++;
		}
	}
}

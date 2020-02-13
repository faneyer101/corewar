/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main_lexer.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: faneyer <faneyer@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/10 16:33:44 by faneyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/13 18:49:44 by faneyer     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
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

int		delimiter(char c, char *analyse)
{
	if (c != '\0')
	{
		//printf("DELIMITEUR |%c|%s|\n", c, analyse);
		if (ft_strchr(analyse, 's'))
			if (ft_isspace(c))
				return (TRUE);
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

void	create_token_comment(t_asm *master, int *i, char *str)
{
	int	start;

	start = *i;
	//printf("DEBUG |%c|%s|%d|%d|\n", str[*i], &str[*i], *i, start), fflush(stdout);
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
	while (str[*i] && str[*i] != '\n' && delimiter(str[*i], "s"))
		i[0]++;
	if (delimiter(str[*i], "*"))
	{
		start = *i;
		i[0]++;
		while (str[*i] && str[*i] != '\n' && str[*i] != DSTRING)
			i[0]++;
		if (str[*i] && str[*i] == DSTRING)
			push_token(master, HEADER_STRING, start, *i - start + 1);
		master->column++;
	}
}

int		control_label_declaration(char *str)
{
	int i;

	i = 0;
	while (str[i] && !delimiter(str[i], "s"))
		i++;
	if (str[i - 1] == LABEL_CHAR)
		return (TRUE);
	return (FALSE);
}

int		check_param(t_asm *master, char *str, int i)
{
	while (i < 16)
	{
		if (ft_strncmp(master->tab_op[i].name, str, ft_strlen(master->tab_op[i].name)) == 0)
			return (TRUE);
		i++;
	}
	return (FALSE);
}

void	create_labbel_declaration(t_asm *master, int *i, char *str)
{
	int	start;

	start = *i;
	while (str[*i] && str[*i] != LABEL_CHAR)
		i[0]++;
	push_token(master, LABEL_DECLARATION, start, *i - start + 1);	
	master->column++;
}



void	create_token_param(t_asm *master, int *i, char *str)
{
	int	start;

	if (str[*i] == '\0')
		return ;
	while (str[*i] && delimiter(str[*i], "s") && str[*i] && str[*i] != '\n')
		i[0]++;
	if (str[i[0]] && str[i[0]] == 'r' && str[i[0] + 1] && ft_isdigit(str[i[0] + 1]))
	{
		i[0]++;
		start = *i;
		while (ft_isdigit(str[i[0]]))
			i[0]++;
		push_token(master, REGISTRE, start, i[0] - start);
		master->column++;
	}
	else if (str[i[0]] && str[*i] == DIRECT_CHAR && str[i[0] + 1] == LABEL_CHAR)
	{
		i[0] += 2;
		start = *i;
		while (cmp_label_chars(str[i[0]], 0))
			i[0]++;
		push_token(master, LABEL_DIRECT, start, i[0] - start);
		master->column++;
	}
	else if (str[i[0]] && str[*i] == LABEL_CHAR)
	{	
		start = *i;
		while (cmp_label_chars(str[i[0]], 0))
			i[0]++;
		push_token(master, LABEL_INDIRECT, start, i[0] - start);
		master->column++;
	}
	else if (str[i[0]] && str[i[0]] == DIRECT_CHAR && (ft_isdigit(str[i[0] + 1]) || str[i[0] + 1] == '-'))
	{
		i[0]++;
		start = *i;
		if (str[i[0]] == '-')
			i[0]++;
		while (ft_isdigit(str[i[0]]))
			i[0]++;
		push_token(master, NUM_DIRECT, start, i[0] - start);
		master->column++;
	}
	else if (str[i[0]] && (ft_isdigit(str[i[0]]) || str[i[0]] == '-'))
	{
		start = *i;
		if (str[i[0]] == '-')
			i[0]++;
		while (ft_isdigit(str[i[0]]))
			i[0]++;
		push_token(master, NUM_DIRECT, start, i[0] - start);
		master->column++;
	}
	if (str[i[0]] && str[i[0]] == SEPARATOR_CHAR)
	{
		push_token(master, SEPARATOR, i[0], 1);
		i[0]++;
		master->column++;
	}
}

void	create_token_name_funtion(t_asm *master, int *i, char *str)
{
	int	j;

	j = 0;
	while (j < 16)
	{
		if (ft_strncmp(master->tab_op[j].name, &str[*i], ft_strlen(master->tab_op[j].name)) == 0 &&
			delimiter(str[*i + ft_strlen(master->tab_op[j].name)], "s") &&
			str[ft_strlen(master->tab_op[j].name)] != '\n')
		{
			push_token(master, FONCTION, i[0], ft_strlen(master->tab_op[j].name));
			break;
		}
		j++;
	}
	master->column++;
	i[0] += ft_strlen(master->tab_op[j].name);
	while (str[*i] && str[*i] != '\n' && delimiter(str[*i], "s"))
		create_token_param(master, i, str);
}

void	init_token(t_asm* master)
{
	int	i;

	i = -1;
	while (++i <= master->numline)
        master->tab_token[i] = NULL;
	master->numline = 1;
	master->column = 1;
}

int 	main_lexer2(t_asm *master, int i)
{
	if(!(master->tab_token = (t_token**)malloc(sizeof(t_token*) * (master->numline + 1))))
		return (ft_printf("a faire une fonction pour free avant et exit 0\n"));
    init_token(master);
    while (++i < master->size_read_total && master->buff_read[i])
    {
        if (master->buff_read[i] && master->buff_read[i] == '\n')
		{
			//push_token(master, NEW_LINE, i, 1);
			master->numline++;
			master->column = 1;
            continue;
		}
		else if (delimiter(master->buff_read[i], "s"))
			continue;
		else if (delimiter(master->buff_read[i], "#"))
			create_token_comment(master, &i, master->buff_read);
        else if (delimiter(master->buff_read[i], "nc"))
			create_token_header(master, &i, master->buff_read, i);
		else if (cmp_label_chars(master->buff_read[i], 0) &&
				control_label_declaration(&master->buff_read[i]))
			create_labbel_declaration(master, &i, master->buff_read);
		else if (check_param(master, &master->buff_read[i], 0))
			create_token_name_funtion(master, &i, master->buff_read);
		//else
		//	ft_printf("Have a probleme of syntax on line %d column %d\n",
		//		master->numline, master->column);
    }
    return (0);
}
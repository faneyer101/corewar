/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parsing.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: faneyer <faneyer@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/06 08:20:27 by faneyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/07 21:01:54 by faneyer     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/asm.h"

int     search_string(char *line)
{
    int cmp_string;
    int i;

    cmp_string = 0;
    i = 0;
    while (line[i])
    {
        if (line[i] == '"')
            cmp_string++;
        i++;
    }
    if (cmp_string != 0 && cmp_string >= 2)
        return (1);
    return (0);
}

void    create_header(char *line, t_asm *master)
{
    if (search_string(line) != 1)
    {
        ft_printf("miss string for name or comment\n");
        ft_strdel(&line);
        exit(0);
    }
    if (ft_strncmp(line, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)) == 0 && master->header.prog_name[0] == '\0')
        if (ft_strlen(line) < PROG_NAME_LENGTH + ft_strlen(NAME_CMD_STRING))
            ft_memcpy(master->header.prog_name, &(*(ft_strchr(line, '"') + 1)), ft_strcspn(&(*(ft_strchr(line, '"') + 1)), "\"")); //voir pour gerer double cote en string si plus de 2
        else
		{	
			ft_strdel(&line);
            ft_printf("Name too long\n");
			exit(0);
		}
    else if (ft_strncmp(line, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING)) == 0 && master->header.comment[0] == '\0')
        if (ft_strlen(line) < COMMENT_LENGTH + ft_strlen(COMMENT_CMD_STRING))
            ft_memcpy(master->header.comment, &(*(ft_strchr(line, '"') + 1)), ft_strcspn(&(*(ft_strchr(line, '"') + 1)), "\"")); //voir pour gerer double cote en string si plus de 2
        else
		{
			ft_strdel(&line);
            ft_printf("Comment too long\n");
			exit (0);
		}
    else
	{
		ft_strdel(&line);
        ft_printf("Choose juste one name and/or one comment\n");
		exit (0);
	}
}

/*

void     create_prog_champion(char *line, t_asm *master)
{
    int i;

    i = -1;
    while (++i < 17)
    {
        //pointeur sur fonction pour cheek le tab de structure si cmp est presente
    }
}

*/

int     start_parsing(t_asm *master)
{
	int	i;

	i = 0;
	while (master->split_read[i])
	{
		printf("%s\n", master->split_read[i]);
    	search_comment_char(master->split_read[i], 0);
		if (ft_strncmp(master->split_read[i], ".", 1) == 0)
        	create_header(master->split_read[i], master);
   // 	else if (search_name_op(*line))
     // 	create_prog_champion(*line, master);
    /*	else
		{
        	ft_printf("bad syntax or bad word on the asm\n");
			free_split(master);
			exit (0);
		}
		*/i++;
	}
    return (0);
}
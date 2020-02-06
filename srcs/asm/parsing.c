/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parsing.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: faneyer <faneyer@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/06 08:20:27 by faneyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/06 16:44:16 by faneyer     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/corewar.h"

void    create_header(char *line, t_asm *master)
{
    static char name = '\0';
    static char comment = '\0';

    if (ft_strncmp(line, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)) == 0 && name == '\0')
    {
        name = '1';
        if (ft_strlen(line) < PROG_NAME_LENGTH + ft_strlen(NAME_CMD_STRING))
            ft_memcpy(master->header.prog_name, &(*(ft_strchr(line, '"') + 1)), ft_strcspn(&(*(ft_strchr(line, '"') + 1)), "\""));
        else
            ft_printf("Name trop grand\n");
    }
    else if (comment == '\0')
    {
        comment = '1';
        if (ft_strlen(line) < COMMENT_LENGTH + ft_strlen(COMMENT_CMD_STRING))
            ft_memcpy(master->header.comment, &(*(ft_strchr(line, '"') + 1)), ft_strcspn(&(*(ft_strchr(line, '"') + 1)), "\""));
        else
            ft_printf("Commentaire trop grand\n");
    }
    else
        ft_printf("Choose juste one name et/ou one comment\n");
}

void    search_comment_char(char **line, int i)
{
    while (line[0][i] != '\0' && line[0][i] != COMMENT_CHAR)
        i++;
    if (line[0][i] != '\0' && line[0][i] == COMMENT_CHAR)
        line[0][i] = '\0';
}

int     start_parsing(char **line, t_asm *master)
{
    
    
    search_comment_char(line, 0);
    if (*line == '\0')
    {
        ft_strdel(line);
        return (1);
    }
    if (ft_strncmp(*line, NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)) == 0 || ft_strncmp(*line, COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING)) == 0)
        create_header(*line, master);

    //gestion prog
    
    ft_strdel(line);

    return (0);
}
/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   toolsparsing.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: faneyer <faneyer@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/07 09:19:03 by faneyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/07 20:57:04 by faneyer     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/asm.h"

void    search_comment_char(char *line, int i)
{
    while (line[i] != '\0' && line[i] != COMMENT_CHAR)
        i++;
    if (line[i] != '\0' && line[i] == COMMENT_CHAR)
        line[i] = '\0';
}

void	free_split(t_asm *master)
{
	int	i;

	i = 0;
	while (master->split_read[i])
	{
		ft_strdel(&master->split_read[i]);
		i++;
	}
	ft_strdel(&master->split_read[i]);
	master->split_read = NULL;
	free(master->split_read);
}
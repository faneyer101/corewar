/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print_error.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: faneyer <faneyer@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/09 01:05:17 by faneyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/13 07:27:39 by faneyer     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../../includes/asm.h"

void    print_error_before_read(char *msg_error, int fd, char *buff, char *line)
{
    if (line)
        ft_strdel(&line);
    if (buff)
        ft_strdel(&buff);
    if (fd > 0)
        close(fd);
    ft_printf("%s", msg_error);
    exit(0);
}

void    printf_error_lexer(t_asm *master, char *msg_error)
{
    if (master->tab_token)
        free_tab_token(master);
    if (master->split_read[0])
       free_split(master, 0);
    ft_printf("{RED}{BOLD}%s on line %d{BLUE}\nLines empty are not count{END}\n",
        msg_error, master->numline);
    exit(0);
}

/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   writefile.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: faneyer <faneyer@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/06 09:51:41 by faneyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/06 17:59:23 by faneyer     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/corewar.h"

int create_namefile(char *name, char namefile[0][ft_strlen(name) + 3])
{
    int i;

    i = -1;
    while (name[++i])
    {
        if (name[i] == '.')
        {
            name[i + 1] = '\0';
            break;
        }
    }
    ft_strcpy(namefile[0], name);
    i = 0;
    while (namefile[0][i])
        i++;
    namefile[0][i] = 'c';
    namefile[0][i + 1] = 'o';
    namefile[0][i + 2] = 'r';
    return (0);
}

void    swap_magic(t_asm *master)
{
    unsigned char a[5];

    ft_bzero(a, 5);
    master->header.magic = COREWAR_EXEC_MAGIC;
    a[0] = (master->header.magic >> 24) & 0xFF;
    a[1] = (master->header.magic >> 16) & 0xFF;
    a[2] = (master->header.magic >> 8) & 0xFF;
    a[3] = (master->header.magic) & 0xFF;
    master->header.magic = a[0] + (a[1] << 8) + (a[2] << 16) + (a[3] << 24);
}

int init_write_file(t_asm *master, char *name)
{
    int fd;
    char namefile[ft_strlen(name) + 3];

    ft_bzero((void*)&namefile, ft_strlen(name) + 3);
    if (create_namefile(name, &namefile) == -1)
        return (-1);
    if ((fd = open(namefile, O_CREAT | O_WRONLY | O_TRUNC, 0600)) == -1)
     	return (-1);
    swap_magic(master);
    write(fd, &master->header, sizeof(t_header));
    ft_printf("writting %s ok\n", namefile);
    return (0);
}
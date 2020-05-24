/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   writefile.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faneyer <faneyer@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 09:45:22 by faneyer           #+#    #+#             */
/*   Updated: 2020/05/24 14:44:01 by faneyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/asm.h"

int		create_namefile(char *name, char namefile[0][ft_strlen(name) + 3])
{
	int i;

	i = -1;
	ft_strcpy(namefile[0], name);
	i = 0;
	while (namefile[0][i])
		i++;
	namefile[0][i - 1] = 'c';
	namefile[0][i] = 'o';
	namefile[0][i + 1] = 'r';
	return (0);
}

void	swap_magic(t_asm *master)
{
	unsigned char a[4];

	ft_bzero(a, 4);
	master->header.magic = COREWAR_EXEC_MAGIC;
	a[0] = (master->header.magic >> 24) & 0xFF;
	a[1] = (master->header.magic >> 16) & 0xFF;
	a[2] = (master->header.magic >> 8) & 0xFF;
	a[3] = (master->header.magic) & 0xFF;
	master->header.magic = a[0] | a[1] << 8 | a[2] << 16 | a[3] << 24;
}

void	swap_size(t_asm *master)
{
	unsigned char a[4];

	ft_bzero(a, 4);
	master->header.prog_size = master->interpretor.index;
	a[0] = (master->header.prog_size >> 24) & 0xFF;
	a[1] = (master->header.prog_size >> 16) & 0xFF;
	a[2] = (master->header.prog_size >> 8) & 0xFF;
	a[3] = (master->header.prog_size) & 0xFF;
	master->header.prog_size = a[0] | a[1] << 8 | a[2] << 16 | a[3] << 24;
}

int		init_write_file(t_asm *master, char *name)
{
	int		fd;
	char	namefile[ft_strlen(name) + 3];

	ft_bzero((void*)&namefile, ft_strlen(name) + 3);
	if (create_namefile(name, &namefile) == -1)
		return (-1);
	swap_size(master);
	swap_magic(master);
	if ((fd = open(namefile, O_CREAT | O_WRONLY | O_TRUNC, 0600)) == -1)
		return (-1);
	write(fd, &master->header, sizeof(t_header));
	write(fd, &master->interpretor.code_champ, sizeof(unsigned char) *
	master->interpretor.index);
	ft_printf("Writing output program to %s done\n", namefile);
	close(fd);
	return (0);
}

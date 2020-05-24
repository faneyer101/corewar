/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faneyer <faneyer@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 20:51:36 by faneyer           #+#    #+#             */
/*   Updated: 2020/05/24 20:52:16 by faneyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/asm.h"

void	stock_buff(char *line, t_asm *master, int fd)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\n')
			master->maxline++;
		i++;
	}
	if (!(master->buff_read = (char*)realloc(master->buff_read,
	sizeof(char) * (ft_strlen(master->buff_read) + ft_strlen(line) + 1))))
		print_error_before_read("problem for reallocate memory\n", fd,
		master->buff_read, line);
	ft_strcpy(&master->buff_read[ft_strlen(master->buff_read)], line);
	ft_bzero(line, 16);
}

void	count_new_line(t_asm *master, char *line, int ret)
{
	while (line[ret])
	{
		if (line[ret] == '\n')
			master->maxline++;
		ret++;
	}
}

int		read_file(t_asm *master, int fd, char *line, int ret)
{
	ft_bzero(line, 16);
	if ((ret = read(fd, line, 10)) <= 0)
	{
		ft_printf("file empty\n");
		return (-1);
	}
	master->size_read_total += ret;
	count_new_line(master, line, 0);
	if (!(master->buff_read = ft_strdup(line)))
		return (-1);
	ft_bzero(line, 16);
	while ((ret = read(fd, line, 10)) > 0)
	{
		if (ret != (int)ft_strlen(line))
		{
			ft_printf("file bad syntax\n");
			return (-1);
		}
		stock_buff(line, master, fd);
		master->size_read_total += ret;
	}
	ft_strdel(&line);
	return (0);
}

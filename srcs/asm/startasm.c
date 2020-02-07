/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   startasm.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: faneyer <faneyer@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/04 12:08:14 by faneyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/07 20:56:23 by faneyer     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/asm.h"

void	stock_buff(char *line, t_asm *master)
{
	int	i;
	
	i = 0;
	while (master->buff_read[i])
		i++;
	if (!(master->buff_read = (char*)realloc(master->buff_read, sizeof(char) * (ft_strlen(master->buff_read) + ft_strlen(line) + 1))))
	{
		ft_strdel(&line);
		ft_strdel(&master->buff_read);
		exit(0);
	}
	ft_strcpy(&master->buff_read[i], line);
}

int	read_file(t_asm *master, int fd, char *line, int ret)
{
	if (!(line = (char*)malloc(sizeof(char) * (16))))
		exit (0);
	ft_bzero(line, 16);
	if ((ret = read(fd, line, 10)) < 0)
	{
		ft_printf("file empty\n");
		ft_strdel(&line);
		return (-1);
	}
	if (!(master->buff_read = ft_strdup(line)))
	{
		ft_strdel(&line);
		return (-1);
	}
	ft_bzero(line, 16);
	while ((ret = read(fd, line, 10)) > 0)
	{
		if (ret != (int)ft_strlen(line))
		{	
			ft_printf("file bad syntax\n");	
			ft_strdel(&line);
			return (-1);
		}
		stock_buff(line, master);
		ft_bzero(line, 16);
	}
	ft_strdel(&line);
	return (0);
}

int	main(int ac, char **av)
{
	int		fd;
	t_asm	master;

	if (ac > 1)
	{
		ft_bzero(&master, sizeof(t_asm));
		init_op_tab((t_op **)&(master.tab_op));
		if ((fd = open(av[1], O_RDONLY)) == -1)
			exit (0);
		if (read_file(&master, fd, NULL, 1) == -1)
		{
			close(fd);
			exit(0);
		}
		printf("%s\n", master.buff_read);
		if (!(master.split_read = ft_strsplit(master.buff_read, '\n')))
		{
			ft_strdel(&master.buff_read);
			close(fd);
			exit(0);
		}
		start_parsing(&master);
		init_write_file(&master, av[1]);
	}
	else
		ft_printf("you need file with extension .s for compile\n");
	return (0);
}
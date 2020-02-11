/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   startasm.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: faneyer <faneyer@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/04 12:08:14 by faneyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/11 10:40:19 by faneyer     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/asm.h"

void	stock_buff(char *line, t_asm *master, int fd)
{
	int	i;
	
	i = 0;
	while (master->buff_read[i])
		i++;
	if (!(master->buff_read = (char*)realloc(master->buff_read, sizeof(char) * (ft_strlen(master->buff_read) + ft_strlen(line) + 1))))
		print_error_before_read("problem for reallocate memory\n", fd, master->buff_read, line);
	ft_strcpy(&master->buff_read[i], line);
}

int	read_file(t_asm *master, int fd, char *line, int ret)
{

	ft_bzero(line, 16);
	if ((ret = read(fd, line, 10)) < 0)
	{
		ft_printf("file empty\n");
		return (-1);
	}
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
		ft_bzero(line, 16);
	}
	ft_strdel(&line);
	return (0);
}

void	create_string_for_parser_lexer(int fd, t_asm *master, char **av)
{
	char	*line;

	if (!(line = (char*)malloc(sizeof(char) * (16))))
		exit (0);
	if ((fd = open(av[1], O_RDONLY)) == -1)
		print_error_before_read("file don't exist\n", fd, master->buff_read, line);
	if (read_file(master, fd, line, 1) == -1)
		print_error_before_read("problem for read\n", fd, master->buff_read, line);
	if (!(master->split_read = ft_strsplit(master->buff_read, '\n')))
	{
		ft_strdel(&master->buff_read);
		close(fd);
		exit(0);
	}
//	ft_strdel(&master->buff_read);
	close(fd);
}

int	main(int ac, char **av)
{
	t_asm	master;

	if (ac == 2)
	{
		ft_bzero(&master, sizeof(t_asm));
		printf("|%p|\n", &(master.tab_op)), fflush(stdout);
		init_op_tab((t_op**)&(master.tab_op));
		printf("|%p|%p|%p|%p|\n", &master.tab_op[0], &master.tab_op[1], &master.tab_op[2],
			&master.tab_op[3]);
		verif_error_first(&master, av[1]);
		create_string_for_parser_lexer(0, &master, av);
		
		main_lexer2(&master, -1);
	//	main_lexer(&master, 0);
		//print_token(&master);
		//main_parser(&master);
		//init_write_file(&master, av[1]);
	}
	else
		ft_printf("you need file with extension .s for compile\n");
	return (0);
}
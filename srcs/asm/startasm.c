/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   startasm.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faneyer <faneyer@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 12:08:14 by faneyer           #+#    #+#             */
/*   Updated: 2020/02/28 20:17:51 by faneyer          ###   ########lyon.fr   */
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

void	create_string_for_parser_lexer(int fd, t_asm *master, char *av)
{
	char	*line;

	if (!(line = (char*)malloc(sizeof(char) * (16))))
		exit(0);
	ft_bzero(line, 16);
	if ((fd = open(av, O_RDONLY)) == -1)
		print_error_before_read("file don't exist\n",
		fd, master->buff_read, line);
	if (read_file(master, fd, line, 1) == -1)
		print_error_before_read("problem for read\n",
		fd, master->buff_read, line);
	close(fd);
}

void	free_token_and_buff(t_asm *master)
{
	free_tab_token(master);
	ft_strdel(&master->buff_read);
}

void	verif_option(t_asm *master, char **av)
{
	int	i;

	if (ft_strncmp(av[1], "-", 1) == 0 && ft_strlen(av[1]) <= 3)
	{
		i = 1;
		while (av[1][i])
		{
			if (av[1][i] == 't')
				master->option.t = 1;
			if (av[1][i] == 'p')
				master->option.p = 1;
			if (av[1][i] != 'p' && av[1][i] != 't')
			{
				print_usage();
				break ;
			}
			i++;
		}
	}
	else
		print_usage();
}

void	end_asm(t_asm *master, char **av, int ac)
{
	if (master->error_parser == 0 && master->parser.name == 1 &&
		master->parser.comment == 1)
	{
		main_interpreteur(master, NULL);
		if (master->error_traitment == 0)
			init_write_file(master, av[ac - 1]);
	}
	if (master->parser.name == 0)
		ft_printf("need .name for compilation this champions\n");
	if (master->parser.comment == 0)
		ft_printf("need .comment for compilation this champions\n");
	free_undefine_label(master);
	free_define_label(master);
	free_token_and_buff(master);
}

int		main(int ac, char **av)
{
	t_asm	master;

	if (ac == 2 || ac == 3)
	{
		ft_bzero(&master, sizeof(t_asm));
		master.numline++;
		master.maxline++;
		if (ac == 3)
			verif_option(&master, av);
		init_op_tab((t_op*)(master.tab_op));
		verif_error_first(&master, av[ac - 1]);
		create_string_for_parser_lexer(0, &master, av[ac - 1]);
		main_lexer(&master, -1);
		if (master.option.t)
			print_token(&master, -1, NULL);
		main_parser(&master, NULL, -1);
		if (master.option.p)
			print_parser(&master);
		end_asm(&master, av, ac);
	}
	else
		print_usage();
	return (0);
}

/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   startasm.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: faneyer <faneyer@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/04 12:08:14 by faneyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/06 17:59:21 by faneyer     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

# include "../../includes/corewar.h"

int	main(int ac, char **av)
{
	
/*
**
**	gerer le nombre d'arguments inferieur a 1 || superieur a 2 error
**
*/

	int		fd;
	char	*line;
	t_asm	master;

	fd = 0;
	if (ac > 1)
	{
		ft_bzero(&master, sizeof(t_asm));
		ft_bzero(&master.header, sizeof(t_header));
		if ((fd = open(av[1], O_RDONLY)) == -1)
			return (-1);
		while (get_next_line(fd, &line) > 0)
		{
			printf("%s\n", line);
			if (start_parsing(&line, &master) == 1)
				continue;
		}
		printf("\n");
		init_write_file(&master, av[1]);
	}
	close(fd);
	return (0);
}


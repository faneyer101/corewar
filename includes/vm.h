/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   vm.h                                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nsalle <nsalle@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/10 12:13:30 by nsalle       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/11 11:24:58 by nsalle      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef	VM_H
# define VM_H
# include "op.h"
# include "../libft_nsalle/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct      	s_player
{
	int					fd;
}                   	t_player;

typedef struct      	s_vm
{
	int					dump;
	unsigned char		booldump;
	int					nb_player;
	t_player			players[MAX_PLAYERS];
}                   	t_vm;

void    all_checks(int argc, char **av, t_vm *vm);
void	usage(void);

#endif
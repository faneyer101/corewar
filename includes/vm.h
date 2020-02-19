/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   vm.h                                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nsalle <nsalle@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/10 12:13:30 by nsalle       #+#   ##    ##    #+#       */
/*   Updated: 2020/02/19 13:49:49 by nsalle      ###    #+. /#+    ###.fr     */
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
	unsigned char		magic[4];
	unsigned char		*code;
	char				*pname;
	char				name[PROG_NAME_LENGTH];
	char				comment[COMMENT_LENGTH];
	int					fd;
	int					size;
	int					start;
}                   	t_player;

typedef struct      	s_vm
{
	int					dump;
	unsigned char		booldump;
	unsigned char		arena[MEM_SIZE];
	int					nb_player;
	t_player			players[MAX_PLAYERS];
}                   	t_vm;

void    all_checks(int argc, char **av, t_vm *vm);
void	usage(void);
int		get_size(t_vm *vm, int ip);
void	check_realsize(t_vm *vm, int ip);
void	get_code(t_vm *vm, int ip);

void	init_arena(t_vm *vm);

#endif
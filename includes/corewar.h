/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   corewar.h                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: faneyer <faneyer@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/04 12:11:22 by faneyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/06 18:08:40 by faneyer     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef	COREWAR_H
# define COREWAR_H
# include "op.h"
# include "../libft_nsalle/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
#include<stdio.h> //////////// A EFFACER !!!!!!!!!!!!!!!!!!!!

typedef struct      s_asm
{
    t_header        header;
    char            string[CHAMP_MAX_SIZE + 1];
}                   t_asm;

typedef struct      s_op
{
    
}                   t_op;


int start_parsing(char **line, t_asm *master);

int init_write_file(t_asm *master, char *name);

/*
**  Fonction de debugs // d'affichages
*/

//int    print_ret_parsing(t_asm *master);

#endif

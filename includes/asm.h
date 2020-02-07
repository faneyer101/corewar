/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   asm.h                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: faneyer <faneyer@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/04 12:11:22 by faneyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/07 20:57:01 by faneyer     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef	ASM_H
# define ASM_H
# include "op.h"
# include "../libft_nsalle/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
#include<stdio.h> //////////// A EFFACER !!!!!!!!!!!!!!!!!!!!
/////gestion de read sans gnl et controler le retour de read en comparant avec
// ft_strlen sur buff


typedef struct              s_list_label
{
    int                     index_define;
    int                     define;
    char                    name[64];
    struct s_list_label     *next;
}                           t_list_label;

typedef struct              s_champion
{
    unsigned char           code_champ[CHAMP_MAX_SIZE + 1];
    t_list_label            *label;
}                           t_champion;

typedef struct              s_asm
{
    char                    *buff_read;
	char					**split_read;
    t_champion              champion;
    t_header                header;
    t_op                    tab_op[17];
}                           t_asm;

void						search_comment_char(char *line, int i);
int                         start_parsing(t_asm *master);
int                         init_write_file(t_asm *master, char *name);
void						free_split(t_asm *master);



/*
**  Fonction de debugs // d'affichages
*/

//int    print_ret_parsing(t_asm *master);

#endif

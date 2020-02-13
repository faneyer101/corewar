/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   asm.h                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: faneyer <faneyer@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/04 12:11:22 by faneyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/13 18:33:12 by faneyer     ###    #+. /#+    ###.fr     */
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

# define DSTRING '"'
# define DNEGATIF '-'

# define FALSE	0
# define TRUE	1



/*
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
*/
typedef enum				e_lexeme
{
	ZERO,
	HEADER_NAME,
	HEADER_COMMENT,
	HEADER_STRING,
	LABEL_DECLARATION,
	LABEL_DIRECT,
	LABEL_INDIRECT,
	NUM_DIRECT,
	NUM_INDIRECT,
	COMMENT,
	FONCTION,
	REGISTRE,
	SEPARATOR,
	NEW_LINE
}							t_lexeme;

typedef struct              s_token
{
	int						numline;
	int						column;
	t_lexeme				kind;	//categorie
	char					*data;	//data
	struct s_token			*next;
}							t_token;

typedef struct              s_asm
{
    char                    *buff_read;
	char					**split_read;
	int						numline;
	int						column;
	int						size_read_total;
	t_token					**tab_token;
	t_token					*error;
    t_header				*header;
    t_op                    tab_op[17];
}                           t_asm;


int 	                    main_lexer(t_asm *master, int i);
int							cheak_header(char *str);
int							cmp_label_chars(char c, int i);
//void    					create_token_for_header(t_asm *master, char *header, t_token *token);
//void    					create_token_comment(t_asm *master, char *comment, t_token *token);
//void    					create_token_champion(t_asm *master, char *code, t_token *token);
void	                    push_token(t_asm *master, t_lexeme lexeme, int index, int size);
void                        printf_error_lexer(t_asm *master, char *str_error);
void                        print_error_before_read(char *msg_error, int fd, char *buff, char *line);
int                         main_parser(t_asm *master);


int 						main_lexer2(t_asm *master, int i);
int							delimiter(char c, char *analyse);
void						verif_error_first(t_asm *master, char *file);


void    					free_tab_token(t_asm *master);
void						free_split(t_asm *master, int i);

int                         init_write_file(t_asm *master, char *name);

/*
**  Fonction de debugs // d'affichages
*/


void    					print_buff_read(t_asm *master);
void                        print_token(t_asm *master);
//int    print_ret_parsing(t_asm *master);

#endif

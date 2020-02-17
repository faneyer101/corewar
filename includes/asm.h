/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   asm.h                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: faneyer <faneyer@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/04 12:11:22 by faneyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/17 06:29:17 by faneyer     ###    #+. /#+    ###.fr     */
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




typedef struct              s_list_label
{
    int                     index_define;
    int                     define_parser; // -1 non definis, 0 definis parser, 1 definis solver
    char                    *name;
    struct s_list_label     *next;
}                           t_list_label;

/*
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
	BAD,
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

typedef struct 				s_parser
{	
	int						name;
	int						comment;
}							t_parser;

typedef struct              s_asm
{
	int						error_lexer;
	int						error_parser;
    char                    *buff_read;
	char					**split_read;
	int						numline;
	int						column;
	int						size_read_total;
	t_parser				parser;
	t_list_label			*define_label;
	t_token					**tab_token;
	t_token					*current;
    t_header				header;
    t_op                    tab_op[17];
}                           t_asm;


void                        printf_error_lexer(t_asm *master, char *str_error);
void                        print_error_before_read(char *msg_error, int fd, char *buff, char *line);
void						verif_error_first(t_asm *master, char *file);

int                         init_write_file(t_asm *master, char *name);
void						free_split(t_asm *master, int i);


void    					free_tab_token(t_asm *master);
/*
**			LEXER Creation de token pour le parser
*/

int 						main_lexer(t_asm *master, int i, int start);
int							delimiter(char c, char *analyse);
int							cmp_label_chars(char c, int i);
int							cheak_header(char *str);
void	                    push_token(t_asm *master, t_lexeme lexeme, int index, int size);
void    					create_token_header(t_asm *master, int *i, char *str, int start);
void						create_token_comment(t_asm *master, int *i, char *str, int start);
void						create_token_bad(t_asm *master, int *i, char *str, int start);
void						create_token_name_funtion(t_asm *master, int *i, char *str, int j);

/*
**			PARSER Verif si tout est ok pour passer a l'interpreteur
*/

int                         main_parser(t_asm *master);
void						parser_header(t_asm *master, t_token **token);




/*
**  Fonction de debugs // d'affichages
*/


void    					print_buff_read(t_asm *master);
void                        print_token(t_asm *master, int i, t_token *list);
//int    print_ret_parsing(t_asm *master);

#endif

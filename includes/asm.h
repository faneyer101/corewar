/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   asm.h                                            .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: faneyer <faneyer@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/04 12:11:22 by faneyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/21 16:05:09 by faneyer     ###    #+. /#+    ###.fr     */
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
	struct s_token			*lnext;
	
}							t_token;

typedef struct              s_list_label
{
    int                     index_define;
    int                     define_parser;
	int						numline;
	int						column;
	char					defaut;
	t_token					*info;
    char                    *name;
    struct s_list_label     *dnext;
    struct s_list_label     *unext;
}                           t_list_label;

typedef struct 				s_parser
{	
	int						name;
	int						comment;
	t_list_label			*undefine_label;
	t_list_label			*curent_label;
	t_list_label			*define_label;
}							t_parser;

typedef struct 				s_interpretor
{
	int						index;
    char					code_champ[CHAMP_MAX_SIZE + 1];
}							t_interpretor;


typedef struct 				s_option
{
	char					p;
	char					t;
}							t_option;

typedef struct              s_asm
{
	int						error_lexer;
	int						error_parser;
    char                    *buff_read;
	char					**split_read;
	int						numline;
	int						max_line;
	int						column;
	int						size_read_total;
	t_interpretor			interpretor;
	t_option				option;
	t_parser				parser;
	t_token					**tab_token;
	t_token					*current;
    t_header				header;
    t_op                    tab_op[17];
}                           t_asm;


void 						print_usage(void);
void                        printf_error_lexer(t_asm *master, char *str_error);
void                        print_error_before_read(char *msg_error, int fd, char *buff, char *line);
void						verif_error_first(t_asm *master, char *file);

int                         init_write_file(t_asm *master, char *name);
void						free_split(t_asm *master, int i);
void    					free_tab_token(t_asm *master);
/*
**			LEXER Creation de token pour le parser
*/

int 						main_lexer(t_asm *master, int i);
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

int                         main_parser(t_asm *master, t_token *list, int i);
int							verif_separator(t_asm *master, t_op function, t_token *verif);
int							verif_kind_bad(t_asm *master, t_token *list);
int							nb_param(t_token *list);
int							search_label(t_list_label *label, char *str);
int							print_error_parser_param(t_asm *master, char *msg_error, char *error, t_token *list);
int							print_error_parser_label(t_asm *master, char *msg_error, char *error, t_list_label *list);
int							verif_type_param(t_asm *master, t_token *list, t_op function, int i);
int							search_label_define(t_list_label *begin_define, t_token *data);
int							search_label_undefine(t_list_label *begin_define, t_token *data);
void						verif_declaration_label(t_asm *master, t_list_label *label);
void						declare_label_param(t_asm *master, t_token *list);
void						push_label_define(t_asm *master, t_token *token);
void						parser_header(t_asm *master, t_token **token);
void						declare_label_define(t_asm *master, t_token *token);
void						push_undefine_label(t_asm *master, t_token *data);
t_list_label				*create_label_undefine(t_token *data);

/*
**			INTERPRETEUR
*/

void						main_interpreteur(t_asm *master);



/*
**  Fonction de debugs // d'affichages
*/

void						print_parser(t_asm *master);
void    					print_buff_read(t_asm *master);
void                        print_token(t_asm *master, int i, t_token *list);
//int    print_ret_parsing(t_asm *master);

#endif

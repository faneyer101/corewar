/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faneyer <faneyer@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 12:11:22 by faneyer           #+#    #+#             */
/*   Updated: 2020/05/24 22:41:28 by faneyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H
# include "op.h"
# include "../libft_nsalle/libft.h"
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <limits.h>
# define DSTRING '"'
# define DNEGATIF '-'
# define FALSE	0
# define TRUE	1

/////A voir dans tools_f2.c (printf) division par 0 pas supporter avec compi clang-9

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

typedef struct				s_token
{
	int						direct;
	int						index_tab_op;
	int						index_function;
	int						call_index;
	int						numline;
	int						column;
	t_lexeme				kind;
	char					*data;
	struct s_token			*next;
	struct s_token			*lnext;
	struct s_token			*unext;
}							t_token;

typedef struct				s_list_label
{
	int						index_define;
	int						define_parser;
	int						numline;
	int						column;
	char					defaut;
	t_token					*info;
	char					*name;
	struct s_list_label		*dnext;
	struct s_list_label		*unext;
}							t_list_label;

typedef struct				s_parser
{
	int						name;
	int						comment;
	int						size_prog;
	t_list_label			*undefine_label;
	t_list_label			*curent_label;
	t_list_label			*define_label;
}							t_parser;

typedef struct				s_function
{
	int						index_declaration;
	int						index_tab;
	int						direct;
	int						octet;
	int						opcode;
}							t_function;

typedef struct				s_interpretor
{
	int						index;
	int						nb_label;
	char					code_champ[CHAMP_MAX_SIZE + 1];
	t_list_label			*begin_label;
	t_token					*wait_label;
	t_function				function;
}							t_interpretor;

typedef struct				s_option
{
	char					p;
	char					t;
}							t_option;

typedef struct				s_asm
{
	int						error_lexer;
	int						error_parser;
	int						error_traitment;
	char					*buff_read;
	int						numline;
	int						maxline;
	int						column;
	int						size_read_total;
	t_interpretor			interpretor;
	t_option				option;
	t_parser				parser;
	t_token					**tab_token;
	t_token					*current;
	t_header				header;
	t_op					tab_op[17];
}							t_asm;

int							read_file(t_asm *master, int fd,
								char *line, int ret);

/*
**			LEXER Creation de token pour le parser
*/

int							main_lexer(t_asm *master, int i);
int							delimiter(char c, char *analyse);
int							cmp_label_chars(char c, int i);
int							cheak_header(char *str);
void						verif_error_first(t_asm *master, char *file);
void						push_token(t_asm *master, t_lexeme lexeme,
								int index, int size);
void						create_token_header(t_asm *master, int *i,
								char *str, int start);
void						create_token_comment(t_asm *master, int *i,
								char *str, int start);
void						create_token_bad(t_asm *master, int *i, char *str,
								int start);
void						create_token_name_funtion(t_asm *master, int *i,
								char *str, int j);
void						cheack_label(int *i, char *str, int *direct);
void						lexer_registre(t_asm *master, int *i,
								char *str, int start);
void						lexer_num_direct(t_asm *master, int *i,
								char *str, int start);
void						lexer_num_indirect(t_asm *master, int *i,
								char *str, int start);
void						lexer_bad(t_asm *master, int *i, char *str);

/*
**			PARSER Verif si tout est ok pour passer a l'interpreteur
*/

void						main_parser(t_asm *master, t_token *list, int i);
int							verif_separator(t_asm *master, t_op function,
								t_token *verif, int i);
int							verif_kind_bad(t_asm *master, t_token *list);
int							nb_param(t_token *list);
int							search_label(t_list_label *label, char *str);
int							print_error_parser_label(t_asm *master,
								char *msg_error, char *error,
								t_list_label *list);
int							verif_type_param(t_asm *master, t_token *list,
								t_op function, int i);
int							search_label_define(t_list_label *begin_define,
								t_token *data);
int							search_label_undefine(t_list_label *begin_define,
								t_token *data);
void						verif_declaration_label(t_asm *master,
								t_list_label *label);
void						declare_label_param(t_asm *master, t_token *list);
void						push_label_define(t_asm *master, t_token *token);
void						parser_header(t_asm *master, t_token **token);
void						declare_label_define(t_asm *master, t_token *token);
void						push_undefine_label(t_asm *master, t_token *data);
void						create_token_label(t_asm *master, t_token *tlist);

t_list_label				*create_label_undefine(t_token *data);

/*
**			INTERPRETEUR
*/

void						main_interpreteur(t_asm *master, t_token *token);
void						init_struct_function(t_asm *master);
void						interpretor_function(t_asm *master, t_token *token);
void						push_label_undefine(t_asm *master, t_token *token);
void						registre(t_asm *master,
								int long long *calcul, t_token *t);
void						num_two_octets(t_asm *master,
								int long long *calcul, t_token *token);
void						num_four_octets(t_asm *master,
								long long int *calcul, t_token *token);
void						labbel_two_octets(t_asm *master,
								long long int *calcul,
								t_token *token, t_list_label *label);
void						labbel_four_octets(t_asm *master,
								long long int *calcul, t_token *token,
								t_list_label *label);
void						search_define_label(t_asm *master, t_token *token,
								int *index_define, t_list_label *curent);
int							init_write_file(t_asm *master, char *name);

/*
**  		Fonction de debugs // d'affichages
*/

void						print_usage(void);
void						print_parser(t_asm *master, t_list_label *label,
								t_token *info);
void						print_buff_read(t_asm *master);
void						print_token(t_asm *master, int i, t_token *list);
void						print_error_before_read(char *msg_error, int fd,
								char *buff, char *line);
void						printf_error_lexer(t_asm *master, char *str_error);
void						print_error_allocation(t_asm *master,
								char *function);
void						print_error_overflow(t_asm *master, int index,
								t_token *token, char *msg);
void						size_champ_max(t_asm *master);
void						print_msg_error_interpretor(t_asm *master,
								char *msg);
int							print_error_parser(t_asm *master, char *msg_error,
								char *error, t_token *list);

/*
**		FREE
*/

void						free_define_label(t_asm *master);
void						free_undefine_label(t_asm *master);
void						free_tab_token(t_asm *master);
void						free_token_and_buff(t_asm *master);
#endif

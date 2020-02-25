/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   op.h                                             .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: nsalle <nsalle@student.le-101.fr>          +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2013/10/04 11:33:27 by zaz          #+#   ##    ##    #+#       */
/*   Updated: 2020/02/25 16:19:47 by nsalle      ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */
/*
** Toutes les tailles sont en octets.
** On part du principe qu'un int fait 32 bits. Est-ce vrai chez vous ?
*/

//.extend peu etre un bonus ???????
//Les lignes vide, commentaires, tab ou space on ignore
//Chaque instructions se termine au saut de lignes


#ifndef OP_H
#define OP_H
//
#define IND_SIZE				2
//Taille en octets de l'argument T_REG
#define REG_SIZE				4
//
#define DIR_SIZE				4


//
# define REG_CODE				1
//
# define DIR_CODE				2
//
# define IND_CODE				3


//
#define MAX_ARGS_NUMBER			4
//
#define MAX_PLAYERS				4
//
#define MEM_SIZE				(4*1024)
//
#define IDX_MOD					(MEM_SIZE / 8)
//
#define CHAMP_MAX_SIZE			(MEM_SIZE / 6)

//commentaire tout ce qui suit jusqu'au \n on ignore
#define COMMENT_CHAR			'#'	//voir pour le gerer vide
//commentaire alternatif rajouter par RickY. A valider si on laisse ou pas
#define ALT_COMMENT_CHAR		';'	//voir pour le gerer vide
//Symbole d'appel de labbel/etiquette
#define LABEL_CHAR				':'	//voir pour le gerer vide
//Symbole qui definie le l'argument direct. Si il n'est pas present c'est indirect
#define DIRECT_CHAR				'%'	//voir pour le gerer vide
//Separateur arguments
#define SEPARATOR_CHAR			','	//voir pour le gerer vide

//caractere que peu contenir une etiquette
#define LABEL_CHARS				"abcdefghijklmnopqrstuvwxyz_0123456789"	//voir pour le gerer vide

//ligne vide ou juste .name c'est error
//definie la ligne avec le nom du champion. ==> .name "Batman" ou .name ""
#define NAME_CMD_STRING			".name"		//voir pour le gerer vide	
//je pense commentaire sur le champion gestion identique que .name
#define COMMENT_CMD_STRING		".comment"	//voir pour le gerer vide



//Nombre de registre maximum r1, r2, r3, ..., r16
#define REG_NUMBER				16
//
#define CYCLE_TO_DIE			1536
//
#define CYCLE_DELTA				50
//
#define NBR_LIVE				21
//
#define MAX_CHECKS				10

/*
**
*/

typedef char	t_arg_type;

#define T_REG					1
#define T_DIR					2
#define T_IND					4
#define T_LAB					8

/*
**
*/

//a verifier mais je pense limite de la longueur MAX de ==> NAME_CMD_STRING	
# define PROG_NAME_LENGTH		(128)
//a verifier mais je pense limite de la longueur MAX de ==> COMMENT_CMD_STRING	
# define COMMENT_LENGTH			(2048)
//
# define COREWAR_EXEC_MAGIC		0xea83f3

typedef struct			s_header
{
	unsigned int		magic;
	char				prog_name[PROG_NAME_LENGTH + 1];
	unsigned int		prog_size;
	char				comment[COMMENT_LENGTH + 1];
}						t_header;

typedef struct      	s_op
{
	char				name[8];
	int					nb_arg;
	char				args[3];
	int					numop;
	int					cycle;
	char				descr[64];
	int					octet;
	int					size_octet_dir;
}                   	t_op;

void					init_op_tab(t_op tab_op[17]);

#endif
/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   verif_oph.c                                      .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: faneyer <faneyer@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/11 08:13:44 by faneyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/11 11:31:51 by faneyer     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../includes/asm.h"

static void	print_error(char *msg_error)
{
	ft_printf("%s", msg_error);
	exit (0);
}

static int	cheak_label_chars(void)
{
	int	i;

	i = 0;
	while (LABEL_CHARS[i])
	{
		if (ft_isalnum(LABEL_CHARS[i]) == 0 && LABEL_CHARS[i] != '_')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

static void	verif_oph_egality_delimiter(void)
{
	if (delimiter(COMMENT_CMD_STRING[0], "d#Ns*") || delimiter(NAME_CMD_STRING[0], "d#Ns*") ||
		delimiter(SEPARATOR_CHAR, "#Ns*") || delimiter(DIRECT_CHAR, "#Ns*") ||
		delimiter(LABEL_CHAR, "#Ns*") || delimiter(ALT_COMMENT_CHAR, "dNs*") ||
		delimiter(COMMENT_CHAR, "dNs*") || delimiter(SEPARATOR_CHAR, "nc") ||
		delimiter(DIRECT_CHAR, "nc") || delimiter(LABEL_CHAR, "nc") ||
		delimiter(ALT_COMMENT_CHAR, "nc") || delimiter(COMMENT_CHAR, "nc") ||
		COMMENT_CHAR == ALT_COMMENT_CHAR || LABEL_CHAR == DIRECT_CHAR ||
		LABEL_CHAR == SEPARATOR_CHAR || LABEL_CHAR == DNEGATIF || DIRECT_CHAR == SEPARATOR_CHAR ||
		DIRECT_CHAR == DNEGATIF || SEPARATOR_CHAR == DNEGATIF)
		print_error("param op.h has bad delimiter. Need different\n");
}

static void	verif_cmd(t_asm *master, int i, int j)
{
	while (++i < 17)
	{
		j = -1;
		while (master->tab_op[i].name[++j])
			if (!ft_isalpha(master->tab_op[i].name[j]))
				print_error("name fonction op.c need juste alpha");
	}
	i = -1;
	while (++i < 17)
	{
		j = -1;
		while (++j < 17)
		{
			if (i != j && !ft_strcmp(master->tab_op[i].name, master->tab_op[j].name))
				print_error("op.c 2 fonction are identic name\n");
		}
	}
}

void	    verif_error_first(t_asm *master, char *file)
{
	int	i;

	i = 0;
	while (file[i])
		i++;
	if (file[i - 2] != '.' || file[i - 1] != 's')
		print_error("bad extension file. Need file with extension .s\n");
	verif_oph_egality_delimiter();
	verif_cmd(master, -1, -1);
	if (ft_strcmp(NAME_CMD_STRING, COMMENT_CMD_STRING) == 0)
		print_error("param op.h [.name] and [.comment] are need different\n");
	else if (COMMENT_CMD_STRING[0] == '\0' || NAME_CMD_STRING[0] == '\0' ||
		SEPARATOR_CHAR == '\0' || DIRECT_CHAR == '\0' || LABEL_CHAR == '\0' ||
		LABEL_CHARS[0] == '\0' || ALT_COMMENT_CHAR == '\0' || COMMENT_CHAR == '\0')
		print_error("op.h don't have params empty\n");
	else if (cheak_label_chars())
		print_error("op.h LABEL_CHARS need juste alpha and/or _ and/or digit. No other chars\n");
	else if (COREWAR_EXEC_MAGIC == 0)
		print_error("op.h Need magic exec different 0\n");
}
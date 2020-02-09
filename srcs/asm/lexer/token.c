/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   token.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: faneyer <faneyer@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/09 01:47:54 by faneyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/09 11:52:22 by faneyer     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../../includes/asm.h"

static t_lexer	*ft_create_elem(t_asm *master, char *s, int i[2], char type)
{
	t_lexer	*box;

	if (!(box = (t_lexer*)malloc(sizeof(t_lexer))))
		return (NULL);
    if (i[0] > 0)
        box->digit = '1';
	else if (type == 'S')
		box->string = '1';
	else if (type == 'D')
		box->delimiter = '1';
	if(!(box->data = ft_strndup(s, i[1])))
    {
        free(box);
        return (NULL);
    }
    box->numline = master->numline;
	box->next = NULL;
	return (box);
}

void	push_token(t_asm *master, char *str, int size, char type)
{
	t_lexer	*list;
    int digit;
    int i[2];

    digit = -1;
    while (str[++digit])
        if (ft_isdigit(str[digit]) == 0)
        {
            digit = 0;
            break;
        }
	list = master->lexer;
	if (list)
	{
		while (list->next != NULL)
			list = list->next;
        i[0] = digit;
        i[1] = size;
		if (!(list->next = ft_create_elem(master, str, i, type)))
            printf_error_lexer(master, "Crash allocate for memory\n");
		list = list->next;
	}
	else
		if (!(master->lexer = ft_create_elem(master, str, i, type)))
            printf_error_lexer(master, "Crash allocate for memory\n");
}


/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   print.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: faneyer <faneyer@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/25 18:52:42 by faneyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/25 18:56:55 by faneyer     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../../includes/asm.h"

void 	print_usage(void)
{
	ft_printf("{UND}Usage:{END}\n./asm [{YELL}opion{END}][{RED}file{END}]\n");
    ft_printf("{YELL}Option{END}:\n	t: print token\n");
    ft_printf("	p: print parser\n{RED}Extension file .s{END}\n\n");
	exit(0);
}
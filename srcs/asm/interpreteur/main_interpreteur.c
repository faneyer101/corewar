/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main_interpreteur.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: faneyer <faneyer@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/20 04:09:47 by faneyer      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/21 16:08:30 by faneyer     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../../../includes/asm.h"

void    main_interpreteur(t_asm *master)
{
    t_list_label    *label;
	//t_token         *token;

    label = master->parser.define_label;
    while (label)
    {
		
    	label = label->dnext;
    }

}
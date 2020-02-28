/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faneyer <faneyer@student.le-101.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/09 01:23:48 by faneyer           #+#    #+#             */
/*   Updated: 2020/02/28 09:47:10 by faneyer          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/asm.h"

void    print_token(t_asm *master, int i, t_token *list)
{
	ft_printf("{GREEN}Valeur lexeme\n{CYAN}0: {RED}ZERO|{CYAN}1: {RED}Name header|");
	ft_printf("{CYAN}2: {RED}Comment header|{CYAN}3: {RED}String header|{CYAN}4: {RED}Label declaration|");
	ft_printf("{CYAN}5: {RED}Label direct|{CYAN}6: {RED}Label indirect|{CYAN}7: {RED}Num direct|{CYAN}8: {RED}Num indirect|");
	ft_printf("{CYAN}9: {RED}Comment|{CYAN}10: {RED}Fonction|{CYAN}11: {RED}Registre|{CYAN}12: {RED}Separateur|{CYAN}13: {RED}BAD|{CYAN}14: {RED}New line{END}\n");
	while (++i < master->maxline)
	{	
		if (master->tab_token[i])
    		list = master->tab_token[i];
		else
			continue;
		while (list)
    	{
			if (list->kind == BAD)
        		ft_printf("[%d]Valeur LEXEME ==> {RED}%d{END} | ", i, list->kind);
			else
        		ft_printf("[%d]Valeur LEXEME ==> {CYAN}%d{END} | ", i, list->kind);
        	ft_printf("{YELL}{UND}Data: |%s|{END} Line %d | column %d\n", list->data,
				list->numline, list->column);
        	list = list->next;
    	}
	}
}

void    print_buff_read(t_asm *master)
{
    int i;

    i = -1;
    while (++i < master->size_read_total)
    {
        if (master->buff_read[i] && master->buff_read[i] == '\n' && ++master->numline)
            continue;
        else if (delimiter(master->buff_read[i], "s"))
			ft_printf("{CYAN}|%c|C'est un space{END}\n", master->buff_read[i]);
		else if (ft_isdigit(master->buff_read[i]))
			ft_printf("{BLUE}|%c|C'est un chiffre{END}\n", master->buff_read[i]);
		else if (ft_isalpha(master->buff_read[i]))
			ft_printf("{RED}|%c|C'est un char{END}\n", master->buff_read[i]);
		else
			ft_printf("{GREEN}|%c|C'est un delimiteur{END}\n", master->buff_read[i]);
    }
}

void	print_parser(t_asm *master)
{
	int				i;
	t_list_label	*label;
	t_token			*info;

	ft_printf("{GREEN}Valeur lexeme\n{CYAN}0: {RED}ZERO|{CYAN}1: {RED}Name header|");
	ft_printf("{CYAN}2: {RED}Comment header|{CYAN}3: {RED}String header|{CYAN}4: {RED}Label declaration|");
	ft_printf("{CYAN}5: {RED}Label direct|{CYAN}6: {RED}Label indirect|{CYAN}7: {RED}Num direct|{CYAN}8: {RED}Num indirect|");
	ft_printf("{CYAN}9: {RED}Comment|{CYAN}10: {RED}Fonction|{CYAN}11: {RED}Registre|{CYAN}12: {RED}Separateur|{CYAN}13: {RED}BAD|{CYAN}14: {RED}New line{END}\n");
	i = 0;
	label = master->parser.define_label;
	while (label)
	{
		if (label->name && label->define_parser == 1)
			ft_printf("{YELL}label declaration{END}:|%s|\n", label->name);
		else if (label->defaut == 1)
			ft_printf("{YELL}label declaration{END}:|Default|\n");
		info = label->info;
		while (info)
		{
			if (info->kind == FONCTION)
				ft_printf("{BLUE}Function{END}:|%s|\n", info->data);
			else
				ft_printf("	{GREEN}Param of function{END}:|%s|{GREEN}Type{END}|{CYAN}%d{END}|\n", info->data, info->kind);
			info = info->lnext;
		}
		label = label->dnext;
	}
}
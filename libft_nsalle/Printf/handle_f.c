/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_f.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/21 21:03:50 by jde-la-m          #+#    #+#             */
/*   Updated: 2020/06/03 15:14:01 by user42           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_printf.h"

void	pf_f_helper(va_list va, t_printf *pf, size_t flen)
{
	pf->ftp = pf_float_sizer(pf, va);
	pf_buffer_alloc(&pf->buff, ft_max(512, ft_max(pf->width,
		pf->precival)), pf);
	pf_flag_manager_f(pf->ftp, pf);
	if (!pf->finf && !pf->fnan)
	{
		if ((flen = pf_flen(pf->ftp) >= 17))
			pf_big_ftoa(pf->ftp, pf, 0);
		else
			pf_small_ftoa(pf->ftp, pf);
	}
	else
		pf->buff = pf->finf ? ft_strcpy(pf->buff, "inf")
					: ft_strcpy(pf->buff, "nan");
}

int		pf_f_handler(va_list va, t_printf *pf)
{
	int		i;
	char	*pchr;
	size_t	flen;

	i = 0;
	flen = 0;
	pf_f_helper(va, pf, flen);
	if ((pchr = ft_strchr(pf->buff, '.')))
		i = pf->precival - pf_count_digits(pchr + 1, 0);
	if (i > 0)
		ft_strpostpend(pf->buff, i, '0');
	i = pf->width - ft_strlen(pf->buff) - (pf->plus + pf->space)
		- (pf->finf == 2) - (pf->szero);
	if (pf->moins && i > 0)
		ft_strpostpend(pf->buff, i, (pf->zero ? '0' : ' '));
	if (i > 0 && !pf->moins)
		pf_strprepend(pf->buff, i, (pf->zero ? '0' : ' '), 0);
	if (pf->ftp >= 0)
		pf_add_plus(pf);
	if (pf->finf == 2 || pf->szero)
		pf_strprepend(pf->buff, 1, '-', ft_strspn(pf->buff, " "));
	if (pf->space && pf->ftp >= 0)
		pf_strprepend(pf->buff, 1, ' ', 0);
	ft_putstr(pf->buff);
	return (ft_delret(&pf->buff, ft_strlen(pf->buff)));
}

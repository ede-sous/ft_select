/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-sous <ede-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 06:21:10 by ede-sous          #+#    #+#             */
/*   Updated: 2017/09/26 01:21:58 by ede-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/slctlib.h"

t_lst				*stocklist(t_lst *lst, int value)
{
	static t_lst	*tmp;

	if (!value)
		tmp = lst;
	return (tmp);
}

int					recount_files(t_lst *list)
{
	int				i;

	i = 0;
	while (list->name != NULL)
	{
		i++;
		list = list->next;
	}
	return (i);
}

t_pad				stock_pad(t_pad pad, int value)
{
	static t_pad	tmp;

	if (!value)
		tmp = pad;
	stock_nbpages(tmp.page, 0);
	return (pad);
}

size_t				stock_nbpages(size_t nb, int value)
{
	static size_t	pages;

	if (!value)
		pages = nb;
	else if (value == -1)
		pages = 0;
	return (pages);
}

t_pad				verify_size(t_lst *tmp, t_pad pad, size_t total_len)
{
	size_t			len;

	pad.s = 1;
	while (tmp->name && (pad.line * 2 < pad.window_y))
	{
		len = ft_strlen(tmp->name) + 1;
		(len > pad.biggest_len ? pad.biggest_len = len : (pad).biggest_len);
		(pad).biggest_len_of_all = ((pad).biggest_len_of_all < (pad).biggest_len
				? (pad).biggest_len : (pad).biggest_len_of_all);
		pad.line++;
		stock_pad(pad, 0);
		if (pad.biggest_len_of_all > pad.window_x)
			ft_error(6);
		if (pad.biggest_len + total_len > pad.window_x)
		{
			pad.s = 0;
			break ;
		}
		tmp = tmp->next;
	}
	pad.biggest_len = 0;
	pad.line = 1;
	return (pad);
}

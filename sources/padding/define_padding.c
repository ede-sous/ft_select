/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_padding.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-sous <ede-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/01 04:11:00 by ede-sous          #+#    #+#             */
/*   Updated: 2017/09/26 00:49:48 by ede-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/slctlib.h"

static t_lst		*tpad(t_lst *tmp, t_pad *pad)
{
	size_t			len;

	len = ft_strlen(tmp->name) + 1;
	(len > (*pad).biggest_len ? (*pad).biggest_len = len : (*pad).biggest_len);
	(*pad).biggest_len_of_all = ((*pad).biggest_len_of_all < (*pad).biggest_len
			? (*pad).biggest_len : (*pad).biggest_len_of_all);
	tmp->line = (*pad).line++;
	tmp->column = (*pad).column;
	tmp->page = (*pad).page;
	return (tmp);
}

static t_lst		*treat_padding(t_lst *list, t_pad pad)
{
	t_lst			*tmp;
	size_t			total_len;

	tmp = list;
	total_len = 0;
	while (tmp->name && (pad.line = 1))
	{
		pad.biggest_len = 0;
		if ((pad = verify_size(tmp, pad, total_len)).s == 1)
			while (tmp->name && (pad.line * 2 < pad.window_y)
					&& (tmp = tpad(tmp, &pad)))
				tmp = tmp->next;
		total_len += pad.biggest_len + 2;
		if (pad.s == 0 || total_len >= pad.window_x)
		{
			total_len = 0;
			pad.column = 0;
			pad.page++;
		}
		pad.column++;
	}
	stock_pad(pad, 0);
	return (list);
}

static t_pad		start_padding(struct winsize w, size_t nb_files)
{
	t_pad			pad;

	pad.window_x = (w.ws_col <= 25 ? 0 : w.ws_col - 25);
	pad.window_y = (w.ws_row <= 25 ? 0 : w.ws_row - 25);
	pad.biggest_len = 1;
	pad.biggest_len_of_all = 0;
	pad.vertical = 0;
	pad.line = 1;
	pad.column = 1;
	pad.columns_per_page = 1;
	pad.page = 1;
	pad.number_of_pages = 1;
	pad.number_of_files = nb_files;
	while (nb_files > pad.columns_per_page * pad.number_of_pages)
		(pad.columns_per_page < 5 ? pad.columns_per_page++
		: pad.number_of_pages++);
	return (pad);
}

static t_pad		init_padding(size_t nb_files, struct winsize w, t_lst *tmp)
{
	t_pad			pad;
	size_t			max_len;
	size_t			opt_y;

	pad = start_padding(w, nb_files);
	opt_y = 0;
	if ((pad.vertical = ((nb_files / pad.columns_per_page))) > pad.window_y)
		pad.vertical = pad.window_y;
	if (pad.vertical <= 5)
	{
		while (tmp->name && !(max_len = 0))
		{
			while (tmp->name && (max_len + pad.biggest_len < pad.window_x)
					&& (max_len += pad.biggest_len))
				tmp = tmp->next;
			opt_y++;
		}
		pad.vertical = opt_y;
	}
	return (pad);
}

t_lst				*define_padding(t_lst *list, size_t nb_files)
{
	t_pad			pad;
	t_lst			*tmp;
	struct winsize	w;

	ioctl(0, TIOCGWINSZ, &w);
	pad = init_padding(nb_files, w, list);
	if (pad.window_y <= 5 || pad.window_x <= 5)
		return (NULL);
	if (!(list = treat_padding(list, pad)))
		return (NULL);
	tmp = list;
	while (tmp->name && !tmp->cursor)
		tmp = tmp->next;
	if (!tmp->name)
		list->cursor = 1;
	return (list);
}

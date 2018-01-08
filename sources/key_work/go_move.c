/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_move.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-sous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/09 04:15:29 by ede-sous          #+#    #+#             */
/*   Updated: 2017/09/26 01:13:14 by ede-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slctlib.h"

int					go_home_or_end(unsigned int key)
{
	t_key			k;

	k.list = stocklist(NULL, 1);
	k.tmp = k.list;
	while (!k.tmp->cursor)
		k.tmp = k.tmp->next;
	k.tmp->cursor = 0;
	while (k.tmp->name)
		k.tmp = k.tmp->next;
	(key == HOME ? k.tmp->next->cursor = 1 : 0);
	(key == END ? k.tmp->prev->cursor = 1 : 0);
	stocklist(k.list, 0);
	return (1);
}

int					go_all_up_or_down(unsigned int key)
{
	t_key			k;

	k.list = stocklist(NULL, 1);
	k.tmp = k.list;
	while (!k.tmp->cursor)
		k.tmp = k.tmp->next;
	k.column = k.tmp->column;
	k.tmp->cursor = 0;
	while ((key == ALT_UP && k.tmp->prev->name &&
				k.tmp->prev->column == k.column)
			|| (key == ALT_DOWN && k.tmp->next->name &&
				k.tmp->next->column == k.column))
		k.tmp = (key == ALT_UP ? k.tmp->prev : k.tmp->next);
	k.tmp->cursor = 1;
	stocklist(k.list, 0);
	return (1);
}

int					change_page(unsigned int key)
{
	t_key			k;
	size_t			pages;

	k.list = stocklist(NULL, 1);
	k.tmp = k.list;
	pages = stock_nbpages(0, 1);
	while (!k.tmp->cursor)
		k.tmp = k.tmp->next;
	k.page = k.tmp->page;
	if (pages == 1)
		return (go_home_or_end(key == PAGE_UP || key == ALT_LEFT ? HOME : END));
	k.tmp->cursor = 0;
	while (k.tmp->name && k.tmp->page == k.page)
		k.tmp = (key == PAGE_UP || key == ALT_LEFT ? k.tmp->prev : k.tmp->next);
	if (!k.tmp->name)
		k.tmp = (key == PAGE_UP || key == ALT_LEFT ? k.tmp->prev : k.tmp->next);
	while (k.tmp->line != 1 || k.tmp->column != 1)
		k.tmp = (key == PAGE_UP || key == ALT_LEFT ? k.tmp->prev : k.tmp->next);
	k.tmp->cursor = 1;
	stocklist(k.list, 0);
	return (1);
}

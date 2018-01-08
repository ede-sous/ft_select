/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_arrows.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-sous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 22:45:47 by ede-sous          #+#    #+#             */
/*   Updated: 2017/09/26 01:13:12 by ede-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slctlib.h"

int					go_up(void)
{
	t_key			k;

	k.list = stocklist(k.list, 1);
	k.tmp = k.list;
	while (!k.tmp->cursor)
		k.tmp = k.tmp->next;
	k.save = k.tmp;
	k.tmp = k.tmp->prev;
	if (!k.tmp->name)
		k.tmp = k.tmp->prev;
	k.save->cursor = 0;
	k.tmp->cursor = 1;
	stocklist(k.list, 0);
	return (1);
}

int					go_down(void)
{
	t_key			k;

	k.list = stocklist(k.list, 1);
	k.tmp = k.list;
	while (!k.tmp->cursor)
		k.tmp = k.tmp->next;
	k.save = k.tmp;
	k.tmp = k.tmp->next;
	if (!k.tmp->name)
		k.tmp = k.tmp->next;
	k.save->cursor = 0;
	k.tmp->cursor = 1;
	stocklist(k.list, 0);
	return (1);
}

int					go_left(void)
{
	t_key			k;

	k.list = stocklist(k.list, 1);
	k.tmp = k.list;
	while (!k.tmp->cursor)
		k.tmp = k.tmp->next;
	k.line = k.tmp->line;
	k.tmp->cursor = 0;
	k.tmp = k.tmp->prev;
	while (k.tmp->name && k.tmp->line != k.line)
		k.tmp = k.tmp->prev;
	if (!k.tmp->name && (k.tmp = k.tmp->prev) && k.line < k.tmp->line)
		while (k.tmp->line != k.line)
			k.tmp = k.tmp->prev;
	k.tmp->cursor = 1;
	stocklist(k.list, 0);
	return (1);
}

int					go_right(void)
{
	t_key			k;

	k.list = stocklist(k.list, 1);
	k.tmp = k.list;
	while (!k.tmp->cursor)
		k.tmp = k.tmp->next;
	k.line = k.tmp->line;
	k.column = k.tmp->column;
	k.page = k.tmp->page;
	k.tmp->cursor = 0;
	k.tmp = k.tmp->next;
	while (k.tmp->name && k.tmp->line != k.line)
		k.tmp = k.tmp->next;
	if (!k.tmp->name && (k.tmp->prev->page != k.page
				|| k.tmp->prev->column != k.column))
		k.tmp = k.tmp->prev;
	else if (!k.tmp->name && (k.tmp = k.tmp->next))
		while (k.tmp->line != k.line)
			k.tmp = k.tmp->next;
	k.tmp->cursor = 1;
	stocklist(k.list, 0);
	return (1);
}

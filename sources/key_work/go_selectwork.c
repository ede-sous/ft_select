/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_selectwork.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-sous <ede-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 23:12:56 by ede-sous          #+#    #+#             */
/*   Updated: 2017/09/27 03:19:21 by ede-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slctlib.h"

int					go_select(void)
{
	t_key			k;

	k.list = stocklist(k.list, 1);
	k.tmp = k.list;
	while (!k.tmp->cursor)
		k.tmp = k.tmp->next;
	k.tmp->select = (!k.tmp->select ? 1 : 0);
	k.tmp->cursor = 0;
	k.tmp = k.tmp->next;
	if (!k.tmp->name)
		k.tmp = k.tmp->next;
	k.tmp->cursor = 1;
	stocklist(k.list, 0);
	return (1);
}

int					go_unselect(void)
{
	t_key			k;

	k.list = stocklist(k.list, 1);
	k.tmp = k.list;
	while (k.tmp->name)
	{
		k.tmp->select = 0;
		k.tmp = k.tmp->next;
	}
	stocklist(k.list, 0);
	return (1);
}

int					go_select_all(void)
{
	t_key			k;

	k.list = stocklist(NULL, 1);
	k.tmp = k.list;
	while (k.tmp->name)
	{
		k.tmp->select = 1;
		k.tmp = k.tmp->next;
	}
	stocklist(k.list, 0);
	return (1);
}

static t_key		go_sel_del(t_key k)
{
	k.prev = k.tmp->prev;
	k.next = k.tmp->next;
	free(k.tmp->name);
	k.tmp->name = NULL;
	free(k.tmp);
	k.tmp = NULL;
	k.prev->next = k.next;
	k.next->prev = k.prev;
	k.tmp = k.next;
	return (k);
}

int					go_selected_delete(void)
{
	t_key			k;

	k.list = stocklist(k.list, 1);
	k.tmp = k.list;
	while (k.tmp->name)
	{
		while (k.tmp->name && !k.tmp->select && !(k.tmp->cursor = 0))
			k.tmp = k.tmp->next;
		if (!k.tmp->name)
			break ;
		k = go_sel_del(k);
	}
	k.list = k.tmp->next;
	if (k.list->name == NULL)
		return (0);
	k.line = recount_files(k.list);
	stocklist(define_padding(k.list, k.line), 0);
	ft_sound(INT_DEL);
	return (1);
}

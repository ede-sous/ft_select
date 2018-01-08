/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_work_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-sous <ede-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 06:01:02 by ede-sous          #+#    #+#             */
/*   Updated: 2017/09/26 01:28:38 by ede-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/slctlib.h"

static t_lst		*make_rotate(t_lst *list)
{
	t_l				l;

	l.tmp = list;
	l.prev = NULL;
	l.next = list;
	while (l.tmp->next)
		l.tmp = l.tmp->next;
	l.prev = l.tmp;
	l.tmp = l.tmp->next;
	if (!(l.tmp = (t_lst*)malloc(sizeof(t_lst))))
		return (NULL);
	l.tmp->first_or_last = 69;
	l.tmp->cursor = 0;
	l.tmp->select = 0;
	l.tmp->name = NULL;
	l.tmp->next = l.next;
	l.tmp->prev = l.prev;
	l.next->prev = l.tmp;
	l.prev->next = l.tmp;
	return (list);
}

static t_lst		*init_list(char **str, t_l l)
{
	if (str[l.i][0] == '\0')
		return (NULL);
	if (!(l.tmp = (t_lst*)malloc(sizeof(t_lst))))
		return (NULL);
	l.tmp->name = NULL;
	l.tmp->name = ft_strdup(str[l.i]);
	l.tmp->len = ft_strlen(str[l.i]);
	l.tmp->select = 0;
	l.tmp->cursor = (l.i == 0 ? 1 : 0);
	l.tmp->line = 0;
	l.tmp->column = 0;
	l.tmp->page = 0;
	l.tmp->first_or_last = (l.i == 0 ? 1 : 0);
	l.tmp->first_or_last = (str[l.i + 1] == NULL ? 2 : l.tmp->first_or_last);
	l.tmp->first_or_last = (l.i == 0 && str[l.i + 1] == NULL
			? 0 : l.tmp->first_or_last);
	l.tmp->next = NULL;
	(l.prev ? l.prev->next = l.tmp : 0);
	l.tmp->prev = l.prev;
	return (l.tmp);
}

int					create_list(char **args)
{
	t_l				l;

	l.i = -1;
	l.list = NULL;
	l.tmp = NULL;
	l.prev = NULL;
	while (args[++l.i])
	{
		if (!l.list)
		{
			if (!(l.tmp = init_list(args, l)))
				return (0);
			l.list = l.tmp;
		}
		else
		{
			l.prev = l.tmp;
			l.tmp = l.tmp->next;
			if (!(l.tmp = init_list(args, l)))
				return (0);
		}
	}
	stocklist(define_padding(make_rotate(l.list), l.i), 0);
	return (1);
}

void				create_and_stock_element(t_key k)
{
	k.list = stocklist(NULL, 1);
	k.tmp = k.list;
	k.prev = k.tmp->prev;
	if (!(k.new_ = (t_lst*)malloc(sizeof(t_lst))))
		return ;
	k.new_->name = k.str;
	k.new_->len = ft_strlen(k.str);
	k.new_->select = 0;
	k.new_->cursor = 0;
	k.new_->line = 0;
	k.new_->column = 0;
	k.new_->page = 0;
	k.new_->first_or_last = 1;
	k.tmp->first_or_last = 0;
	k.new_->next = k.tmp;
	k.new_->prev = k.prev;
	k.prev->next = k.new_;
	k.tmp->prev = k.new_;
	k.list = k.new_;
	stocklist(define_padding(k.list, recount_files(k.list)), 0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_delete_or_insert.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-sous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 00:23:31 by ede-sous          #+#    #+#             */
/*   Updated: 2017/09/27 06:16:48 by ede-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slctlib.h"

static t_key		go_del(t_key k)
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

int					go_delete(void)
{
	t_key			k;

	k.list = stocklist(k.list, 1);
	k.tmp = k.list;
	while (!k.tmp->cursor)
		k.tmp = k.tmp->next;
	k = go_del(k);
	if (!k.tmp->prev->name)
		k.list = k.tmp;
	if (!k.list->name)
		return (0);
	if (!k.tmp->name)
		k.tmp->next->cursor = 1;
	else
		k.tmp->cursor = 1;
	k.line = recount_files(k.list);
	stocklist(define_padding(k.list, k.line), 0);
	ft_sound(INT_DEL);
	return (1);
}

static void			ft_print_input(t_key k, t_pad pad, int value)
{
	if (!value)
	{
		XY_(2, pad.w.ws_row - 3);
		PS("\033[92mINSERT MODE:\033[0m ");
		PA("ve", NULL);
	}
	else
	{
		XY_(15, pad.w.ws_row - 3);
		PA("ce", NULL);
		XY_(15, pad.w.ws_row - 3);
		PS(k.str);
	}
}

static t_key		ft_read_input(t_key k, t_pad pad)
{
	while (read(0, k.buff, 5) != -1 && (k.key = (unsigned int)*k.buff) != ENTER
			&& k.key != ESC)
	{
		k.bf[0] = k.key;
		if (k.str && (k.key == BACKSPACE || k.key == DELETE)
				&& (k.line = ft_strlen(k.str)) && k.x > 0)
		{
			k.str[k.line - 1] = '\0';
			ft_print_input(k, pad, 0);
			ft_print_input(k, pad, 1);
			k.x--;
		}
		else if (k.x < 20 && k.key >= 32 && k.key < 127 &&
				(k.str = ft_strjoin(k.str, k.bf, 1)))
		{
			ft_print_input(k, pad, 0);
			ft_print_input(k, pad, 1);
			k.x++;
		}
		ft_bzero(k.buff, 5);
	}
	return (k);
}

int					go_insert(void)
{
	t_key			k;
	t_pad			pad;

	ioctl(0, TIOCGWINSZ, &pad.w);
	ft_print_input(k, pad, 0);
	k.x = 0;
	ft_bzero(k.buff, 5);
	ft_bzero(&k.bf, 2);
	k.str = ft_strdup("");
	ft_sound(ENDSOUND);
	ft_sound(INT_INS);
	k = ft_read_input(k, pad);
	if (k.key == ENTER && k.str && k.str[0])
		create_and_stock_element(k);
	PA("vi", NULL);
	ft_sound(ENDSOUND);
	ft_sound(RESET);
	return (1);
}

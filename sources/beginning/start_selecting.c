/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_selecting.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-sous <ede-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 02:08:26 by ede-sous          #+#    #+#             */
/*   Updated: 2017/09/29 03:15:53 by ede-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slctlib.h"

static int			treat_key(unsigned int key)
{
	(key == UP ? go_up() : 0);
	(key == DOWN ? go_down() : 0);
	(key == LEFT || key == SHIFT_TAB ? go_left() : 0);
	(key == RIGHT || key == TAB ? go_right() : 0);
	(key == SPACE ? go_select() : 0);
	if ((key == BACKSPACE || key == DELETE) && !go_delete())
		return (0);
	(key == PLUS ? go_select_all() : 0);
	if (key == CLEAR && !go_selected_delete())
		return (0);
	(key == INS || key == INS_M ? go_insert() : 0);
	(key == UN_ALL ? go_unselect() : 0);
	(key == HOME || key == END ? go_home_or_end(key) : 0);
	(key == PAGE_UP || key == PAGE_DOWN || key == ALT_LEFT || key == ALT_RIGHT
	? change_page(key) : 0);
	(key == ALT_UP || key == ALT_DOWN ? go_all_up_or_down(key) : 0);
	(key == INVERSE ? go_inverse() : 0);
	return (1);
}

void				print_selected(void)
{
	t_lst			*tmp;
	int				i;

	i = 0;
	tmp = stocklist(NULL, 1);
	while (tmp->name)
	{
		if (tmp->select)
		{
			(i ? P(" ") : 0);
			P(tmp->name);
			i = 1;
		}
		tmp = tmp->next;
	}
	ft_dellist();
	ft_sound(INT_ENT);
}

int					start_selecting(char **tmp)
{
	t_lst			*list;
	char			*buff[5];
	unsigned int	key;

	if (!(create_list(tmp)))
		return (ft_error(4));
	if (!(list = stocklist(NULL, 1)))
		return (ft_error(6));
	print_intro(0);
	print_list(list);
	ft_bzero(buff, 5);
	ft_sound(STARTSOUND);
	while (read(0, buff, 5) != -1 && (key = (unsigned int)*buff) != ENTER)
	{
		if (key == ESC || !treat_key(key))
			return (2);
		print_intro(1);
		print_list(stocklist(list, 1));
		ft_bzero(buff, 5);
		key = 0;
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-sous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/08 05:55:13 by ede-sous          #+#    #+#             */
/*   Updated: 2017/09/29 03:22:09 by ede-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/slctlib.h"

t_print			print_details(t_lst *tmp, t_print detail)
{
	XY_(detail.x_sep + 2, detail.y_sep);
	PS("\033[97m");
	if (tmp->select)
		PS("\033[45m");
	if (tmp->cursor)
		PS("\033[4;93m");
	PS(tmp->name);
	PS("\033[0m");
	if (tmp->column == 1 && (!tmp->next->name || tmp->next->column != 1
				|| tmp->next->page != tmp->page))
	{
		XY_(detail.x_sep + 2, detail.y_sep + 2);
		PS("\033[92mPage : ");
		ft_putnbr_fd((int)tmp->page, 2);
		PS(" / ");
		ft_putnbr_fd((int)stock_nbpages(0, 1), 2);
		PS("\033[0m");
	}
	detail.len = (detail.len < tmp->len ? tmp->len : detail.len);
	return (detail);
}

void			print_list(t_lst *list)
{
	t_lst		*tmp;
	t_print		detail;

	tmp = list;
	while (tmp->cursor != 1)
		tmp = tmp->next;
	detail.page = tmp->page;
	detail.col = 1;
	detail.x_sep = 2;
	XY_(2, 19);
	PA("cd", NULL);
	while (tmp->line != 1 || tmp->column != 1 || tmp->page != detail.page)
		tmp = tmp->prev;
	while (tmp->name && tmp->page == detail.page && !(detail.len = 0))
	{
		detail.y_sep = 17;
		while (tmp->column == detail.col && detail.page == tmp->page
				&& (detail.y_sep += 2))
		{
			detail = print_details(tmp, detail);
			tmp = tmp->next;
		}
		detail.x_sep += detail.len + 2;
		detail.col++;
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   go_inverse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-sous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/26 00:27:37 by ede-sous          #+#    #+#             */
/*   Updated: 2017/09/26 01:13:10 by ede-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slctlib.h"

int					go_inverse(void)
{
	t_key			k;

	k.list = stocklist(k.list, 1);
	k.tmp = k.list;
	while (k.tmp->name)
	{
		k.tmp->select = (k.tmp->select ? 0 : 1);
		k.tmp = k.tmp->next;
	}
	stocklist(k.list, 0);
	return (1);
}

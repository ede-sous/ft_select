/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dellist.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-sous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 00:17:20 by ede-sous          #+#    #+#             */
/*   Updated: 2017/09/26 01:22:46 by ede-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/slctlib.h"

void			*ft_dellist(void)
{
	t_key		k;

	k.tmp = stocklist(NULL, 1);
	while (k.tmp->name)
	{
		k.save = k.tmp;
		k.tmp = k.tmp->next;
		k.save->next = NULL;
		k.save->prev = NULL;
		ft_strdel(&k.save->name);
		free(k.save);
		k.save = NULL;
	}
	k.tmp->prev = NULL;
	k.tmp->next = NULL;
	free(k.tmp);
	k.tmp = NULL;
	stocklist(NULL, 0);
	stock_nbpages(0, -1);
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-sous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/04 16:14:08 by ede-sous          #+#    #+#             */
/*   Updated: 2017/09/26 02:52:23 by ede-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_putnbr(int n)
{
	char	*p;

	p = NULL;
	if (n == -2147483648)
		write(1, "-2147483648", 11);
	else if (n > 2147483647)
		write(1, "Too big", 7);
	else
		ft_putstr(p = ft_itoa(n));
	ft_strdel(&p);
}

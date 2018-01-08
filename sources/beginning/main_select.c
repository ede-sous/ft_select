/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_select.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-sous <ede-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/01 03:37:53 by ede-sous          #+#    #+#             */
/*   Updated: 2017/09/27 05:06:21 by ede-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slctlib.h"

int					main(int ac, char **av)
{
	char			**tmp;
	t_intro			win;
	t_key			k;

	tmp = &av[1];
	ioctl(0, TIOCGWINSZ, &win.w);
	if (ac < 1 || !av || !av[1])
		return (ft_error(1));
	ft_catch_signal();
	if (!modify_or_repair_terminal(0) || !(k.i = start_selecting(tmp))
			|| !modify_or_repair_terminal(1))
		return (-1);
	tmp = NULL;
	ft_sound(ENDSOUND);
	if (k.i == 1 && stocklist(NULL, 1))
		print_selected();
	else
		ft_sound(INT_ESC);
	return (EXIT_SUCCESS);
}

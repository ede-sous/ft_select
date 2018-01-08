/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-sous <ede-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/01 06:32:32 by ede-sous          #+#    #+#             */
/*   Updated: 2017/09/29 03:05:40 by ede-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slctlib.h"

static int			ft_error_2(int error)
{
	if (error == 1)
		PEFD("\033[91mError: Arguments missing.\n\
Usage: ./ft_select [`command files`] [files] [arguments]\033[0m", 2);
	if (error == 2)
		PEFD("\033[93m$TERM is no xterm-256color \
or problem with tty.\033[0m", 2);
	if (error == 3)
		PEFD("\033[93mProblem Setting or Reparing terminal attributes.\033[0m",
			2);
	if (error == 4)
		PEFD("\033[93mProblem creating my list or one of the arguments \
is NULL/Invalid.\033[0m", 2);
	if (error == 6)
		PEFD("\033[91mResize your Window please !\n\
One of the arguments do not fit in the current window size \
and it's preventing me from doing my padding ...\n\
Relaunch ft_select with a good window size and I'll let you go on.\033[0m", 2);
	ft_sound(ENDSOUND);
	exit(EXIT_FAILURE);
}

int					ft_error(int error)
{
	t_intro			p;

	if ((error > 3 && error < 5) || error == 6)
		modify_or_repair_terminal(1);
	if (error <= 4 || error == 6)
		ft_error_2(error);
	if (error == 5)
	{
		PA("cl", NULL);
		PEFD("\033[91mResize your Window please !\n\033[0m", 0);
		ioctl(0, TIOCGWINSZ, &p.w);
		while (p.w.ws_row <= 30 || p.w.ws_col <= 30)
			ioctl(0, TIOCGWINSZ, &p.w);
		return (1);
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-sous <ede-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/11 05:08:01 by ede-sous          #+#    #+#             */
/*   Updated: 2017/09/29 03:15:16 by ede-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/slctlib.h"

void		ft_handler_stop(void)
{
	char	bf[2];
	t_term	term;

	signal(SIGTSTP, SIG_DFL);
	PA("cl", NULL);
	ft_sound(ENDSOUND);
	ft_sound(INT_WAIT);
	modify_or_repair_terminal(1);
	tcgetattr(STDIN_FILENO, &term.modify);
	bf[0] = term.modify.c_cc[VSUSP];
	bf[1] = 0;
	ioctl(0, TIOCSTI, &bf);
	P(" ");
}

void		ft_handler_cont(void)
{
	t_key	k;

	signal(SIGTSTP, ft_handler);
	modify_or_repair_terminal(0);
	PA("cl", NULL);
	print_intro(0);
	k.list = stocklist(NULL, 1);
	print_list(define_padding(k.list, recount_files(k.list)));
	ft_sound(ENDSOUND);
	ft_sound(RESET);
}

void		ft_handler_winch(void)
{
	t_key	k;
	t_pad	pad;

	signal(SIGWINCH, SIG_IGN);
	k.list = stocklist(NULL, 1);
	ioctl(0, TIOCGWINSZ, &pad.w);
	if ((pad.w.ws_row <= 30 || pad.w.ws_col <= 30))
		ft_error(5);
	k.list = stocklist(NULL, 1);
	if (!(k.list = define_padding(k.list, recount_files(k.list))))
		ft_error(6);
	signal(SIGWINCH, ft_handler);
	if (k.list)
	{
		print_intro(0);
		print_list(k.list);
		stocklist(k.list, 0);
	}
}

void		ft_handler(int sig)
{
	t_key	k;
	t_pad	pad;

	if (sig == SIGINT || sig == SIGKILL)
	{
		ft_dellist();
		ft_sound(ENDSOUND);
		ft_sound(INT_ESC);
		modify_or_repair_terminal(1);
		exit(EXIT_SUCCESS);
	}
	else if (sig == SIGWINCH)
		ft_handler_winch();
	else if (sig == SIGTSTP)
		ft_handler_stop();
	else if (sig == SIGCONT)
		ft_handler_cont();
	else if (sig == EOF)
		;
}

int			ft_catch_signal(void)
{
	int		i;

	i = 0;
	while (i <= 32)
		signal(i++, ft_handler);
	return (1);
}

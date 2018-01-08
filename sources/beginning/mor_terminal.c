/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mor_terminal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-sous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/01 23:47:01 by ede-sous          #+#    #+#             */
/*   Updated: 2017/09/21 05:40:07 by ede-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slctlib.h"

int							modify_or_repair_terminal(int value)
{
	static t_term			term;

	if (!value)
	{
		if (!(term.name = ttyname(0)))
			return (ft_error(2));
		if (!(term.env = getenv("TERM")) || !ft_strcmp(term.env, "dumb"))
			return (ft_error(2));
		if (tcgetattr(STDIN_FILENO, &term.modify) == -1 ||
				tcgetattr(STDIN_FILENO, &term.repair) == -1 ||
				tgetent(NULL, term.env) < 1)
			return (ft_error(3));
		term.modify.c_lflag &= ~(ECHO | ICANON);
		if (tcsetattr(STDIN_FILENO, TCSADRAIN, &term.modify) == -1)
			return (ft_error(3));
		PA("ti", NULL);
		PA("vi", NULL);
		PA("cl", NULL);
		return (1);
	}
	else if (tcsetattr(STDIN_FILENO, TCSADRAIN, &term.repair) == -1)
		return (ft_error(3));
	PA("te", NULL);
	PA("ve", NULL);
	return (1);
}

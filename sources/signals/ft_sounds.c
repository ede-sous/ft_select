/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sounds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-sous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/27 02:05:08 by ede-sous          #+#    #+#             */
/*   Updated: 2017/09/29 07:01:56 by ede-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slctlib.h"

static void			ft_background(int v, char *sounds[5])
{
	if (v == RESET || v == STARTSOUND)
		system(PUT_BACKGRD);
	else if (v == ENDSOUND)
		system(TAKE_BACKGRD);
	else if (v == INT_INS)
		system(INS_BACKGRD);
	if (SOUND_IMAGE == 3 && v == INT_WAIT)
	{
		system(WAIT_BACKGRD);
		system(sounds[INT_WAIT]);
	}
}

void				ft_sound(int v)
{
	static char		*sounds[5];

	if (SOUND_IMAGE == 0)
		return ;
	if (v == RESET || v == STARTSOUND)
		system(BACKGROUND);
	if (v == STARTSOUND)
	{
		sounds[INT_DEL] = SOUND_DEL;
		sounds[INT_ESC] = SOUND_ESC;
		sounds[INT_ENT] = SOUND_ENT;
		sounds[INT_INS] = SOUND_INS;
		sounds[INT_WAIT] = SOUND_C_Z;
	}
	else if (v == ENDSOUND)
		system(STOP_BACK);
	else if (v != RESET && v != INT_WAIT)
		system(sounds[v]);
	(SOUND_IMAGE >= 2 ? ft_background(v, sounds) : 0);
}

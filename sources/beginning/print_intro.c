/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_intro.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-sous <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/07 22:59:45 by ede-sous          #+#    #+#             */
/*   Updated: 2017/09/29 03:21:01 by ede-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "slctlib.h"

static void			recount_intro(int *p, int *files)
{
	t_lst			*list;

	list = stocklist(list, 1);
	while (list->name)
	{
		if (list->select == 1)
			(*p)++;
		++(*files);
		list = list->next;
	}
}

static void			print_select_files(t_intro win)
{
	t_lst			*list;
	int				files;
	int				i;
	int				p;

	p = 0;
	files = 0;
	recount_intro(&p, &files);
	XY_((win.x_max / 22) + 58, 13);
	PS("\e[1;37;106m Number of Files    \e[0m\e[97m ==>               📑 📑    ");
	XY_((win.x_max / 22) + 83, 13);
	ft_putnbr_fd(files, 2);
	XY_((win.x_max / 22) + 58, 15);
	PS("\e[1;37;106m Number of Selected \e[0m\e[97m ==>            \
\e[1;97;105m꧌ SLCT ꧌\e[0m ");
	XY_((win.x_max / 22) + 83, 15);
	ft_putnbr_fd(p, 2);
	PS("\e[0m");
}

static void			print_bonus(t_intro win, int i)
{
	if (!i)
	{
		XY_((win.x_max / 22) + 58, 3);
		PS("\e[1;37;106m        I / i     :");
		PS("\e[0m\e[97m Insert Argument.          ");
		XY_((win.x_max / 22) + 58, 5);
		PS("\e[1;37;106m          _       :");
		PS("\e[0m\e[97m Delete selected arguments.");
		XY_((win.x_max / 22) + 58, 7);
		PS("\e[1;37;106m        - / +     :");
		PS("\e[0m\e[97m Unslct/Slct all arguments.");
		XY_((win.x_max / 22) + 58, 9);
		PS("\e[1;37;106m     HOME / END   :");
		PS("\e[0m\e[97m Go to First/Last argument.");
		XY_((win.x_max / 22) + 58, 11);
		PS("\e[1;37;106m     ATL+ARROW    :");
		PS("\e[0m\e[97m ''Move faster.''          ");
	}
	print_select_files(win);
}

static void			print_info(t_intro win, int i)
{
	if (!i)
	{
		XY_(win.x_max / 20 + 1, 3);
		PS("\e[92m      SPACE       :\e[97m Selected/Unselect argument. \e[0m");
		XY_(win.x_max / 20 + 1, 5);
		PS("\e[93m      ENTER       :\e[97m Confirm selected arguments. \e[0m");
		XY_(win.x_max / 20 + 1, 7);
		PS("\e[91m       ESC        :\e[97m Exit.                       \e[0m");
		XY_(win.x_max / 20 + 1, 9);
		PS("\e[34m  BACKSPACE/DELETE:\e[97m Delete argument.            \e[0m");
		XY_(win.x_max / 20 + 1, 11);
		PS("\e[36m      ARROWS      :\e[97m Move on arguments.          \e[0m");
		XY_(win.x_max / 20 + 1, 13);
		PS("\e[95m  TAB -- SHIFT+TAB:\e[97m Move right/left.            \e[0m");
		XY_(win.x_max / 20 + 1, 15);
		PS("\e[33m  PAGE (UP / DOWN):\e[97m Previous / Next Page.       \e[0m");
	}
	print_bonus(win, i);
}

void				print_intro(int i)
{
	t_intro			win;

	ioctl(0, TIOCGWINSZ, &win.w);
	win.y = 0;
	win.x_max = win.w.ws_col;
	if (!i)
	{
		PA("cl", NULL);
		MOVE("do");
		PS("  ");
		while (++win.y <= 17 && !(win.x = 0))
		{
			while (++win.x < win.x_max / 2)
				(win.x <= 3 || win.x > win.x_max / 2 - 4 ? PS("🌈 ") : PS("🦄 "));
			PS("\n  ");
		}
	}
	if (win.x_max >= 150)
		print_info(win, i);
}

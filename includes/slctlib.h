/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   slctlib.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ede-sous <ede-sous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/01 03:39:16 by ede-sous          #+#    #+#             */
/*   Updated: 2017/10/03 06:01:05 by ede-sous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SLCTLIB_H
# define SLCTLIB_H
# include "../Libft/libft.h"

# include <curses.h>
# include <sys/ioctl.h>
# include <term.h>
# include <termios.h>
# include <signal.h>

# define P(x)		ft_putstr(x)
# define PS(x)		ft_putstr_fd(x, 2)
# define PE(x)		ft_putendl(x)
# define PEFD(x, y)	ft_putendl_fd(x, y)
# define PA(x, y)	PS(tgetstr(x, y))
# define MOVE(x)	PS(tgetstr(x, NULL))
# define XY_(x, y)	PS(tgoto(tgetstr("cm", NULL), x, y))

# define BUFFSIZE	4096

/*
**				Everything that contains Sound and Image
*/

# define SOUND_IMAGE 0

# define BACKGROUND	"while :; do afplay .sound/backmusic.mp3;done &>/dev/null &"
# define STOP_BACK	"killall sh | killall afplay"
# define SOUND_DEL	"afplay .sound/delete.wav &>/dev/null &"
# define SOUND_ESC	"afplay .sound/escape.mp3 &>/dev/null &"
# define SOUND_ENT	"afplay .sound/bingo.mp3 &>/dev/null &"
# define SOUND_INS	"while :; do afplay .sound/insert.mp3;done &>/dev/null &"
# define SOUND_C_Z	"while :; do afplay .sound/wait_z.mp3;done &>/dev/null &"

# define PUT_BACKGRD	"sh .scripts/back_put/put_back.sh &>/dev/null &"
# define INS_BACKGRD	"sh .scripts/insert/insert.sh &>/dev/null &"
# define WAIT_BACKGRD	"sh .scripts/elevator/el.sh &>/dev/null &"
# define TAKE_BACKGRD	"osascript .scripts/back_take.scpt &>/dev/null &"

# define ENTSOUND	-4
# define RESET		-3
# define STARTSOUND	-2
# define ENDSOUND	-1
# define INT_DEL	0
# define INT_ESC	1
# define INT_ENT	2
# define INT_INS	3
# define INT_WAIT	4
# define INT_NULL	5

/*
**		--      Keys       --
*/

# define UP			4283163
# define DOWN		4348699
# define LEFT		4479771
# define RIGHT		4414235

# define SPACE		32
# define ENTER		10
# define ESC		27
# define BACKSPACE	127
# define DELETE		2117294875
# define TAB		9
# define SHIFT_TAB	5921563

/*
**		--   Bonus Keys    --
**  i
**  I
**  +          => Select all arguments;
**  -          => Unselect all arguments
**  _          => Delete selected arguments
**  HOME       => 1rst Argument
**  END        => Last Argument
**  PAGE UP    => Previous Page
**  PAGE DOWN  => Next Page
**  ALT+UP     => Top of column
**  ALT+DOWN   => Bottom of column
**  ALT+LEFT   => Previous Page
**  ALT+RIGHT  => Next Page
*/

# define INS		105
# define INS_M		73
# define PLUS		43
# define UN_ALL		45
# define INVERSE	92
# define CLEAR		95
# define HOME		4741915
# define END		4610843
# define PAGE_UP	2117425947
# define PAGE_DOWN	2117491483
# define ALT_UP		1096489755
# define ALT_DOWN	1113266971
# define ALT_LEFT	1146821403
# define ALT_RIGHT	1130044187

/*
**		-- Listes + Structs --
*/

typedef struct			s_intro
{
	struct winsize		w;
	unsigned short		x;
	unsigned short		y;
	unsigned short		x_max;
	unsigned short		y_max;
}						t_intro;

typedef struct			s_term
{
	char				*name;
	char				*env;
	struct termios		modify;
	struct termios		repair;
}						t_term;

typedef struct			s_lst
{
	char				*name;
	char				*perm;
	size_t				len;
	size_t				select;
	size_t				cursor;
	size_t				line;
	size_t				column;
	size_t				page;
	size_t				first_or_last;
	struct s_lst		*next;
	struct s_lst		*prev;
}						t_lst;

typedef struct			s_l
{
	t_lst				*list;
	t_lst				*prev;
	t_lst				*next;
	t_lst				*tmp;
	int					i;
}						t_l;

typedef struct			s_pad
{
	int					s;
	size_t				window_x;
	size_t				window_y;
	size_t				biggest_len;
	size_t				biggest_len_of_all;
	size_t				vertical;
	size_t				line;
	size_t				column;
	size_t				columns_per_page;
	size_t				page;
	size_t				number_of_pages;
	size_t				number_of_files;
	size_t				ver;
	struct winsize		w;
}						t_pad;

typedef struct			s_print
{
	size_t				col;
	size_t				page;
	size_t				len;
	size_t				x_sep;
	size_t				y_sep;
}						t_print;

typedef struct			s_key
{
	t_lst				*list;
	t_lst				*tmp;
	t_lst				*save;
	t_lst				*prev;
	t_lst				*next;
	t_lst				*new_;
	char				*buff[5];
	char				bf[2];
	char				*str;
	char				*popo;
	size_t				line;
	size_t				column;
	size_t				page;
	unsigned int		key;
	int					x;
	int					i;
}						t_key;

/*
**		--    Fonctions    --
*/

void					print_intro(int i);
void					print_list(t_lst *list);
void					print_selected(void);
void					*ft_dellist();
void					ft_handler(int sig);
void					create_and_stock_element(t_key k);
void					ft_sound(int value);

int						ft_error(int error);
int						modify_or_repair_terminal(int value);
int						start_selecting(char **tmp);
int						create_list(char **tmp);
int						recount_files(t_lst *list);
int						ft_catch_signal(void);

size_t					stock_nbpages(size_t nb, int value);

t_lst					*define_padding(t_lst *lst, size_t nb_files);
t_lst					*stocklist(t_lst *list, int value);

t_pad					stockpadding(t_pad pad, int value);
t_pad					verify_size(t_lst *tmp, t_pad pad, size_t total_len);
t_pad					stock_pad(t_pad pad, int value);

/*
**		-- Key Functions --
*/

int						change_page(unsigned int key);
int						go_up(void);
int						go_down(void);
int						go_left(void);
int						go_right(void);
int						go_home_or_end(unsigned int key);
int						go_all_up_or_down(unsigned int key);

int						go_select(void);
int						go_select_all(void);
int						go_selected_delete(void);
int						go_delete(void);
int						go_unselect(void);
int						go_insert(void);
int						go_inverse(void);

#endif

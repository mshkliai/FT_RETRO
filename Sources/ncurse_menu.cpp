/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurse_menu.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshkliai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 20:24:00 by mshkliai          #+#    #+#             */
/*   Updated: 2018/10/07 20:24:03 by mshkliai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/includes.h"

static void	print_menu(int y, int x)
{
	t_cord	top;
	system("afplay ./sounds/main_theme.mp3 &");
	clear();
	
	top.y = y >> 4;
	top.x = (x >> 2) + 3;
	mvwprintw(stdscr, top.y, top.x, " _____ _____      ____  _____ _____  ____  ____ ");
	mvwprintw(stdscr, ++top.y, top.x, "/    //__ __\\    /  __\\/  __//__ __\\/  __\\/  _ \\");
	mvwprintw(stdscr, ++top.y, top.x, "|  __\\  / \\      |  \\/||  \\    / \\  |  \\/|| / \\|");
	mvwprintw(stdscr, ++top.y, top.x, "| |     | |      |    /|  /_   | |  |    /| \\_/|");
	mvwprintw(stdscr, ++top.y, top.x, "\\_/     \\_/       \\_/\\_\\____\\  \\_/   \\_/\\_\\____/");
	mvwprintw(stdscr, (y >> 1) - 3, (x >> 1) - 6, "Start game");
	mvwprintw(stdscr, y >> 1, (x >> 1) - 3, "Exit");
	mvwprintw(stdscr, (y >> 1) - 3, (x >> 1) - 7, ">");
	refresh();
}

int			ncurse_menu(int y, int x)
{
	int x1, y1 = 0;
	int	t = time(NULL);
	t_cord	start, exit;

	start.y = (y >> 1) - 3;
	start.x = (x >> 1) - 7;
	exit.y = y >> 1;
	exit.x = (x >> 1) - 4;

	refresh();
	print_menu(y, x);	
	while (1)
	{
		if (time(NULL) - 92 >= t)
		{
			system("afplay ./sounds/main_theme.mp3 &");
			t = time(NULL);
		}
	 	switch (getch())
	 	{
	 		case KEY_DOWN:
				mvwprintw(stdscr, start.y, start.x, " ");
	 			mvwprintw(stdscr, exit.y, exit.x, ">");
				refresh();
	 			break ;
			case KEY_UP:
				mvwprintw(stdscr, exit.y, exit.x, " ");
	 			mvwprintw(stdscr, start.y, start.x, ">");
	 			refresh();
	 			break ;
	 		case 10:
				system("killall afplay");
				getsyx(y1, x1);
	 			if (y1 == exit.y) {
	 				return 0;
	 			}
	 			else {
	 				return 1;
	 			}
				break ;
	 	}
	}
}

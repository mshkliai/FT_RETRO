/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   includes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshkliai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 12:35:32 by mshkliai          #+#    #+#             */
/*   Updated: 2018/10/06 12:35:33 by mshkliai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INCLUDES_H
# define INCLUDES_H

# include <unistd.h>
# include <iostream>
# include <ncurses.h>

typedef struct		s_cord
{
	int				y;
	int				x;
}					t_cord;

int					ncurse_menu(int y, int x);

#endif
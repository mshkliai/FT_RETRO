/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshkliai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/07 20:23:54 by mshkliai          #+#    #+#             */
/*   Updated: 2018/10/07 20:23:55 by mshkliai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Inc/includes.h"
#include "../Classes_inc/Batya.hpp"
#include "../Classes_inc/Ship.hpp"
#include "../Classes_inc/Game.hpp"
#include "../Classes_inc/Boss.hpp"

int	main(void)
{
	Game	*process = new Game;

	while (ncurse_menu(process->getTerm().y, process->getTerm().x) == 1)
	{
		clear();
		if (process->all_process() == 1)
		{
			delete process;
			process = 0;
			process = new Game;
		}
		else {
			break ;
		}
	}
	if (process) {
		delete process;
	}
	
	return 0;
}

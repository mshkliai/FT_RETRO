/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ship.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshkliai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 12:35:19 by mshkliai          #+#    #+#             */
/*   Updated: 2018/10/06 12:35:24 by mshkliai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHIP_H
# define SHIP_H

# include "../Inc/includes.h"
# include "../Classes_inc/Batya.hpp"

class					Ship : public Batya
{

	public:

		Ship();
		Ship(Ship const &obj);
		virtual ~Ship();
		
		Ship			&operator = (Ship const &obj);

		int				getSpeed();
		int				getMaxEns();

		void			new_level();
		void			collision(int how_hp);

		int				gameOver();
		int				Victory();
		int				print_myship();

	private:

		int				totalShoots;
		int				speed;
		int				max_ens;

		void			reload();

		void			pause();
		int				print_temp();

		void			print_stats();
		int				catch_button();

		char			*getTimer();
};

#endif

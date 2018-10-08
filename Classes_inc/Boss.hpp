/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Boss.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshkliai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 12:35:05 by mshkliai          #+#    #+#             */
/*   Updated: 2018/10/06 12:35:06 by mshkliai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BOSS_H
# define BOSS_H

# include "../Inc/includes.h"
# include "../Classes_inc/Batya.hpp"

class	Boss : public Batya
{
	public:
	
		Boss();
		Boss(Boss const &obj);
		virtual ~Boss();

		Boss	&operator = (Boss const &obj);

		void	print_boss();

	private:
		
		void	next_pos();
		void	make_shoot();
		void	clear_boss();
	
};

#endif

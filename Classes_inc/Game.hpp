/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshkliai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 17:36:09 by mshkliai          #+#    #+#             */
/*   Updated: 2018/10/06 17:36:15 by mshkliai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAME_H
# define GAME_H

# include "../Inc/includes.h"
# include "../Classes_inc/Batya.hpp"
# include "../Classes_inc/Ship.hpp"
# include "../Classes_inc/Boss.hpp"

class	Game : public Batya
{
		public:

			Game();
			Game(Game const &obj);
			virtual ~Game();

			Game	&operator = (Game const &obj);

			int		all_process();

		private:

			int		boss_auth;
			t_cord	ens[10];
			int		count_ens;
			Ship	*ship;
			Boss	*boss;

			int		check_conf(int index);
			void	new_enemy(int how);
			void	next_pos(int index);
			void	print_ens(int *timer);
			int		del_en(int index);
			void	check_boss_kill(t_cord ship_shoot, int index);
			void	check_kills_ens();
			void	check_ship_kill();
			void	print_timer();
};

#endif

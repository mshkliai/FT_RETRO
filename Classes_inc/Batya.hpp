/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Batya.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshkliai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 12:34:57 by mshkliai          #+#    #+#             */
/*   Updated: 2018/10/06 12:34:58 by mshkliai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BATYA_H
# define BATYA_H

# include "../Inc/includes.h"

class	Batya
{
	public:

		Batya();
		Batya(Batya const &obj);
		~Batya();

		Batya	&operator = (Batya const &obj);

		chtype			getSign();
		chtype			getPatron();
		int				getHP();
		int				getMaxHP();
		int				getBullet();
		int				getMaxBullet();
		int				getLevel();
		int				getScore();
		int				getTime();
		int				getStartTime();
		t_cord			getTerm();
		t_cord			getPos();
		t_cord			*getShoot();

		void			takeDamage(int damage);
		virtual void	make_shoot();
		void			make_shoot(t_cord enemy);
	 	void			print_shoots();
		void			print_shoots(int);

		void			setSign(chtype n_sign);
		void			setPatron(chtype n_patron);
		void			setHP(int n_hp);
		void			setMaxHP(int n_maxhp);
		void			setBullet(int n_bullet);
		void			setMaxBullet(int n_maxbullet);
		void			setLevel(int n_level);
		void			setScore(int n_score);
		void			setTime();
		void			setStartTime();
		void			setPos(int y, int x);
		void			setShoot(int y, int x, int index);
		void			del_shoot(int index);
	
	private:

		chtype			sign;
		chtype			patron;
		int				hp;
		int				maxhp;
		int				bullet;
		int				maxbullet;
		int				level;
		int				score;
		int				c_time;
		int				start_time;
		t_cord			term;
		t_cord			pos;
		t_cord			shoot[64];
};


#endif

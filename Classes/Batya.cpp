/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Batya.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshkliai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 12:33:58 by mshkliai          #+#    #+#             */
/*   Updated: 2018/10/06 12:33:59 by mshkliai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Classes_inc/Batya.hpp"

Batya::Batya() : hp(50), maxhp(50), bullet(10), maxbullet(10), level(0), score(0)
{
	initscr();

	this->c_time = time(NULL);
	this->start_time = time(NULL);

	getmaxyx(stdscr, this->term.y, this->term.x);
	this->pos.y = this->term.y >> 1;
	this->pos.x = 1;

	for(int i = 0; i < 64; i++) {
		this->shoot[i].y = -1;
	}

	start_color();
	init_pair(1, COLOR_GREEN, 0);
	init_pair(2, COLOR_RED, 0);
	init_pair(3, COLOR_YELLOW, 0);
	init_pair(4, COLOR_BLUE, 0);

	this->sign = '>' | COLOR_PAIR(1);
	this->patron = '-' | COLOR_PAIR(3);

	keypad(stdscr, 1);
	noecho();
	curs_set(0);
	nodelay(stdscr, true);
}

Batya::Batya(Batya const &obj)
{
	*this = obj;
}

Batya::~Batya()
{
	endwin();
}

Batya	&Batya::operator = (Batya const &obj)
{
	this->sign = obj.sign;
	this->patron = obj.patron;
	this->hp = obj.hp;
	this->maxhp = obj.maxhp;
	this->bullet = obj.bullet;
	this->maxbullet = obj.maxbullet;
	this->level = obj.level;
	this->score = obj.score;
	this->c_time = obj.c_time;
	this->term = obj.term;
	this->pos = obj.pos;

	for (int i = 0; i < 64; i++)
	{
		this->shoot[i].x = obj.shoot[i].x;
		this->shoot[i].y = obj.shoot[i].y;
	}

	return *this;
}

chtype	Batya::getSign()
{
	return this->sign;
}

chtype	Batya::getPatron()
{
	return this->patron;
}

int		Batya::getHP()
{
	return this->hp;
}

int 	Batya::getMaxHP()
{
	return this->maxhp;
}

int 	Batya::getBullet()
{
	return this->bullet;
}

int 	Batya::getMaxBullet()
{
	return this->maxbullet;
}

int 	Batya::getLevel()
{
	return	this->level;
}

int 	Batya::getScore()
{
	return this->score;
}

int 	Batya::getTime()
{
	return this->c_time;
}

int 	Batya::getStartTime()
{
	return this->start_time;
}

t_cord 	Batya::getTerm()
{
	return this->term;
}

t_cord	Batya::getPos()
{
	return this->pos;
}

t_cord *Batya::getShoot()
{
	return this->shoot;
}

void	Batya::print_shoots()
{
	for (int i = 0; i < 64; i++)
	{
		mvwaddch(stdscr, this->shoot[i].y, this->shoot[i].x, ' ');
		mvwaddch(stdscr, this->shoot[i].y, ++this->shoot[i].x, this->patron);
	}
}

void	Batya::print_shoots(int)
{
	for (int i = 0; i < 64; i++)
	{
		if (this->shoot[i].y != -1)
		{
			mvwaddch(stdscr, this->shoot[i].y, this->shoot[i].x, ' ');
			mvwaddch(stdscr, this->shoot[i].y, --this->shoot[i].x, this->patron);
		}
	}
}

void	Batya::takeDamage(int damage)
{
	this->setHP(this->getHP() - damage);
}

void	Batya::make_shoot()
{
	if (this->bullet == 0)
	{
		system("afplay ./sounds/no_patron.wav &");
		return ;
	}

	int i = 0;

	while (i < 64 && this->shoot[i].y != -1) {
		i++;
	}
	this->shoot[i].y = this->pos.y;
	this->shoot[i].x = this->pos.x + 2;
	this->bullet--;
	system("afplay ./sounds/my_shoot.wav &");
}

void	Batya::make_shoot(t_cord enemy)
{
	int i = 0;

	while (i < 64 && this->shoot[i].y != -1) {
		i++;
	}
	this->shoot[i].y = enemy.y;
	this->shoot[i].x = enemy.x - 2;
	if (enemy.x > 0 && enemy.x < term.x && enemy.y < term.y && enemy.y > 0) {
		system("afplay ./sounds/enemy_shoot.wav &");
	}
}

void	Batya::setSign(chtype n_sign)
{
	this->sign = n_sign;
}

void	Batya::setPatron(chtype n_patron)
{
	this->patron = n_patron;
}

void	Batya::setHP(int n_hp)
{
	this->hp = n_hp;
}

void	Batya::setMaxHP(int n_maxhp)
{
	this->maxhp = n_maxhp;
}

void	Batya::setBullet(int n_bullet)
{
	this->bullet = n_bullet;
}

void	Batya::setMaxBullet(int n_maxbullet)
{
	this->maxbullet = n_maxbullet;
}

void	Batya::setLevel(int n_level)
{
	this->level = n_level;
}

void	Batya::setScore(int n_score)
{
	this->score = n_score;
}

void	Batya::setTime()
{
	this->c_time = time(NULL);
}

void	Batya::setStartTime()
{
	this->start_time = time(NULL);
}

void	Batya::setPos(int y, int x)
{
	this->pos.y = y;
	this->pos.x = x;
}


void	Batya::setShoot(int y, int x, int index)
{
	this->shoot[index].y = y;
	this->shoot[index].x = x;
}

void	Batya::del_shoot(int index)
{
	if (index != -1) {
		this->shoot[index].y = -1;
	}

	for (int i = 0; i < 64; i++) {
		if (this->shoot[i].x < 0 || this->shoot[i].x > this->term.x) {
			this->shoot[i].y = -1;
		}
	}
}
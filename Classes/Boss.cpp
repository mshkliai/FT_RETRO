/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Boss.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshkliai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 12:34:14 by mshkliai          #+#    #+#             */
/*   Updated: 2018/10/06 12:34:15 by mshkliai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Classes_inc/Boss.hpp"


Boss::Boss() : Batya()
{
	chtype	n_patron = '*' | COLOR_PAIR(4);

	this->setHP(200);
	this->setMaxHP(200);
	this->setPos(this->getTerm().y >> 1, this->getTerm().x - 4);
	this->setPatron(n_patron);
}

Boss::Boss(Boss const &obj) : Batya(obj)
{
	*this = obj;
}

Boss::~Boss()
{
	return ;
}

Boss	&Boss::operator = (Boss const &obj)
{
	Batya::operator = (obj);

	return *this;
}

void	Boss::make_shoot()
{
	t_cord	*shoots = this->getShoot();
	int		count_shoots = 0;

	system("afplay ./sounds/boss_shoot.wav &");

	for (int i = 0; i < 32; i++)
	{
		if (shoots[i].y == -1) {
			this->setShoot(this->getPos().y + count_shoots++, this->getPos().x - 1, i);
		}
		if (count_shoots == 4) {
			break ;
		}
	}
}

void	Boss::next_pos()
{
	t_cord	old_cords;
	old_cords.y = this->getPos().y;
	old_cords.x = this->getPos().x;

	int random = rand() % 4;

	if (random == 1) {
		this->setPos(old_cords.y, old_cords.x - (random + rand()) % 3);
	}
	else if (random == 2) {
		this->setPos(old_cords.y + (random + rand()) % 3, old_cords.y);
	}
	else if (random == 3) {
		this->setPos(old_cords.y - (random + rand()) % 3, old_cords.x);
	}
	else {
		this->setPos(old_cords.y + (random + rand()) % 3, old_cords.x);
	}
	if (this->getPos().y < 0 || this->getPos().y + 3 >= this->getTerm().y ||
	this->getPos().x - 1 < 0) {
		this->setPos(old_cords.y, old_cords.x);
	}
	else {
		system("afplay ./sounds/boss_next_pos.wav &");
	}
}

void	Boss::clear_boss()
{
	mvwprintw(stdscr, 0, this->getTerm().x - 10, "   ");
	mvwprintw(stdscr, this->getPos().y, this->getPos().x, "   ");
	mvwprintw(stdscr, this->getPos().y + 1, this->getPos().x - 1, "   ");
	mvwprintw(stdscr, this->getPos().y + 2, this->getPos().x - 1, "   ");
	mvwprintw(stdscr, this->getPos().y + 3, this->getPos().x - 1, "    ");
}

void	Boss::print_boss()
{
	clear_boss();

	mvwprintw(stdscr, 0, this->getTerm().x - 20, "Boss: %d/%d", this->getMaxHP(), this->getHP());

	if (this->getTime() + 1 < time(NULL)) {
		this->next_pos();
	}
	if (this->getTime() + 2 < time(NULL))
	{
		this->make_shoot();
		this->setTime();
	}
	mvwprintw(stdscr, this->getPos().y, this->getPos().x, "/ /");
	mvwprintw(stdscr, this->getPos().y + 1, this->getPos().x - 1, "/ /");
	mvwprintw(stdscr, this->getPos().y + 2, this->getPos().x - 1, "\\ \\");
	mvwprintw(stdscr, this->getPos().y + 3, this->getPos().x - 1, " \\ \\");
	this->print_shoots(1);
	this->del_shoot(-1);
}
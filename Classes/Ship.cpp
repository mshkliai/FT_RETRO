/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ship.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshkliai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 12:34:25 by mshkliai          #+#    #+#             */
/*   Updated: 2018/10/06 12:34:26 by mshkliai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Classes_inc/Ship.hpp"

Ship::Ship() : totalShoots(0), speed(30), max_ens(5)
{
	return ;
}

Ship::Ship(Ship const &obj)
{
	*this = obj;
}

Ship::~Ship()
{
	return ;
}

Ship	&Ship::operator = (Ship const &obj)
{
	Batya::operator = (obj);

	this->speed = obj.speed;
	this->max_ens = obj.max_ens;
	return *this;
}

int		Ship::getSpeed()
{
	return this->speed;
}

int		Ship::getMaxEns()
{
	return this->max_ens;
}

void	Ship::new_level()
{
	if (this->getScore() > (this->getLevel() << 4) && this->getLevel() < 5)
	{
		this->setMaxHP(getMaxHP() + 10);
		this->setHP(getMaxHP());
		this->setMaxBullet(getMaxBullet() + 2);
		this->setBullet(getMaxBullet());
		this->setLevel(getLevel() + 1);
		this->speed -= 5;
		this->max_ens++;
		system("afplay ./sounds/new_level.wav &");
	}
	if (this->getLevel() == 5) {
		this->speed = 3;
	}
}

void	Ship::print_stats()
{
	mvwprintw(stdscr, 0, 1, "%d/%d; ", this->getHP(), this->getMaxHP());

	if (this->getBullet() > 9) {
		mvwprintw(stdscr, 0, 10, "%d/%d;", this->getMaxBullet(), this->getBullet());
	}
	else {
		mvwprintw(stdscr, 0, 10, "%d/0%d;", this->getMaxBullet(), this->getBullet());
	}

	mvwprintw(stdscr, 0, 17, "Scores: %d;", this->getScore());
	mvwprintw(stdscr, 0, 29, "Level: %d", this->getLevel());
}

void	Ship::reload()
{
	if (time(NULL) - 1 > this->getTime() && this->getBullet() != this->getMaxBullet())
	{
		this->setBullet(this->getBullet() + 2);

		if (this->getBullet() > this->getMaxBullet()) {
			this->setBullet(this->getMaxBullet());
		}
		this->setTime();
	}
}

void	Ship::collision(int how_hp)
{
	this->takeDamage(how_hp);
	system("afplay ./sounds/collision.wav &");
}

void	Ship::pause()
{
	int	button = 0;

	mvwaddch(stdscr, this->getPos().y, this->getPos().x, this->getSign());
	mvwprintw(stdscr, this->getTerm().y >> 1, this->getTerm().x >> 1, "Pause");
	refresh();

	while (button != 'P' && button != 'p') {
		button = getch();
	}
	mvwprintw(stdscr, this->getTerm().y >> 1, this->getTerm().x >> 1, "     ");
	refresh();
}

int		Ship::print_temp()
{
	int x1, y1 = 0;

	mvwprintw(stdscr, (this->getTerm().y >> 1) - 5,
		(this->getTerm().x >> 1) - 6, "Main menu");
	mvwprintw(stdscr, (this->getTerm().y >> 1) - 3,
		(this->getTerm().x >> 1) - 3, "Exit");
	mvwprintw(stdscr, (this->getTerm().y >> 1) - 5,
		(this->getTerm().x >> 1) - 7, ">");
	refresh();

	while (1)
	{
	 	switch (getch())
	 	{
	 		case KEY_DOWN:
				mvwaddch(stdscr, (getTerm().y >> 1) - 5, (getTerm().x >> 1) - 7, ' ');
				mvwaddch(stdscr, (getTerm().y >> 1) - 3, (getTerm().x >> 1) - 4, '>');
				refresh();
	 			break ;
			case KEY_UP:
				mvwaddch(stdscr, (getTerm().y >> 1) - 3, (getTerm().x >> 1) - 4, ' ');
				mvwaddch(stdscr, (getTerm().y >> 1) - 5, (getTerm().x >> 1) - 7, '>');
				refresh();
 				break ;
 			case 10:
				getsyx(y1, x1);
				if (y1 == (getTerm().y >> 1) - 3) {
	 				return 0;
				}
	 			else {
	 				return 1;
	 			}
				break ;
	 	}
	 }
}

int		Ship::gameOver()
{
	char	*timer = this->getTimer();

	system("afplay ./sounds/game_over.wav &");

	clear();
	mvwprintw(stdscr, this->getTerm().y >> 3,
		(this->getTerm().x >> 1) - 12,
		"Game Over (Total score: %d)", this->getScore());
	mvwprintw(stdscr, (this->getTerm().y >> 3) + 2,
		(this->getTerm().x >> 1) - 8,
		"Total time: %s", timer);
	mvwprintw(stdscr, (this->getTerm().y >> 3) + 4, (this->getTerm().x >> 1) - 8,
		"Total shoots: %d", this->totalShoots);

	delete [] timer;
	return print_temp();
}

int		Ship::Victory()
{
	int		res;
	char	*timer = this->getTimer();

	system("afplay ./sounds/victory.mp3 &");
	clear();
	
	mvwprintw(stdscr, this->getTerm().y >> 3,
		(this->getTerm().x >> 1) - 12,
		"Victory! (Total score: %d)", this->getScore());
	mvwprintw(stdscr, (this->getTerm().y >> 3) + 2, (this->getTerm().x >> 1) - 12,
		"Total time: %s", timer);
	mvwprintw(stdscr, (this->getTerm().y >> 3) + 4, (this->getTerm().x >> 1) - 12,
		"Total shoots: %d", this->totalShoots);

	res = print_temp();
	system("killall afplay");

	delete [] timer;
	return res;
}

int		Ship::catch_button()
{
	int	button = getch();

	mvwaddch(stdscr, getPos().y, getPos().x, ' ');
	if (button == KEY_DOWN && this->getPos().y != this->getTerm().y - 1) {
		this->setPos(getPos().y + 1, getPos().x);
	}
	else if (button == KEY_UP && this->getPos().y != 1) {
		this->setPos(getPos().y - 1, getPos().x);
	}
	else if (button == KEY_LEFT && this->getPos().x != 0) {
		this->setPos(getPos().y, getPos().x - 1);
	}
	else if (button == KEY_RIGHT && this->getPos().x != this->getTerm().x >> 1) {
		this->setPos(getPos().y, getPos().x + 1);
	}
	else if (button == ' ') {
 		Batya::make_shoot();
		this->totalShoots++;
	}
 	else if (button == 'p' || button == 'P') {
 		this->pause();
 	}
 	else if (button == 10) {
 		return (0);
 	}
 	return (1);
}

char	*Ship::getTimer()
{
	char 	*buff;
	struct 	tm	*time_stamp;
	time_t 	timer = static_cast<time_t>(time(NULL) - this->getStartTime());

	buff = new char[10];
	time_stamp = gmtime(&timer);
	strftime(buff, 10, "%M:%S", time_stamp);

	return buff;
}

int		Ship::print_myship()
{
	reload();
	print_stats();
	usleep(27500);
	if (catch_button() == 0)
	{
		clear();
		return (0);
	}
	this->print_shoots();
	mvwaddch(stdscr, getPos().y, getPos().x, getSign());
	return (1);
}
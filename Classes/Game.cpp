/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Game.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mshkliai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/06 17:36:01 by mshkliai          #+#    #+#             */
/*   Updated: 2018/10/06 17:36:15 by mshkliai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../Classes_inc/Game.hpp"

Game::Game() : Batya(), boss_auth(0)
{
	chtype	n_sign = '<' | COLOR_PAIR(2);
	chtype	n_patron = '+' | COLOR_PAIR(3);

	this->setSign(n_sign);
	this->setPatron(n_patron);
	this->ship = new Ship;
	this->boss = new Boss;

	for (int i = 0; i < 10; i++)
	{
		this->ens[i].y = -1;
		this->ens[i].x = -1;
	}
	new_enemy(ship->getMaxEns());
	count_ens = ship->getMaxEns();
}

Game::Game(Game const &obj) : Batya(obj)
{
	*this = obj;
}

Game::~Game()
{
	delete this->ship;
	delete this->boss;
}
	
Game	&Game::operator = (Game const &obj)
{
	Batya::operator = (obj);

	this->boss_auth = obj.boss_auth;
	
	for (int i = 0; i < 10; i++)
	{
		this->ens[i].y = obj.ens[i].y;
		this->ens[i].x = obj.ens[i].x;
	}

	this->count_ens = obj.count_ens;
	this->ship = obj.ship;
	this->boss = obj.boss;

	return *this;
}

int		Game::check_conf(int index)
{
	for (int i = 0; i < 10; i++)
	{
		if (i != index && this->ens[index].y == this->ens[i].y &&
		this->ens[index].x == this->ens[index].x) {
			return 0;
		}
	}
	return 1;
}

void	Game::new_enemy(int how)
{
	for (int i = 0; i < 10 && how; i++)
	{
		if (ens[i].y == -1)
		{
			if (i % 2) {
				this->ens[i].y = this->getTerm().y + rand() % this->getTerm().y;
			}
			else {
				this->ens[i].y = this->getTerm().y - rand() % this->getTerm().y;
			}
			this->ens[i].x = this->getTerm().x - 1;
			how--;
		}
	}
}

void	Game::next_pos(int index)
{
	int	i = 0;
	t_cord	old_cords;
	old_cords.y = this->ens[index].y;
	old_cords.x = this->ens[index].x;

	while (i < index) {
		i++;
	}
	int random = (rand() + i) % 4;
	if (random == 1) {
		this->ens[i].x--;
	}
	else if (random == 2 && this->ens[i].y + 1 != this->getTerm().y) {
		this->ens[i].y++;
	}
	else if (random == 3 && this->ens[i].y - 1 > 1) {
		this->ens[i].y--;
	}
	if (!check_conf(index))
	{
		this->ens[i].y = old_cords.y;
		this->ens[i].x = old_cords.x;
	}

	if (this->ens[i].y == ship->getPos().y
		&& this->ens[i].x == ship->getPos().x)
	{
		system("afplay ./sounds/collision.wav &");
		ship->takeDamage(30);
		this->del_en(i);
	}
}

void	Game::print_ens(int *timer)
{
	for (int i = 0; i < 10; i++)
	{
		if (this->ens[i].y != -1)
		{
			mvwprintw(stdscr, this->ens[i].y, this->ens[i].x, " ");
			if (*timer >= ship->getSpeed()) {
				next_pos(i);
			}
			mvwaddch(stdscr, this->ens[i].y, this->ens[i].x, this->getSign());
		}
		if (this->getTime() < time(NULL))
		{
				this->make_shoot(this->ens[rand() % 10]);
				this->setTime();
				if (ship->getHP() <= 10) {
					system("afplay ./sounds/low_hp.wav &");
				}
		}
	}
	*timer >= ship->getSpeed() ? *timer = 0 : 0;
}

int		Game::del_en(int index)
{
	int	count = 0;
	if (index != -1 && ++count) {
		this->ens[index].y = -1;
	}

	for (int i = 0; i < 10; i++)
		if (this->ens[i].x < 0 || this->ens[i].x >= this->getTerm().x)
		{
			if (this->ens[i].y > -1 && this->ens[i].y < this->getTerm().y && this->ens[i].x == -1)
			{
				ship->setScore(ship->getScore() - 1);
				system("afplay ./sounds/bie_enemy.wav &");
			}
			this->ens[i].y = -1;
			this->ens[i].x = 1;
			count++;
		}
		return count;
}

void	Game::check_boss_kill(t_cord ship_shoot, int index)
{
	if (ship_shoot.y != -1)
	{
		if (ship_shoot.y == boss->getPos().y && ship_shoot.x == boss->getPos().x)
		{
			mvwprintw(stdscr, ship_shoot.y, ship_shoot.x, " ");
			boss->takeDamage(10);
			ship->del_shoot(index);
			system("afplay ./sounds/boss_damage.wav &");
		}
		else
		{
			for (int i = 1; i < 4; i++)
			{
				if (ship_shoot.y == boss->getPos().y + i
					&& ship_shoot.x == boss->getPos().x - 1)
				{
					mvwprintw(stdscr, ship_shoot.y, ship_shoot.x, " ");
					boss->takeDamage(10);
					ship->del_shoot(index);
					system("afplay ./sounds/boss_damage.wav &");
				}
			}
		}
	}
}

void	Game::check_kills_ens()
{
	t_cord	*shoots = ship->getShoot();
	int		a = -1;

	while (++a < 10)
	{
		for (int i = 0; i < 64; i++)
		{
			if (this->ens[a].y != -1
				&& this->ens[a].y == shoots[i].y
				&& this->ens[a].x == shoots[i].x)
			{
				count_ens -= del_en(a);
				mvwprintw(stdscr, shoots[i].y, shoots[i].x, " ");
				ship->del_shoot(i);
				ship->setScore(ship->getScore() + 1);
				system("afplay ./sounds/enemy_death.mp3 &");
			}
			if (this->boss_auth) {
				check_boss_kill(shoots[i], i);
			}
		}
	}
}

void	Game::check_ship_kill()
{
	t_cord	*enemy_shoots = this->getShoot();
	t_cord	*boss_shoots = boss->getShoot();

	for (int i = 0; i < 64; i++)
	{
		if (enemy_shoots[i].y == ship->getPos().y
			&& enemy_shoots[i].x == ship->getPos().x)
		{
			ship->takeDamage(20);
			system("afplay ./sounds/damage_me.wav &");
			this->del_shoot(i);
			mvwprintw(stdscr, enemy_shoots[i].y, enemy_shoots[i].x, " ");
		}
		if (boss_shoots[i].y == ship->getPos().y
			&& boss_shoots[i].x == ship->getPos().x)
		{
			ship->takeDamage(50);
			system("afplay ./sounds/damage_me.wav &");
			boss->del_shoot(i);
			mvwprintw(stdscr, boss_shoots[i].y, boss_shoots[i].x, " ");
		}
	}

	if (!boss_auth) {
		return ;
	}
	if (ship->getPos().y == boss->getPos().y && ship->getPos().x == boss->getPos().x) {
		ship->collision(ship->getMaxHP());
	}
	else
	{
		for (int i = 1; i < 4; i++)
		{
			if (ship->getPos().y == boss->getPos().y + i &&
			ship->getPos().x == boss->getPos().x - 1) {
				ship->collision(ship->getMaxHP());
			}
		}
	}
}

void	Game::print_timer()
{
	char 	buff[10];
	struct 	tm	*time_stamp;
	time_t 	timer = static_cast<time_t>(this->getTime() - this->getStartTime());

	time_stamp = gmtime(&timer);
	strftime(buff, 10, "%M:%S", time_stamp);

	mvwprintw(stdscr, 0, this->getTerm().x >> 1, "%s", buff);
}

int		Game::all_process()
{
	int		timer = 0;

	system("afplay ./sounds/new_game.mp3 &");

	this->setStartTime();
	ship->setStartTime();
	while (ship->print_myship())
	{
		ship->new_level();
		check_kills_ens();
		check_ship_kill();

		if (boss->getHP() <= 0)
		{
			system("afplay ./sounds/death_boss.wav");
			return ship->Victory() == 0 ? 0 : 1;
		}
		if (ship->getHP() <= 0 || ship->getScore() < 0) {
			return ship->gameOver() == 0 ? 0 : 1;
		}

		print_ens(&timer);
		if (ship->getScore() < 70 && count_ens < ship->getMaxEns())
		{
			new_enemy(ship->getMaxEns() - count_ens);
			count_ens += ship->getMaxEns() - count_ens;
		}
		if (ship->getScore() >= 70 && boss_auth == 0)
		{
			system("afplay ./sounds/hi_boss.wav &");
			boss_auth = 1;
		}
		if (boss_auth == 1) {
			boss->print_boss();
		}

		count_ens -= del_en(-1);
		this->print_shoots(1);
		this->del_shoot(-1);

		print_timer();

		refresh();
		timer++;
	}
	return 1;
}
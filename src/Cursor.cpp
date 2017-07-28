//
// Cursor.cpp for shootandrun in /home/melot_g/rendu/cpp_va
// 
// Made by gautier melot
// Login   <melot_g@epitech.net>
// 
// Started on  Tue Jul 22 10:49:07 2014 gautier melot
// Last update Thu Jul 24 14:38:15 2014 gautier melot
//

#include "Cursor.hpp"
#include "Cell.hpp"
#include "IDynLib.hpp"

Cursor::Cursor(IDynLib *& _lib, std::vector< std::vector< Cell > > & _map,
	       bool & _keepRunning, std::vector< Unit * > & _units)
  : lib(_lib), map(_map), units(_units), keepRunning(_keepRunning)
{
  std::vector<std::string>	tmp;

  this->x = 0;
  this->y = 0;
  this->funcs.push_back(&Cursor::moveUp);
  this->funcs.push_back(&Cursor::moveRight);
  this->funcs.push_back(&Cursor::moveDown);
  this->funcs.push_back(&Cursor::moveLeft);
  this->funcs.push_back(&Cursor::ending);
  this->funcs.push_back(&Cursor::selecting);
  this->selection = NULL;
  this->menu = false;
  this->voidMenu.push_back("End Turn");
  this->voidMenu.push_back("Cancel");
  this->quitMenu.push_back("Quit");
  this->quitMenu.push_back("Cancel");
  tmp.push_back("Attack");
  tmp.push_back("Move");
  tmp.push_back("Special");
  tmp.push_back("Cancel");
  this->unitMenu.push_back(tmp);
  tmp.clear();
  tmp.push_back("Attack");
  tmp.push_back("Special");
  tmp.push_back("Cancel");
  this->unitMenu.push_back(tmp);
  tmp.clear();
  tmp.push_back("Move");
  tmp.push_back("Special");
  tmp.push_back("Cancel");
  this->unitMenu.push_back(tmp);
  tmp.clear();
  tmp.push_back("Attack");
  tmp.push_back("Move");
  tmp.push_back("Cancel");
  this->unitMenu.push_back(tmp);
  tmp.clear();
  tmp.push_back("Attack");
  tmp.push_back("Cancel");
  this->unitMenu.push_back(tmp);
  tmp.clear();
  tmp.push_back("Move");
  tmp.push_back("Cancel");
  this->unitMenu.push_back(tmp);
  tmp.clear();
  this->players.push_back("Red");
  this->players.push_back("Blue");
  this->turn = RED;
  this->selects["End Turn"] = &Cursor::endTurn;
  this->selects["Quit"] = &Cursor::quit;
  this->selects["Attack"] = &Cursor::attack;
  this->selects["Move"] = &Cursor::move;
  this->selects["Special"] = &Cursor::special;
  this->selects["Cancel"] = &Cursor::clearMenu;
}

Cursor::~Cursor(void)
{
  this->funcs.clear();
  this->voidMenu.clear();
  this->quitMenu.clear();
  for (size_t i = 0; i < this->unitMenu.size(); ++i)
    this->unitMenu[i].clear();
  this->unitMenu.clear();
  this->players.clear();
  this->selects.clear();
}

int			Cursor::getX(void) const
{
  return (this->x);
}

int			Cursor::getY(void) const
{
  return (this->y);
}

std::string const &	Cursor::getPlayer(void) const
{
  return (this->players[this->turn]);
}

std::string const &	Cursor::getPlayer(eTeam team) const
{
  return (this->players[team]);
}

int			Cursor::getTurn(void) const
{
  return (this->turn);
}

void	Cursor::clearMenu(void)
{
  this->lib->cleanMenu(this->map[0].size(), this->lastMenu->size());
  this->menu = false;
}

void	Cursor::endTurn(void)
{
  this->turn = (this->turn == RED) ? BLUE : RED;
  for (size_t i = 0; i < this->units.size(); ++i)
    {
      if (this->units[i]->getTeam() == static_cast<eTeam>(this->turn))
	this->units[i]->newTurn();
    }
  this->clearMenu();
}

void	Cursor::quit(void)
{
  this->keepRunning = false;
}

void	Cursor::attack(void)
{
  if (this->selection == NULL && !this->map[this->y][this->x].getUnit()->hasAttacked())
    {
      this->selection = &this->map[this->y][this->x];
      this->selection->getUnit()->attackSelect(this->map, true);
      this->clearMenu();
    }
  else if (!this->map[this->y][this->x].isEmpty()
	   && this->map[this->y][this->x].getUnit()->getTeam() != static_cast<eTeam>(this->turn))
    {
      this->selection->getUnit()->attackSelect(this->map, false);
      this->selection->getUnit()->attack(this->map[this->y][this->x].getUnit());
      this->lib->playSound(ATTACK);
      this->selection = NULL;
    }
  else
    this->lib->playSound(ERROR);
}

void	Cursor::move(void)
{
  if (this->selection == NULL && !this->map[this->y][this->x].getUnit()->hasMoved())
    {
      this->selection = &this->map[this->y][this->x];
      this->selection->getUnit()->moveSelect(this->map, true);
      this->clearMenu();
    }
  else if (this->map[this->y][this->x].isEmpty())
    {
      this->selection->getUnit()->moveSelect(this->map, false);
      this->selection->getUnit()->move(this->x, this->y, &this->map[this->y][this->x]);
      this->lib->playSound(MOVE);
      this->selection = NULL;
    }
  else
    this->lib->playSound(ERROR);
}

void	Cursor::special(void)
{
  if (!this->map[this->y][this->x].getUnit()->hasUsedSpecial())
    {
      this->map[this->y][this->x].getUnit()->special();
      this->lib->playSound(SPECIAL);
      this->clearMenu();
    }
  else
    this->lib->playSound(ERROR);
}

void	Cursor::moveUp(void)
{
  if (this->menu)
    {
      this->p -= 1;
      if (this->p < 0)
	this->p = this->lastMenu->size() - 1;
      this->lib->menu(*this->lastMenu, this->p);
    }
  else if (this->selection != NULL && ((this->y - 1) < 0 || !this->map[this->y - 1][this->x].isEnlightened()))
    this->lib->playSound(ERROR);
  else
    {
      this->y = this->y - 1;
      if (this->y < 0)
	this->y = this->map.size() - 1;
    }
}

void	Cursor::moveRight(void)
{
  if (this->menu)
    {
      this->lib->playSound(ERROR);
      this->lib->menu(*this->lastMenu, this->p);
    }
  else if (this->selection != NULL && ((this->x + 1) > (static_cast<int>(this->map[this->y].size()) - 1) || !this->map[this->y][this->x + 1].isEnlightened()))
    this->lib->playSound(ERROR);
  else
    {
      this->x = this->x + 1;
      if (this->x > (static_cast<int>(this->map[this->y].size()) - 1))
	this->x = 0;
    }
}

void	Cursor::moveDown(void)
{
  if (this->menu)
    {
      this->p += 1;
      if (this->p >= static_cast<int>(this->lastMenu->size()))
	this->p = 0;
      this->lib->menu(*this->lastMenu, this->p);
    }
  else if (this->selection != NULL && ((this->y + 1) > (static_cast<int>(this->map[this->y].size()) - 1) || !this->map[this->y + 1][this->x].isEnlightened()))
    this->lib->playSound(ERROR);
  else
    {
      this->y = this->y + 1;
      if (this->y > (static_cast<int>(this->map.size()) - 1))
	this->y = 0;
    }
}

void	Cursor::moveLeft(void)
{
  if (this->menu)
    {
      this->lib->playSound(ERROR);
      this->lib->menu(*this->lastMenu, this->p);
    }
  else if (this->selection != NULL && ((this->x - 1) < 0 || !this->map[this->y][this->x - 1].isEnlightened()))
    this->lib->playSound(ERROR);
  else
    {
      this->x = this->x - 1;
      if (this->x < 0)
	this->x = this->map[0].size() - 1;
    }
}

void	Cursor::ending(void)
{
  if (this->selection != NULL)
    {
      if ((*this->lastMenu)[this->p] == "Attack")
	this->selection->getUnit()->attackSelect(this->map, false);
      else if ((*this->lastMenu)[this->p] == "Move")
	this->selection->getUnit()->moveSelect(this->map, false);
      this->selection = NULL;
    }
  else if (this->menu)
    {
      this->lib->cleanMenu(this->map[0].size(), this->lastMenu->size());
      this->menu = false;
    }
  else
    {
      this->menu = true;
      this->p = 0;
      this->lastMenu = &this->quitMenu;
      this->lib->menu(*this->lastMenu, this->p);
    }
}

void	Cursor::selecting(void)
{
  if (!this->menu && this->selection == NULL)
    {
      int	tmp;

      this->p = 0;
      this->lastMenu = NULL;
      if (this->map[this->y][this->x].isEmpty())
	this->lastMenu = &this->voidMenu;
      else if (this->map[this->y][this->x].getUnit()->getTeam() == static_cast<eTeam>(this->turn)
	       && (tmp = USTATE(this->map[this->y][this->x].getUnit()->hasAttacked(),
				this->map[this->y][this->x].getUnit()->hasMoved(),
				this->map[this->y][this->x].getUnit()->hasUsedSpecial())) < 6)
	this->lastMenu = &this->unitMenu[tmp];
      else
	this->lib->playSound(ERROR);
      if (this->lastMenu != NULL)
	{
	  this->lib->menu(*this->lastMenu, this->p);
	  this->menu = true;
	}
    }
  else if (this->selection == NULL)
    (this->*selects[(*this->lastMenu)[this->p]])();
  else
    (this->*selects[(*this->lastMenu)[this->p]])();
}

void	Cursor::act(void)
{
  static eMove	move = NONE;

  move = this->lib->getMove();
  if (move != NONE)
    (this->*this->funcs[move])();
}

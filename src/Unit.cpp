//
// Unit.cpp for shootandrun in /home/melot_g/rendu/cpp_va
// 
// Made by gautier melot
// Login   <melot_g@epitech.net>
// 
// Started on  Mon Jul 21 15:00:10 2014 gautier melot
// Last update Thu Jul 24 12:59:28 2014 gautier melot
//

#include <iostream>
#include <stdexcept>
#include "Unit.hpp"
#include "Cell.hpp"
#include "messages.h"

Unit::Unit(eUnitType t, eTeam _team, std::string const & _name,
	   int l, int a, int s, int r, int _x, int _y)
{
  this->type = t;
  this->team = _team;
  this->name = _name;
  this->life = l;
  this->att = a;
  this->speed = s;
  this->range = r;
  this->used = false;
  this->moved = false;
  this->attacked = false;
  this->x = _x;
  this->y = _y;
  this->position = NULL;
  this->specialAbility = false;
}

Unit::Unit(Unit const & model)
{
  this->type = model.getType();
  this->team = model.getTeam();
  this->name = model.getName();
  this->life = model.getLife();
  this->att = model.getAttack();
  this->speed = model.getSpeed();
  this->range = model.getRange();
  this->used = false;
  this->moved = false;
  this->attacked = false;
  this->x = model.getX();
  this->y = model.getY();
  this->position = model.getPosition();
  this->specialAbility = false;
}

Unit::~Unit(void)
{
}

Unit &	Unit::operator=(Unit const & model)
{
  this->type = model.getType();
  this->team = model.getTeam();
  this->name = model.getName();
  this->life = model.getLife();
  this->att = model.getAttack();
  this->speed = model.getSpeed();
  this->range = model.getRange();
  this->used = false;
  this->moved = false;
  this->attacked = false;
  this->x = model.getX();
  this->y = model.getY();
  this->position = model.getPosition();
  return (*this);
}

void		Unit::attack(Unit * target)
{
  if (this->position == NULL)
    throw std::runtime_error(UNIT_NOP);

  target->setLife(target->getLife() - (this->att + this->position->getAttackMod() - target->getPosition()->getDefenseMod()));
  if (target->getLife() <= 0)
    target->getPosition()->setUnit(NULL);
  this->attacked = true;
}

void	Unit::move(int _x, int _y, Cell * target)
{
  if (this->position == NULL)
    throw std::runtime_error(UNIT_NOP);

  this->x = _x;
  this->y = _y;
  this->position->setUnit(NULL);
  this->position = target;
  this->position->setUnit(this);
  this->moved = true;
}

void	Unit::attackSelect(std::vector< std::vector< Cell > > & map, bool enlight)
{
  int	ys = static_cast<int>(map.size());
  int	xs = static_cast<int>(map[0].size());
  int	rt = this->range + this->position->getRangeMod();

  for (int i = (-rt); i <= rt; ++i)
    {
      int	yt = i + this->y;

      for (int j = (-rt); j <= rt; ++j)
	{
	  int	xt = j + this->x;

	  if ((ABS(i) + ABS(j)) <= rt && yt >= 0 && yt < ys && xt >= 0 && xt < xs)
	    map[yt][xt].enlightenment(enlight);
	}
    }
}

void	Unit::launchSelection(std::vector< std::vector< Cell > > & map, bool enlight,
			      int _speed, int _x, int _y)
{
  if ((_y - 1) >= 0)
    this->moveSelect(map, enlight, _speed - 1 + map[_y][_x].getSpeedMod(), _x, _y - 1);
  if ((_y + 1) < static_cast<int>(map.size()))
    this->moveSelect(map, enlight, _speed - 1 + map[_y][_x].getSpeedMod(), _x, _y + 1);
  if ((_x - 1) >= 0)
    this->moveSelect(map, enlight, _speed - 1 + map[_y][_x].getSpeedMod(), _x - 1, _y);
  if ((_x + 1) < static_cast<int>(map[0].size()))
    this->moveSelect(map, enlight, _speed - 1 + map[_y][_x].getSpeedMod(), _x + 1, _y);
}

void	Unit::moveSelect(std::vector< std::vector< Cell > > & map, bool enlight)
{
  map[this->y][this->x].enlightenment(enlight);
  this->launchSelection(map, enlight, this->speed, this->x, this->y);
}

void	Unit::moveSelect(std::vector< std::vector< Cell > > & map, bool enlight,
			 int _speed, int _x, int _y)
{
  if (map[_y][_x].isEmpty() && _speed >= 0)
    {
      map[_y][_x].enlightenment(enlight);
      this->launchSelection(map, enlight, _speed, _x, _y);
    }
}

void	Unit::newTurn(void)
{
  this->moved = false;
  this->attacked = false;
  this->specialAbility = false;
}

bool	Unit::hasMoved(void) const
{
  return (this->moved);
}

bool	Unit::hasAttacked(void) const
{
  return (this->attacked);
}

bool	Unit::hasUsedSpecial(void) const
{
  return (this->used);
}

eUnitType	Unit::getType(void) const
{
  return (this->type);
}

eTeam		Unit::getTeam(void) const
{
  return (this->team);
}

std::string const &	Unit::getName(void) const
{
  return (this->name);
}

int		Unit::getLife(void) const
{
  return (this->life);
}

int		Unit::getAttack(void) const
{
  return (this->att);
}

int		Unit::getSpeed(void) const
{
  return (this->speed);
}

int		Unit::getRange(void) const
{
  return (this->range);
}

Cell *		Unit::getPosition(void) const
{
  return (this->position);
}

int		Unit::getX(void) const
{
  return (this->x);
}

int		Unit::getY(void) const
{
  return (this->y);
}

void	Unit::setPosition(Cell * pos, int _x, int _y)
{
  this->position = pos;
  this->x = _x;
  this->y = _y;
}

void	Unit::setLife(int l)
{
  this->life = l;
}

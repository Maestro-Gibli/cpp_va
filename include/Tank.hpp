//
// Tank.hpp for shootandrun in /home/melot_g/rendu/cpp_va
// 
// Made by gautier melot
// Login   <melot_g@epitech.net>
// 
// Started on  Thu Jul 24 10:23:48 2014 gautier melot
// Last update Thu Jul 24 10:54:59 2014 gautier melot
//

#ifndef		TANK_HPP_
# define	TANK_HPP_

#include <stdexcept>
#include "messages.h"
#include "Cell.hpp"

class	Tank : public Unit
{
public:
  Tank(eTeam _team, std::string const & _name, int _x, int _y)
    : Unit(TANK, _team, _name, 10, 5, 7, 3, _x, _y)
  {
  }

  Tank(Unit const & model)
    : Unit(TANK, model.getTeam(), model.getName(), 10, 5, 7, 3, model.getX(), model.getY())
  {
  }

  virtual ~Tank(void)
  {
  }

  virtual void	special(void)
  {
    if (this->getPosition() == NULL)
      throw std::runtime_error(UNIT_NOP);

    this->used = true;
    this->specialAbility = true;
  }

  virtual void	attack(Unit * target)
  {
    int		mod = (this->specialAbility) ? 2 : 1;

    if (this->getPosition() == NULL)
      throw std::runtime_error(UNIT_NOP);

    target->setLife(target->getLife() - ((this->att + this->getPosition()->getAttackMod() - target->getPosition()->getDefenseMod()) * mod));
    if (target->getLife() <= 0)
      target->getPosition()->setUnit(NULL);
    this->attacked = true;
  }
};

#endif		// !TANK_HPP_

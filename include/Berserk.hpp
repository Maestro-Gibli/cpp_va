//
// Berserk.hpp for shootandrun in /home/melot_g/rendu/cpp_va
// 
// Made by gautier melot
// Login   <melot_g@epitech.net>
// 
// Started on  Thu Jul 24 09:17:55 2014 gautier melot
// Last update Thu Jul 24 10:54:36 2014 gautier melot
//

#ifndef		BERSERK_HPP_
# define	BERSERK_HPP_

#include <stdexcept>
#include "messages.h"
#include "Cell.hpp"

class	Berserk : public Unit
{
public:
  Berserk(eTeam _team, std::string const & _name, int _x, int _y)
    : Unit(BERSERK, _team, _name, 15, 4, 5, 1, _x, _y)
  {
  }

  Berserk(Unit const & model)
    : Unit(BERSERK, model.getTeam(), model.getName(), 15, 4, 5, 1, model.getX(), model.getY())
  {
  }

  virtual ~Berserk(void)
  {
  }
  
  virtual void	special(void)
  {
    if (this->getPosition() == NULL)
      throw std::runtime_error(UNIT_NOP);

    this->used = true;
    this->specialAbility = true;
  }

  virtual void  moveSelect(std::vector< std::vector< Cell > > & map, bool enlight,
			   int _speed, int _x, int _y)
  {
    if ((map[_y][_x].isEmpty() || this->specialAbility) && _speed >= 0)
      {
	map[_y][_x].enlightenment(enlight);
	this->launchSelection(map, enlight, _speed, _x, _y);
      }
  }
};

#endif		// !BERSERK_HPP_

//
// MissileLauncher.hpp for shootandrun in /home/melot_g/rendu/cpp_va
// 
// Made by gautier melot
// Login   <melot_g@epitech.net>
// 
// Started on  Thu Jul 24 09:44:48 2014 gautier melot
// Last update Thu Jul 24 10:54:46 2014 gautier melot
//

#ifndef		MISSILE_LAUNCHER_HPP_
# define	MISSILE_LAUNCHER_HPP_

#include <stdexcept>
#include "messages.h"
#include "Cell.hpp"

class	MissileLauncher : public Unit
{
public:
  MissileLauncher(eTeam _team, std::string const & _name, int _x, int _y)
    : Unit(MISSILE_LAUNCHER, _team, _name, 5, 6, 6, 5, _x, _y)
  {
  }

  MissileLauncher(Unit const & model)
    : Unit(MISSILE_LAUNCHER, model.getTeam(), model.getName(), 5, 6, 6, 5, model.getX(), model.getY())
  {
  }

  virtual ~MissileLauncher(void)
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
    if (this->getPosition() == NULL)
      throw std::runtime_error(UNIT_NOP);

    if (!this->specialAbility)
      {
	target->setLife(target->getLife() - (this->att + this->getPosition()->getAttackMod() - target->getPosition()->getDefenseMod()));
	if (target->getLife() <= 0)
	  target->getPosition()->setUnit(NULL);
      }
    else
      {
	std::vector< std::vector< Cell > > *	map = this->getPosition()->getMap();
	int					ys = static_cast<int>(map->size());
	int					xs = static_cast<int>((*map)[0].size());
	int					rt = 8;
	int					ap = 3;

	for (int i = (-rt); i <= rt; ++i)
	  {
	    int	yt = i + target->getY();

	    for (int j = (-rt); j <= rt; ++j)
	      {
		int	xt = j + target->getX();

		if ((ABS(i) + ABS(j)) <= rt && yt >= 0 && yt < ys
		    && xt >= 0 && xt < xs && !(*map)[yt][xt].isEmpty())
		  {
		    (*map)[yt][xt].getUnit()->setLife((*map)[yt][xt].getUnit()->getLife() - ap);
		    if ((*map)[yt][xt].getUnit()->getLife() <= 0)
		      (*map)[yt][xt].setUnit(NULL);
		  }
	      }
	  }
      }
    this->attacked = true;

  }
};

#endif		// !MISSILE_LAUNCHER_HPP_


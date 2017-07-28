//
// UnitFactory.hpp for shootandrun in /home/melot_g/rendu/cpp_va
// 
// Made by gautier melot
// Login   <melot_g@epitech.net>
// 
// Started on  Wed Jul 23 13:47:20 2014 gautier melot
// Last update Thu Jul 24 10:54:12 2014 gautier melot
//

#ifndef		UNITFACTORY_HPP_
# define	UNITFACTORY_HPP_

#include "Berserk.hpp"
#include "Tank.hpp"
#include "MissileLauncher.hpp"

class	UnitFactory
{
private:
  std::vector< std::vector< Unit * > >	models;

public:
  UnitFactory(void);
  ~UnitFactory(void);

  template <typename T, eUnitType type, eTeam team>
  Unit *	producePreciseUnit(Cell * position, int x, int y) const
  {
    T * ret = new T(static_cast<T>(*this->models[team][type]));

    ret->setPosition(position, x, y);
    return (ret);
  }
};

template
Unit *	UnitFactory::producePreciseUnit<Berserk, BERSERK, RED>(Cell * position, int x, int y) const;
template
Unit *	UnitFactory::producePreciseUnit<Tank, TANK, RED>(Cell * position, int x, int y) const;
template
Unit *	UnitFactory::producePreciseUnit<MissileLauncher, MISSILE_LAUNCHER, RED>(Cell * position, int x, int y) const;

#endif		// !UNITFACTORY_HPP_

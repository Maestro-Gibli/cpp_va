//
// Cell.cpp for shootandrun in /home/melot_g/rendu/cpp_va
// 
// Made by gautier melot
// Login   <melot_g@epitech.net>
// 
// Started on  Mon Jul 21 14:48:11 2014 gautier melot
// Last update Thu Jul 24 10:32:56 2014 gautier melot
//

#include "Cell.hpp"

Cell::Cell(eCellType t, std::string const & _name, int rM, int sM,
	   int aM, int dM, std::vector< std::vector< Cell > > *	_map)
{
  this->type = t;
  this->name = _name;
  this->rangeMod = rM;
  this->speedMod = sM;
  this->attackMod = aM;
  this->defenseMod = dM;
  this->unit = NULL;
  this->enlight = false;
  this->map = _map;
}

Cell::Cell(eCellType t, std::string const & _name, int rM, int sM, int aM, int dM)
{
  this->type = t;
  this->name = _name;
  this->rangeMod = rM;
  this->speedMod = sM;
  this->attackMod = aM;
  this->defenseMod = dM;
  this->unit = NULL;
  this->enlight = false;
  this->map = NULL;
}

Cell::Cell(Cell const & model)
{
  this->type = model.getType();
  this->name = model.getName();
  this->rangeMod = model.getRangeMod();
  this->speedMod = model.getSpeedMod();
  this->attackMod = model.getAttackMod();
  this->defenseMod = model.getDefenseMod();
  this->unit = NULL;
  this->enlight = false;
  this->map = model.getMap();
}

Cell::~Cell(void)
{
}

Cell &	Cell::operator=(Cell const & model)
{
  this->type = model.getType();
  this->name = model.getName();
  this->rangeMod = model.getRangeMod();
  this->speedMod = model.getSpeedMod();
  this->attackMod = model.getAttackMod();
  this->defenseMod = model.getDefenseMod();
  this->map = model.getMap();
  return (*this);
}

int					Cell::getRangeMod(void) const
{
  return (this->rangeMod);
}

int					Cell::getSpeedMod(void) const
{
  return (this->speedMod);
}

int					Cell::getAttackMod(void) const
{
  return (this->attackMod);
}

int					Cell::getDefenseMod(void) const
{
  return (this->defenseMod);
}

bool					Cell::isEmpty(void) const
{
  return (this->unit == NULL);
}

bool					Cell::isEnlightened(void) const
{
  return (this->enlight);
}

eCellType				Cell::getType(void) const
{
  return (this->type);
}

std::string const &			Cell::getName(void) const
{
  return (this->name);
}

Unit *					Cell::getUnit(void) const
{
  return (this->unit);
}

std::vector< std::vector< Cell > > *	Cell::getMap(void) const
{
  return (this->map);
}

void	Cell::setUnit(Unit * _unit)
{
  this->unit = _unit;
}

void	Cell::setMap(std::vector< std::vector< Cell > > * _map)
{
  this->map = _map;
}


void	Cell::enlightenment(bool _enlight)
{
  this->enlight = _enlight;
}

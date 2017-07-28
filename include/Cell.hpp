//
// Cell.hpp for shootandrun in /home/melot_g/rendu/cpp_va
// 
// Made by gautier melot
// Login   <melot_g@epitech.net>
// 
// Started on  Mon Jul 21 14:48:23 2014 gautier melot
// Last update Thu Jul 24 10:02:48 2014 gautier melot
//

#ifndef		CELL_HPP_
# define	CELL_HPP_

#include "Unit.hpp"

enum	eCellType
  {
    MOUNTAIN = 0,
    RIVER = 1,
    PLAIN = 2
  };

class	Cell
{
private:
  eCellType		type;
  std::string		name;
  int			rangeMod;
  int			speedMod;
  int			attackMod;
  int			defenseMod;
  Unit *		unit;
  bool			enlight;
  std::vector< std::vector< Cell > > *	map;

public:
  Cell(eCellType t, std::string const & _name, int rM, int sM,
       int aM, int dM, std::vector< std::vector< Cell > > * _map);
  Cell(eCellType t, std::string const & _name, int rM, int sM, int aM, int dM);
  Cell(Cell const & model);
  ~Cell(void);

  Cell &	operator=(Cell const & model);

  int					getRangeMod(void) const;
  int					getSpeedMod(void) const;
  int					getAttackMod(void) const;
  int					getDefenseMod(void) const;
  bool					isEmpty(void) const;
  bool					isEnlightened(void) const;
  eCellType				getType(void) const;
  std::string const &			getName(void) const;
  Unit *				getUnit(void) const;
  std::vector< std::vector< Cell > > *	getMap(void) const;

  void	setUnit(Unit * _unit);
  void	setMap(std::vector< std::vector< Cell > > * _map);
  void	enlightenment(bool _enlight);
};

#endif		// !CELL_HPP_

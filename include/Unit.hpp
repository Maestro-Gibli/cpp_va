//
// Unit.hpp for shootandrun in /home/melot_g/rendu/cpp_va
// 
// Made by gautier melot
// Login   <melot_g@epitech.net>
// 
// Started on  Mon Jul 21 15:00:25 2014 gautier melot
// Last update Thu Jul 24 12:31:25 2014 gautier melot
//

#ifndef		UNIT_HPP_
# define	UNIT_HPP_

#include <string>
#include <vector>

#define ABS(x)	((x < 0) ? (-x) : x)

class	Cell;

enum	eUnitType
  {
    BERSERK = 0,
    TANK = 1,
    MISSILE_LAUNCHER = 2
  };

enum	eTeam
  {
    RED = 0,
    BLUE = 1,
    NEITHER = 2
  };

class	Unit
{
private:
  eUnitType	type;
  eTeam		team;
  std::string	name;
  int		x;
  int		y;
  Cell *	position;

protected:
  int		life;
  int		att;
  bool		attacked;
  int		speed;
  bool		moved;
  int		range;
  bool		used;
  bool		specialAbility;

public:
  Unit(eUnitType t, eTeam _team, std::string const & _name,
       int l, int a, int s, int r, int _x, int _y);
  Unit(Unit const & model);
  virtual ~Unit(void);

  Unit &	operator=(Unit const & model);

  virtual void	attack(Unit * target);
  virtual void	move(int _x, int _y, Cell * target);
  virtual void	special(void) = 0;

  virtual void	attackSelect(std::vector< std::vector< Cell > > & map, bool enlight);
  virtual void  launchSelection(std::vector< std::vector< Cell > > & map, bool enlight,
			int _speed, int _x, int _y);
  virtual void	moveSelect(std::vector< std::vector< Cell > > & map, bool enlight);
  virtual void	moveSelect(std::vector< std::vector< Cell > > & map, bool enlight,
		   int _speed, int _x, int _y);

  void	newTurn(void);

  bool	hasMoved(void) const;
  bool	hasAttacked(void) const;
  bool	hasUsedSpecial(void) const;

  eUnitType		getType(void) const;
  eTeam			getTeam(void) const;
  std::string const &	getName(void) const;
  int			getLife(void) const;
  int			getAttack(void) const;
  int			getSpeed(void) const;
  int			getRange(void) const;
  Cell *		getPosition(void) const;
  int			getX(void) const;
  int			getY(void) const;

  void	setPosition(Cell * pos, int _x, int _y);
  void	setLife(int l);
};

#endif		// !UNIT_HPP_

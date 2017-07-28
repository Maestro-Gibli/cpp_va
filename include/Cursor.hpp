//
// Cursor.hpp for shootandrun in /home/melot_g/rendu/cpp_va
// 
// Made by gautier melot
// Login   <melot_g@epitech.net>
// 
// Started on  Tue Jul 22 10:49:18 2014 gautier melot
// Last update Thu Jul 24 14:23:01 2014 gautier melot
//

#ifndef		CURSOR_HPP_
# define	CURSOR_HPP_

#include <map>
#include <vector>
#include <string>
#include "Unit.hpp"

# define USTATE(i, j, k) ((!i && !j && !k) ? 0 : \
			  ((!i && j && !k) ? 1 : \
			   ((i && !j && !k) ? 2 : \
			    ((!i && !j && k) ? 3 : \
			     ((!i && j && k) ? 4 : \
			      ((i && !j && k) ? 5 : 6))))))

class	IDynLib;

class	Cursor
{
private:
  int						x;
  int						y;
  std::vector<void (Cursor::*)(void)>		funcs;
  Cell *					selection;
  bool						menu;
  IDynLib *&					lib;
  std::vector< std::vector< Cell > > &		map;
  std::vector< Unit * > &			units;
  bool &					keepRunning;
  std::vector< std::string >			voidMenu;
  std::vector< std::string >			quitMenu;
  std::vector< std::vector< std::string > >	unitMenu;
  std::vector< std::string > *			lastMenu;
  int						p;
  std::vector< std::string >			players;
  int						turn;
  std::map<std::string, void (Cursor::*)(void)>	selects;

  void	clearMenu(void);
  void	endTurn(void);
  void	quit(void);
  void	attack(void);
  void	move(void);
  void	special(void);

public:
  Cursor(IDynLib *& _lib, std::vector< std::vector< Cell > > & _map,
	 bool & _keepRunning, std::vector< Unit * > & _units);
  ~Cursor(void);

  int			getX(void) const;
  int			getY(void) const;
  std::string const &	getPlayer(void) const;
  std::string const &	getPlayer(eTeam team) const;
  int			getTurn(void) const;

  void	moveUp(void);
  void	moveRight(void);
  void	moveDown(void);
  void	moveLeft(void);
  void	ending(void);
  void	selecting(void);

  void	act(void);
};

#endif		// !CURSOR_HPP_

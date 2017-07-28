//
// IDynLib.hpp for shootandrun in /home/melot_g/rendu/cpp_va
// 
// Made by gautier melot
// Login   <melot_g@epitech.net>
// 
// Started on  Mon Jul 21 14:36:05 2014 gautier melot
// Last update Thu Jul 24 16:49:43 2014 gautier melot
//

#ifndef		IDYNLIB_HPP_
# define	IDYNLIB_HPP_

#include <vector>
#include "Cell.hpp"
#include "Cursor.hpp"

enum	eMove
  {
    UP = 0,
    RIGHT = 1,
    DOWN = 2,
    LEFT = 3,
    END = 4,
    SELECT = 5,
    NONE
  };

enum	eSound
  {
    ERROR = 0,
    ATTACK = 1,
    MOVE = 2,
    SPECIAL = 3
  };

class	IDynLib
{
public:
  virtual ~IDynLib(void)
  {
  }

  virtual void	intro(void) = 0;
  virtual eMove	getMove(void) = 0;
  virtual void	aff(std::vector< std::vector< Cell > > const & map, int x, int y, std::string const & player, eTeam turn) = 0;
  virtual void	playSound(eSound sound) = 0;
  virtual void	menu(std::vector<std::string> const & menu, int p) = 0;
  virtual void	cleanMenu(int size_x, size_t ntime) = 0;
  virtual void	end(std::string const & player, eTeam turn) = 0;
};

#endif		// !IDYNLIB_HPP_

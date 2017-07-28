//
// CellFactory.hpp for shootandrun in /home/melot_g/rendu/cpp_va
// 
// Made by gautier melot
// Login   <melot_g@epitech.net>
// 
// Started on  Mon Jul 21 15:41:56 2014 gautier melot
// Last update Tue Jul 22 14:12:24 2014 gautier melot
//

#ifndef		CELLFACTORY_HPP_
# define	CELLFACTORY_HPP_

#include <vector>
#include <map>
#include "Cell.hpp"

class	CellFactory
{
private:
  std::vector<Cell>		models;
  std::map<char, eCellType>	typeMap;

public:
  CellFactory(void);
  ~CellFactory(void);

  Cell		produceRandomCell(void) const;
  Cell		producePreciseCell(eCellType type) const;
  eCellType	getCellTypeFromChar(char c) const;
};

#endif		// !CELLFACTORY_HPP_

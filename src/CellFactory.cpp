//
// CellFactory.cpp for shootandrun in /home/melot_g/rendu/cpp_va
// 
// Made by gautier melot
// Login   <melot_g@epitech.net>
// 
// Started on  Tue Jul 22 09:15:40 2014 gautier melot
// Last update Tue Jul 22 14:17:01 2014 gautier melot
//

#include <cstdlib>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdexcept>
#include "CellFactory.hpp"
#include "messages.h"

CellFactory::CellFactory(void)
{
  this->models.push_back(Cell(MOUNTAIN, "Moutain", 1, -2, 0, 0));
  this->typeMap['m'] = MOUNTAIN;
  this->models.push_back(Cell(RIVER, "River", 0, -1, 0, 1));
  this->typeMap['r'] = RIVER;
  this->models.push_back(Cell(PLAIN, "Plain", 0, 0, 1, 1));
  this->typeMap['p'] = PLAIN;
  srand(time(NULL) * getpid());
}

CellFactory::~CellFactory(void)
{
  this->models.clear();
  this->typeMap.clear();
}

Cell	CellFactory::produceRandomCell(void) const
{
  return (this->models[rand() % this->models.size()]);
}

Cell	CellFactory::producePreciseCell(eCellType type) const
{
  return (this->models[type]);
}

eCellType	CellFactory::getCellTypeFromChar(char c) const
{
  if (this->typeMap.find(c) == this->typeMap.end())
    throw std::runtime_error(WRONG_CT);
  else
    return (this->typeMap.find(c)->second);
}

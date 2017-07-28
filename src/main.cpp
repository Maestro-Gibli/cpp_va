//
// main.cpp for shootandrun in /home/melot_g/rendu/cpp_va/src
// 
// Made by gautier melot
// Login   <melot_g@epitech.net>
// 
// Started on  Mon Jul 21 11:02:31 2014 gautier melot
// Last update Thu Jul 24 15:53:33 2014 gautier melot
//

#include <iostream>
#include <sstream>
#include <exception>
#include <stdexcept>
#include <dlfcn.h>
#include <fstream>
#include <signal.h>
#include "CellFactory.hpp"
#include "UnitFactory.hpp"
#include "IDynLib.hpp"
#include "messages.h"

bool    keepRunning;

static void	signalHandler(int signal)
{
  if (signal == SIGINT)
    keepRunning = false;
}

static int	getInt(int ac, char **av, std::string const & str)
{
  int			ret = 30;
  std::stringstream	sstream;

  for (int i = 1; i < ac; ++i)
    {
      if (std::string(av[i]) == str)
	{
	  ++i;
	  if (i >= ac)
	    throw std::runtime_error(MISS_ARG);
	  sstream.str(std::string(av[i]));
	  if (! (sstream >> ret))
	    throw std::runtime_error(INVAL_XY);
	}
    }
  if (ret > 30)
    throw std::runtime_error(STOO_BIG);
  else if (ret < 20)
    throw std::runtime_error(STOO_SMA);
  return (ret);
}

static std::string	getStr(int ac, char **av, std::string const & str)
{
  std::string		ret = "";

  for (int i = 1; i < ac; ++i)
    {
      if (std::string(av[i]) == str)
	{
	  ++i;
	  if (i >= ac)
	    throw std::runtime_error(MISS_ARG);
	  ret = std::string(av[i]);
	}
    }
  return (ret);
}

static void	initMap(std::vector< std::vector< Cell > > & map, size_t xSize, size_t ySize)
{
  CellFactory	tileProducer;

  for (size_t i = 0; i < ySize; ++i)
    {
      std::vector<Cell>	tmp;

      for (size_t j = 0; j < xSize; ++j)
	{
	  tmp.push_back(tileProducer.produceRandomCell());
	  tmp.back().setMap(&map);
	}
      map.push_back(tmp);
    }
}

static void	getMap(std::vector< std::vector< Cell > > & map, std::string const & loadMap)
{
  CellFactory			tileProducer;
  std::ifstream			filestream(loadMap.c_str());
  std::vector<Cell>		tmp;
  size_t			size;

  for (char c = filestream.get(); filestream.good(); c = filestream.get())
    {
      if (c == '\n')
	{
	  if (tmp.size() == 0)
	    throw std::runtime_error(EMPTY_ML);
	  else if (map.size() == 0)
	    size = tmp.size();
	  else if (tmp.size() != size)
	    throw std::runtime_error(WRONG_ML);
	  map.push_back(tmp);
	  tmp.clear();
	}
      else
	{
	  tmp.push_back(tileProducer.producePreciseCell(tileProducer.getCellTypeFromChar(c)));
	  tmp.back().setMap(&map);
	}
    }
  if (map.size() == 0)
    throw std::runtime_error(EMPTY_MF);
  else if (map.size() > 30 || map[0].size() > 30)
    throw std::runtime_error(STOO_BIG);
  else if (map.size() < 10 || map[0].size() < 10)
    throw std::runtime_error(STOO_SMA);
}

static void	initUnits(std::vector< std::vector< Cell > > & map, std::vector< Unit * > & units)
{
  UnitFactory	unitProducer;

  for (int i = -1, size_x = map[0].size(), size_y = map.size(); i <= 1; ++i)
    {
      units.push_back(unitProducer.producePreciseUnit<Berserk, BERSERK, RED>(&map[2][(size_x / 2) + i], (size_x / 2) + i, 2));
      units.push_back(unitProducer.producePreciseUnit<Tank, TANK, RED>(&map[1][(size_x / 2) + i], (size_x / 2) + i, 1));
      units.push_back(unitProducer.producePreciseUnit<MissileLauncher, MISSILE_LAUNCHER, RED>(&map[0][(size_x / 2) + i], (size_x / 2) + i, 0));
      units.push_back(unitProducer.producePreciseUnit<Berserk, BERSERK, BLUE>(&map[size_y - 3][(size_x / 2) + i], (size_x / 2) + i, size_y - 3));
      units.push_back(unitProducer.producePreciseUnit<Tank, TANK, BLUE>(&map[size_y - 2][(size_x / 2) + i], (size_x / 2) + i, size_y - 2));
      units.push_back(unitProducer.producePreciseUnit<MissileLauncher, MISSILE_LAUNCHER, BLUE>(&map[size_y - 1][(size_x / 2) + i], (size_x / 2) + i, size_y - 1));
    }
  for (size_t i = 0; i < units.size(); ++i)
    map[units[i]->getY()][units[i]->getX()].setUnit(units[i]);
}

static void	init(std::vector< std::vector< Cell > > & map, IDynLib *& lib, void *& handle, std::vector< Unit * > & units, int ac, char **av)
{
  size_t	xSize = getInt(ac, av, "-x");
  size_t	ySize = getInt(ac, av, "-y");
  std::string	loadMap = getStr(ac, av, "-m");
  std::string	loadLib = getStr(ac, av, "-l");
  IDynLib *	(*ptr)(int size_x, int size_y);
  char *	err;

  keepRunning = true;
  if (signal(SIGINT, signalHandler) == SIG_ERR)
    throw std::runtime_error(SIGN_ERR);
  if (loadLib == "")
    loadLib = "./Sdl/lib_va_sdl.so";
  handle = dlopen(loadLib.c_str(), RTLD_LOCAL | RTLD_NOW);
  if (!(handle))
    throw std::runtime_error(std::string(dlerror()));
  if ((ptr = ((IDynLib * (*)(int, int))dlsym(handle, "loadLibrary"))) == NULL && (err = dlerror()) != NULL)
    throw std::runtime_error(std::string(err));
  if (loadMap == "")
    initMap(map, xSize, ySize);
  else
    getMap(map, loadMap);
  lib = (*ptr)(map[0].size(), map.size());
  initUnits(map, units);
  lib->intro();
}

static void	clearMem(std::vector< std::vector< Cell > > & map, IDynLib *& lib, void *& handle, std::vector< Unit * > & units)
{
  void		(*ptr)(IDynLib *lib);
  char *	err;

  for (size_t i = 0; i < map.size(); ++i)
    map[i].clear();
  map.clear();
  for (size_t i = 0; i < units.size(); ++i)
    delete units[i];
  units.clear();
  if ((ptr = ((void (*)(IDynLib *))dlsym(handle, "deleteLibrary"))) == NULL && (err = dlerror()) != NULL)
    throw std::runtime_error(std::string(err));
  (*ptr)(lib);
  if (dlclose(handle))
    throw std::runtime_error(dlerror());
}

static void	countArmy(IDynLib *& lib, std::vector< Unit * > & units, Cursor & cursor)
{
  int		nb[2];

  nb[RED] = 0;
  nb[BLUE] = 0;
  for (size_t i = 0; i < units.size(); ++i)
    {
      if (units[i]->getLife() > 0)
	nb[units[i]->getTeam()] += 1;
    }
  if (nb[RED] == 0 || nb[BLUE] == 0)
    {
      if (nb[RED] != 0)
	lib->end(cursor.getPlayer(RED), RED);
      else if (nb[BLUE] != 0)
	lib->end(cursor.getPlayer(BLUE), BLUE);
      else
	lib->end(END_MSG_10, NEITHER);
      keepRunning = false;
    }
}

static void	run(std::vector< std::vector< Cell > > & map, IDynLib *& lib, std::vector< Unit * > & units)
{
  Cursor	cursor(lib, map, keepRunning, units);

  lib->aff(map, cursor.getX(), cursor.getY(), cursor.getPlayer(), static_cast<eTeam>(cursor.getTurn()));
  while (keepRunning)
    {
      cursor.act();
      lib->aff(map, cursor.getX(), cursor.getY(), cursor.getPlayer(), static_cast<eTeam>(cursor.getTurn()));
      countArmy(lib, units, cursor);
    }
}

int	main(int ac, char **av)
{
  if (ac == 2 && std::string(av[1]) == "help")
    std::cout << USAGE << std::endl;
  else
    {
      try
	{
	  IDynLib *				lib;
	  std::vector< std::vector< Cell > >	map;
	  std::vector< Unit * >			units;
	  void *				handle;

	  init(map, lib, handle, units, ac, av);
	  run(map, lib, units);
	  clearMem(map, lib, handle, units);
	}
      catch (std::exception const & e)
	{
	  std::cerr << ERR << e.what() << std::endl;
	  return (1);
	}
    }
  return (0);
}

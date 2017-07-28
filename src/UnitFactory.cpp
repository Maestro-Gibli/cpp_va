//
// UnitFactory.cpp for shootandrun in /home/melot_g/rendu/cpp_va
// 
// Made by gautier melot
// Login   <melot_g@epitech.net>
// 
// Started on  Wed Jul 23 13:47:08 2014 gautier melot
// Last update Thu Jul 24 10:47:16 2014 gautier melot
//

#include "UnitFactory.hpp"

UnitFactory::UnitFactory(void)
{
  std::vector<Unit *>	tmp;

  tmp.push_back(new Berserk(RED, "Red Berserk", 0, 0));
  tmp.push_back(new Tank(RED, "Red Tank", 0, 0));
  tmp.push_back(new MissileLauncher(RED, "Red Missile-Launcher", 0, 0));
  this->models.push_back(tmp);
  tmp.clear();
  tmp.push_back(new Berserk(BLUE, "Blue Berserk", 0, 0));
  tmp.push_back(new Tank(BLUE, "Blue Tank", 0, 0));
  tmp.push_back(new MissileLauncher(BLUE, "Blue Missile-Launcher", 0, 0));
  this->models.push_back(tmp);
  tmp.clear();
}

UnitFactory::~UnitFactory(void)
{
  for (size_t i = 0; i < this->models.size(); ++i)
    {
      for (size_t j = 0; j < this->models[i].size(); ++j)
	delete models[i][j];
      models[i].clear();
    }
  models.clear();
}

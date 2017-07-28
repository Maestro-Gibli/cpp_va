//
// Sdl.cpp for shootandrun in /home/melot_g/rendu/cpp_va
// 
// Made by gautier melot
// Login   <melot_g@epitech.net>
// 
// Started on  Mon Jul 21 14:18:17 2014 gautier melot
// Last update Thu Jul 24 16:56:10 2014 gautier melot
//

#include <stdexcept>
#include <sstream>
#include "Sdl.hpp"
#include "messages.h"

eCellType		Cell::getType(void) const
{
  return (this->type);
}

bool			Cell::isEmpty(void) const
{
  return (this->unit == NULL);
}

bool			Cell::isEnlightened(void) const
{
  return (this->enlight);
}

Unit *			Cell::getUnit(void) const
{
  return (this->unit);
}

std::string const &	Cell::getName(void) const
{
  return (this->name);
}

int			Cell::getAttackMod(void) const
{
  return (this->attackMod);
}

int			Cell::getDefenseMod(void) const
{
  return (this->defenseMod);
}

int			Cell::getRangeMod(void) const
{
  return (this->rangeMod);
}

int			Cell::getSpeedMod(void) const
{
  return (this->speedMod);
}

bool			Unit::hasMoved(void) const
{
  return (this->moved);
}

bool			Unit::hasAttacked(void) const
{
  return (this->attacked);
}

eUnitType		Unit::getType(void) const
{
  return (this->type);
}

eTeam			Unit::getTeam(void) const
{
  return (this->team);
}

std::string const &	Unit::getName(void) const
{
  return (this->name);
}

int			Unit::getLife(void) const
{
  return (this->life);
}

int			Unit::getAttack(void) const
{
  return (this->att);
}

int			Unit::getRange(void) const
{
  return (this->range);
}

int			Unit::getSpeed(void) const
{
  return (this->speed);
}

Sdl::Sdl(int size_x, int size_y)
{
  std::vector<SDL_Surface *>			tmp;
  std::vector< std::vector< SDL_Surface *> >	tmp2;

  if (SDL_Init(SDL_INIT_VIDEO) == -1)
    throw std::runtime_error("Wrong initialisation of SDL.");
  if ((this->screen = SDL_SetVideoMode(SIZE * size_x + 150, SIZE * size_y, 32, SDL_HWSURFACE)) == NULL)
    throw std::runtime_error("Screen initialisation fail.");
  this->cursor.push_back(IMG_Load("Sdl/resources/RedCursor.png"));
  this->cursor.push_back(IMG_Load("Sdl/resources/BlueCursor.png"));
  tmp.push_back(IMG_Load("Sdl/resources/Mountain.png"));
  tmp.push_back(IMG_Load("Sdl/resources/River.png"));
  tmp.push_back(IMG_Load("Sdl/resources/Plain.png"));
  this->tiles.push_back(tmp);
  tmp.clear();
  tmp.push_back(IMG_Load("Sdl/resources/EnlightMountain.png"));
  tmp.push_back(IMG_Load("Sdl/resources/EnlightRiver.png"));
  tmp.push_back(IMG_Load("Sdl/resources/EnlightPlain.png"));
  this->tiles.push_back(tmp);
  tmp.clear();
  tmp.push_back(IMG_Load("Sdl/resources/RedBerserk.png"));
  tmp.push_back(IMG_Load("Sdl/resources/RedTank.png"));
  tmp.push_back(IMG_Load("Sdl/resources/RedMissileLauncher.png"));
  tmp2.push_back(tmp);
  tmp.clear();
  tmp.push_back(IMG_Load("Sdl/resources/RedBerserkShaded.png"));
  tmp.push_back(IMG_Load("Sdl/resources/RedTankShaded.png"));
  tmp.push_back(IMG_Load("Sdl/resources/RedMissileLauncherShaded.png"));
  tmp2.push_back(tmp);
  tmp.clear();
  this->units.push_back(tmp2);
  tmp2.clear();
  tmp.push_back(IMG_Load("Sdl/resources/BlueBerserk.png"));
  tmp.push_back(IMG_Load("Sdl/resources/BlueTank.png"));
  tmp.push_back(IMG_Load("Sdl/resources/BlueMissileLauncher.png"));
  tmp2.push_back(tmp);
  tmp.clear();
  tmp.push_back(IMG_Load("Sdl/resources/BlueBerserkShaded.png"));
  tmp.push_back(IMG_Load("Sdl/resources/BlueTankShaded.png"));
  tmp.push_back(IMG_Load("Sdl/resources/BlueMissileLauncherShaded.png"));
  tmp2.push_back(tmp);
  tmp.clear();
  this->units.push_back(tmp2);
  tmp2.clear();
  SDL_WM_SetCaption("Vanguard Army", NULL);
  SDL_EnableKeyRepeat(200, 10);
  this->cleanLine = IMG_Load("Sdl/resources/clean.png");
  this->surline = IMG_Load("Sdl/resources/surline.png");
  if (TTF_Init() != 0)
    throw std::runtime_error("Unable to load TTF's SDL library.");
  if ((font = TTF_OpenFont("Sdl/resources/old_game.ttf", TEXT)) == NULL)
    throw std::runtime_error("Failed to load font.");
  this->musicHandler.loadMusic("Sdl/resources/menutheme.mp3");
}

Sdl::~Sdl(void)
{
  SDL_FreeSurface(this->screen);
  for (size_t i = 0; i < this->cursor.size(); ++i)
    SDL_FreeSurface(this->cursor[i]);
  this->cursor.clear();
  for (size_t i = 0; i < this->tiles.size(); ++i)
    {
      for (size_t j = 0; j < this->tiles[i].size(); ++j)
	SDL_FreeSurface(this->tiles[i][j]);
      this->tiles[i].clear();
    }
  this->tiles.clear();
  for (size_t i = 0; i < this->units.size(); ++i)
    {
      for (size_t j = 0; j < this->units[i].size(); ++j)
	{
	  for (size_t k = 0; k < this->units[i][j].size(); ++k)
	    SDL_FreeSurface(this->units[i][j][k]);
	  this->units[i][j].clear();
	}
      this->units[i].clear();
    }
  this->units.clear();
  SDL_FreeSurface(this->cleanLine);
  SDL_FreeSurface(this->surline);
  TTF_Quit();
  SDL_Quit();
  this->musicHandler.emptyMusic();
}

eMove	Sdl::getMove(void)
{
  this->lastMove = NONE;
  if (SDL_PollEvent(&event) == 1)
    {
      if (event.type == SDL_KEYDOWN)
	{
	  if (event.key.keysym.sym == SDLK_UP)
	    this->lastMove = UP;
	  else if (event.key.keysym.sym == SDLK_RIGHT)
	    this->lastMove = RIGHT;
	  else if (event.key.keysym.sym == SDLK_DOWN)
	    this->lastMove = DOWN;
	  else if (event.key.keysym.sym == SDLK_LEFT)
	    this->lastMove = LEFT;
	  else if (event.key.keysym.sym == SDLK_ESCAPE)
	    this->lastMove = END;
	  else if (event.key.keysym.sym == SDLK_RETURN)
	    this->lastMove = SELECT;
	}
      else if (event.type == SDL_QUIT)
	this->lastMove = END;
    }
  return (this->lastMove);
}

static std::string	intToString(int i)
{
  std::stringstream	sstream("");

  sstream << i;
  return (sstream.str());
}

void	Sdl::affText(std::string const & str, int x, int y, Uint8 r, Uint8 g, Uint8 b, SDL_Surface * bg)
{
  SDL_Surface *	text;
  SDL_Rect	position;
  SDL_Color	color = {r, g, b, 0};

  position.x = SIZE * x + 5;
  position.y = TEXT * y + 5;
  text = TTF_RenderText_Solid(this->font, str.c_str(), color);
  SDL_BlitSurface(bg, NULL, this->screen, &position);
  SDL_BlitSurface(text, NULL, this->screen, &position);
  SDL_FreeSurface(text);
}

void	Sdl::affTileInfos(std::string const & name, int a, int d, int r, int s, size_t size)
{
  this->affText(name, size, 1, 255, 255, 255, this->cleanLine);
  this->affText(intToString(a), size, 3, 255, 255, 255, this->cleanLine);
  this->affText(intToString(d), size, 5, 255, 255, 255, this->cleanLine);
  this->affText(intToString(r), size, 7, 255, 255, 255, this->cleanLine);
  this->affText(intToString(s), size, 9, 255, 255, 255, this->cleanLine);
}

void	Sdl::affUnitInfos(std::string const & name, int l, int a, int r, int s, size_t size)
{
  this->affText(name, size, 12, 255, 255, 255, this->cleanLine);
  this->affText(intToString(l), size, 14, 255, 255, 255, this->cleanLine);
  this->affText(intToString(a), size, 16, 255, 255, 255, this->cleanLine);
  this->affText(intToString(r), size, 18, 255, 255, 255, this->cleanLine);
  this->affText(intToString(s), size, 20, 255, 255, 255, this->cleanLine);
}

void	Sdl::affCleanUnitInfos(size_t size)
{
  this->affText("", size, 12, 255, 255, 255, this->cleanLine);
  this->affText("", size, 14, 255, 255, 255, this->cleanLine);
  this->affText("", size, 16, 255, 255, 255, this->cleanLine);
  this->affText("", size, 18, 255, 255, 255, this->cleanLine);
  this->affText("", size, 20, 255, 255, 255, this->cleanLine);
}

void	Sdl::aff(std::vector< std::vector < Cell > > const & map, int x, int y, std::string const & player, eTeam turn)
{
  SDL_Rect		position;
  static bool		printed = false;
  static std::string	lastPlayer = "";

  for (size_t i = 0; i < map.size(); ++i)
    {
      for (size_t j = 0; j < map[i].size(); ++j)
	{
	  position.x = SIZE * j;
	  position.y = SIZE * i;
	  SDL_BlitSurface(this->tiles[(map[i][j].isEnlightened()) ? 1 : 0][map[i][j].getType()], NULL, this->screen, &position);
	  if (!map[i][j].isEmpty())
	    {
	      int	a = map[i][j].getUnit()->getTeam();
	      int	b = (!(map[i][j].getUnit()->hasAttacked() &&
			       map[i][j].getUnit()->hasMoved())) ? 0 : 1;
	      int	c = map[i][j].getUnit()->getType();

	      SDL_BlitSurface(this->units[a][b][c], NULL, this->screen, &position);
	    }
	}
    }
  position.x = SIZE * x;
  position.y = SIZE * y;
  SDL_BlitSurface(this->cursor[turn], NULL, this->screen, &position);
  this->affTileInfos(map[y][x].getName(), map[y][x].getAttackMod(), map[y][x].getDefenseMod(), map[y][x].getRangeMod(), map[y][x].getSpeedMod(), map[0].size());
  if (!map[y][x].isEmpty())
    {
      this->affUnitInfos(map[y][x].getUnit()->getName(), map[y][x].getUnit()->getLife(), map[y][x].getUnit()->getAttack(), map[y][x].getUnit()->getRange(), map[y][x].getUnit()->getSpeed(), map[0].size());
      printed = true;
    }
  else if (printed)
    {
      this->affCleanUnitInfos(map[0].size());
      printed = false;
    }
  if (lastPlayer != player)
    {
      lastPlayer = player;
      this->affText("Turn: " + player, map[0].size(), 22, 255, 255, 255, this->cleanLine);
    }
  SDL_Flip(this->screen);
}

void	Sdl::playSound(eSound sound)
{
  (void)sound;
}

void	Sdl::menu(std::vector<std::string> const & menu, int p)
{
  for (size_t i = 0; i < menu.size(); ++i)
    {
      if (static_cast<int>(i) != p)
	this->affText(menu[i], (this->screen->w - 150) / SIZE, 23 + i, 255, 255, 255, this->cleanLine);
      else
	this->affText(menu[i], (this->screen->w - 150) / SIZE, 23 + i, 0, 0, 0, this->surline);
    }
}

void	Sdl::cleanMenu(int size_x, size_t ntime)
{
  for (size_t i = 0; i < ntime; ++i)
    this->affText("", size_x, 23 + i, 255, 255, 255, this->cleanLine);
}

void	Sdl::end(std::string const & player, eTeam turn)
{
  int	x = (this->screen->w - 150) / SIZE;
  int	y = this->screen->h / SIZE;
  eMove	move;

  this->musicHandler.pauseMusic();
  SDL_FillRect(this->screen, NULL, SDL_MapRGB(this->screen->format, 0, 0, 0));
  if (turn != NEITHER)
    {
      this->affText(player + END_MSG_00, (x / 2) - 1, (y / 2), (turn == RED) ? 255 : 0, 0, (turn == BLUE) ? 255 : 0, this->cleanLine);
      this->affText(END_MSG_01, (x / 2) - 2, (y / 2) + 1, 255, 255, 255, this->cleanLine);
      this->affText(END_MSG_02, (x / 2) - 2, (y / 2) + 2, 255, 255, 255, this->cleanLine);
    }
  else
    {
      this->affText(END_MSG_10, (x / 2), (y / 2), 0, 255, 0, this->cleanLine);
      this->affText(END_MSG_11, (x / 2) - 3, (y / 2) + 1, 255, 255, 255, this->cleanLine);
      this->affText(END_MSG_12, (x / 2) - 3, (y / 2) + 2, 255, 255, 255, this->cleanLine);
    }
  SDL_Flip(this->screen);
  while ((move = this->getMove()) != END && move != SELECT);
}

void	Sdl::intro(void)
{
  int	x = (this->screen->w - 150) / SIZE;
  int	y = this->screen->h / SIZE;
  eMove	move;

  SDL_FillRect(this->screen, NULL, SDL_MapRGB(this->screen->format, 0, 0, 0));
  this->affText(INI_MSG_00, (x / 2) - 2, (y / 2) - 4, 255, 255, 255, this->cleanLine);
  this->affText(INI_MSG_01, (x / 2) - 2, (y / 2) - 3, 255, 255, 255, this->cleanLine);
  this->affText(INI_MSG_02, (x / 2) - 2, (y / 2) - 2, 255, 255, 255, this->cleanLine);
  this->affText(INI_MSG_03, (x / 2) - 2, (y / 2) - 1, 255, 255, 255, this->cleanLine);
  this->affText(INI_MSG_04, (x / 2) - 2, (y / 2), 255, 255, 255, this->cleanLine);

  this->affText(INI_MSG_10, (x / 2) - 2, (y / 2) + 2, 255, 255, 255, this->cleanLine);
  this->affText(INI_MSG_11, (x / 2) - 2, (y / 2) + 3, 255, 255, 255, this->cleanLine);
  this->affText(INI_MSG_12, (x / 2) - 2, (y / 2) + 4, 255, 255, 255, this->cleanLine);

  this->affText(INI_MSG_20, (x / 2) - 2, (y / 2) + 6, 255, 255, 255, this->cleanLine);
  this->affText(INI_MSG_21, (x / 2) - 2, (y / 2) + 7, 255, 255, 255, this->cleanLine);
  this->affText(INI_MSG_22, (x / 2) - 2, (y / 2) + 8, 255, 255, 255, this->cleanLine);

  SDL_Flip(this->screen);

  while ((move = this->getMove()) != END && move != SELECT);

  this->affText("Tile:", x, 0, 255, 255, 255, this->cleanLine);
  this->affText("Attack Mod:", x, 2, 255, 255, 255, this->cleanLine);
  this->affText("Defense Mod:", x, 4, 255, 255, 255, this->cleanLine);
  this->affText("Range Mod:", x, 6, 255, 255, 255, this->cleanLine);
  this->affText("Speed Mod:", x, 8, 255, 255, 255, this->cleanLine);
  this->affText("Unit:", x, 11, 255, 255, 255, this->cleanLine);
  this->affText("Life:", x, 13, 255, 255, 255, this->cleanLine);
  this->affText("Attack:", x, 15, 255, 255, 255, this->cleanLine);
  this->affText("Range:", x, 17, 255, 255, 255, this->cleanLine);
  this->affText("Speed:", x, 19, 255, 255, 255, this->cleanLine);

  this->musicHandler.playMusic();
}

extern "C" IDynLib *	loadLibrary(int size_x, int size_y)
{
  return (new Sdl(size_x, size_y));
}

extern "C" void		deleteLibrary(IDynLib * sdl)
{
  delete sdl;
}

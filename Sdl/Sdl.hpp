//
// Sdl.hpp for shootandrun in /home/melot_g/rendu/cpp_va
// 
// Made by gautier melot
// Login   <melot_g@epitech.net>
// 
// Started on  Mon Jul 21 14:14:32 2014 gautier melot
// Last update Thu Jul 24 16:56:12 2014 gautier melot
//

#ifndef		SLD_HPP_
# define	SDL_HPP_

#include <vector>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL_ttf.h>
#include "IDynLib.hpp"
#include "Music.hpp"

#define SIZE	33
#define TEXT	24

class	Sdl : public IDynLib
{
private:
  eMove								lastMove;
  SDL_Event							event;
  SDL_Surface *							screen;
  std::vector<SDL_Surface *>					cursor;
  std::vector< std::vector< SDL_Surface * > >			tiles;
  std::vector< std::vector< std::vector< SDL_Surface * > > >	units;
  TTF_Font *							font;
  SDL_Surface *							cleanLine;
  SDL_Surface *							surline;
  Music								musicHandler;

  void	affText(std::string const & text, int x, int y, Uint8 r, Uint8 g, Uint8 b, SDL_Surface * bg);
  void	affTileInfos(std::string const & name, int a, int d, int r, int s, size_t size);
  void	affUnitInfos(std::string const & name, int l, int a, int r, int s, size_t size);
  void	affCleanUnitInfos(size_t size);

public:
  Sdl(int size_x, int size_y);
  ~Sdl(void);

  virtual void	intro(void);
  virtual eMove	getMove(void);
  virtual void  aff(std::vector< std::vector< Cell > > const & map, int x, int y, std::string const & player, eTeam turn);
  virtual void  playSound(eSound sound);
  virtual void	menu(std::vector<std::string> const & menu, int p);
  virtual void	cleanMenu(int size_x, size_t ntime);
  virtual void	end(std::string const & player, eTeam turn);
};

#endif		// !SDL_HPP_

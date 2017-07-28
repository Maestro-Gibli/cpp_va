//
// Music.hpp for shootandrun in /home/melot_g/rendu/cpp_va/Sdl
// 
// Made by gautier melot
// Login   <melot_g@epitech.net>
// 
// Started on  Thu Jul 24 14:51:36 2014 gautier melot
// Last update Thu Jul 24 15:28:06 2014 gautier melot
//

#ifndef		MUSIC_HPP_
# define	MUSIC_HPP_

# include <string>
# include <iostream>
# include "fmod.h"

class	Music
{
private:
  bool			verif;
  FMOD_RESULT		result;
  FMOD_SYSTEM *		system;
  FMOD_CHANNEL *	channel;
  FMOD_SOUND *		sound;

public:
  Music(void);
  ~Music(void);

  void	loadMusic(std::string const & path);
  void	loadSample(std::string const & path);
  void	emptyMusic(void);
  void	pauseMusic(void);
  void	playMusic(void);
};

#endif		// !MUSIC_HPP_

//
// Music.cpp for shootandrun in /home/melot_g/rendu/cpp_va/Sdl
// 
// Made by gautier melot
// Login   <melot_g@epitech.net>
// 
// Started on  Thu Jul 24 14:59:56 2014 gautier melot
// Last update Thu Jul 24 15:30:37 2014 gautier melot
//

#include "Music.hpp"

Music::Music(void)
{
  this->verif = true;
  if (FMOD_System_Create(&(this->system)) == FMOD_OK && 
      FMOD_System_Init(this->system, 2, FMOD_INIT_NORMAL, 0) == FMOD_OK)
    FMOD_Channel_SetVolume(this->channel,0.0f);
  else
    this->verif = false;
}

Music::~Music(void)
{
  FMOD_System_Close(this->system);
  FMOD_System_Release(this->system);
}

void	Music::loadMusic(std::string const & path)
{
  if (this->verif)
    {
      FMOD_Sound_Release(this->sound);
      if ((result = FMOD_System_CreateSound(this->system, path.c_str(), FMOD_LOOP_NORMAL | FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &(this->sound))) != FMOD_OK)
	this->verif = false;
      FMOD_Sound_SetLoopCount(this->sound, -1);
    } 
}

void	Music::loadSample(std::string const & path)
{
  if (this->verif)
    {
      FMOD_Sound_Release(this->sound);
      if ((result = FMOD_System_CreateSound(this->system, path.c_str(), FMOD_CREATESAMPLE, 0, &(this->sound))) != FMOD_OK)
	this->verif = false;
    } 
}

void	Music::emptyMusic(void)
{
  if (this->verif)
    FMOD_Sound_Release(this->sound);
}

void	Music::pauseMusic(void)
{
  if (this->verif)
    FMOD_System_PlaySound(this->system, FMOD_CHANNEL_FREE, this->sound, 1, &channel);
}

void	Music::playMusic(void)
{
  if (this->verif)
    FMOD_System_PlaySound(this->system, FMOD_CHANNEL_FREE, this->sound, 0, &channel);
}

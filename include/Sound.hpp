//
// Sound.hpp for sounderman in /home/manass_j/rendu/cpp_indie_studio/include
// 
// Made by jonathan manassen
// Login   <jonathan.manassen@epitech.eu@epitech.net>
// 
// Started on  Tue May 16 13:23:04 2017 jonathan manassen
// Last update Sun Jun 18 22:05:22 2017 Gabin Meyrieux-Drevet
//

#ifndef SOUND_HPP_
# define SOUND_HPP_

#include <fmod.hpp>
#include <string>
#include <map>
#include <vector>

class	Sound
{
  std::map<std::string, FMOD::Sound *>    sounds;
  std::map<unsigned int, FMOD::Channel *> channels;
  std::vector<FMOD::Channel *>            channelsCOM;
  FMOD::System         *engine;
  const std::string    soundPath;
  float	volMusic;
  float	volEffect;
public:
  static Sound             *manager;
  static Sound             *getSound();
  Sound();
  ~Sound();
  void	play(std::string const &sound, unsigned  int id = 0, bool loop = false, bool intro = false);
  void  stop(const int &id);
  void  stopAll();
  void  stopAllBack();
  void	setVolumeMusic(int i);
  void	setVolumeEffects(int i);
};

#endif /* SOUND_HPP_ */

//
// sound.cpp for indieStudio in /home/meyrie_g/rendu/cpp_indie_studio
// 
// Made by Gabin Meyrieux-Drevet
// Login   <meyrie_g@epitech.net>
// 
// Started on  Tue May 16 15:02:29 2017 Gabin Meyrieux-Drevet
// Last update Sun Jun 18 22:05:29 2017 Gabin Meyrieux-Drevet
//

#include <fstream>
#include <fmod_errors.h>
#include "Sound.hpp"

Sound            *Sound::manager = NULL;

Sound            *Sound::getSound()
{
    if (!manager)
        manager = new Sound();
    return (manager);
}

Sound::Sound() : soundPath("media/sound/")
{
  FMOD::System_Create(&engine);
  engine->init(512, FMOD_INIT_NORMAL, 0);
  volMusic = 1;
  volEffect = 1;
}

Sound::~Sound()
{
  for (const auto& pair : sounds)
    pair.second->release();
  engine->close();
  engine->release();
}

void	Sound::setVolumeMusic(int i)
{
  if (i > 100)
    i = i % 100;
  volMusic = static_cast<float>(i) / 100;
  for (FMOD::Channel *channel : channelsCOM)
    channel->setVolume(volMusic);
}

void	Sound::setVolumeEffects(int i)
{
  if (i > 100)
    i = i % 100;
  volEffect = static_cast<float>(i) / 100;
  for (const auto& pair : channels)
    pair.second->setVolume(volEffect);
}

void    Sound::play(std::string const &sound, unsigned int id, bool loop, bool intro)
{
  FMOD::Channel   *tmpChannel;
  float	vol;

  if (id == 0)
    vol = volMusic;
  else
    vol = volEffect;
  if (sounds[sound] == 0)
    engine->createSound((soundPath + sound).c_str(), (loop) ? FMOD_LOOP_NORMAL : FMOD_DEFAULT, 0, &sounds[sound]);
  engine->playSound(sounds[sound], 0, false, &tmpChannel);
  if (intro == true)
    tmpChannel->setVolume(10);
  else
    tmpChannel->setVolume(vol);
  if (channels[id] && id)
    channels[id]->stop();
  if (id == 0)
    channelsCOM.push_back(tmpChannel);
  else
    channels[id] = tmpChannel;
}

void    Sound::stop(const int &id)
{
  if (id == -1)
    stopAll();
  if (channels[id])
    {
      channels[id]->stop();
      channels.erase(id);
    }
}

void    Sound::stopAll()
{
  for (const auto& pair : channels)
    pair.second->stop();
  this->channels.clear();
  this->stopAllBack();
}

void    Sound::stopAllBack()
{
  for (FMOD::Channel *c : channelsCOM)
    c->stop();
  this->channelsCOM.clear();
}

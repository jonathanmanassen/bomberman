//
// Settings.hpp for indieStudio in /home/meyrie_g/rendu/cpp_indie_studio
// 
// Made by Gabin Meyrieux-Drevet
// Login   <meyrie_g@epitech.net>
// 
// Started on  Tue May 16 16:08:43 2017 Gabin Meyrieux-Drevet
// Last update Tue Jun  6 16:41:18 2017 Christophe Mei
//

#ifndef SETTINGS_HPP_
# define SETTINGS_HPP_

#include <vector>
#include <string>
#include <stdbool.h>

typedef struct	Position
{
  int	x;
  int	y;
}		Position;

class	Settings
{
  Position	winSize;
  int		resolution;
  bool		fullscreen;
  int		volMusic;
  int		volEffects;
public:
  Settings(std::string const&);
  ~Settings();
  void	parseSettings(std::string const&);
  Position	getWinSize() const {return winSize;};
  void	setWinSize(int x, int y) {winSize.x = x;winSize.y = y;};
  int	getResolution() {return (resolution);}
  void	setResolution(int res) {resolution = res;}
  void	setResolutionNext()
  {
    resolution += 1;
    if (resolution > 3)
      resolution = 0;
  }
  int	getFullscreen() {return (fullscreen);}
  void	setFullscreen(bool f) {fullscreen = f;}
  void	setFullscreenNext() {(fullscreen == true) ? fullscreen = false : fullscreen = true;}
  int	getVolMusic() {return volMusic;}
  void	setVolMusic(int vol)
  {
    volMusic += vol;
    if (volMusic > 100)
      volMusic = 100;
    else if (volMusic < 0)
      volMusic = 0;
  }
  int	getVolEffects() {return volEffects;}
  void	setVolEffects(int vol)
  {
    volEffects += vol;
    if (volEffects > 100)
      volEffects = 100;
    else if (volEffects < 0)
      volEffects = 0;
  }
};

#endif /*!SETTINGS_HPP_*/

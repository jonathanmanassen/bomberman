//
// Core.hpp for indieStudio in /home/meyrie_g/rendu/cpp_indie_studio
// 
// Made by Gabin Meyrieux-Drevet
// Login   <meyrie_g@epitech.net>
// 
// Started on  Tue May 16 15:02:14 2017 Gabin Meyrieux-Drevet
// Last update Sat Jun 17 21:32:15 2017 jonathan manassen
//

#ifndef CORE_HPP_
# define CORE_HPP_

#include <memory>
#include <irrlicht.h>
#include "Menu.hpp"
#include "Settings.hpp"
#include "Command.hpp"
//#include "Score.hpp"
#include "Game.hpp"

class	Core
{
  int	winx = 1920;
  int	winy = 1080;
  //Score	*score;
  irr::IrrlichtDevice		*window;
  Settings	*settings;
  Command	*command;
  Menu		*menu;
  Game		*game;
public:
  Core();
  ~Core();
};

#endif /*!CORE_HPP_*/

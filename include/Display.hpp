//
// Display.hpp for Display in /home/mei_c/rendu/cpp/cpp_indie_studio
// 
// Made by Christophe Mei
// Login   <mei_c@epitech.net>
// 
// Started on  Thu May 18 18:38:27 2017 Christophe Mei
// Last update Sun Jun 18 19:09:53 2017 Gabin Meyrieux-Drevet
//

#ifndef DISPLAY_HPP_
# define DISPLAY_HPP_

#include <irrlicht.h>
#include "Settings.hpp"

class	Display : public irr::scene::IAnimationEndCallBack
{
  irr::IrrlichtDevice		*window;
  irr::video::IVideoDriver	*driver;
  irr::scene::ISceneManager	*smgr;
  irr::gui::IGUIEnvironment	*guienv;
  irr::video::ITexture		*button;
  irr::video::ITexture		*button2;
  irr::video::ITexture		*button3;
  irr::video::ITexture		*buttonsquare;
  irr::video::ITexture		*buttonsquare2;
  irr::video::ITexture		*buttonsquare3;
  Settings			*settings;
public:
  Display(irr::IrrlichtDevice*, irr::video::IVideoDriver*,
	  irr::scene::ISceneManager*, irr::gui::IGUIEnvironment*,
	  Settings*);
  ~Display();
  irr::IrrlichtDevice		*getWindow() {return (window);}
  irr::video::IVideoDriver	*getDriver() {return (driver);}
  irr::scene::ISceneManager	*getSmgr() {return (smgr);}
  irr::gui::IGUIEnvironment	*getGuienv() {return (guienv);}
  Settings	*getSettings(){return settings;}
  virtual void	displayAll() = 0;
  virtual void OnAnimationEnd(irr::scene::IAnimatedMeshSceneNode* node){}
  void	text(irr::core::stringw const &, const int&, const int&);
  void	addButton(const irr::core::stringw&, const int&, int, const int&);
  void	addButtonSquare(const irr::core::stringw&, const int&, int, const int&);
};

#endif /* !DISPLAY_HPP_ */

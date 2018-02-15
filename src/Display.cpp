//
// Display.cpp for Display in /home/mei_c/rendu/cpp/cpp_indie_studio
// 
// Made by Christophe Mei
// Login   <mei_c@epitech.net>
// 
// Started on  Thu May 18 17:58:21 2017 Christophe Mei
// Last update Sun Jun 18 21:11:03 2017 Gabin Meyrieux-Drevet
//

#include "Display.hpp"

Display::Display(irr::IrrlichtDevice* _window,
		 irr::video::IVideoDriver* _driver,
		 irr::scene::ISceneManager* _smgr,
		 irr::gui::IGUIEnvironment* _guienv,
		 Settings* _settings)
  : window(_window), driver(_driver), smgr(_smgr), guienv(_guienv)
{
  button = driver->getTexture("media/button.jpg");
  button2 = driver->getTexture("media/button2.jpg");
  button3 = driver->getTexture("media/button3.jpg");
  buttonsquare = driver->getTexture("media/buttonsquare.jpg");
  buttonsquare2 = driver->getTexture("media/buttonsquare2.jpg");
  buttonsquare3 = driver->getTexture("media/buttonsquare3.jpg");
  settings = _settings;
  settings->setResolution(3);
  settings->setFullscreen(true);
  settings->setVolMusic(0);
  settings->setVolEffects(0);
}

Display::~Display()
{
  window->drop();
}

void	Display::text(irr::core::stringw const &txt, const int &x, const int &y)
{
  irr::gui::IGUISkin* skin = guienv->getSkin();
  irr::gui::IGUIFont* font = guienv->getFont("media/lolfont.xml");
  if (font)
    skin->setFont(font);
  skin->setColor(irr::gui::EGDC_BUTTON_TEXT, irr::video::SColor(255,217,200,56));
  skin->setFont(guienv->getBuiltInFont(), irr::gui::EGDF_TOOLTIP);
  guienv->addStaticText(txt.c_str(), irr::core::rect<irr::s32>(x - 88,y,88 + x, 88 + y), false)->setTextAlignment(irr::gui::EGUIA_CENTER, irr::gui::EGUIA_CENTER);
}

void	Display::addButton(const irr::core::stringw &txt, const int &x, int y, const int &select = 0)
{
  irr::gui::IGUISkin* skin = guienv->getSkin();
  irr::gui::IGUIFont* font = guienv->getFont("media/lolfont36.xml");
  if (font)
    skin->setFont(font);
  irr::core::stringw	text = L"";
  text += txt.c_str();
  skin->setFont(guienv->getBuiltInFont(), irr::gui::EGDF_TOOLTIP);
  switch (select)
    {
    case 1 :
      guienv->addImage(button2, irr::core::position2d<irr::s32>(x, y));
      y -= 3;
      break;
    case 2 :
      guienv->addImage(button3, irr::core::position2d<irr::s32>(x, y));
      break;
    default :
      guienv->addImage(button, irr::core::position2d<irr::s32>(x, y));
      y -= 3;
    }
  skin->setColor(irr::gui::EGDC_BUTTON_TEXT, irr::video::SColor(255,217,200,56));
  guienv->addStaticText(text.c_str(), irr::core::rect<irr::s32>(x, y, 498 + x, 88 + y), false)->setTextAlignment(irr::gui::EGUIA_CENTER, irr::gui::EGUIA_CENTER);
}

void	Display::addButtonSquare(const irr::core::stringw &txt, const int &x, int y, const int &select = 0)
{
  irr::gui::IGUISkin* skin = guienv->getSkin();
  irr::gui::IGUIFont* font = guienv->getFont("media/lolfont36.xml");
  if (font)
    skin->setFont(font);
  irr::core::stringw	text = L"";
  text += txt.c_str();
  skin->setFont(guienv->getBuiltInFont(), irr::gui::EGDF_TOOLTIP);
  switch (select)
    {
    case 1 :
      guienv->addImage(buttonsquare2, irr::core::position2d<irr::s32>(x, y));
      y -= 3;
      break;
    case 2 :
      guienv->addImage(buttonsquare3, irr::core::position2d<irr::s32>(x, y));
      break;
    default :
      guienv->addImage(buttonsquare, irr::core::position2d<irr::s32>(x, y));
      y -= 3;
    }
  skin->setColor(irr::gui::EGDC_BUTTON_TEXT, irr::video::SColor(255,217,200,56));
  guienv->addStaticText(text.c_str(), irr::core::rect<irr::s32>(x, y, 88 + x, 88 + y), false)->setTextAlignment(irr::gui::EGUIA_CENTER, irr::gui::EGUIA_CENTER);
}

//
// Core.cpp for indieStudio in /home/meyrie_g/rendu/cpp_indie_studio
// 
// Made by Gabin Meyrieux-Drevet
// Login   <meyrie_g@epitech.net>
// 
// Started on  Tue May 16 15:02:29 2017 Gabin Meyrieux-Drevet
// Last update Sun Jun 18 22:05:52 2017 Gabin Meyrieux-Drevet
//

#include "Core.hpp"

Core::Core()
{
  settings = new Settings("");
  command = new Command;

  window = irr::createDevice(irr::video::EDT_OPENGL, irr::core::dimension2d<irr::u32>(winx, winy), 16, true, false, true, command);
  if (!window)
    exit(0);
  window->setWindowCaption(L"Bomberman");  
  window->getCursorControl()->setVisible(false);
  Sound::getSound()->play("introBomber.wav", 0, false, true);
  while (window->run())
    {
      for (int i = 1; i < 90; i++)
	{
	  std::string	image = "media/bombermansplashscreen/bombermansplashscreen";

	  if (i < 10)
	    image += "0000";
	  else if (i < 100)
	    image += "000";
	  else
	    image += "00";
	  image += std::to_string(i);
	  image += ".png";
	  window->getGUIEnvironment()->clear();
	  window->getGUIEnvironment()->addImage(window->getVideoDriver()->getTexture(image.c_str()), irr::core::position2d<irr::s32>(0,0));
	  window->getSceneManager()->drawAll();
	  window->getGUIEnvironment()->drawAll();
	  window->getVideoDriver()->endScene();
	}
      break;
    }
  
  game = new Game(window, settings);
  menu = new Menu(window, settings);
  gameInstruction gameStat;
  gameStat.execCode = 0;
  gameStat.endParty = 0;
  while (gameStat.execCode <= 2)
    {
      switch (gameStat.execCode)
	{
	case 0 :
	  gameStat = menu->mainMenu(command, 0);
	  if (gameStat.execCode != 3)
	    game->initGameInstruction(gameStat, command);
	  else
	    game->endParty();
	  break;
	case 1 :
	  gameStat.execCode = game->play(command);
	  break;
	case 2 :
	  gameStat = menu->mainMenu(command, 1);
	  game->displaySpectate(gameStat.spectate);
	  while (gameStat.loadSave == 1)
	    {
	      game->saveGame(gameStat.saveNbr);
	      gameStat = menu->mainMenu(command, 1);
	    }
	  if (gameStat.endParty == 1)
	    game->endParty();
	  break;
	}      
    }
}

Core::~Core()
{
  if (!window)
    window->drop();
  delete settings;
  delete command;
  delete menu;
  delete game;
}

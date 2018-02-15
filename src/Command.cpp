//
// Command.cpp for bomberman in /home/manass_j/rendu/cpp_indie_studio
// 
// Made by jonathan manassen
// Login   <jonathan.manassen@epitech.eu@epitech.net>
// 
// Started on  Mon May 15 14:06:51 2017 jonathan manassen
// Last update Sat Jun 17 21:50:55 2017 jonathan manassen
//

#include <cstdlib>
#include <stdio.h>
#include <ctime>
#include "Command.hpp"

bool Command::OnEvent(const irr::SEvent& event)
{
  if (event.EventType == irr::EET_KEY_INPUT_EVENT)
    KeyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
  if (event.EventType == irr::EET_MOUSE_INPUT_EVENT)
    {
      switch(event.MouseInput.Event)
	{
	case irr::EMIE_LMOUSE_PRESSED_DOWN:
	  MouseState.LeftButtonDown = true;
	  break;

	case irr::EMIE_LMOUSE_LEFT_UP:
	  MouseState.LeftButtonDown = false;
	  break;

	case irr::EMIE_MOUSE_MOVED:
	  MouseState.time = std::chrono::system_clock::now();
	  MouseState.Position.X = event.MouseInput.X;
	  MouseState.Position.Y = event.MouseInput.Y;
	  break;
	default:
	  break;
	}
    }
  return false;
}

irr::EKEY_CODE	Command::getKey()
{
  static irr::EKEY_CODE	last;
  static bool	lStat;
  int	i;
  if (last != 0 && IsKeyDown(last) == true && lStat == true)
    return irr::KEY_KEY_CODES_COUNT;
  for (i = 0x01; i < irr::KEY_KEY_CODES_COUNT; i++)
    {
      if (KeyIsDown[i] == true)
	{
	  last = static_cast<irr::EKEY_CODE>(i);
	  lStat = KeyIsDown[i];
	  return static_cast<irr::EKEY_CODE>(i);
	}
    }
  lStat = false;
  return static_cast<irr::EKEY_CODE>(i);
}

CAction	Command::getCommand(int pNb, int i, bool j)
{
  if (j == true)
    i = 2;
  switch (i)
    {
    case 0 :
      return ((KeyIsDown[pCom[pNb]->getBomb()]) ? CAction::BOMB : (getCommand(pNb, i+1)));
    case 1 :
      return ((KeyIsDown[pCom[pNb]->getBack()]) ? CAction::BACK : (getCommand(pNb, i+1)));
    case 2 :
      return ((KeyIsDown[pCom[pNb]->getUp()] &&
	       KeyIsDown[pCom[pNb]->getRight()]) ? CAction::DIAG_UR : (getCommand(pNb, i+1)));
    case 3 :
      return ((KeyIsDown[pCom[pNb]->getUp()] &&
	       KeyIsDown[pCom[pNb]->getLeft()]) ? CAction::DIAG_UL : (getCommand(pNb, i+1)));
    case 4 :
      return ((KeyIsDown[pCom[pNb]->getDown()] &&
	       KeyIsDown[pCom[pNb]->getLeft()]) ? CAction::DIAG_DL : (getCommand(pNb, i+1)));
    case 5 :
      return ((KeyIsDown[pCom[pNb]->getDown()] &&
	       KeyIsDown[pCom[pNb]->getRight()]) ? CAction::DIAG_DR : (getCommand(pNb, i+1)));
    case 6 :
      return ((KeyIsDown[pCom[pNb]->getUp()]) ? CAction::UP : (getCommand(pNb, i+1)));
    case 7 :
      return ((KeyIsDown[pCom[pNb]->getDown()]) ? CAction::DOWN : (getCommand(pNb, i+1)));
    case 8 :
      return ((KeyIsDown[pCom[pNb]->getRight()]) ? CAction::RIGHT : (getCommand(pNb, i+1)));
    case 9 :
      return ((KeyIsDown[pCom[pNb]->getLeft()]) ? CAction::LEFT : (getCommand(pNb, i+1)));
    default :
      return (CAction::NONE);
    };
}

Command::Command()
{
  for (int i=0; i<irr::KEY_KEY_CODES_COUNT; ++i)
    KeyIsDown[i] = false;
  pCom = new PCommand*[4];
  pCom[0] = new PCommand(0);
  pCom[1] = new PCommand(1);
  pCom[2] = new PCommand(2);
  pCom[3] = new PCommand(3);
}

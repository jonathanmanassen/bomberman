//
// Command.hpp for bomberman in /home/manass_j/rendu/cpp_indie_studio/include
// 
// Made by jonathan manassen
// Login   <jonathan.manassen@epitech.eu@epitech.net>
// 
// Started on  Wed May 24 14:42:44 2017 jonathan manassen
// Last update Sun Jun 18 21:44:58 2017 Christophe Mei
//

#ifndef COMMAND_HPP_
# define COMMAND_HPP_

#include <iostream>
#include <chrono>
#include <irrlicht.h>
#include <map>
#include "enum.hpp"
#include "struct.hpp"

class	PCommand
{
protected:
  irr::EKEY_CODE	up;
  irr::EKEY_CODE	down;
  irr::EKEY_CODE	right;
  irr::EKEY_CODE	left;
  irr::EKEY_CODE	bomb;
  irr::EKEY_CODE	back;
  std::map<CAction, irr::EKEY_CODE>	defaultCom[4] =
    {
      {
	{CAction::UP, irr::EKEY_CODE::KEY_KEY_Z},
	{CAction::DOWN, irr::EKEY_CODE::KEY_KEY_S},
	{CAction::RIGHT, irr::EKEY_CODE::KEY_KEY_D},
	{CAction::LEFT, irr::EKEY_CODE::KEY_KEY_Q},
	{CAction::BOMB, irr::EKEY_CODE::KEY_KEY_E},
	{CAction::BACK, irr::EKEY_CODE::KEY_KEY_A},
      },
      {
	{CAction::UP, irr::EKEY_CODE::KEY_UP},
	{CAction::DOWN, irr::EKEY_CODE::KEY_DOWN},
	{CAction::RIGHT, irr::EKEY_CODE::KEY_RIGHT},
	{CAction::LEFT, irr::EKEY_CODE::KEY_LEFT},
	{CAction::BOMB, irr::EKEY_CODE::KEY_END},
	{CAction::BACK, irr::EKEY_CODE::KEY_RSHIFT},
      },
      {
	{CAction::UP, irr::EKEY_CODE::KEY_KEY_O},
	{CAction::DOWN, irr::EKEY_CODE::KEY_KEY_L},
	{CAction::RIGHT, irr::EKEY_CODE::KEY_KEY_M},
	{CAction::LEFT, irr::EKEY_CODE::KEY_KEY_K},
	{CAction::BOMB, irr::EKEY_CODE::KEY_KEY_P},
	{CAction::BACK, irr::EKEY_CODE::KEY_KEY_I},
      },
      {
	{CAction::UP, irr::EKEY_CODE::KEY_KEY_G},
	{CAction::DOWN, irr::EKEY_CODE::KEY_KEY_B},
	{CAction::RIGHT, irr::EKEY_CODE::KEY_KEY_N},
	{CAction::LEFT, irr::EKEY_CODE::KEY_KEY_V},
	{CAction::BOMB, irr::EKEY_CODE::KEY_KEY_H},
	{CAction::BACK, irr::EKEY_CODE::KEY_KEY_F},
      },
    };
public:
  PCommand(int pNb)
  {
    up = defaultCom[pNb].at(CAction::UP);
    down = defaultCom[pNb].at(CAction::DOWN);
    right = defaultCom[pNb].at(CAction::RIGHT);
    left = defaultCom[pNb].at(CAction::LEFT);
    bomb = defaultCom[pNb].at(CAction::BOMB);
    back = defaultCom[pNb].at(CAction::BACK);
  }
  const irr::EKEY_CODE	&getUp() const {return up;}
  const irr::EKEY_CODE	&getDown() const {return down;}
  const irr::EKEY_CODE	&getRight() const {return right;}
  const irr::EKEY_CODE	&getLeft() const {return left;}
  const irr::EKEY_CODE	&getBomb() const {return bomb;}
  const irr::EKEY_CODE	&getBack() const {return back;}
  void	setUp(irr::EKEY_CODE const &_up) {up = _up;}
  void	setDown(irr::EKEY_CODE const &_down) {down = _down;}
  void	setRight(irr::EKEY_CODE const &_right) {right = _right;}
  void	setLeft(irr::EKEY_CODE const &_left) {left = _left;}
  void	setBomb(irr::EKEY_CODE const &_bomb) {bomb = _bomb;}
  void	setBack(irr::EKEY_CODE const &_back) {back = _back;}
};

class	Command : public irr::IEventReceiver
{
  SMouseState   MouseState;
  PCommand	**pCom;
  bool KeyIsDown[irr::KEY_KEY_CODES_COUNT];
public:
  Command();
  irr::EKEY_CODE	getKey();
  CAction	getCommand(int pNb, int i = 0, bool j = false);
  virtual bool	OnEvent(const irr::SEvent&);
  virtual bool	IsKeyDown(irr::EKEY_CODE keyCode) const { return KeyIsDown[keyCode]; }

  void	setMouseState(const int &state) {MouseState.state = state;}
  void	setMouseTime(const std::chrono::time_point<std::chrono::system_clock> &time) {MouseState.time = time;}
  irr::core::vector2d<int>	getMousePosition() {return MouseState.Position;}
  PCommand	**getPCom() const { return pCom; }
  const SMouseState	&getMouseState() const {return MouseState;}
  const std::chrono::time_point<std::chrono::system_clock>	&getMouseTime() const {return MouseState.time;}};

#endif /*!COMMAND_HPP_*/

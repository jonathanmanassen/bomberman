//
// player.hpp for bomberman in /home/manass_j/rendu/cpp_indie_studio/include
// 
// Made by jonathan manassen
// Login   <jonathan.manassen@epitech.eu@epitech.net>
// 
// Started on  Tue May 16 13:23:04 2017 jonathan manassen
// Last update Sat Jun 17 22:11:52 2017 jonathan manassen
//

#ifndef PLAYER_HPP_
# define PLAYER_HPP_

#include <irrlicht.h>
#include "Thread.hpp"
#include "Map.hpp"
#include "Command.hpp"
#include "enum.hpp"
#include "Game.hpp"
#include "struct.hpp"
#include "Bonus.hpp"

class	Map;
class	Game;

class	Player : public Thread
{
protected:
  irr::core::vector3df	pos;
  irr::core::vector3df	rotation;
  irr::core::vector3df	scale;
  const irr::f32	mov_speed = 5.f;
  Action		action;
  Action		lastAction;
  int			pNb;
  Bonus			*bonus;
  irr::u32		then;
  bool			attackIsEnd;
  CAction		cA;
  bool			isAlive;
  int			deathAnimStat;
  bool			inPause;
  int			bomb[2];
public:
  Player(Map*, int);
  virtual ~Player() {}
  virtual void play(Game*, Command*, Map*) = 0;
  virtual void	initPlay(Game*, Command*, Map*) = 0;
  bool	setPosRot(Game*, Map*, CAction, bool);
  void	setAction(Map*);
  bool	getIsAlive() const {return isAlive;}
  int	getDeathAnimStat() const {return deathAnimStat;}
  void	setIsAlive(bool _isAlive){isAlive = _isAlive;}
  bool	getInPause() const {return inPause;}
  void	setInPause(bool _inPause){inPause = _inPause;}
  void	incDeathAnimStat(){deathAnimStat++;}
  void	setActionReal(Action _action){action = _action;}
  void	displayPlayer(t_model const&, Action, Action, irr::scene::ISceneManager*);
  void	initPNode(t_model const&, Action, irr::scene::ISceneManager*);
  irr::core::vector3df getPosition() const {return pos;}
  irr::core::vector3df getRotation() const {return rotation;}
  Action	getAction() const {return action;}
  Action	getLastAction() const {return lastAction;}
  void	attackEnd() {attackIsEnd = true;}
  void	updateLastAction() {lastAction = action;}
  void	setBonus(BonusType b);
  void	paramBonus(Bonus *b) { bonus->setBonus(b->getBonus()); }
  Bonus	*getBonus() {return bonus;}
  void	setPosition(irr::core::vector3df _pos) {pos = _pos;}
  void	setRotation(irr::core::vector3df _rot) {rotation = _rot;}

  void	detach() { t.detach(); }
};

#endif /* PLAYER_HPP_ */

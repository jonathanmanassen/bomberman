//
// Player.cpp for indieStudio in /home/meyrie_g/rendu/cpp_indie_studio
// 
// Made by Gabin Meyrieux-Drevet
// Login   <meyrie_g@epitech.net>
// 
// Started on  Tue May 16 15:02:29 2017 Gabin Meyrieux-Drevet
// Last update Sun Jun 18 20:32:06 2017 jonathan manassen
//

#include <cmath>
#include <mutex>
#include <random>
#include "Player.hpp"
#include "Sound.hpp"

std::mutex mutexp;
int	pBomb[4];
extern std::random_device	generator;

Player::Player(Map *map, int _pNb) : Thread(), pNb(_pNb)
{
  bonus = new Bonus(pNb);
  pos = map->getSpawn(pNb);
  rotation = irr::core::vector3df(0,0,0);
  scale = irr::core::vector3df(1.0f, 1.0f, 1.0f);
  action = Action::STATIC;
  lastAction = Action::RUN;
  cA = CAction::NONE;
  pBomb[pNb] = 0;
  isAlive = true;
  deathAnimStat = 0;
  inPause = false;
  attackIsEnd = true;
  bomb[0] = -1;
  bomb[1] = -1;
}

void	Player::setBonus(BonusType b)
{
  switch (b)
    {
    case BonusType::UNDEFINED :
      break;
    case BonusType::BOMBM :
      Sound::getSound()->play("BombM.wav", 1);
      bonus->incBombNbr();
      break;
    case BonusType::BOMBL :
      Sound::getSound()->play("BombL.wav", 1);
      bonus->decBombNbr();
      break;
    case BonusType::EXPLENM :
      Sound::getSound()->play("EXPLENM.wav", 1);
      bonus->incExpLen();
      break;
    case BonusType::EXPLENL :
      bonus->decExpLen();
      break;
    case BonusType::MULEXP :
      Sound::getSound()->play("mul.wav", pNb + 1);
      bonus->activateDelMulW();
      break;
    case BonusType::PUSHBOMB :
      Sound::getSound()->play("PUSHBOMB.wav", pNb + 1);
      bonus->activatePushBomb();
      break;
    case BonusType::DELSW :
      Sound::getSound()->play("DELSW1.wav", pNb + 1);
      bonus->activateDelSW();
      break;
    case BonusType::NORMALB :
      bonus->setBombEffect(BombEffect::NORMAL);
      break;
    case BonusType::AOEB :
      Sound::getSound()->play("Atomic.wav", pNb + 1);
      bonus->setBombEffect(BombEffect::AOE);
      break;
    case BonusType::LONGB :
      Sound::getSound()->play("LONG.wav", pNb + 1);
      bonus->setBombEffect(BombEffect::LONG);
      bonus->incBombLStack();
      break;
    }
}

void	Player::setAction(Map *map)
{
  std::uniform_int_distribution<int> dist(0, 1);

  if (attackIsEnd == false && pBomb[pNb] == 0)
    attackIsEnd = true;
  if ((action == Action::STATIC || (action == Action::ATTACK && attackIsEnd == true)) &&
      cA >= CAction::UP && cA <= CAction::DIAG_DR)
    action = Action::RUN;
  switch (cA)
    {
    case CAction::NONE :
      if (action == Action::RUN || (action == Action::ATTACK && attackIsEnd == true))
	action = Action::STATIC;
      break;
    case CAction::BOMB :
      if (action != Action::ATTACK && pBomb[pNb] < bonus->getBombNbr())
	{
	  mutexp.lock();
	  if (map->getMapPiece(static_cast<int>(pos.X + 0.5), static_cast<int>(pos.Z + 0.5)).bomb == nullptr)
	    {
	      (dist(generator) == 1) ? Sound::getSound()->play("attack.wav") : Sound::getSound()->play("attack2.wav");
	      attackIsEnd = false;
	      action = Action::ATTACK;
	      pBomb[pNb]++;
	      mutexp.unlock();
	      map->spawnBomb(pos, *bonus);
	    }
	  else
	    mutexp.unlock();
	}
      break;
    }
}

bool	Player::setPosRot(Game *game, Map *map, CAction cA, bool rot)
{
  irr::u32 now = game->getWindow()->getTimer()->getTime();
  irr::f32 frameDeltaTime = (irr::f32)(now - then) / 1000.f;
  irr::core::vector3df	tmp = pos;
  irr::core::vector3df	tmprot = rotation;
  float move = mov_speed * frameDeltaTime;

  if (frameDeltaTime == 0)
    return (false);
  switch (cA)
    {
    case CAction::UP :
      tmp.Z += move;
      tmprot = irr::core::vector3df(0,180,0);
      break;
    case CAction::DOWN :
      tmp.Z -= move;
      tmprot = irr::core::vector3df(0,0,0);
      break;	    
    case CAction::RIGHT :
      tmp.X += move;
      tmprot = irr::core::vector3df(0,270,0);
      break;
    case CAction::LEFT :
      tmp.X -= move;
      tmprot = irr::core::vector3df(0,90,0);
      break;
    case CAction::DIAG_UL :
      tmp.Z += move;
      tmp.X -= move;
      tmprot = irr::core::vector3df(0,135,0);
      break;
    case CAction::DIAG_UR :
      tmp.Z += move;
      tmp.X += move;
      tmprot = irr::core::vector3df(0,225,0);
      break;
    case CAction::DIAG_DR :
      tmp.Z -= move;
      tmp.X += move;
      tmprot = irr::core::vector3df(0,315,0);
      break;
    case CAction::DIAG_DL :
      tmp.Z -= move;
      tmp.X -= move;
      tmprot = irr::core::vector3df(0,45,0);
      break;
    }
  if (map->isOnFire(pos) == true)
    isAlive = false;
  if (map->getMapPiece(static_cast<int>(pos.X + 0.5), static_cast<int>(pos.Z + 0.5)).bomb != nullptr)
    {
      bomb[0] = static_cast<int>(pos.X + 0.5);
      bomb[1] = static_cast<int>(pos.Z + 0.5);
    }
  else
    {
      bomb[0] = -1;
      bomb[1] = -1;
    }
  if ((tmp.X != pos.X || tmp.Z != pos.Z) && map->getColision(tmp, pos, bomb) == true)
    {
      pos = tmp;
      rotation = tmprot;
      then = now;
      setBonus(map->getColisionBonus(pos));
      return (true);
    }
  else
    {
      switch (cA)
	{
	case CAction::DIAG_UL :
	  if (setPosRot(game, map, CAction::UP, false) == false)
	    setPosRot(game, map, CAction::LEFT, false);
	  break;
	case CAction::DIAG_UR :
	  if (setPosRot(game, map, CAction::UP, false) == false)
	    setPosRot(game, map, CAction::RIGHT, false);
	  break;
	case CAction::DIAG_DR :
	  if (setPosRot(game, map, CAction::DOWN, false) == false)
	    setPosRot(game, map, CAction::RIGHT, false);
	  break;
	case CAction::DIAG_DL :
	  if (setPosRot(game, map, CAction::DOWN, false) == false)
	    setPosRot(game, map, CAction::LEFT, false);
	  break;
	}
    }
  if (rot == true)
    {
      rotation = tmprot;
      then = now;
    }
  return (false);
}

//
// Bomb.cpp for indieStudio in /home/meyrie_g/rendu/cpp_indie_studio
// 
// Made by Gabin Meyrieux-Drevet
// Login   <meyrie_g@epitech.net>
// 
// Started on  Tue May 16 15:02:29 2017 Gabin Meyrieux-Drevet
// Last update Sat Jun 17 21:39:16 2017 jonathan manassen
//

#include <mutex>
#include "Bomb.hpp"

std::mutex	bombmutex;
extern int	pBomb[4];

bool	Bomb::destroy_wall(const int &x, const int &y, Map *map)
{
  if (map->getMapPiece(x, y).bStat == BlockStatus::BOMB && map->getMapPiece(x, y).bomb != nullptr)
    map->getMapPiece(x, y).bomb->setStat(BombStatus::EXP);
  else if (map->getMapPiece(x, y).block == Block::AIR || map->getMapPiece(x, y).block == Block::WALL || (map->getMapPiece(x, y).block == Block::STRONG_WALL && getCanDelSW() == true))
    {
      const Block tmp = map->getMapPiece(x, y).block;
      map->setMapBStat(BlockStatus::FIRE, x, y);
      map->setMapBlock(Block::AIR, x, y);
      map->setMapBonusType(BonusType::UNDEFINED, x, y);
      if (nbFire == 0)
	{
	  map->addFire(x, y, 1);
	  mapFire.push_back(x);
	  mapFire.push_back(y);
	}
      if ((tmp == Block::WALL && getCanDelMulW() == false) || tmp == Block::STRONG_WALL)
	return (false);
      return (true);
    }
  return (false);
}

void	Bomb::init_vector(const int &i)
{
  posFire.clear();
  posFire.emplace_back(posY, posX - i);
  posFire.emplace_back(posY + i, posX);
  posFire.emplace_back(posY, posX + i);
  posFire.emplace_back(posY - i, posX);
  posFire.emplace_back(posY - i, posX - i);
  posFire.emplace_back(posY + i, posX + i);
  posFire.emplace_back(posY - i, posX + i);
  posFire.emplace_back(posY + i, posX - i);
}

void	Bomb::fireExpansion(Map *map)
{
  bool	dir[8] = {true, true, true, true, true, true, true, true};

  if (stat != BombStatus::END)
    stat = BombStatus::EXP;
  for (int i = 1; i < getExpLen(); i++)
    {
      init_vector(i);
      for (int j = 0; j < 8; j++)
	{
	  if (dir[j] == false || (bonus.getBombEffect() != BombEffect::AOE && j > 3))
	    continue;
	  dir[j] = destroy_wall(posFire[j].first, posFire[j].second, map);
	}
    }
}

BombStatus	Bomb::timeDiff()
{
  tNow = std::chrono::system_clock::now();
  std::chrono::duration<double> elaps;
  int	expTime = 1;
  expTime = (bonus.getBombEffect() == BombEffect::LONG) ? bonus.getBombLStack() : 1;
  if (stat == BombStatus::TIMER)
    elaps = tNow - bSpawn;
  else
    {
      elaps = tNow - bExp;
      return (elaps.count() > expTime) ? BombStatus::END : BombStatus::EXP;
    }
  return (elaps.count() > 3) ? BombStatus::EXP : BombStatus::TIMER;
}

void	Bomb::play(Map *map)
{
  bSpawn = std::chrono::system_clock::now();
  while (stat != BombStatus::END)
    {
      bombmutex.lock();
      if (stat != BombStatus::EXP || step != 0)
      stat = timeDiff();
      bombmutex.unlock();
      if (step == 0 && stat == BombStatus::EXP)
	{
	  if (step == 0)
	    {
	      bExp = std::chrono::system_clock::now();
	      Sound::getSound()->play("explosion.mp3");
	      step++;
	      map->setMapBStat(BlockStatus::FIRE, posY, posX);
	    }
	  fireExpansion(map);
	  nbFire++;
	}
    }
  mapFire.push_back(posY);
  mapFire.push_back(posX);
  for (int i = 0; (i + 1) < mapFire.size(); i += 2)
    {
      map->addFire(mapFire[i], mapFire[i + 1], -1);
      map->setMapBStat(BlockStatus::SAFE, mapFire[i], mapFire[i + 1]);
    }
  pBomb[bonus.getPNb()]--;
  
}

Bomb::Bomb(Bonus const &Bonus, Map *map, const int &i, const int &j) : Thread(), bonus(Bonus), stat(BombStatus::TIMER), step(0), posY(i), posX(j), nbFire(0)
{
  t = std::thread(&Bomb::play, this, map);
}

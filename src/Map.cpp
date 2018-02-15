//
// Map.cpp for bomberman in /home/manass_j/rendu/cpp_indie_studio
// 
// Made by jonathan manassen
// Login   <jonathan.manassen@epitech.eu@epitech.net>
// 
// Started on  Mon May 15 14:06:51 2017 jonathan manassen
// Last update Sun Jun 18 20:32:41 2017 jonathan manassen
//

#include <fstream>
#include <stdio.h>
#include <cmath>
#include <mutex>
#include <random>
#include "Map.hpp"

typedef Block (*ptr)();

static Block wall() {return Block::WALL;}
static Block strong_wall() {return Block::STRONG_WALL;}
static Block air() {return Block::AIR;}

ptr	ptrTab[10];
std::mutex mutex;
std::random_device	generator;

void	initPtrTab()
{
  int	i = 0;

  for (i; i < 4; i++)
    ptrTab[i] = wall;
  for (i; i < 9; i++)
    ptrTab[i] = strong_wall;
  for (i; i < 10; i++)
    ptrTab[i] = air;
}

void	Map::clear_extra_sw()
{
  for (int i = 0; i < mapSize; i++)
    for (int j = 0; j < mapSize; j++)
      {
	bool	first = true;
	if (map[i][j].block == Block::STRONG_WALL)
	  {
	    for (int k = i - 1; k <= i + 1 && k < mapSize; k++)
	      for (int l = j - 1; l <= j + 1 && l < mapSize; l++)
		{
		  k = (k < 0) ? k + 1 : k;
		  l = (l < 0) ? l + 1 : l;
		  l = (k == i && l == j) ? l + 1 : l;
		  if (map[k][l].block == Block::STRONG_WALL && first == true)
		    first = false;
		  else if (map[k][l].block == Block::STRONG_WALL)
		    map[k][l].block = Block::WALL;
		}
	  }
      }
}

void	Map::genMap()
{
  std::uniform_int_distribution<int> dist(0, 9);
  std::uniform_int_distribution<int> dist2(0, 7);

  initPtrTab();
  mapSize = dist2(generator) + 8;
  if (mapSize % 2  == 0)
    mapSize += 1;
  map = new t_Map*[mapSize];
  for (int i = 0; i < mapSize; i++)
    map[i] = new t_Map[mapSize];
  for (int i = 0; i < mapSize; i++)
    for (int j = 0; j < mapSize; j++)
      {
	map[i][j].block = ptrTab[dist(generator)]();
	map[i][j].bonusType = BonusType::UNDEFINED;
	map[i][j].bStat = BlockStatus::SAFE;
	map[i][j].bomb = nullptr;
	map[i][j].ps = nullptr;
	map[i][j].node = nullptr;
	map[i][j].lightNode = nullptr;
      }
  for (int i = 0; i < mapSize; i++)
    for (int j = 0; j < mapSize; j++)
      {
	if (i == 0 || i == mapSize - 1 || j == 0 || j == mapSize - 1)
	  map[i][j].block = Block::BEDROCK;
	else if (((i < 4 || i > mapSize - 5) && (j == 1 || j == mapSize - 2)) ||
		 ((j < 4 || j > mapSize - 5) && (i == 1 || i == mapSize - 2)))
	  map[i][j].block = Block::AIR;
      }
  for (int i = 0; i < mapSize; i++)
    for (int j = 0; j < mapSize; j++)
      {
	if (i == 0 || i == mapSize - 1 || j == 0 || j == mapSize - 1)
	  map[i][j].block = Block::BEDROCK;
	else if (((i < 4 || i > mapSize - 5) && (j == 1 || j == mapSize - 2)) ||
		 ((j < 4 || j > mapSize - 5) && (i == 1 || i == mapSize - 2)))
	  map[i][j].block = Block::AIR;
      }
  clear_extra_sw();
}

void	Map::clearNode()
{
  for (int i = 0; i < mapSize; i++)
    for (int j = 0; j < mapSize; j++)
      {
	if (map[i][j].node != nullptr)
	  {
	    map[i][j].node->remove();
	    map[i][j].node = nullptr;
	  }
	if (map[i][j].lightNode != nullptr)
	  {
	    map[i][j].lightNode->remove();
	    map[i][j].lightNode = nullptr;
	  }
	if (map[i][j].ps != nullptr)
	  {
	    map[i][j].ps->setEmitter(0);
	    map[i][j].ps->remove();
	    map[i][j].ps = nullptr;
	  }
      }
}

saveMap	**Map::getSaveMap(Map const &m)
{
  saveMap **map;
  int mapSize = m.getMapSize();
  map = new saveMap*[mapSize];
  for (int i = 0; i < mapSize; i++)
    map[i] = new saveMap[mapSize];
  for (int i = 0; i < mapSize; i++)
    for (int j = 0; j < mapSize; j++)
      {
	map[i][j].block = m.getMap()[i][j].block;
	map[i][j].bStat = m.getMap()[i][j].bStat;
	map[i][j].bonusType = m.getMap()[i][j].bonusType;
	if (map[i][j].bStat == BlockStatus::BOMB)
	  map[i][j].bonus = m.getMap()[i][j].bomb->getBonus();
      }
  return map;
}

void	Map::setMap(saveMap **save, unsigned int mSize, Game *game)
{
  clearNode();
  for (int i = 0; i < mapSize; i++)
    delete map[i];
  delete map;
  mapSize = mSize;
  map = new t_Map*[mapSize];
  for (int i = 0; i < mapSize; i++)
    map[i] = new t_Map[mapSize];
  spawn[0] = irr::core::vector3df(1,0,1);
  spawn[1] = irr::core::vector3df(mapSize - 2,0,1);
  spawn[2] = irr::core::vector3df(mapSize - 2,0,mapSize - 2);
  spawn[3] = irr::core::vector3df(1,0,mapSize - 2);
  for (int i = 0; i < mapSize; i++)
    for (int j = 0; j < mapSize; j++)
      {
	map[i][j].block = save[i][j].block;
	map[i][j].bStat = save[i][j].bStat;
	map[i][j].bonusType = save[i][j].bonusType;
	map[i][j].bomb = nullptr;
	map[i][j].node = nullptr;
	map[i][j].lightNode = nullptr;
	map[i][j].ps = nullptr;
	if (map[i][j].bStat == BlockStatus::BOMB)
	  {
	    Bonus	tmp(save[i][j].bonus.pNb);
	    tmp.setBonus(save[i][j].bonus);
	    spawnBomb(irr::core::vector3df(i, 0, j), tmp);
	  }
      }
  genNode(game);
}

Map::~Map()
{
  for (int i = 0; i < mapSize; i++)
    for (int j = 0; j < mapSize; j++)
      {
	if (map[i][j].bomb != nullptr)
	  {
	    map[i][j].bomb->setStat(BombStatus::END);
	    map[i][j].bomb->end();
	    delete map[i][j].bomb;
	    map[i][j].bomb = nullptr;
	  }
      }
}

void		Map::my_swap(irr::f32 &a, irr::f32 &b)
{
  irr::f32	tmp = a;

  a = b;
  b = tmp;
}

bool	Map::getColision(irr::core::vector3df end, irr::core::vector3df pos, const int posBomb[2])
{
  float	tmp;

  if (end.X < pos.X)
    my_swap(end.X, pos.X);
  if (end.Z < pos.Z)
    my_swap(end.Z, pos.Z);
  float	x = (end.X - pos.X) / 5;
  float	z = (end.Z - pos.Z) / 5;

  for (int i = 0; i < mapSize; i++)
    for (int j = 0; j < mapSize; j++)
      {
	if (map[i][j].block == Block::WALL || map[i][j].block == Block::STRONG_WALL || (map[i][j].bStat == BlockStatus::BOMB && (i != posBomb[0] || j != posBomb[1])))
	  {
	    map[i][j].hitbox[0][0] = (map[i][j].bStat == BlockStatus::BOMB) ? i - 0.5 : i - 0.7;
	    map[i][j].hitbox[0][1] = (map[i][j].bStat == BlockStatus::BOMB) ? i + 0.5 : i + 0.7;
	    map[i][j].hitbox[1][0] = (map[i][j].bStat == BlockStatus::BOMB) ? j - 0.5 : j - 0.7;
	    map[i][j].hitbox[1][1] = (map[i][j].bStat == BlockStatus::BOMB) ? j + 0.5 : j + 0.7;
	  }
	else if (map[i][j].block == Block::BEDROCK)
	  {
	    map[i][j].hitbox[0][0] = i - 0.9;
	    map[i][j].hitbox[0][1] = i + 0.9;
	    map[i][j].hitbox[1][0] = j - 0.9;
	    map[i][j].hitbox[1][1] = j + 0.9;
	  }
	else
	  {
	    map[i][j].hitbox[0][0] = -1;
	    map[i][j].hitbox[0][1] = -1;
	    map[i][j].hitbox[1][0] = -1;
	    map[i][j].hitbox[1][1] = -1;
	  }
      }
  while (pos.X < end.X || pos.Z < end.Z)
    {
      if (pos.X >= 0 && pos.X < mapSize &&
	  pos.Z >= 0 && pos.Z < mapSize)
	{
	  for (int i = 0; i < mapSize; i++)
	    for (int j = 0; j < mapSize; j++)
	      if (pos.X >= map[i][j].hitbox[0][0] && pos.X <= map[i][j].hitbox[0][1] &&
		  pos.Z >= map[i][j].hitbox[1][0] && pos.Z <= map[i][j].hitbox[1][1])
		return (false);
	  pos.X += (pos.X < end.X) ? x : 0;
	  pos.Z += (pos.Z < end.Z) ? z : 0;
	}
      else
	return (false);
    }
  for (int i = 0; i < mapSize; i++)
    for (int j = 0; j < mapSize; j++)
      if (pos.X >= map[i][j].hitbox[0][0] && pos.X <= map[i][j].hitbox[0][1] &&
	  pos.Z >= map[i][j].hitbox[1][0] && pos.Z <= map[i][j].hitbox[1][1])
	return (false);
  return (true);
}

bool	Map::isOnFire(const irr::core::vector3df &pos)
{
  BonusType	tmp;
  int	i = static_cast<int>(pos.X + 0.5);
  int	j = static_cast<int>(pos.Z + 0.5);

  if (i >= 0 && i < mapSize &&
      j >= 0 && j < mapSize)
    {
      if (map[i][j].bStat == BlockStatus::FIRE)
	return (true);
    }
  return (false);
}

BonusType	Map::getColisionBonus(const irr::core::vector3df &pos)
{
  BonusType	tmp;
  int	i = static_cast<int>(pos.X + 0.5);
  int	j = static_cast<int>(pos.Z + 0.5);

  if (i >= 0 && i < mapSize &&
      j >= 0 && j < mapSize)
    {
      if (map[i][j].bonusType != BonusType::UNDEFINED && map[i][j].block == Block::AIR)
	{
	  tmp = map[i][j].bonusType;
	  map[i][j].bonusType = BonusType::UNDEFINED;
	  return (tmp);
	}
    }
  return (BonusType::UNDEFINED);
}

void	Map::spawnBomb(const irr::core::vector3df &pos, Bonus const &b)
{
  mutex.lock();
  int	i = static_cast<int>(pos.X + 0.5);
  int	j = static_cast<int>(pos.Z + 0.5);
  if (i >= 0 && i < mapSize &&
      j >= 0 && j < mapSize)
    {
      map[i][j].bStat = BlockStatus::BOMB;
      if (map[i][j].bonusType != BonusType::UNDEFINED)
	map[i][j].bonusType = BonusType::UNDEFINED;
      map[i][j].bomb = new Bomb(b, this, i, j);
    }
  mutex.unlock();
}

BonusType	Map::getNewBonus()
{
  std::uniform_int_distribution<int> dist(0, 10);
  int	r = dist(generator);

  switch (r)
    {
    case 0:
      return BonusType::UNDEFINED;
    case 1:
      return BonusType::BOMBM;
    case 2:
      return BonusType::BOMBL;
    case 3:
      return BonusType::EXPLENM;
    case 4:
      return BonusType::EXPLENL;
    case 5:
      return BonusType::MULEXP;
    case 6:
      return BonusType::DELSW;
    case 7:
      return BonusType::PUSHBOMB;
    case 8:
      return BonusType::NORMALB;
    case 9:
      return BonusType::AOEB;
    case 10:
      return BonusType::LONGB;
    }
}

void	Map::refreshNode(Game *game)
{
  for (int i = 0; i < mapSize ; i++)
    for (int j = 0; j < mapSize ; j++)
      {
	if (map[i][j].bomb != nullptr && map[i][j].bomb->getStat() == BombStatus::END)
	  {
	    map[i][j].bomb->end();
	    delete map[i][j].bomb;
	    map[i][j].bomb = nullptr;
	  }
	if (map[i][j].bStat == BlockStatus::SAFE && map[i][j].block == Block::AIR && map[i][j].bonusType == BonusType::UNDEFINED)
	  if (map[i][j].node != nullptr)
	    {
	      map[i][j].node->remove();
	      map[i][j].node = nullptr;
	    }
	mutex.lock();
	if (map[i][j].bStat == BlockStatus::BOMB && map[i][j].nodeStat == BlockStatus::SAFE && map[i][j].bomb != nullptr)
	  {
	    if (map[i][j].node != nullptr)
	      {
		map[i][j].node->remove();
		map[i][j].node = nullptr;
	      };
	    map[i][j].node = game->displayNode(game->getMeshBomb(map[i][j].bomb->getBombEffect()), Action::STATIC,
					       irr::core::vector3df(i, 0, j),
					       irr::core::vector3df(0, 0, 0),
					       irr::core::vector3df(0.03f, 0.03f, 0.03f));
	    map[i][j].nodeStat = BlockStatus::BOMB;
	  }
	mutex.unlock();
	if (map[i][j].bStat == BlockStatus::FIRE &&
	    (map[i][j].nodeStat != BlockStatus::FIRE))
	  {
	    map[i][j].nodeStat = BlockStatus::FIRE;
	    map[i][j].ps = game->getSmgr()->addParticleSystemSceneNode(false);
	      
	    irr::scene::IParticleEmitter* em = map[i][j].ps->createBoxEmitter(irr::core::aabbox3d<irr::f32>(0,0,0,0,0,0),
									      irr::core::vector3df(0.0f,0.01f,0.0f),
									      40,50,
									      irr::video::SColor(0,255,255,255), irr::video::SColor(0,255,255,255),
									      200,400,0,
									      irr::core::dimension2df(1.f,1.f),
									      irr::core::dimension2df(3.f,3.f));
	    map[i][j].ps->setEmitter(em); // this grabs the emitter
	    em->drop(); // so we can drop it here without deleting it
	    irr::scene::IParticleAffector* paf = map[i][j].ps->createFadeOutParticleAffector();
	    map[i][j].ps->addAffector(paf);
	    paf->drop();
	      
	    map[i][j].ps->setPosition(irr::core::vector3df(i,0,j));
	    map[i][j].ps->setScale(irr::core::vector3df(1,0,1));
	    map[i][j].ps->setMaterialFlag(irr::video::EMF_LIGHTING, false);
	    map[i][j].ps->setMaterialFlag(irr::video::EMF_ZWRITE_ENABLE, false);
	    map[i][j].ps->setMaterialTexture(0, game->getDriver()->getTexture("media/fire.bmp"));
	    map[i][j].ps->setMaterialType(irr::video::EMT_TRANSPARENT_ADD_COLOR);
	      
	      
	    if (map[i][j].node != nullptr && map[i][j].bonusType == BonusType::UNDEFINED)
	      {
		map[i][j].node->remove();
		map[i][j].node = nullptr;
	      }
	  }
	if (map[i][j].bStat == BlockStatus::SAFE &&
	    (map[i][j].nodeStat == BlockStatus::BOMB ||
	     map[i][j].nodeStat == BlockStatus::FIRE) &&
	    map[i][j].nbFire == 0)
	  {
	    if (map[i][j].nodeStat == BlockStatus::FIRE)
	      map[i][j].ps->setEmitter(0);
	    if (map[i][j].node != nullptr && map[i][j].bonusType == BonusType::UNDEFINED)
	      {
		map[i][j].node->remove();
		map[i][j].node = nullptr;
	      }
	    if (map[i][j].bonusType != BonusType::UNDEFINED)
	      {
		map[i][j].node = game->displayNode(game->getMeshBonus(map[i][j].bonusType), Action::STATIC,
						   irr::core::vector3df(i, 0, j),
						   irr::core::vector3df(0, 0, 0),
						   (static_cast<int>(map[i][j].bonusType) > 6) ?  irr::core::vector3df(0.02f, 0.02f, 0.02f) : (irr::core::vector3df(0.3f, 0.3f, 0.3f)));
		irr::scene::ISceneNodeAnimator* ani= game->getSmgr()->createRotationAnimator(irr::core::vector3df(0,1,0));
		map[i][j].node->addAnimator(ani);
		ani->drop();
	      }
	    map[i][j].nodeStat = BlockStatus::SAFE;
	  }
	if (map[i][j].block == Block::AIR && map[i][j].nodeB != Block::AIR)
	  {
	    map[i][j].bonusType = getNewBonus();
	    if (map[i][j].node != nullptr)
	      {
		map[i][j].node->remove();
		map[i][j].node = nullptr;
	      }
	    map[i][j].nodeB = map[i][j].block;
	  }
      }
}

void	Map::genNode(Game *game)
{
  for (int i = 0; i < mapSize ; i++)
    for (int j = 0; j < mapSize ; j++)
      {
	Block const &tmp = map[i][j].block;
	/*	  displayNode(ground, Action::STATIC,
		  irr::core::vector3df(i, -1.4f, j),
		  irr::core::vector3df(0, 0, 0),
		  irr::core::vector3df(1.0f, 1.0f, 1.0f));*/
	map[i][j].nodeB = tmp;
	map[i][j].nodeStat = BlockStatus::SAFE;
	switch (tmp)
	  {
	  case Block::BEDROCK :
	    map[i][j].lightNode =
	      game->getSmgr()->addVolumeLightSceneNode(0, -1,
						 32,32,
						 irr::video::SColor(0, 255, 255, 255),
						 irr::video::SColor(0, 0, 0, 0),
						 irr::core::vector3df(i,0,j),
						 irr::core::vector3df(0,0,0),
						 irr::core::vector3df(1.5f, 1.5f, 1.5f));
	    if (map[i][j].lightNode)
	      {
		irr::core::array<irr::video::ITexture*> textures;
		for (irr::s32 g=7; g > 0; --g)
		  {
		    irr::core::stringc tmp;
		    tmp = "media/portal";
		    tmp += g;
		    tmp += ".bmp";
		    irr::video::ITexture* t = game->getDriver()->getTexture( tmp.c_str() );
		    textures.push_back(t);
		  }
		irr::scene::ISceneNodeAnimator* glow = game->getSmgr()->createTextureAnimator(textures, 150);
		map[i][j].lightNode->addAnimator(glow);
		glow->drop();
	      }
	    break;
	  case Block::WALL :
	    map[i][j].node = game->displayNode(game->getMeshW(), Action::RUN,
					       irr::core::vector3df(i, 0, j),
					       irr::core::vector3df(0, 0, 0),
					       irr::core::vector3df(1.0f, 1.0f, 1.0f));
	    map[i][j].node->setLoopMode(false);
	    break;
	  case Block::STRONG_WALL :
	    map[i][j].node = game->displayNode(game->getMeshSW(), Action::STATIC,
					       irr::core::vector3df(i, 0, j),
					       irr::core::vector3df(0, 0, 0),
					       irr::core::vector3df(0.015f, 0.015f, 0.015f));
	    break;
	  }
	if (map[i][j].bonusType != BonusType::UNDEFINED)
	  {
	    map[i][j].node = game->displayNode(game->getMeshBonus(map[i][j].bonusType), Action::STATIC,
					       irr::core::vector3df(i, 0, j),
					       irr::core::vector3df(0, 0, 0),
					       (static_cast<int>(map[i][j].bonusType) > 6) ?  irr::core::vector3df(0.02f, 0.02f, 0.02f) : (irr::core::vector3df(0.3f, 0.3f, 0.3f)));
	    irr::scene::ISceneNodeAnimator* ani= game->getSmgr()->createRotationAnimator(irr::core::vector3df(0,1,0));
	    map[i][j].node->addAnimator(ani);
	    ani->drop();
	  }
      }
}

Map::Map()
{
  genMap();
  spawn[0] = irr::core::vector3df(1,1,1);
  spawn[1] = irr::core::vector3df(mapSize,1,1);
  spawn[2] = irr::core::vector3df(mapSize,1,mapSize);
  spawn[3] = irr::core::vector3df(1,1,mapSize);
}

Map::Map(Game *g)
{
  genMap();
  spawn[0] = irr::core::vector3df(1,0,1);
  spawn[1] = irr::core::vector3df(mapSize - 2,0,1);
  spawn[2] = irr::core::vector3df(mapSize - 2,0,mapSize - 2);
  spawn[3] = irr::core::vector3df(1,0,mapSize - 2);
  genNode(g);
}

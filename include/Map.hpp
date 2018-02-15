//
// Map.hpp for bomberman in /home/manass_j/cpp_indie_studio/include
// 
// Made by jonathan manassen
// Login   <jonathan.manassen@epitech.eu@epitech.net>
// 
// Started on  Mon May 15 13:01:46 2017 jonathan manassen
// Last update Sat Jun 17 22:24:30 2017 jonathan manassen
//

#ifndef MAP_H_
# define MAP_H_

#include <string>
#include <iostream>
#include <irrlicht.h>
#include "Bomb.hpp"
#include "Game.hpp"
#include "enum.hpp"
#include "Bonus.hpp"

class	Game;
class	Bomb;
class	SaveGame;

struct	t_Map
{
  float	hitbox[2][2];
  Block	block;
  BlockStatus bStat;
  Bomb *bomb;
  irr::scene::IAnimatedMeshSceneNode	*node;
  Block	nodeB;
  BlockStatus nodeStat;
  irr::scene::IParticleSystemSceneNode* ps;
  irr::scene::IVolumeLightSceneNode *lightNode;
  BonusType	bonusType;
  int	nbFire = 0;
};

class	Map
{
  unsigned int  mapSize;
  irr::core::vector3df spawn[4];
  t_Map	**map;
public:
  Map();
  Map(Game *);
  ~Map();
  saveMap	**getSaveMap(Map const &m);
  void	setMap(saveMap **save, unsigned int, Game*);
  void	clearNode();
  void	genMap();
  void	genNode(Game *);
  void	display();
  void	refreshNode(Game*);
  const unsigned int	&getMapSize() const {return (mapSize);}
  const irr::core::vector3df	&getSpawn(const int &i) const {return spawn[i];}
  bool	getColision(irr::core::vector3df, irr::core::vector3df, const int[2]);
  void	spawnBomb(const irr::core::vector3df&, Bonus const&);
  BonusType	getNewBonus();
  BonusType	getColisionBonus(const irr::core::vector3df&);
  bool	isOnFire(const irr::core::vector3df&);
  void	clear_extra_sw();
  void	my_swap(irr::f32&, irr::f32&);
  t_Map	**getMap() const { return map; }
  const t_Map	&getMapPiece(int i, int j) const { return map[i][j]; }
  void	setMapBlock(const Block &block, const int &x, const int &y) { map[x][y].block = block; }
  void	setMapBStat(const BlockStatus &block, const int &x, const int &y) { map[x][y].bStat = block; }
  void	setMapBonusType(const BonusType &block, const int &x, const int &y) { map[x][y].bonusType = block; }
  const Block	&getMapBlock(int x, int y) const { return map[x][y].block; }
  void	addFire(const int &x, const int &y, const int &i) { map[x][y].nbFire += i; if (map[x][y].nbFire < 0) map[x][y].nbFire = 0; }
};

#endif /* MAP_H_ */

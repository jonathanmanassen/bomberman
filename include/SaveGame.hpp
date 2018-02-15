//
// SaveGame.hpp for indieStudio in /home/meyrie_g/rendu/cpp_indie_studio
// 
// Made by Gabin Meyrieux-Drevet
// Login   <meyrie_g@epitech.net>
// 
// Started on  Tue May 16 16:08:43 2017 Gabin Meyrieux-Drevet
// Last update Sun Jun 18 22:21:05 2017 Gabin Meyrieux-Drevet
//

#ifndef SAVEGAME_HPP_
# define SAVEGAME_HPP_

#include <vector>
#include <string>
#include <stdbool.h>
#include "struct.hpp"
#include "Player.hpp"
#include "Human.hpp"
#include "Ia.hpp"
#include "Map.hpp"

struct t_SaveGame
{
  saveMap	**map;
  unsigned int	mapSize;
  irr::core::vector3df	pPos[4];
  irr::core::vector3df	pRot[4];
  bool	isAlive[4];
  bool	isHuman[4];
  t_Bonus	pBonus[4];
  int	skinOrder[4];
};

class	SaveGame
{
  t_SaveGame	save;
public:
  SaveGame(){}
  SaveGame(Map *_map, Player **_player, int pNb, int *skinOrder);
  void	loadFile(std::string const &file);
  void	writeFile(std::string const &file);
  saveMap	**getSaveMap() const { return save.map; }
  const unsigned int	&getSaveMapSize() const { return save.mapSize; }
  const irr::core::vector3df	&getPosition(int pNb) const { return save.pPos[pNb]; }
  const irr::core::vector3df	&getRotation(int pNb) const { return save.pRot[pNb]; }
  int	getPlayerNbr() const { int i = 0; for (i; save.isHuman[i] == true; i++); return i;}
  int	getPlayerAliveNbr() const { int j = 0; for (int i = 0; i < 4; i++)if (save.isAlive[i] == true)j++; return j;}
  bool	getIsAlive(int i) const { return save.isAlive[i];}
  t_Bonus const	&getBonus(int i) const { return save.pBonus[i]; }
  int	getSkinOrder(int i) { return save.skinOrder[i]; }
};

#endif /*!SAVEGAME_HPP_*/

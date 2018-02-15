//
// struct.hpp for indieStudio in /home/meyrie_g/rendu/cpp_indie_studio
// 
// Made by Gabin Meyrieux-Drevet
// Login   <meyrie_g@epitech.net>
// 
// Started on  Mon May 22 17:51:46 2017 Gabin Meyrieux-Drevet
// Last update Sun Jun 18 15:05:44 2017 Gabin Meyrieux-Drevet
//

#ifndef STRUCT_HPP_
# define STRUCT_HPP_

#include <map>
#include <vector>
#include <chrono>
#include <irrlicht.h>
#include "enum.hpp"

struct	t_Bonus
{
  int		pNb;
  int		expLen;
  bool		canDelMulW;
  bool		canDelSW;
  bool		canPushB;
  int		bombNbr;
  BombEffect	bombEffect;
  int		bombLStack;
};

struct saveMap
{
  Block	block;
  BlockStatus bStat;
  BonusType	bonusType;
  t_Bonus	bonus;
};

struct	t_model
{
  std::map<Action,irr::scene::IAnimatedMesh*>	mesh;
  std::vector<irr::video::ITexture*>		texture;
};

struct	gameInstruction
{
  int		playerNbr;
  int		skinOrder[4];
  int		loadSave;
  int		saveNbr;
  int		map;
  int		execCode;
  int		endParty;
  int		spectate;
};

struct	t_nodeMap
{
  Block	b;
  irr::scene::IAnimatedMeshSceneNode	*node;
};

struct	SMouseState
{
  irr::core::position2di Position;
  std::chrono::time_point<std::chrono::system_clock>	time;
  int	state;
  bool LeftButtonDown;
  SMouseState() : LeftButtonDown(false) { }
};

#endif /* STRUCT_HPP_ */

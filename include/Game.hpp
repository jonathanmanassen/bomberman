//
// game.hpp for bomberman in /home/manass_j/cpp_indie_studio/include
// 
// Made by jonathan manassen
// Login   <jonathan.manassen@epitech.eu@epitech.net>
// 
// Started on  Mon May 15 13:01:46 2017 jonathan manassen
// Last update Sun Jun 18 20:25:33 2017 Gabin Meyrieux-Drevet
//

#ifndef GAME_H_
# define GAME_H_

#include <string>
#include <iostream>
#include <vector>
#include <fstream>
#include <map>
#include <irrlicht.h>
#include "Display.hpp"
#include "Menu.hpp"
#include "Player.hpp"
#include "Map.hpp"

class	Map;
class	Player;

class	Game : public Display
{
  Map		*map;
  irr::IrrlichtDevice		*screen;
  Settings	*settings;
  //  Score		*score;
  t_model	skin[4];
  t_model	ground;
  t_model	stage;
  t_model	wall;
  t_model	strongwall;
  t_model	bedrock;
  t_model	bomb[3];
  t_model	fire;
  t_model	bonus[7];
  t_model	decor[13];
  irr::scene::ICameraSceneNode	*cam;
  int	introStat;
  gameInstruction gI;
  irr::scene::IMeshSceneNode *floor;
  irr::scene::IAnimatedMeshSceneNode *pNode[4];
  irr::scene::IAnimatedMeshSceneNode *decorNode[13];
  Player	*player[4];
  const irr::f32 mov_speed = 5.f;
  int	pAlive;
public:
  Game(irr::IrrlichtDevice *, Settings*);
  //  Game(Command&, Score&, Settings&);
  ~Game()
  {
    endParty();
    cam->remove();
  }
  virtual void OnAnimationEnd(irr::scene::IAnimatedMeshSceneNode* node);
  t_model &getMeshW() {return wall;}
  t_model &getMeshSW() {return strongwall;}
  t_model &getMeshBomb(const BombEffect&);
  t_model &getMeshBonus(const BonusType&);
  t_model &getMeshFire() {return fire;}
  irr::IrrlichtDevice *getScreen() const {return screen;}
  int	play(Command *command);
  int	checkWin();
  int	victoryDisplay(Command*);
  int	aceDisplay(Command*);
  void	endParty();
  void	initGameInstruction(gameInstruction, Command *command);
  virtual void displayAll();
  int	displayMap();
  void	displaySpectate(int);
  void	saveGame(int);
  void	displayPlayer(const irr::core::vector3df &pos,
		      const irr::core::vector3df &rot, int pNb, Action i);
  void	setPlayerMouvement(int pNbr, const irr::core::vector3df &pos, const irr::core::vector3df &rot);
  void	loadDecor(std::string path);
  void	loadWall(t_model &model, std::string path);
  void	loadModel(t_model &model, std::string pathModel,
		  std::string pathTexture);
  void	loadZiggs(t_model &model, std::string path);
  void	loadFloor(t_model &model, std::string path);
  irr::scene::IAnimatedMeshSceneNode	*displayNode(t_model &model, Action i,
						     const irr::core::vector3df &pos,
						     const irr::core::vector3df &rot,
						     const irr::core::vector3df &scl);
  irr::scene::IMeshSceneNode	*displayNodeNoTex(t_model &model, Action i,
						     const irr::core::vector3df &pos,
						     const irr::core::vector3df &rot,
						     const irr::core::vector3df &scl);
  void	playerRefreshNode();
  void	voiceEvent();
  bool	fileExist(std::string const &file) {std::ifstream f(file.c_str());return f.good();}
};

#endif /* GAME_H_ */

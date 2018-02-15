//
// game.cpp for bomberman in /home/manass_j/rendu/cpp_indie_studio
// 
// Made by jonathan manassen
// Login   <jonathan.manassen@epitech.eu@epitech.net>
// 
// Started on  Mon May 15 14:06:51 2017 jonathan manassen
// Last update Sun Jun 18 23:31:26 2017 Gabin Meyrieux-Drevet
//

#include <fstream>
#include "SaveGame.hpp"
#include "Game.hpp"
#include "Human.hpp"
#include "Ia.hpp"

Game::Game(irr::IrrlichtDevice *_screen, Settings *_settings) :
  Display(_screen, _screen->getVideoDriver(), _screen->getSceneManager(), _screen->getGUIEnvironment(), _settings), screen(_screen), settings(_settings)
{
  displayAll();
  map = nullptr;
  pNode[0] = nullptr;
  pNode[1] = nullptr;
  pNode[2] = nullptr;
  pNode[3] = nullptr;
  floor = nullptr;
  for (int i = 0; i < 4; i++)
    player[i] = nullptr;
  for (int i = 0; i < 13; i++)
    decorNode[i] = nullptr;
  pAlive = 4;
}

void	Game::endParty()
{
  for (int i = 0; i < 4; i++)
    {
      if (player[i] != nullptr)
	{
	  player[i]->incDeathAnimStat();
	  player[i]->incDeathAnimStat();
	  player[i]->setIsAlive(false);
	  player[i]->end();
	  delete player[i];
	  player[i] = nullptr;
	}
      if (pNode[i] != nullptr)
	{
	  pNode[i]->remove();
	  pNode[i] = nullptr;
	}
    }
  if (map != nullptr)
    {
      map->clearNode();
      delete map;
      map = nullptr;
    }
  for (int i = 0; i < 13; i++)
    {
      if (decorNode[i] != nullptr)
	{
	  decorNode[i]->remove();
	  decorNode[i] = nullptr;
	}
    }
  if (floor != nullptr)
    {
      floor->remove();
      floor = nullptr;
    }
  Sound::getSound()->stopAll();
}

void	Game::initGameInstruction(gameInstruction _gI, Command *command)
{
  SaveGame load;
  int	j = 0;

  gI = _gI;
  map = new Map(this);
  if (gI.loadSave == 1)
    {
      std::string tmp = "save"+std::to_string(_gI.saveNbr);
      load.loadFile(tmp);
      map->setMap(load.getSaveMap(), load.getSaveMapSize(), this);
      gI.playerNbr = load.getPlayerNbr();
      pAlive = load.getPlayerAliveNbr();
      for (int i = 0; i < 4; i++)
	gI.skinOrder[i] = load.getSkinOrder(i);
    }
  for (int i = 0; i < 4; i++)
    if (player[i] != nullptr)
      {
	player[i]->end();
	delete player[i];
	player[i] = nullptr;
      }
  for (j; j < gI.playerNbr; j++)
    player[j] = new Human(map, j);
  for (j; j < 4; j++)
    player[j] = new Ia(map, j);
  if (gI.loadSave == 1)
    for (int i = 0; i < 4; i++)
      {
	Bonus tmp(i);
	tmp.setBonus(load.getBonus(i));
	player[i]->setPosition(load.getPosition(i));
	player[i]->setRotation(load.getRotation(i));
	player[i]->setIsAlive(load.getIsAlive(i));
	player[i]->paramBonus(&tmp);
      }
  for (int i = 0; i < 4; i++)
    player[i]->initPlay(this, command, map);
  displayMap();
  displaySpectate(gI.spectate);
}

irr::scene::IAnimatedMeshSceneNode	*Game::displayNode(t_model &model,Action i,
							   const irr::core::vector3df &pos =
							   irr::core::vector3df(0, 0, 0),
							   const irr::core::vector3df &rot =
							   irr::core::vector3df(0, 0, 0),
							   const irr::core::vector3df &scl =
							   irr::core::vector3df(1.0f, 1.0f, 1.0f))
{
  irr::scene::IAnimatedMeshSceneNode	*node;

  node = getSmgr()->addAnimatedMeshSceneNode(model.mesh.at(i), 0, -1,
					     pos, rot, scl);
  if (node)
    {
      node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
      for (int	j = 0; j < model.texture.size(); j++)
	{
	  if (model.texture.at(j))
	    node->setMaterialTexture(0, model.texture.at(j));
	  else
	    exit(0);
	}
      node->setAnimationSpeed(20);
      if (i == Action::ATTACK)
	node->setLoopMode(false);
      else
	node->setLoopMode(true);
    }
  else
    exit(0);
  return (node);
}

void	Game::OnAnimationEnd(irr::scene::IAnimatedMeshSceneNode *node)
{
  for (int i = 0; i < 4; i++)
    {
      if (player[i]->getAction() == Action::ATTACK && pNode[i]->getFrameNr() == pNode[i]->getEndFrame())
	{
	  player[i]->attackEnd();
	}
      if (player[i]->getDeathAnimStat() == 1 && pNode[i]->getFrameNr() == pNode[i]->getEndFrame())
	player[i]->incDeathAnimStat();
    }
}

void	Game::playerRefreshNode()
{
  for (int i = 0; i < 4; i++)
    {
      if (player[i]->getIsAlive() == false)
	switch (player[i]->getDeathAnimStat())
	  {
	  case 0 :
	    displayPlayer(player[i]->getPosition(), player[i]->getRotation(), i, Action::DEATH);
	    player[i]->incDeathAnimStat();
	    break;
	  }
      else
	{
	  if (player[i]->getAction() != player[i]->getLastAction())
	    displayPlayer(player[i]->getPosition(), player[i]->getRotation(), i, player[i]->getAction());
	  setPlayerMouvement(i, player[i]->getPosition(), player[i]->getRotation());
	}
    }
}

void	Game::displayPlayer(const irr::core::vector3df &pos,
			     const irr::core::vector3df &rot, int pNb, Action i)
{
  if (pNode[pNb] != nullptr)
    {
      pNode[pNb]->remove();
      pNode[pNb] = nullptr;
    }
  pNode[pNb] = getSmgr()->addAnimatedMeshSceneNode(skin[gI.skinOrder[pNb]].mesh.at(i), 0, -1,
						   pos, rot, irr::core::vector3df(1, 1, 1));
  player[pNb]->updateLastAction();
  if (pNode[pNb])
    {
      pNode[pNb]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
      for (int	j = 0; j < skin[gI.skinOrder[pNb]].texture.size(); j++)
	pNode[pNb]->setMaterialTexture(0, skin[gI.skinOrder[pNb]].texture.at(j));
      pNode[pNb]->setAnimationSpeed(20);
      if (i == Action::ATTACK || i == Action::DEATH)
	{
	  pNode[pNb]->setLoopMode(false);
	  (i == Action::ATTACK) ? pNode[pNb]->setAnimationSpeed(50) : pNode[pNb]->setAnimationSpeed(30);
	  OnAnimationEnd(pNode[pNb]);
	  pNode[pNb]->setAnimationEndCallback(this);
	}
    }
}

void	Game::setPlayerMouvement(int pNb, const irr::core::vector3df &pos, const irr::core::vector3df &rot)
{
  if (pNode[pNb] != nullptr)
    {
      pNode[pNb]->setPosition(pos);
      pNode[pNb]->setRotation(rot);
    }
}

irr::scene::IMeshSceneNode	*Game::displayNodeNoTex(t_model &model,Action i,
							   const irr::core::vector3df &pos =
							   irr::core::vector3df(0, 0, 0),
							   const irr::core::vector3df &rot =
							   irr::core::vector3df(0, 0, 0),
							   const irr::core::vector3df &scl =
							   irr::core::vector3df(1.0f, 1.0f, 1.0f))
{
  irr::scene::IMeshSceneNode	*node;

  node = getSmgr()->addMeshSceneNode(model.mesh.at(i), 0, -1,
					     pos, rot, scl);
  node->setMaterialFlag(irr::video::EMF_LIGHTING, false);
  node->setMaterialType(irr::video::EMT_TRANSPARENT_ALPHA_CHANNEL);
  return (node);
}

void	Game::saveGame(int saveNbr)
{
  std::string tmp = "save"+std::to_string(saveNbr);
  SaveGame	save(map, player, gI.playerNbr, gI.skinOrder);
  save.writeFile(tmp);
}

int	Game::checkWin()
{
  int	j = 0;
  int	nb;
  for (int i = 0; i < 4; i++)
    if (player[i]->getIsAlive() == true)
      {
	nb = i;
	j++;
      }
  if (j == 1)
    {
      int	k = 0;
      for (int i = 0; i < 4; i++)
	if (player[i]->getDeathAnimStat() >= 1)
	  k++;
      if (k == 3)
	return nb;
    }
  if (j == 0)
    return 4;
  return -1;
}

int	Game::aceDisplay(Command *command)
{
  int	pause = 1;
  int	nb = checkWin();
  unsigned int tmp = map->getMapSize();

  irr::scene::ISceneNodeAnimator *anim =
    getSmgr()->createFlyCircleAnimator(irr::core::vector3df(tmp/2, tmp, tmp/3),10);
  cam->addAnimator(anim);
  anim->drop();
  Sound::getSound()->play("VoiceEvent/Ace.wav", 6);
  while (getWindow()->run() && pause == 1)
    {
      irr::core::stringw	fps = L"Bomberman ";
      fps += getDriver()->getFPS();
      getWindow()->setWindowCaption(fps.c_str());
      getDriver()->beginScene(true, true, irr::video::SColor(255,100,101,140));
      getSmgr()->drawAll();
      getGuienv()->drawAll();
      getDriver()->endScene();
      if (command->IsKeyDown(irr::KEY_RETURN) == true)
	(pause == 1) ? pause = 0 : 1;
    }
  endParty();
  Sound::getSound()->stopAll();
  return pause;
}

int	Game::victoryDisplay(Command *command)
{
  int	pause = 1;
  int	nb = checkWin();

  irr::scene::ISceneNodeAnimator *anim =
    getSmgr()->createFlyCircleAnimator(irr::core::vector3df(player[nb]->getPosition().X,
							    2,player[nb]->getPosition().Z), 2);
  cam->setTarget(player[nb]->getPosition());
  cam->addAnimator(anim);
  anim->drop();
  displayPlayer(player[nb]->getPosition(), player[nb]->getRotation(), nb, Action::WIN);
  Sound::getSound()->play("VoiceEvent/victoire.wav", 6);
  Sound::getSound()->play("lol.wav", 1, true);
  irr::video::ITexture		*victoire = getDriver()->getTexture("media/Victory.png");
  getGuienv()->addImage(victoire, irr::core::position2d<irr::s32>(getDriver()->getScreenSize().Width / 6, getDriver()->getScreenSize().Height / 6));
  while (getWindow()->run() && pause == 1)
    {
      irr::core::stringw	fps = L"Bomberman ";
      fps += getDriver()->getFPS();
      getWindow()->setWindowCaption(fps.c_str());
      getDriver()->beginScene(true, true, irr::video::SColor(255,100,101,140));
      getSmgr()->drawAll();
      getGuienv()->drawAll();
      getDriver()->endScene();
      if (command->IsKeyDown(irr::KEY_RETURN) == true)
	(pause == 1) ? pause = 0 : 1;
    }
  endParty();
  Sound::getSound()->stopAll();
  return pause;
}

void	Game::voiceEvent()
{
  int	tmpPAlive = 0;
  for (int i = 0; i < 4; i++)
    if (player[i]->getIsAlive() == true)
      tmpPAlive++;
  if (tmpPAlive < pAlive)
    {
      int	tmp = pAlive - tmpPAlive;
      pAlive = tmpPAlive;
      switch (tmp)
	{
	case 1 :
	  Sound::getSound()->play("VoiceEvent/mortSimple.wav", 8);
	  break;
	case 2 :
	  Sound::getSound()->play("VoiceEvent/Double.wav", 8);
	  break;
	case 3 :
	  Sound::getSound()->play("VoiceEvent/triple.wav", 8);
	  break;
	case 4 :
	  Sound::getSound()->play("VoiceEvent/Quadra.wav", 8);
	  break;
	}
    }
}

int	Game::play(Command *command)
{
  int	pause = 1;
  unsigned int tmp = map->getMapSize();
  int	checkWinPNb = -1;
  std::chrono::time_point<std::chrono::system_clock> start;
  int	voiceExec = 0;

  cam = getSmgr()->addCameraSceneNode(0, irr::core::vector3df(tmp/2, tmp,tmp/3), irr::core::vector3df(tmp/2,0,tmp/2));
  if (gI.loadSave == 1)
    {
      Sound::getSound()->play("WelcomeToTheRift.wav", 0, true);
      for (int i = 0; i < 4; i++)
	player[i]->setInPause(false);
    }
  else
    {
      for (int i = 0; i < 4; i++)
	player[i]->setInPause(true);
      Sound::getSound()->play("VoiceEvent/welcome.wav", 5);
      start = std::chrono::system_clock::now();
      introStat = 0;
    }
  while (getWindow()->run() && pause == 1 && checkWinPNb == -1)
    {
      irr::core::stringw	fps = L"Bomberman ";
      checkWinPNb = checkWin();
      fps += getDriver()->getFPS();
      getWindow()->setWindowCaption(fps.c_str());
      if (voiceExec >= 10)
	voiceExec = 0;
      if (voiceExec == 0)
	voiceEvent();
      playerRefreshNode();
      map->refreshNode(this);
      if (gI.loadSave == 0)
	{
	  std::chrono::time_point<std::chrono::system_clock> tNow = std::chrono::system_clock::now();
	  std::chrono::duration<double> diff = tNow - start;
	  if (diff.count() > 1)
	    {
	      introStat++;
	      start = std::chrono::system_clock::now();
	    }
	  irr::core::stringw tmp = L"";
	  switch (introStat)
	    {
	    case 0 :
	      tmp = L"3";
	      text(tmp, getDriver()->getScreenSize().Width / 2, 0);
	      break;
	    case 1 :
	      tmp = L"2";
	      text(tmp, getDriver()->getScreenSize().Width / 2, 0);
	      break;
	    case 2 :
	      tmp = L"1";
	      text(tmp, getDriver()->getScreenSize().Width / 2, 0);
	      break;
	    case 3 :
	      Sound::getSound()->play("VoiceEvent/startFight.wav", 5);
	      Sound::getSound()->play("WelcomeToTheRift.wav", 0, true);
	      for (int i = 0; i < 4; i++)
		player[i]->setInPause(false);
	      gI.loadSave = 1;
	      break;
	    }
	}
      getDriver()->beginScene(true, true, irr::video::SColor(255,100,101,140));
      getSmgr()->drawAll();
      getGuienv()->drawAll();
      getDriver()->endScene();
      getGuienv()->clear();
      if (command->IsKeyDown(irr::KEY_ESCAPE) == true)
	(pause == 1) ? pause = 2 : 1;
      voiceExec++;
    }
  for (int i = 0; i < 4; i++)
    player[i]->setInPause(true);
  if (checkWinPNb != -1 && checkWinPNb < 4)
    return victoryDisplay(command);
  if (checkWinPNb == 4)
    return aceDisplay(command);
  Sound::getSound()->stopAll();
  return pause;
}

void	Game::displaySpectate(int stat)
{
  int tmp = map->getMapSize();
  for (int i = 0; i < 13; i++)
    {
      if (decorNode[i] != nullptr)
	{
	  decorNode[i]->remove();
	  decorNode[i] = nullptr;
	}
    }
  if (stat >= 1)
    {
      decorNode[0] = displayNode(decor[1], Action::STATIC, irr::core::vector3df(-2, 0, tmp/2),
				 irr::core::vector3df(0, -90, 0),
				 irr::core::vector3df(1.5f, 1.5f, 1.5f));
      decorNode[1] = displayNode(decor[3], Action::STATIC, irr::core::vector3df(-2, 0, tmp),
				 irr::core::vector3df(0, -60, 0),
				 irr::core::vector3df(1.5f, 1.5f, 1.5f));
      decorNode[2] = displayNode(decor[5], Action::STATIC, irr::core::vector3df(tmp/2.5f, 0, tmp + 1),
				 irr::core::vector3df(0, 0, 0),
				 irr::core::vector3df(1.5f, 1.5f, 1.5f));
      decorNode[3] = displayNode(decor[7], Action::STATIC, irr::core::vector3df(tmp + 1, 0, tmp + 1),
				 irr::core::vector3df(0, 60, 0),
				 irr::core::vector3df(1.5f, 1.5f, 1.5f));
      decorNode[4] = displayNode(decor[8], Action::STATIC, irr::core::vector3df(-2, 0, -1),
				 irr::core::vector3df(0, -120, 0),
				 irr::core::vector3df(1, 1, 1));
      decorNode[5] = displayNode(decor[9], Action::STATIC, irr::core::vector3df(tmp + 1, 0, tmp/2),
				 irr::core::vector3df(0, 90, 0),
				 irr::core::vector3df(1.5f, 1.5f, 1.5f));
      decorNode[6] = displayNode(decor[11], Action::STATIC, irr::core::vector3df(tmp + 1, 0, 0),
				 irr::core::vector3df(0, 120, 0),
				 irr::core::vector3df(2, 2, 2));
    }
  if (stat >= 2)
    {
      decorNode[7] = displayNode(decor[12], Action::STATIC, irr::core::vector3df(tmp + 1, 0, tmp/5),
				 irr::core::vector3df(0, 120, 0),
				 irr::core::vector3df(2, 2, 2));
      decorNode[8] = displayNode(decor[10], Action::STATIC, irr::core::vector3df(tmp + 1, 0, tmp/1.5f),
				 irr::core::vector3df(0, 90, 0),
				 irr::core::vector3df(1, 1, 1));
      decorNode[8]->setLoopMode(false);
      
      decorNode[9] = displayNode(decor[6], Action::STATIC, irr::core::vector3df(tmp/1.5f, 0, tmp + 1),
				 irr::core::vector3df(0, 0, 0),
				 irr::core::vector3df(1.5f, 1.5f, 1.5f));
      decorNode[10] = displayNode(decor[4], Action::STATIC, irr::core::vector3df(tmp/4, 0, tmp + 1),
				  irr::core::vector3df(0, 0, 0),
				  irr::core::vector3df(1.5f, 1.5f, 1.5f));
      decorNode[11] = displayNode(decor[0], Action::STATIC, irr::core::vector3df(-2, 0, tmp/3),
				  irr::core::vector3df(0, -90, 0),
				  irr::core::vector3df(1.5f, 1.5f, 1.5f));
      decorNode[12] = displayNode(decor[2], Action::STATIC, irr::core::vector3df(-2, 0, tmp/1.5f),
				  irr::core::vector3df(0, -90, 0),
				  irr::core::vector3df(1.5f, 1.5f, 1.5f));
    }
}

int	Game::displayMap()
{
  int tmp = map->getMapSize();
  floor = displayNodeNoTex(stage, Action::STATIC, irr::core::vector3df(tmp + tmp/2, -tmp/1.45, -tmp /2),
		       irr::core::vector3df(0, 0, 0),
		       irr::core::vector3df(tmp, tmp, tmp));
  return (0);
}

void	Game::loadModel(t_model &model, std::string pathModel,
			std::string pathTexture)
{
  model.mesh.emplace(Action::STATIC, getSmgr()->getMesh(pathModel.c_str()));
  model.texture.push_back(getDriver()->getTexture(pathTexture.c_str()));
}

void	Game::loadZiggs(t_model &model, std::string path)
{
  model.mesh.emplace(Action::STATIC, getSmgr()->getMesh((path + "/Static.b3d").c_str()));
  model.mesh.emplace(Action::RUN, getSmgr()->getMesh((path + "/Run.b3d").c_str()));
  model.mesh.emplace(Action::ATTACK, getSmgr()->getMesh((path + "/Attack.b3d").c_str()));
  model.mesh.emplace(Action::DEATH, getSmgr()->getMesh((path + "/Death.b3d").c_str()));
  model.mesh.emplace(Action::WIN, getSmgr()->getMesh((path + "/Win.b3d").c_str()));
  model.texture.push_back(getDriver()->getTexture((path+"/skin.jpg").c_str()));
}

void	Game::loadWall(t_model &model, std::string path)
{
  model.mesh.emplace(Action::STATIC, getSmgr()->getMesh((path + "/idl.b3d").c_str()));
  model.mesh.emplace(Action::RUN, getSmgr()->getMesh((path + "/spawn.b3d").c_str()));
  model.texture.push_back(getDriver()->getTexture((path+"/barrel.jpg").c_str()));
}

void	Game::loadFloor(t_model &model, std::string path)
{
  model.mesh.emplace(Action::STATIC, getSmgr()->getMesh((path + "/map3.obj").c_str()));
}

void	Game::loadDecor(std::string path)
{
  decor[0].mesh.emplace(Action::STATIC, getSmgr()->getMesh((path + "/Amumu/amumu.b3d").c_str()));
  decor[0].texture.push_back(getDriver()->getTexture((path+"/Amumu/skin.png").c_str()));
  decor[1].mesh.emplace(Action::STATIC, getSmgr()->getMesh((path + "/AzirSoldier/soldier.b3d").c_str()));
  decor[1].texture.push_back(getDriver()->getTexture((path+"/AzirSoldier/skin.png").c_str()));
  decor[2].mesh.emplace(Action::STATIC, getSmgr()->getMesh((path + "/Bard/bard.b3d").c_str()));
  decor[2].texture.push_back(getDriver()->getTexture((path+"/Bard/skin.png").c_str()));
  decor[3].mesh.emplace(Action::STATIC, getSmgr()->getMesh((path + "/Blitzcrank/blitz.b3d").c_str()));
  decor[3].texture.push_back(getDriver()->getTexture((path+"/Blitzcrank/skin.png").c_str()));
  decor[4].mesh.emplace(Action::STATIC, getSmgr()->getMesh((path + "/Chogath/cho.b3d").c_str()));
  decor[4].texture.push_back(getDriver()->getTexture((path+"/Chogath/skin.png").c_str()));
  decor[5].mesh.emplace(Action::STATIC, getSmgr()->getMesh((path + "/Darius/darius.b3d").c_str()));
  decor[5].texture.push_back(getDriver()->getTexture((path+"/Darius/skin.png").c_str()));
  decor[6].mesh.emplace(Action::STATIC, getSmgr()->getMesh((path + "/Gnar/gnar.b3d").c_str()));
  decor[6].texture.push_back(getDriver()->getTexture((path+"/Gnar/skin.png").c_str()));
  decor[7].mesh.emplace(Action::STATIC, getSmgr()->getMesh((path + "/Gragas/gragas.b3d").c_str()));
  decor[7].texture.push_back(getDriver()->getTexture((path+"/Gragas/skin.png").c_str()));
  decor[8].mesh.emplace(Action::STATIC, getSmgr()->getMesh((path + "/HA_AP_Poro_Large/poroSleep.b3d").c_str()));
  decor[8].texture.push_back(getDriver()->getTexture((path+"/HA_AP_Poro_Large/skin.png").c_str()));
  decor[9].mesh.emplace(Action::STATIC, getSmgr()->getMesh((path + "/Kled/kled.b3d").c_str()));
  decor[9].texture.push_back(getDriver()->getTexture((path+"/Kled/skin.png").c_str()));
  //decor[9].texture.push_back(getDriver()->getTexture((path+"/Kled/skin1.png").c_str()));
  decor[10].mesh.emplace(Action::STATIC, getSmgr()->getMesh((path + "/KogMaw/kog.b3d").c_str()));
  decor[10].texture.push_back(getDriver()->getTexture((path+"/KogMaw/skin.png").c_str()));
  decor[11].mesh.emplace(Action::STATIC, getSmgr()->getMesh((path + "/MasterYi/yi.b3d").c_str()));
  decor[11].texture.push_back(getDriver()->getTexture((path+"/MasterYi/skin.png").c_str()));
  decor[12].mesh.emplace(Action::STATIC, getSmgr()->getMesh((path + "/Zilean/zilean.b3d").c_str()));
  decor[12].texture.push_back(getDriver()->getTexture((path+"/Zilean/skin.png").c_str()));
}

void	Game::displayAll()
{
  loadZiggs(skin[0], "media/ziggs/Default");
  loadZiggs(skin[1], "media/ziggs/Arcaniste");
  loadZiggs(skin[2], "media/ziggs/Major");
  loadZiggs(skin[3], "media/ziggs/PoolParty");
  loadWall(wall, "media/barrel");
  loadModel(bonus[0], "media/woodenBox.obj", "media/wodenBox1.png");
  loadModel(bonus[1], "media/woodenBox.obj", "media/wodenBox2.png");
  loadModel(bonus[2], "media/woodenBox.obj", "media/wodenBox3.png");
  loadModel(bonus[3], "media/woodenBox.obj", "media/wodenBox4.png");
  loadModel(bonus[4], "media/woodenBox.obj", "media/wodenBox5.png");
  loadModel(bonus[5], "media/woodenBox.obj", "media/wodenBox6.png");
  loadModel(bonus[6], "media/woodenBox.obj", "media/wodenBox7.png");
  loadModel(strongwall, "media/block/stones/obj/stone_3.obj", "media/block/stones/textures/Rock_02_UV_H_CM_1.jpg");
  loadModel(bomb[0], "media/classicBomb.md2", "media/classicBomb.png");
  loadModel(bomb[1], "media/classicBomb.md2", "media/atomicBomb.png");
  loadModel(bomb[2], "media/classicBomb.md2", "media/fragBomb.png");
  loadFloor(stage, "media/map/map1");
  loadDecor("media/Characters");
}

t_model &Game::getMeshBomb(const BombEffect &b)
{
  switch (b)
    {
    case BombEffect::NORMAL :
      return bomb[0];
    case BombEffect::AOE :
      return bomb[1];
    case BombEffect::LONG :
      return bomb[2];
    }
  return bomb[0];
}

t_model	&Game::getMeshBonus(const BonusType &b)
{
  switch (b)
    {
    case BonusType::BOMBM :
      return bonus[0];
    case BonusType::BOMBL :
      return bonus[1];
    case BonusType::EXPLENM :
      return bonus[2];
    case BonusType::EXPLENL :
      return bonus[3];
    case BonusType::PUSHBOMB :
      return bonus[4];
    case BonusType::MULEXP :
      return bonus[5];
    case BonusType::DELSW :
      return bonus[6];
    case BonusType::NORMALB :
      return bomb[0];
    case BonusType::AOEB :
      return bomb[1];
    case BonusType::LONGB :
      return bomb[2];
    }
  return bonus[5];
}

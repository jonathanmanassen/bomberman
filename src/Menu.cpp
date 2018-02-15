//
// Menu.cpp for Menu in /home/mei_c/rendu/cpp/cpp_indie_studio/src
// 
// Made by Christophe Mei
// Login   <mei_c@epitech.net>
// 
// Started on  Mon May 29 18:39:52 2017 Christophe Mei
// Last update Sun Jun 18 22:36:59 2017 Gabin Meyrieux-Drevet
//

#include <chrono>
#include "Menu.hpp"
#include "Sound.hpp"

typedef	void	(Menu::*menuFunc)();

Menu::Menu(irr::IrrlichtDevice *screen, Settings *_settings) : Display(screen, screen->getVideoDriver(), screen->getSceneManager(), screen->getGUIEnvironment(), _settings), settings(_settings)
{
  splashi = 91;
  standline = -1;
  keyboardline = 0;
  actualMenu = typeMenu::MAIN;
  gI.skinOrder[0] = 0;
  gI.skinOrder[1] = 1;
  gI.skinOrder[2] = 2;
  gI.skinOrder[3] = 3;
  gI.execCode = 1;
  gI.endParty = 0;
  gI.spectate = 0;
  resolution = screen->getVideoDriver()->getScreenSize();
  loadZiggs(skin[0], "media/ziggs/Default");
  loadZiggs(skin[1], "media/ziggs/Arcaniste");
  loadZiggs(skin[2], "media/ziggs/Major");
  loadZiggs(skin[3], "media/ziggs/PoolParty");
  for (int i = 0; i < 4; i++)
    pNode[i] = nullptr;
  tmp.push_back(&Menu::mainB1);
  tmp.push_back(&Menu::mainB2);
  tmp.push_back(&Menu::mainB3);
  tmp.push_back(&Menu::mainB4);
  allMenu.emplace(typeMenu::MAIN, tmp);
  tmp.clear();
  tmp.push_back(&Menu::pauseB1);
  tmp.push_back(&Menu::pauseB2);
  tmp.push_back(&Menu::pauseB3);
  tmp.push_back(&Menu::pauseB4);
  allMenu.emplace(typeMenu::PAUSE, tmp);
  tmp.clear();
  tmp.push_back(&Menu::optionB1);
  tmp.push_back(&Menu::optionB2);
  tmp.push_back(&Menu::optionB3);
  tmp.push_back(&Menu::optionB4);
  allMenu.emplace(typeMenu::OPTION, tmp);
  tmp.clear();
  tmp.push_back(&Menu::videoB1);
  tmp.push_back(&Menu::videoB2);
  tmp.push_back(&Menu::videoB3);
  tmp.push_back(&Menu::videoB4);
  allMenu.emplace(typeMenu::VIDEO, tmp);
  tmp.clear();
  tmp.push_back(&Menu::audioB1);
  tmp.push_back(&Menu::audioB2);
  tmp.push_back(&Menu::audioB3);
  tmp.push_back(&Menu::audioB4);
  allMenu.emplace(typeMenu::AUDIO, tmp);
  tmp.clear();
  tmp.push_back(&Menu::keyboard);
  tmp.push_back(&Menu::keyboard);
  tmp.push_back(&Menu::keyboard);
  tmp.push_back(&Menu::keyboard);
  allMenu.emplace(typeMenu::KEYBOARD, tmp);
  tmp.clear();
  tmp.push_back(&Menu::launchSkinSelection);
  tmp.push_back(&Menu::launchSkinSelection);
  tmp.push_back(&Menu::launchSkinSelection);
  tmp.push_back(&Menu::launchSkinSelection);
  allMenu.emplace(typeMenu::PLAY, tmp);
  tmp.clear();
  tmp.push_back(&Menu::load);
  tmp.push_back(&Menu::load);
  tmp.push_back(&Menu::load);
  tmp.push_back(&Menu::load);
  allMenu.emplace(typeMenu::LOAD, tmp);
  tmp.clear();
  tmp.push_back(&Menu::save);
  tmp.push_back(&Menu::save);
  tmp.push_back(&Menu::save);
  tmp.push_back(&Menu::save);
  allMenu.emplace(typeMenu::SAVE, tmp);
  tmp.clear();
}

gameInstruction	Menu::mainMenu(Command *command, int pause)
{
  std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();
  SMouseState mouse = command->getMouseState();

  command->setMouseTime(start);
  command->setMouseState(0);
  menuLaunch = 1;
  menuPause = pause;
  standline = -1;
  gI.loadSave = 0;
  keyboardline = 0;
  if (menuPause == 0)
    actualMenu = typeMenu::MAIN;
  else
    actualMenu = typeMenu::PAUSE;
  Sound::getSound()->play("VengefulMaelstrom.wav", 0, true);
  Sound::getSound()->play("intro1.wav", 1);
  while (getWindow()->run() && menuLaunch)
    {
      std::chrono::time_point<std::chrono::system_clock> tNow = std::chrono::system_clock::now();
      std::chrono::duration<double> diff = tNow - start;
      std::chrono::duration<double> diffmouse = tNow - command->getMouseTime();
      if (actualMenu != typeMenu::MAIN)
	command->setMouseTime(tNow);
      if (diffmouse.count() > 10 && actualMenu == typeMenu::MAIN)
	{
	  gI.loadSave = 0;
	  gI.playerNbr = 0;
	  gI.endParty = 0;
	  gI.execCode = 1;
	  menuLaunch = 0;
	}
      if (diff.count() > 10)
	{
	  Sound::getSound()->play("menuLong.wav", 1);
	  start = std::chrono::system_clock::now();
	}
      if (command->getMouseState().state == 1)
	Sound::getSound()->play("bouton.mp3", 1);
      irr::core::stringw        fps = L"Bomberman ";
      fps += getDriver()->getFPS();
      getWindow()->setWindowCaption(fps.c_str());
      getGuienv()->clear();
      if (menuPause == 0 && actualMenu != typeMenu::SELECTPLAYER)
	{
	  getGuienv()->addImage(getDriver()->getTexture("media/wall.jpg"), irr::core::position2d<irr::s32>(0,0));
	  getGuienv()->addImage(getDriver()->getTexture("media/bombermanlogo.png"), irr::core::position2d<irr::s32>(0,0));
	}
      else if (menuPause == 0)
	getGuienv()->addImage(getDriver()->getTexture("media/wallselectplayer.png"), irr::core::position2d<irr::s32>(0,0));
      displayAll(command);
      if (splashi < 149)
	{
	  std::string	image = "media/bombermansplashscreen/bombermansplashscreen";

	  if (splashi < 10)
	    image += "0000";
	  else if (splashi < 100)
	    image += "000";
	  else
	    image += "00";
	  image += std::to_string(splashi);
	  image += ".png";
	  getGuienv()->addImage(getDriver()->getTexture(image.c_str()), irr::core::position2d<irr::s32>(0,0));
	  splashi += 2;
	}
      getGuienv()->addImage(getDriver()->getTexture("media/cursor.png"), irr::core::position2d<irr::s32>(command->getMousePosition().X, command->getMousePosition().Y));
      getDriver()->beginScene(true, true, irr::video::SColor(255,120,120,120));
      getSmgr()->drawAll();
      getGuienv()->drawAll();
      getDriver()->endScene();
      if (command->IsKeyDown(irr::KEY_ESCAPE) == true)
	{
	  gI.loadSave = 0;
	  if (menuPause == 0)
	    actualMenu = typeMenu::MAIN;
	  else
	    actualMenu = typeMenu::PAUSE;
	  for (int i = 0; i < 4; i++)
	    if (pNode[i] != nullptr)
	      {
		pNode[i]->remove();
		pNode[i] = nullptr;
	      }
	}
    }
  Sound::getSound()->stopAll();  
  Sound::getSound()->play("startGame1.wav", 0);
  getGuienv()->clear();
  return gI;
}

void	Menu::selectPlayerSkin(int player, int k)
{
  int	max;

  max = 4;
  if (k == 0)
    {
      gI.skinOrder[player] -= 1;
      if (gI.skinOrder[player] < 0)
	gI.skinOrder[player] = max - 1;
    }
  else if (k == 1)
    {
      gI.skinOrder[player] += 1;
      if (gI.skinOrder[player] == max)
	gI.skinOrder[player] = 0;
    }
  irr::core::vector3df pos;
  switch (player)
    {
    case 0:
      pos = irr::core::vector3df(-3.2, 30.3, -2.5);
      break;
    case 1:
      pos = irr::core::vector3df(-3.2, 30.3, 2.5);
      break;
    case 2:
      pos = irr::core::vector3df(-3.2, 28.3, -2.5);
      break;
    case 3:
      pos = irr::core::vector3df(-3.2, 28.3, 2.5);
      break;
    }
  const irr::core::vector3df &rot = irr::core::vector3df(0, -90, 0);
  if (k != -1)
    {
      pNode[player]->remove();
      pNode[player] = nullptr;
    }
  pNode[player] = getSmgr()->addAnimatedMeshSceneNode(skin[gI.skinOrder[player]].mesh.at(Action::STATIC), 0, -1, pos, rot, irr::core::vector3df(1, 1, 1));
  if (pNode[player])
    {
      pNode[player]->setMaterialFlag(irr::video::EMF_LIGHTING, false);
      for (int	j = 0; j < skin[gI.skinOrder[player]].texture.size(); j++)
	{
	  if (skin[gI.skinOrder[player]].texture.at(j))
	    pNode[player]->setMaterialTexture(0, skin[gI.skinOrder[player]].texture.at(j));
	  else
	    exit(0);
	}
      pNode[player]->setAnimationSpeed(20);
    }
  else
    exit(0);
  irr::scene::ISceneNodeAnimator* ani= getSmgr()->createRotationAnimator(irr::core::vector3df(0,1,0));
  pNode[player]->addAnimator(ani);
  ani->drop();
}

void	Menu::displayStartParty(Command *command)
{
  SMouseState mouse = command->getMouseState();
  int	posx = resolution.Width / 2 - 498 / 2;
  int	posy = resolution.Height - 100;

  if (mouse.Position.X > posx && mouse.Position.X < posx + 498 && mouse.Position.Y > posy && mouse.Position.Y < posy + 88 && mouse.LeftButtonDown == true)
    {
      addButton("C'est parti !", posx, posy, 2);
      if (mouse.state == 0)
	command->setMouseState(1);
    }
  else if (mouse.Position.X > posx && mouse.Position.X < posx + 498 && mouse.Position.Y > posy && mouse.Position.Y < posy + 88)
    {
      addButton("C'est parti !", posx, posy, 1);
      switch (mouse.state)
	{
	case 1:
	  command->setMouseState(0);
	  for (int i = 0; i < 4; i++)
	    {
	      pNode[i]->remove();
	      pNode[i] = nullptr;
	    }
	  menuLaunch = 0;
	  break;
	}
    }
  else
    addButton("C'est parti !", posx, posy, 0);
}

void	Menu::displaySelectPlayer(Command *command)
{
  SMouseState mouse = command->getMouseState();

  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 2; j++)
      for (int k = 0; k < 2; k++)
	{
	  if (mouse.Position.X > 615 + j * 600 && mouse.Position.X < 615 + 88 + j * 600 && mouse.Position.Y > 200 + i * 500 + k * 100 && mouse.Position.Y < 200 + 88 + i * 500 + k * 100 && mouse.LeftButtonDown == true)
	    {
	      addButtonSquare((k == 0) ? "^" : "v", 615 + j * 600, 200 + i * 500 + k * 100, 2);
	      if (mouse.state == 0)
		command->setMouseState(1);
	    }
	  else if (mouse.Position.X > 615 + j * 600 && mouse.Position.X < 615 + 88 + j * 600 && mouse.Position.Y > 200 + i * 500 + k * 100 && mouse.Position.Y < 200 + 88 + i * 500 + k * 100)
	    {
	      addButtonSquare((k == 0) ? "^" : "v", 615 + j * 600, 200 + i * 500 + k * 100, 1);
	      switch (mouse.state)
		{
		case 1:
		  command->setMouseState(0);
		  switch (i)
		    {
		    case 0:
		      selectPlayerSkin(j, k);
		      break;
		    case 1:
		      selectPlayerSkin(j + 2, k);
		      break;
		    }
		  break;
		}
	    }
	  else
	    addButtonSquare((k == 0) ? "^" : "v", 615 + j * 600, 200 + i * 500 + k * 100, 0);
	}
}

void	Menu::displayAudioMenu(Command *command)
{
  SMouseState mouse = command->getMouseState();
  int	posx = resolution.Width / 2 - 498 / 2 + 510;
  int	posy = resolution.Height / 2 - 200;

  if (menuPause == 0)
    {
      posx = 130 + 510;
      posy = 500;
    }
  for (int i = 0; i < 2; i++)
    for (int j = 0; j < 2; j++)
      {
	if ((mouse.Position.X > posx + j * 100 && mouse.Position.X < posx + 88 + j * 100 && mouse.Position.Y > posy + 100 * i) && mouse.Position.Y < posy + 88 + 100 * i && mouse.LeftButtonDown == true)
	  {
	    addButtonSquare((j == 0) ? "-" : "+", posx + j * 100, posy + i * 100, 2);
	    if (mouse.state == 0)
	      command->setMouseState(1);
	  }
	else if ((mouse.Position.X > posx + j * 100 && mouse.Position.X < posx + 88 + j * 100 && mouse.Position.Y > posy + 100 * i) && mouse.Position.Y < posy + 88 + 100 * i)
	  {
	    addButtonSquare((j == 0) ? "-" : "+", posx + j * 100, posy + i * 100, 1);
	    switch (mouse.state)
	      {
	      case 1:
		command->setMouseState(0);
		switch (i)
		  {
		  case 0:
		    settings->setVolMusic((j) ? 10 : -10);
		    Sound::getSound()->setVolumeMusic(settings->getVolMusic());
		    break;
		  case 1:
		    settings->setVolEffects((j) ? 10 : -10);
		    Sound::getSound()->setVolumeEffects(settings->getVolEffects());
		  }
	      }
	  }
	else
	  addButtonSquare((j == 0) ? "-" : "+", posx + j * 100, posy + i * 100, 0);
      }
}

void	Menu::displayKeyboardChange(int player, Command *command)
{
  irr::EKEY_CODE tc;
  int	posx = resolution.Width / 2 - 300;
  int	posy = resolution.Height / 2;

  if (menuPause == 0)
    {
      posx = 130;
      posy = 600;
    }
  addButtonSquare("^", posx + 100, posy - 100, (keyboardline == 0) ? 1 : 0);
  addButtonSquare("<", posx, posy, (keyboardline == 1) ? 1 : 0);
  addButtonSquare("v", posx + 100, posy, (keyboardline == 2) ? 1 : 0);
  addButtonSquare(">", posx + 200, posy, (keyboardline == 3) ? 1 : 0);
  addButtonSquare("A", posx + 400, posy, (keyboardline == 4) ? 1 : 0);
  addButtonSquare("B", posx + 500, posy, (keyboardline == 5) ? 1 : 0);

  tc = command->getKey();
  switch (keyboardline)
    {
      if (tc != irr::KEY_KEY_CODES_COUNT)
	{
	case 0:
	  command->getPCom()[player]->setUp(tc);
	  break;
	case 1:
	  command->getPCom()[player]->setLeft(tc);
	  break;
	case 2:
	  command->getPCom()[player]->setDown(tc);
	  break;
	case 3:
	  command->getPCom()[player]->setRight(tc);
	  break;
	case 4:
	  command->getPCom()[player]->setBack(tc);
	  break;
	case 5:
	  command->getPCom()[player]->setBomb(tc);
	  break;
	}
    case 6:
      Sound::getSound()->play("changecommand.wav");
      actualMenu = typeMenu::OPTION;
      keyboardline = 0;
      break;
    }
  if (tc != irr::KEY_KEY_CODES_COUNT && keyboardline < 6 && keyboardline >= 0)
    keyboardline++;
}

void	Menu::displayDefaultMenu(const std::vector<irr::core::stringw> &list, Command *command)
{
  SMouseState mouse = command->getMouseState();
  int	posx = resolution.Width / 2 - 498 / 2;
  int	posy = resolution.Height / 2 - 200;

  bNb = 0;
  if (menuPause == 0)
    {
      posx = 130;
      posy = 500;
    }
  for(irr::core::stringw const &tmp : list)
    {
      if ((mouse.Position.X > posx && mouse.Position.X < posx + 498 && mouse.Position.Y > posy + 100 * bNb) && mouse.Position.Y < posy + 88 + 100 * bNb && mouse.LeftButtonDown == true)
	{
	  addButton(tmp, posx, posy + 100 * bNb, 2);
	  if (mouse.state == 0)
	    command->setMouseState(1);
	}
      else if (bNb == standline || (mouse.Position.X > posx && mouse.Position.X < posx + 498 && mouse.Position.Y > posy + 100 * bNb) && mouse.Position.Y < posy + 88 + 100 * bNb )
	{
	  addButton(tmp, posx, posy + 100 * bNb, 1);
	  if (mouse.state == 1)
	    {
	      command->setMouseState(0);
	      (*this.*allMenu.at(actualMenu).at(bNb))();
	    }
	}
      else
	addButton(tmp, posx, posy + 100 * bNb, 0);
      bNb++;
    }
}

void	Menu::launchSkinSelection()
{
  getSmgr()->addCameraSceneNode(0,
				irr::core::vector3df(0, 30, 0),
				irr::core::vector3df(-90, 30, 0));
  for (int i = 0; i < 4; i++)
    selectPlayerSkin(i, -1);
  actualMenu = typeMenu::SELECTPLAYER;
  gI.playerNbr = bNb + 1;
  gI.endParty = 0;
  gI.execCode = 1;
}

void	Menu::load()
{
  std::string tmp = "save"+std::to_string(bNb+1);
  if (fileExist(tmp) == true)
    {
      menuLaunch = 0;
      gI.endParty = 0;
      gI.execCode = 1;
      gI.saveNbr = bNb + 1;
    }
}

void	Menu::displayAll(Command *command)
{
  std::vector<irr::core::stringw>	list;

  switch (actualMenu)
    {
    case typeMenu::MAIN :
      list.push_back(L"Nouvelle partie");
      list.push_back(L"Charger une partie");
      list.push_back(L"Options");
      list.push_back(L"Quitter le jeu");
      break;
    case typeMenu::PAUSE :
      list.push_back(L"Reprendre");
      list.push_back(L"Sauvegarder");
      list.push_back(L"Options");
      list.push_back(L"Quitter la partie");
      break;
    case typeMenu::LOAD :
      (fileExist("save1") == true) ? list.push_back(L"Partie n°1") : (list.push_back(L"Empty"));
      (fileExist("save2") == true) ? list.push_back(L"Partie n°2") : (list.push_back(L"Empty"));
      (fileExist("save3") == true) ? list.push_back(L"Partie n°3") : (list.push_back(L"Empty"));
      (fileExist("save4") == true) ? list.push_back(L"Partie n°4") : (list.push_back(L"Empty"));
      break;
    case typeMenu::SAVE :
      (fileExist("save1") == true) ? list.push_back(L"Partie n°1") : (list.push_back(L"Empty"));
      (fileExist("save2") == true) ? list.push_back(L"Partie n°2") : (list.push_back(L"Empty"));
      (fileExist("save3") == true) ? list.push_back(L"Partie n°3") : (list.push_back(L"Empty"));
      (fileExist("save4") == true) ? list.push_back(L"Partie n°4") : (list.push_back(L"Empty"));
      break;
    case typeMenu::OPTION :
      list.push_back(L"Vidéo");
      list.push_back(L"Audio");
      list.push_back(L"Commandes");
      list.push_back(L"Retour");
      break;
    case typeMenu::PLAY :
      list.push_back(L"Un joueur");
      list.push_back(L"Deux joueurs");
      list.push_back(L"Trois joueurs");
      list.push_back(L"Quatre joueurs");
      break;
    case typeMenu::KEYBOARD :
      list.push_back(L"Joueur 1");
      list.push_back(L"Joueur 2");
      list.push_back(L"Joueur 3");
      list.push_back(L"Joueur 4");
      break;
    case typeMenu::VIDEO :
      switch (settings->getResolution())
	{
	case 0:
	  list.push_back(L"Résolution : 720 x 480");
	  break;
	case 1:
	  list.push_back(L"Résolution : 800 x 640");
	  break;
	case 2:
	  list.push_back(L"Résolution : 1280 x 720");
	  break;
	case 3:
	  list.push_back(L"Résolution : 1920 x 1080");
	}
      if (settings->getFullscreen() == true)
	list.push_back(L"Plein écran : oui");
      else
	list.push_back(L"Plein écran : non");
      switch (gI.spectate)
	{
	case 0 :
	  list.push_back(L"Désactivé");
	  break;
	case 1 :
	  list.push_back(L"Moitié");
	  break;
	case 2 :
	  list.push_back(L"Tous");
	  break;
	}
      list.push_back(L"Retour");
      break;
    case typeMenu::AUDIO :
      irr::core::stringw	volMusic = L"Volume musique : ";
      volMusic += settings->getVolMusic();
      volMusic += " %";
      list.push_back(volMusic);
      irr::core::stringw	volEffects = L"Volume effets : ";
      volEffects += settings->getVolEffects();
      volEffects += " %";
      list.push_back(volEffects);
      list.push_back(L"");
      list.push_back(L"Retour");
      break;
    };

  switch (actualMenu)
    {
    case typeMenu::KEYBOARDCHANGE :
      displayKeyboardChange(keyboardchangeplayer, command);
      break;
    case typeMenu::SELECTPLAYER :
      displaySelectPlayer(command);
      displayStartParty(command);
      break;
    case typeMenu::AUDIO :
      displayDefaultMenu(list, command);
      displayAudioMenu(command);
      break;
    default:
      displayDefaultMenu(list, command);
    }
}

void	Menu::loadZiggs(t_model &model, std::string path)
{
  model.mesh.emplace(Action::STATIC, getSmgr()->getMesh((path + "/Static.b3d").c_str()));
  model.mesh.emplace(Action::RUN, getSmgr()->getMesh((path + "/Run.b3d").c_str()));
  model.mesh.emplace(Action::ATTACK, getSmgr()->getMesh((path + "/Attack.b3d").c_str()));
  model.mesh.emplace(Action::DEATH, getSmgr()->getMesh((path + "/Death.b3d").c_str()));
  model.mesh.emplace(Action::WIN, getSmgr()->getMesh((path + "/Win.b3d").c_str()));
  model.texture.push_back(getDriver()->getTexture((path+"/skin.jpg").c_str()));
}

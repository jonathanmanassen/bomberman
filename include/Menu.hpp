//
// Menu.hpp for Menu in /home/mei_c/rendu/cpp/cpp_indie_studio/include
// 
// Made by Christophe Mei
// Login   <mei_c@epitech.net>
// 
// Started on  Mon May 29 18:38:17 2017 Christophe Mei
// Last update Sun Jun 18 20:51:29 2017 Christophe Mei
//

#ifndef MENU_H_
# define MENU_H_

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <irrlicht.h>
#include "Display.hpp"
#include "Command.hpp"
#include "Settings.hpp"
#include "struct.hpp"
#include "enum.hpp"

class	Menu : public Display
{
  typedef	void	(Menu::*menuFunc)();
  std::vector<menuFunc> tmp;
  std::map<typeMenu,std::vector<void (Menu::*)()>> allMenu;
  Settings	*settings;
  t_model	skin[4];
  int		menuLaunch;
  int		menuPause;
  int		standline;
  int		splashi;
  typeMenu	actualMenu;
  int		keyboardline;
  int		keyboardchangeplayer;
  gameInstruction gI;
  int	bNb;
  irr::scene::IAnimatedMeshSceneNode	*pNode[4];
  irr::core::dimension2d<irr::u32>	resolution;
public:
  Menu(irr::IrrlichtDevice*, Settings*);
  gameInstruction	mainMenu(Command *command, int pause);
  void	displayDefaultMenu(const std::vector<irr::core::stringw>&, Command *command);
  void	displayKeyboardChange(int player, Command *command);
  virtual void	displayAll(){}
  virtual void	displayAll(Command *command);
  void	displayAudioMenu(Command *command);
  void	displaySelectPlayer(Command *command);
  void	displayStartParty(Command *command);
  void	selectPlayerSkin(int player, int k);
  void	loadZiggs(t_model &model, std::string path);

  void	mainB1() {actualMenu = typeMenu::PLAY;}
  void	mainB2() {actualMenu = typeMenu::LOAD;gI.loadSave = 1;}
  void	mainB3() {actualMenu = typeMenu::OPTION;}
  void	mainB4() {getWindow()->drop();exit(0);}
  void	pauseB1() {menuLaunch = 0;gI.endParty = 0;}
  void	pauseB2() {actualMenu = typeMenu::SAVE;gI.loadSave = 1;}
  void	pauseB3() {actualMenu = typeMenu::OPTION;}
  void	pauseB4() {menuLaunch = 0;gI.endParty = 1;gI.execCode = 0;}
  void	optionB1() {actualMenu = typeMenu::VIDEO;}
  void	optionB2() {actualMenu = typeMenu::AUDIO;}
  void	optionB3() {actualMenu = typeMenu::KEYBOARD;}
  void	optionB4() { (menuPause == 0) ? actualMenu = typeMenu::MAIN : (actualMenu = typeMenu::PAUSE);}
  void	videoB1() {settings->setResolutionNext();}
  void	videoB2() {settings->setFullscreenNext();}
  void	videoB3() {gI.spectate++;if (gI.spectate > 2)gI.spectate = 0;}
  void	videoB4() {actualMenu = typeMenu::OPTION;}
  void	audioB1() {}
  void	audioB2() {}
  void	audioB3() {}
  void	audioB4() {actualMenu = typeMenu::OPTION;}
  void	load();
  void	save() {menuLaunch = 0;gI.saveNbr = bNb + 1;}
  void	keyboard() {actualMenu = typeMenu::KEYBOARDCHANGE;keyboardchangeplayer = bNb;}
  void	launchSkinSelection();
  
  bool	fileExist(std::string const &file) {std::ifstream f(file.c_str());return f.good();}
};

#endif /* MENU_H_ */

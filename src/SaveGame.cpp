//
// SaveGame.cpp for indieStudio in /home/meyrie_g/rendu/cpp_indie_studio
// 
// Made by Gabin Meyrieux-Drevet
// Login   <meyrie_g@epitech.net>
// 
// Started on  Sun Jun 18 22:11:26 2017 Gabin Meyrieux-Drevet
// Last update Sun Jun 18 22:20:17 2017 Gabin Meyrieux-Drevet
//

#include "SaveGame.hpp"

SaveGame::SaveGame(Map *_map, Player **_player, int pNb, int *skinOrder)
{
  save.map = _map->getSaveMap(*_map);
  save.mapSize = _map->getMapSize();
  int	i;
  for (i = 0; i < 4; i++)
    {
      save.pPos[i] = _player[i]->getPosition();
      save.pRot[i] = _player[i]->getRotation();
      save.isAlive[i] = _player[i]->getIsAlive();
      save.pBonus[i] = _player[i]->getBonus()->getBonus();
      save.skinOrder[i] = skinOrder[i];
      if (i < pNb)
	save.isHuman[i] = true;
      else
	save.isHuman[i] = false;
    }
}

void	SaveGame::loadFile(std::string const &file)
{
  std::ifstream input(file,std::ios::binary);
  input.read(reinterpret_cast<char*>(&save.mapSize),sizeof(save.mapSize));
  save.map = new saveMap*[save.mapSize];
  for (int i = 0; i < save.mapSize; i++)
    save.map[i] = new saveMap[save.mapSize];
  for (int i = 0; i < save.mapSize; i++)
    for (int j = 0; j < save.mapSize; j++)
      input.read(reinterpret_cast<char*>(&save.map[i][j]),sizeof(save.map[i][j]));
  for (int i = 0; i < 4; i++)
    {
      input.read(reinterpret_cast<char*>(&save.pPos[i]),sizeof(save.pPos[i]));
      input.read(reinterpret_cast<char*>(&save.pRot[i]),sizeof(save.pRot[i]));
      input.read(reinterpret_cast<char*>(&save.isAlive[i]),sizeof(save.isAlive[i]));
      input.read(reinterpret_cast<char*>(&save.isHuman[i]),sizeof(save.isHuman[i]));
      input.read(reinterpret_cast<char*>(&save.pBonus[i]),sizeof(save.pBonus[i]));
      input.read(reinterpret_cast<char*>(&save.skinOrder[i]),sizeof(save.skinOrder[i]));
    }
  input.close();
}

void	SaveGame::writeFile(std::string const &file)
{
  std::ofstream output(file,std::ios::binary);
    
  output.write(reinterpret_cast<char*>(&save.mapSize),sizeof(save.mapSize));
  for (int i = 0; i < save.mapSize; i++)
    for (int j = 0; j < save.mapSize; j++)
      output.write(reinterpret_cast<char*>(&save.map[i][j]),sizeof(save.map[i][j]));
  for (int i = 0; i < 4; i++)
    {
      output.write(reinterpret_cast<char*>(&save.pPos[i]),sizeof(save.pPos[i]));
      output.write(reinterpret_cast<char*>(&save.pRot[i]),sizeof(save.pRot[i]));
      output.write(reinterpret_cast<char*>(&save.isAlive[i]),sizeof(save.isAlive[i]));
      output.write(reinterpret_cast<char*>(&save.isHuman[i]),sizeof(save.isHuman[i]));
      output.write(reinterpret_cast<char*>(&save.pBonus[i]),sizeof(save.pBonus[i]));
      output.write(reinterpret_cast<char*>(&save.skinOrder[i]),sizeof(save.skinOrder[i]));
    }
  output.close();
}

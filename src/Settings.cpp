//
// Settings.cpp for indieStudio in /home/meyrie_g/rendu/cpp_indie_studio
// 
// Made by Gabin Meyrieux-Drevet
// Login   <meyrie_g@epitech.net>
// 
// Started on  Tue May 16 15:02:29 2017 Gabin Meyrieux-Drevet
// Last update Sun Jun 18 19:06:40 2017 Gabin Meyrieux-Drevet
//

#include <fstream>
#include <cstdlib>
#include "Settings.hpp"

void	Settings::parseSettings(std::string const &fileName)
{
  std::ifstream file (fileName);

  if (file.is_open())
    {
      for (int i = 0; i < 5; i++)
	{
	  int		j = 0;
	  std::string	line;
	  getline(file, line);
	  while (j < line.size() && line[j] != ' ')
	    j++;
	  winSize.x = std::atoi(line.substr(0, j).c_str());
	  winSize.y = std::atoi(line.substr(j, line.size()).c_str());
	}
      file.close();
    }
  else
    {
      winSize.x = 1920;
      winSize.y = 1080;
    }
  volMusic = 100;
  volEffects = 100;
}

Settings::Settings(std::string const &fileName)
{
  parseSettings(fileName);
}

Settings::~Settings()
{
  std::ofstream file ("Settings", std::ios::out | std::ios::trunc);
  if (file.bad())
    return;
  file << winSize.x << " " << winSize.y << std::endl;
  file.close();
}

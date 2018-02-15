//
// Score.cpp for indieStudio in /home/meyrie_g/rendu/cpp_indie_studio
// 
// Made by Gabin Meyrieux-Drevet
// Login   <meyrie_g@epitech.net>
// 
// Started on  Tue May 16 15:02:29 2017 Gabin Meyrieux-Drevet
// Last update Thu Jun 15 14:47:30 2017 jonathan manassen
//

#include <fstream>
#include <cstdlib>
#include "Score.hpp"

void	Score::parseScore(std::string const &fileName)
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
	  HSName.push_back(line.substr(0, j));
	  HSPoint.push_back(std::atoi(line.substr(j, line.size()).c_str()));
	}
      file.close();
    }
}

Score::Score(std::string const &fileName)
{
  parseScore(fileName);
}

Score::~Score()
{
  std::ofstream file ("HighScore", std::ios::out | std::ios::trunc);
  for (int i = 0; i < HSPoint.size(); i++)
    {
      if (score > HSPoint[i] && newHighScore == 0)
	{
	  for (int j = HSPoint.size() - 1; j > i; j--)
	    {
	      HSPoint[j] = HSPoint[j - 1];
	      HSName[j] = HSName[j - 1];
	    }
	  HSPoint[i] = score;
	  HSName[i] = curName;
	  break;
	}
    }
  if (file.bad())
    return;
  for (int i = 0; i < HSPoint.size(); i++)
    file << HSName[i] << " " << HSPoint[i] << std::endl;
  HSPoint.clear();
  HSName.clear();
  file.close();
}

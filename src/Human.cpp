//
// Human.cpp for bomberman in /home/manass_j/rendu/cpp_indie_studio
// 
// Made by jonathan manassen
// Login   <manass_j@epitech.net>
// 
// Started on  Thu Jun 15 15:26:01 2017 jonathan manassen
// Last update Sun Jun 18 17:18:24 2017 jonathan manassen
//

#include "Human.hpp"

Human::Human(Map *m, int pNb) : Player(m, pNb) {}

extern	int	pBomb[4];

void	Human::play(Game *game, Command *command, Map *map)
{
  while (isAlive == true)
    {
      if (inPause == false)
	{
	  cA = command->getCommand(pNb);
	  setAction(map);
	  cA = command->getCommand(pNb, 0, true);
	  setPosRot(game, map, cA, true);
	}
    }
  if (deathAnimStat == 0)
    {
      Sound::getSound()->play("death.wav", 2);
      while (deathAnimStat < 2);
    }
}

void	Human::initPlay(Game *game, Command *command, Map *map)
{
  then = game->getWindow()->getTimer()->getTime();
  t = std::thread(&Human::play, this, game, command, map);
}

//
// player.hpp for bomberman in /home/manass_j/rendu/cpp_indie_studio/include
// 
// Made by jonathan manassen
// Login   <jonathan.manassen@epitech.eu@epitech.net>
// 
// Started on  Tue May 16 13:23:04 2017 jonathan manassen
// Last update Thu Jun 15 18:19:30 2017 jonathan manassen
//

#ifndef HUMAN_HPP_
# define HUMAN_HPP_

#include "Command.hpp"
#include "Player.hpp"

class	Game;
class	Map;

class	Human : public Player
{
public:
  Human(Map*, int);
  virtual ~Human() {}
  virtual void	play(Game*, Command*, Map*);
  void	initPlay(Game*, Command*, Map*);
};

#endif /* HUMAN_HPP_ */

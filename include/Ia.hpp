//
// player.hpp for bomberman in /home/manass_j/rendu/cpp_indie_studio/include
// 
// Made by jonathan manassen
// Login   <jonathan.manassen@epitech.eu@epitech.net>
// 
// Started on  Tue May 16 13:23:04 2017 jonathan manassen
// Last update Sun Jun 18 21:26:52 2017 jonathan manassen
//

#ifndef IA_HPP_
# define IA_HPP_

#include <stdbool.h>
#include "Command.hpp"
#include "Player.hpp"
#include "enum.hpp"

class	Game;
class	Map;

class	Ia : public Player
{
  std::map<int, CAction>	Dir;
public:
  Ia(Map*, int);
  virtual ~Ia() {}
  virtual void	play(Game*, Command*, Map*);
  void	initPlay(Game*, Command*, Map*);
  bool	check_around_wall(Map*);
  bool	no_more_walls(Map*);
  bool	canBombTouch(Map*);
  bool	closest_bomb(Map*, Game*);
  void	randomCmd();
  bool	bombxinf(const int&, const int&, Map*, Game*);
  bool	bombxsup(const int&, const int&, Map*, Game*);
  bool	checkMap(const int&, const int&, Map*);
  bool	correctDir(Map*, const int&, const int&, const int&);
};

#endif /* IA_HPP_ */

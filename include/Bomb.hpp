//
// Bomb.hpp for bomberman in /home/manass_j/rendu/cpp_indie_studio/include
// 
// Made by jonathan manassen
// Login   <jonathan.manassen@epitech.eu@epitech.net>
// 
// Started on  Tue May 16 13:23:04 2017 jonathan manassen
// Last update Sat Jun 17 21:40:24 2017 jonathan manassen
//

#ifndef BOMB_HPP_
# define BOMB_HPP_

#include <vector>
#include "Thread.hpp"
#include "Map.hpp"
#include "Bonus.hpp"
#include "stdbool.h"
#include "Sound.hpp"
#include "enum.hpp"

class	Map;

class	Bomb : public Thread
{
  std::chrono::time_point<std::chrono::system_clock> bExp;
  std::chrono::time_point<std::chrono::system_clock> bSpawn;
  std::chrono::time_point<std::chrono::system_clock> tNow;
  Bonus	bonus;
  Sound	*sound;
  BombStatus	stat;
  int	step;
  const int	posX;
  const int	posY;
  int	nbFire;
  std::vector<int>	mapFire;
  std::vector<std::pair<int, int>>	posFire;
public:
  Bomb(Bonus const &, Map*, const int&, const int&);
  virtual ~Bomb() {}
  virtual void	play(Map *map);
  BombStatus	timeDiff();
  void	init_vector(const int&);
  void	fireExpansion(Map*);
  bool	destroy_wall(const int&, const int&, Map*);

  void	incStep() {step++;}
  void	setStat(const BombStatus &_stat) {stat = _stat;}
  const BombEffect	&getBombEffect() const {return bonus.getBombEffect();}
  const bool	&getCanDelSW() const {return bonus.getCanDelSW();}
  const bool	&getCanDelMulW() const {return bonus.getCanDelMulW();}
  const int	&getStep() const {return step;}
  const int	&getExpLen() const {return bonus.getExpLen();}
  const BombStatus	&getStat() const {return stat;}
  const t_Bonus	&getBonus() const { return bonus.getBonus(); }
};

#endif /* BOMB_HPP_ */

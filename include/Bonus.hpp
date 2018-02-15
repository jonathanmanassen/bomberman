//
// Map.hpp for bomberman in /home/manass_j/cpp_indie_studio/include
// 
// Made by jonathan manassen
// Login   <jonathan.manassen@epitech.eu@epitech.net>
// 
// Started on  Mon May 15 13:01:46 2017 jonathan manassen
// Last update Sat Jun 17 21:42:04 2017 jonathan manassen
//

#ifndef BONUS_H_
# define BONUS_H_

#include <string>
#include <iostream>
#include <stdbool.h>
#include "struct.hpp"
#include "enum.hpp"

class	Bonus
{
  t_Bonus	bonus;
public:
  Bonus(int);
  void	incExpLen() {bonus.expLen++;}
  void	incBombNbr() {bonus.bombNbr++;}
  void	incBombLStack() {bonus.bombLStack*=2;}
  void	decExpLen() {if (bonus.expLen > 2)bonus.expLen--;}
  void	decBombNbr() {if (bonus.bombNbr > 1)bonus.bombNbr--;}
  void	activateDelSW() {bonus.canDelSW = true;}
  void	activateDelMulW() {bonus.canDelMulW = true;}
  void	activatePushBomb() {bonus.canPushB = true;}
  void	setBonus(const t_Bonus &b) { bonus = b;}
  void	setBombEffect(const BombEffect &bE) {bonus.bombEffect = bE;}
  const int	&getBombNbr() const { return bonus.bombNbr; }
  const int	&getExpLen() const { return bonus.expLen; }
  const int	&getBombLStack() const { return bonus.bombLStack; }
  const bool	&getCanDelSW() const { return bonus.canDelSW; }
  const bool	&getCanPushBomb() const { return bonus.canPushB; }
  const bool	&getCanDelMulW() const { return bonus.canDelMulW; }
  const BombEffect	&getBombEffect() const {return bonus.bombEffect;}
  const t_Bonus	&getBonus() { return bonus; }
  const t_Bonus	&getBonus() const { return bonus; }
  const int	&getPNb() const {return bonus.pNb;}
};

#endif /* BONUS_H_ */

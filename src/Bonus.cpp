//
// Bonus.cpp for indieStudio in /home/meyrie_g/rendu/cpp_indie_studio
// 
// Made by Gabin Meyrieux-Drevet
// Login   <meyrie_g@epitech.net>
// 
// Started on  Tue May 16 15:02:29 2017 Gabin Meyrieux-Drevet
// Last update Sat Jun 17 22:13:52 2017 jonathan manassen
//

#include "Bonus.hpp"

Bonus::Bonus(int _pNb)
{
  bonus.pNb = _pNb;
  bonus.expLen = 2;
  bonus.canDelSW = false;
  bonus.canDelMulW = false;
  bonus.canPushB = false;
  bonus.bombNbr = 1;
  bonus.bombEffect = BombEffect::NORMAL;
  bonus.bombLStack = 1;
}

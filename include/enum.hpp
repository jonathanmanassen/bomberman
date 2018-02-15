//
// enum.hpp for indieStudio in /home/meyrie_g/rendu/cpp_indie_studio
// 
// Made by Gabin Meyrieux-Drevet
// Login   <meyrie_g@epitech.net>
// 
// Started on  Sat May 27 15:55:59 2017 Gabin Meyrieux-Drevet
// Last update Sat Jun 17 21:59:51 2017 jonathan manassen
//

#ifndef ENUM_HPP_
# define ENUM_HPP_

enum class     CAction
  {
    NONE = 0,
    UP,
    DOWN,
    RIGHT,
    LEFT,
    DIAG_UR,
    DIAG_UL,
    DIAG_DL,
    DIAG_DR,
    BOMB,
    BACK
  };

enum class     Action
  {
    STATIC = 0,
    RUN,
    ATTACK,
    DEATH,
    WIN
  };

enum class Block
  {
    UNDEFINED = 0,
    WALL,
    BEDROCK,
    STRONG_WALL,
    AIR,
  };

enum class BlockStatus
  {
    UNDEFINED = 0,
    BOMB,
    FIRE,
    SAFE,
    BONUS,
  };

enum class BonusType
  {
    UNDEFINED = 0,
    BOMBM,
    BOMBL,
    EXPLENM,
    EXPLENL,
    MULEXP,
    DELSW,
    PUSHBOMB,
    NORMALB,
    AOEB,
    LONGB
  };

enum class      BombStatus
  {
    UNDEFINED = 0,
    TIMER,
    EXP,
    END
  };

enum class	BombEffect
  {
    UNDEFINED = 0,
    NORMAL,
    AOE,
    LONG,
  };

enum class	typeMenu
  {
    UNDEFINED = 0,
    MAIN,
    PAUSE,
    PLAY,
    LOAD,
    SAVE,
    OPTION,
    KEYBOARD,
    VIDEO,
    AUDIO,
    KEYBOARDCHANGE,
    SELECTPLAYER
  };

#endif /* ENUM_HPP_ */

//
// Ia.cpp for bomberman in /home/manass_j/rendu/cpp_indie_studio
// 
// Made by jonathan manassen
// Login   <manass_j@epitech.net>
// 
// Started on  Thu Jun 15 15:59:53 2017 jonathan manassen
// Last update Sun Jun 18 21:26:36 2017 jonathan manassen
//

#include <random>
#include "Ia.hpp"

extern std::random_device	generator;

Ia::Ia(Map *m, int pNb) : Player(m, pNb) {}

void	Ia::randomCmd()
{
  Dir.emplace(0, CAction::DIAG_UR);
  Dir.emplace(1, CAction::DIAG_UL);
  Dir.emplace(2, CAction::DIAG_DL);
  Dir.emplace(3, CAction::DIAG_DR);
  Dir.emplace(4, CAction::UP);
  Dir.emplace(5, CAction::DOWN);
  Dir.emplace(6, CAction::RIGHT);
  Dir.emplace(7, CAction::LEFT);
}

bool	Ia::check_around_wall(Map *map)
{
  int	i = static_cast<int>(pos.X + 0.5);
  int	j = static_cast<int>(pos.Z + 0.5);

  if ((map->getMapPiece(i + 1, j).block == Block::WALL || map->getMapPiece(i, j + 1).block == Block::WALL ||
       map->getMapPiece(i - 1, j).block == Block::WALL || map->getMapPiece(i, j - 1).block == Block::WALL) &&
      map->getMapPiece(i, j).bomb == nullptr)
    return (true);
  return (false);
}

bool	Ia::no_more_walls(Map *map)
{
  for (int i = 0; i < map->getMapSize(); i++)
    for (int j = 0; i < map->getMapSize(); j++)
      {
	if (map->getMapPiece(i, j).block == Block::WALL)
	  return (false);
      }
  return (true);
}

bool	Ia::canBombTouch(Map *map)
{
  int	i = static_cast<int>(pos.X + 0.5);
  int	j = static_cast<int>(pos.Z + 0.5);

  for (int l = 1; l < bonus->getExpLen(); l++)
    {
      if ((i + l < map->getMapSize() && map->getMapPiece(i + l, j).bomb != nullptr) ||
	  (j + l < map->getMapSize() && map->getMapPiece(i, j + l).bomb != nullptr) ||
	  (i - l > 0 && map->getMapPiece(i - l, j).bomb != nullptr) ||
	  (j - l > 0 && map->getMapPiece(i, j - l).bomb != nullptr) ||
	  map->getMapPiece(i, j).bomb != nullptr)
	return (true);
    }
  return (false);
}

bool	Ia::bombxinf(const int &bomby, const int &j, Map *map, Game *game)
{
  if (bomby < j)
    {
      if (setPosRot(game, map, cA = Dir[0], false) == false)
	if (setPosRot(game, map, cA = Dir[1], false) == false)
	  return (setPosRot(game, map, cA = Dir[3], false));
    }
  else if (bomby == j)
    {
      if (setPosRot(game, map, cA = Dir[0], false) == false)
	return (setPosRot(game, map, cA = Dir[1], false));
    }
  else
    {
      if (setPosRot(game, map, cA = Dir[0], false) == false)
	if (setPosRot(game, map, cA = Dir[1], false) == false)
	  return (setPosRot(game, map, cA = Dir[2], false));
    }
}

bool	Ia::bombxsup(const int &bomby, const int &j, Map *map, Game *game)
{
  if (bomby < j)
    {
      if (setPosRot(game, map, cA = Dir[3], false) == false)
	if (setPosRot(game, map, cA = Dir[0], false) == false)
	  return (setPosRot(game, map, cA = Dir[2], false));
    }
  else if (bomby == j)
    {
      if (setPosRot(game, map, cA = Dir[2], false) == false)
	return (setPosRot(game, map, cA = Dir[3], false));
    }
  else
    {
      if (setPosRot(game, map, cA = Dir[2], false) == false)
	if (setPosRot(game, map, cA = Dir[3], false) == false)
	  return (setPosRot(game, map, cA = Dir[1], false));
    }
}

bool	Ia::checkMap(const int &i, const int &j, Map *map)
{
  if (map->getMapPiece(i - 1, j).block == Block::WALL)
    return (true);
  return (false);
}

bool	Ia::correctDir(Map *map, const int &i, const int &j, const int &k)
{
  if ((Dir[k] == CAction::DIAG_DL && (checkMap(i - 1, j, map) || checkMap(i , j - 1, map) || checkMap(i - 1, j - 1, map))) ||
      (Dir[k] == CAction::DIAG_DR && (checkMap(i - 1, j + 1, map) || checkMap(i - 1, j, map) || checkMap(i, j + 1, map))) ||
      (Dir[k] == CAction::DIAG_UR && (checkMap(i, j + 1, map) || checkMap(i + 1, j, map) || checkMap(i + 1, j + 1, map))) ||
      (Dir[k] == CAction::DIAG_UL && (checkMap(i + 1, j, map) || checkMap(i + 1, j - 1, map) || checkMap(i, j - 1, map))))
    return (false);
  return (true);
}

bool	Ia::closest_bomb(Map *map, Game *game)
{
  int	i = static_cast<int>(pos.X + 0.5);
  int	j = static_cast<int>(pos.Z + 0.5);
  int	bombx = 0;
  int	bomby = 0;

  for (int k = i - 3; k <= (i + 3) && k < map->getMapSize(); k++)
    for (int l = j - 3; l <= (j + 3) && l < map->getMapSize(); l++)
      {
	if (k > 0 && l > 0 && (map->getMapPiece(k, l).bomb != nullptr || map->getMapPiece(k, l).bStat == BlockStatus::FIRE || map->getMapPiece(k, l).bStat == BlockStatus::BOMB) &&
	    (bombx == 0 || ((k > bombx && k <= i) || (k < bombx && k >= i))) && (bomby == 0 || ((l > bomby && l <= j) || (l < bomby && l >= j))))
	  {
	    bombx = k;
	    bomby = l;
	  }
      }
  if (bombx == 0 && bomby == 0)
    return (false);
  if (canBombTouch(map) == false)
    {
      cA = CAction::NONE;
      return (true);
    }
  if (bombx < i)
    return (bombxinf(bomby, j, map, game));
  else if (bombx > i)
    return (bombxsup(bomby, j, map, game));
  else
    {
      bool stop = false;
      for (int k = 4; k <= 7 && stop == false; k++)
	if (correctDir(map, i, j, k) == true)
	  stop = setPosRot(game, map, cA = Dir[k], false);
      return (stop);
    }
  return (true);
}

void	Ia::play(Game *game, Command *command, Map *map)
{
  CAction	tmp;
  std::uniform_int_distribution<int> dist(0, 7);
  std::chrono::time_point<std::chrono::system_clock> start = std::chrono::system_clock::now();

  randomCmd();
  setAction(map);
  setPosRot(game, map, cA, true);
  while (isAlive == true)
    {
      if (inPause == false)
	{
	  std::chrono::time_point<std::chrono::system_clock> tNow = std::chrono::system_clock::now();
	  std::chrono::duration<double> diff = tNow - start;
	  if (diff.count() > 1)
	    {
	      if (closest_bomb(map, game) == false)
		{
		  cA = Dir[dist(generator)];
		  if (check_around_wall(map) == true || no_more_walls(map) == true)
		    cA = CAction::BOMB;
		}
	      start = std::chrono::system_clock::now();
	    }
	  if (diff.count() > 0.1)
	    {
	      tmp = cA;
	      if (closest_bomb(map, game) == false)
		cA = tmp;
	      else
		start = std::chrono::system_clock::now();
	    }
	  setAction(map);
	  setPosRot(game, map, cA, true);
	}
    }
  if (deathAnimStat == 0)
    {
      Sound::getSound()->play("death.wav", 2);
      while (deathAnimStat < 2);
    }
}

void	Ia::initPlay(Game *game, Command *command, Map *map)
{
  then = game->getWindow()->getTimer()->getTime();
  t = std::thread(&Ia::play, this, game, command, map);
}

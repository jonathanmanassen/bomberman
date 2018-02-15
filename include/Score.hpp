//
// Score.hpp for indieStudio in /home/meyrie_g/rendu/cpp_indie_studio
// 
// Made by Gabin Meyrieux-Drevet
// Login   <meyrie_g@epitech.net>
// 
// Started on  Tue May 16 16:08:43 2017 Gabin Meyrieux-Drevet
// Last update Tue May 23 15:58:46 2017 Gabin Meyrieux-Drevet
//

#ifndef SCORE_HPP_
# define SCORE_HPP_

#include <vector>
#include <string>
#include <stdbool.h>

class	Score
{
  std::vector<int>		HSPoint;
  std::vector<std::string>	HSName;
  std::string			curName;
  int				score;
  bool				newHighScore;
public:
  Score(std::string const&);
  ~Score();
  void	parseScore(std::string const &fileName);
  int	getScore() const {return score;};
  void	setScore(int _score) {score = _score;};
  void	setCurName(std::string const &_name) {curName = _name;};
};

#endif /*!SCORE_HPP_*/

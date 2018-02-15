//
// player.hpp for bomberman in /home/manass_j/rendu/cpp_indie_studio/include
// 
// Made by jonathan manassen
// Login   <jonathan.manassen@epitech.eu@epitech.net>
// 
// Started on  Tue May 16 13:23:04 2017 jonathan manassen
// Last update Sat Jun 17 22:17:38 2017 jonathan manassen
//

#ifndef THREAD_HPP_
# define THREAD_HPP_

#include <iostream>
#include <string>
#include <thread>
#include <exception>

class	Thread
{
public:
  std::thread	t;
  Thread() {}
  virtual ~Thread() {}
  Thread(Thread const&) = delete;
  Thread& operator=(Thread const&) = delete;

  void	end() {t.join();}
};

#endif /* THREAD_HPP_ */

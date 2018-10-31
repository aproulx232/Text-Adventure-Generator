/*
 * engine.hpp
 *
 *  Created on: Oct 16, 2018
 *      Author: User
 */

#ifndef ENGINE_HPP_
#define ENGINE_HPP_

#include "Element.hpp"
#include "Person.hpp"
#define LEN_OF_TURN_ON 8 //length of "turn on " for string parsing

int runGame(Element* map);
int getInput(string* input);
int runUserCommand(std::string input, Person* player);



#endif /* ENGINE_HPP_ */

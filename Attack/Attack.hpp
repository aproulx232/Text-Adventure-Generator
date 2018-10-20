/*
 * Attack.hpp
 *
 *  Created on: Oct 10, 2018
 *      Author: User
 */

#ifndef ATTACK_HPP_
#define ATTACK_HPP_

#include "Condition.hpp"

#include <list>
#include <iterator>

class Attack{
public:
	std::list<Condition*> conditions;
	std::list<char*> prints;
	std::list<char*> actions;

	Attack();
	virtual~Attack();

};



#endif /* ATTACK_HPP_ */

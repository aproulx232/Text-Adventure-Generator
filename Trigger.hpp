/*
 * Trigger.hpp
 *
 *  Created on: Oct 5, 2018
 *      Author: User
 */

#ifndef TRIGGER_HPP_
#define TRIGGER_HPP_

#include "Condition.hpp"
#include <string.h>
#include <string>

#include <list>
#include <iterator>

class Trigger{
public:
	char* type;
	std::list<char*> commands;
	std::list<Condition*> conditions;
	std::list<char*> prints;
	std::list<char*> actions;
	bool activate();
	bool isCommandMet(std::string command);
	bool areAllCommandsMet(std::string command);
	bool isConditionMet(Condition* condition);
	bool areAllConditionsMet();
	Trigger();
	virtual ~Trigger();
	int print();

};


#endif /* TRIGGER_HPP_ */

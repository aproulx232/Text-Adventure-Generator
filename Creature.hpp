/*
 * Creature.hpp
 *
 *  Created on: Oct 5, 2018
 *      Author: User
 */

#ifndef CREATURE_HPP_
#define CREATURE_HPP_

#include "Element.hpp"
#include "Trigger.hpp"
#include "Attack.hpp"
#include "Item.hpp"

class Creature: public Element{
public:
	char * name;
	char * status;
	char * description;
	std::list<char*> vulnerabilities;
	std::list<Attack*> attacks;
	std::list<Trigger*> triggers;
	Creature();
	int checkTriggers(string command);
	int attackWith(Item* item);
	virtual char* getName();
	virtual int print();
	virtual std::string getStatus();

};



#endif /* CREATURE_HPP_ */

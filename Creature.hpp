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
	int checkTriggers(std::string command);
	int checkIfBlocked(std::string command);
	int attackWith(Item* item);
	virtual char* getName();
	virtual int print();
	virtual std::string getStatus();
	virtual int setStatus(std::string newStatus);
	virtual int add(Element* add);
	virtual int deleteElement(std::string toDelete);

};



#endif /* CREATURE_HPP_ */

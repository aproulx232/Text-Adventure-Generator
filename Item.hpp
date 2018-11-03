/*
 * Item.hpp
 *
 *  Created on: Oct 5, 2018
 *      Author: User
 */

#ifndef ITEM_HPP_
#define ITEM_HPP_

#include "Element.hpp"
#include "Trigger.hpp"

class Item :public Element{
public:
	Item();
	virtual ~Item();
	char * name;
	char * status;
	char * description;
	char * writing;
	char * turn_on_Print;
	char * turn_on_Action;
	std::list<Trigger*> triggers;

	void printWriting();
	int checkTriggers(std::string command);
	int checkIfBlocked(std::string command);
	virtual char* getName();
	virtual int print();
	virtual std::string getStatus();
	virtual int setStatus(std::string newStatus);
	virtual int deleteElement(std::string toDelete);

};



#endif /* ITEM_HPP_ */

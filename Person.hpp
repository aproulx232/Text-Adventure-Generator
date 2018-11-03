/*
 * Person.hpp
 *
 *  Created on: Oct 16, 2018
 *      Author: User
 */

#ifndef PERSON_HPP_
#define PERSON_HPP_

#include "Room.hpp"

class Person: public Element{
public:
	char* name;
	Room* currentRoom;
	std::list<Item*> inventory;

	Person();
	Person(Element* map);
	void addItem(Item* item);
	Item* deleteItem(std::string item);
	Item* getItem(std::string item);
	bool hasItem(char* item);
	int checkIfBlocked(std::string command);
	virtual char* getName();
	void printInventory();
};



#endif /* PERSON_HPP_ */

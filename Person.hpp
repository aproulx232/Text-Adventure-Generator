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
	Item* getItem(string item);
	bool hasItem(char* item);
	char* getName();
	void printInventory();
};



#endif /* PERSON_HPP_ */

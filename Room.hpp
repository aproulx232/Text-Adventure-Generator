/*
 * Room.hpp
 *
 *  Created on: Oct 5, 2018
 *      Author: User
 */


#ifndef ROOM_HPP_
#define ROOM_HPP_

#include "Element.hpp"
#include "Container.hpp"
#include "Item.hpp"
#include "Creature.hpp"
#include "Trigger.hpp"
#include "Border.hpp"

#include <list>
#include <iterator>

class Room : public Element{
public:
	char * name;
	char * status;//WHAT is this?
	char * type;
	char * description;
	std::list <Border*> borders;
	std::list <Container*> containers;
	std::list <Item*> items;
	std::list <Creature*> creatures;
	std::list <Trigger*> triggers;
	Room();
	Room(char* name,char* status);
	Room* getBorderRoom(string s);
	int checkTriggers();
	int checkTriggers(string command);
	Item* getItemAll(string item);
	Item* getItemRoom(string item);

	virtual char* getName();
	virtual int print();
	virtual std::string getStatus();
	virtual int setStatus(std::string newStatus);
};



#endif /* ROOM_HPP_ */

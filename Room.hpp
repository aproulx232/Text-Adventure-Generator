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
	Room* getBorderRoom(std::string s);
	int checkTriggers();
	int checkTriggers(std::string command);
	int checkOverrideInput(std::string command);
	Item* getItemAll(std::string item);
	void addItem(Item* item);
	Item* getItemRoom(std::string item);
	Creature* getCreatureRoom(std::string creature);
	Container* getContainerRoom(std::string container);
	Item* removeItemRoom(std::string item);
	Item* removeItemAll(std::string item);

	virtual char* getName();
	virtual int print();
	virtual std::string getStatus();
	virtual int setStatus(std::string newStatus);
	virtual int add(Element* add);
	virtual int deleteElement(std::string toDelete);
};



#endif /* ROOM_HPP_ */

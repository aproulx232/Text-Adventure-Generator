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

#include <list>
#include <iterator>

class Room : public Element{
public:
	char * name;
	char * status;//WHAT is this?
	char * type;
	char * description;
	std::list <Room*> borders;//TODO, change to Border object containing room
	std::list <Container*> containers;
	std::list <Item*> items;
	std::list <Creature*> creatures;
	std::list <Trigger*> triggers;
	Room();
	Room(char* name,char* status);
};



#endif /* ROOM_HPP_ */

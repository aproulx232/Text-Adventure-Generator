/*
 * builder.hpp
 *
 *  Created on: Oct 9, 2018
 *      Author: User
 */

#ifndef BUILDER_HPP_
#define BUILDER_HPP_
#include "XML_Parser/rapidxml.hpp"
#include "Room.hpp"
#include "Container.hpp"
#include "item.hpp"

using namespace rapidxml;

int buildGame(char * buffer);
int buildRoom(xml_node<> * node, Room * room);
int buildContainer(xml_node<> * node, Container * container);
int buildItem(xml_node<> * node, Item * item);

enum STATUS{
	OK = 0,
	ERROR = 1
};



#endif /* BUILDER_HPP_ */

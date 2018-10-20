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
#include "Item.hpp"

using namespace rapidxml;

int buildGame(char * buffer, Element * map);
int buildRoom(xml_node<> * node, Room * room);
int buildContainer(xml_node<> * node, Container * container);
int buildItem(xml_node<> * node, Item * item);
int buildCreature(xml_node<> * node, Creature * creature);
int buildTrigger(xml_node<> * node, Trigger * trigger);
int buildCondition(xml_node<> * node, Condition * condition);
int buildAttack(xml_node<> * node, Attack * attack);
int buildBorder(xml_node<> * node, Border * border);




#endif /* BUILDER_HPP_ */

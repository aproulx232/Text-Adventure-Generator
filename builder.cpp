/*
 * builder.cpp
 *
 *  Created on: Oct 9, 2018
 *      Author: User
 */

#include "builder.hpp"
#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "Element.hpp"
#include "Room.hpp"
#include "util.hpp"

#include <list>
#include <iterator>

using namespace std;
using namespace rapidxml;

int buildGame(char * buffer, Element * map){
	int status = OK;

	xml_document<> doc;
	doc.parse<0>(buffer);
	xml_node<> * mapNode = doc.first_node();
	//cout<< mapNode->name()<<endl;
	if(strcmp(mapNode->name(),(char*)"map") != STR_EQUAL){
		status = ERROR;
	}
	else{
		xml_node<> * firstNode = mapNode->first_node();
		for(xml_node<> * nodeIndex = firstNode; nodeIndex; nodeIndex= nodeIndex->next_sibling()){
			//std::cout << nodeIndex->name()<<std::endl;
			if(strcmp(nodeIndex->name(),(char*)"room") == STR_EQUAL){
				Room* room = new Room();
				map->mapList.push_back(room);
				status = buildRoom(nodeIndex, room);
			}
			else if(strcmp(nodeIndex->name(),(char*)"item") == STR_EQUAL){
				Item* temp= new Item();
				status = buildItem(nodeIndex, temp);
				Element* itemName;
				itemName = itemName->getElement(temp->name);
				if(itemName != NULL){
					status = buildItem(nodeIndex, dynamic_cast<Item*>(itemName));
					//room->items.push_back(dynamic_cast<Item*>(itemName));
				}
				else{
					Item* item = new Item();
					map->mapList.push_back(item);
					status = buildItem(nodeIndex, item);
				}

			}
			else if(strcmp(nodeIndex->name(),(char*)"container") == STR_EQUAL){
				Container* temp = new Container();
				status = buildContainer(nodeIndex, temp);
				Element* containerName;
				containerName = containerName->getElement(temp->name);
				if(containerName != NULL){
					status = buildContainer(nodeIndex, dynamic_cast<Container*>(containerName));
				}
				else{
					Container* container = new Container();
					map->mapList.push_back(container);
					status = buildContainer(nodeIndex, container);
				}
			}
			else if(strcmp(nodeIndex->name(),(char*)"creature") == STR_EQUAL){
				Creature* temp = new Creature();
				status = buildCreature(nodeIndex, temp);
				Element* creatureName;
				creatureName = creatureName->getElement(temp->name);
				if(creatureName != NULL){
					status = buildCreature(nodeIndex, dynamic_cast<Creature*>(creatureName));
				}
				else{
					//TODO use temp creature instead
					Creature* creature = new Creature();
					map->mapList.push_back(creature);
					status = buildCreature(nodeIndex, creature);
				}

			}
			else{
				cout<<"ERROR: Undefined field for map builder in builder.cpp: "<< nodeIndex->name()<<endl;
				status = ERROR;
			}
		}
	}
	map->printMapList();
	return status;
}

// Reads xml node info into Room object that is passed in
int buildRoom(xml_node<> * node, Room * room){
	int status = OK;
	for(xml_node<> * roomNodeIndex = node->first_node(); roomNodeIndex; roomNodeIndex = roomNodeIndex->next_sibling()){
		//cout<<roomNodeIndex->name()<<endl;
		if(strcmp(roomNodeIndex->name(),(char*)"name") == STR_EQUAL){
			room->name = roomNodeIndex->value();
		}
		else if(strcmp(roomNodeIndex->name(),(char*)"description") == STR_EQUAL){
			room->description = roomNodeIndex->value();
		}
		else if(strcmp(roomNodeIndex->name(),(char*)"status") == STR_EQUAL){
			room->status = roomNodeIndex->value();
		}
		else if(strcmp(roomNodeIndex->name(),(char*)"type") == STR_EQUAL){
			room->type = roomNodeIndex->value();
		}
		else if(strcmp(roomNodeIndex->name(),(char*)"container") == STR_EQUAL){
			/* Find if container was already created in element list*/
			Element* containerName;
			containerName = containerName->getElement(roomNodeIndex->value());
			/*If yes, point to it*/
			if(containerName != NULL){
				room->containers.push_back(dynamic_cast<Container*>(containerName));
			}
			/* Else, create new container in element list*/
			else{
				Container* containerObj = new Container();
				containerObj->name = roomNodeIndex->value();
				room->containers.push_back(containerObj);
				room->mapList.push_back(containerObj);
			}
		}
		else if(strcmp(roomNodeIndex->name(),(char*)"item") == STR_EQUAL){
			Element* itemName;
			itemName = itemName->getElement(roomNodeIndex->value());
			if(itemName != NULL){
				room->items.push_back(dynamic_cast<Item*>(itemName));
			}
			else{
				Item* itemObj = new Item();
				itemObj->name = roomNodeIndex->value();
				room->items.push_back(itemObj);
				room->mapList.push_back(itemObj);
			}
		}
		else if(strcmp(roomNodeIndex->name(),(char*)"creature") == STR_EQUAL){
			/* Find if creature was already created in element list*/
			Element* creatureName;
			creatureName = creatureName->getElement(roomNodeIndex->value());
			/*If yes, point to it*/
			if(creatureName != NULL){
				room->creatures.push_back(dynamic_cast<Creature*>(creatureName));
			}
			/* Else, create new creature in element list*/
			else{
				Creature* creatureObj = new Creature();
				creatureObj->name = roomNodeIndex->value();
				room->creatures.push_back(creatureObj);
				room->mapList.push_back(creatureObj);
			}
		}
		else if(strcmp(roomNodeIndex->name(),(char*)"trigger") == STR_EQUAL){
			Trigger* trigger = new Trigger();
			status = buildTrigger(roomNodeIndex, trigger);
			room->triggers.push_back(trigger);
		}
		else if(strcmp(roomNodeIndex->name(),(char*)"border") == STR_EQUAL){
			Border* border = new Border();
			status = buildBorder(roomNodeIndex, border);
			room->borders.push_back(border);
		}
		else{
			cout<<"ERROR: Undefined field for Room in builder.cpp: "<< roomNodeIndex->name()<<endl;
			status = ERROR;
		}
	}
	return status;
}


/*
 * TODO
 */
int buildTrigger(xml_node<> * node, Trigger * trigger){
	//cout<<"TODO: buildTrigger"<<endl;
	int status = OK;
	for(xml_node<> * nodeIndex = node->first_node(); nodeIndex; nodeIndex = nodeIndex->next_sibling()){
		if(strcmp(nodeIndex->name(),(char*)"type") == STR_EQUAL){
			trigger->type = nodeIndex->value();
		}
		else if(strcmp(nodeIndex->name(),(char*)"command") == STR_EQUAL){
			trigger->commands.push_back(nodeIndex->value());
		}
		else if(strcmp(nodeIndex->name(),(char*)"print")== STR_EQUAL){
			trigger->prints.push_back(nodeIndex->value());
		}
		else if(strcmp(nodeIndex->name(),(char*)"action")==STR_EQUAL){
			trigger->actions.push_back(nodeIndex->value());
		}
		else if(strcmp(nodeIndex->name(),(char*)"condition")==STR_EQUAL){
			Condition* condition = new Condition();
			status = buildCondition(nodeIndex, condition);
			trigger->conditions.push_back(condition);
		}
		else{
			cout<<"ERROR: Undefined field for "<<node->name()<< " in builder.cpp: "<< nodeIndex->name()<<endl;
			status = ERROR;
		}
	}
	return status;
}


/*
 * TODO
 */
int buildCondition(xml_node<> * node, Condition * condition){
	//cout<<"TODO: buildCondition"<<endl;
	int status = OK;
	for(xml_node<> * nodeIndex = node->first_node(); nodeIndex; nodeIndex = nodeIndex->next_sibling()){
		//cout<<nodeIndex->name()<<endl;
		if(strcmp(nodeIndex->name(),(char*)"status") == STR_EQUAL){
			condition->status = nodeIndex->value();
			condition->condType = STATUS;
		}
		else if(strcmp(nodeIndex->name(),(char*)"owner") == STR_EQUAL){
			condition->owner = nodeIndex->value();
			condition->condType = OWNER;
		}
		else if(strcmp(nodeIndex->name(),(char*)"has")== STR_EQUAL){
			condition->has = nodeIndex->value();
		}
		else if(strcmp(nodeIndex->name(),(char*)"object")==STR_EQUAL){
			condition->object = nodeIndex->value();
		}
		else{
			cout<<"ERROR: Undefined field for "<<node->name()<< " in builder.cpp: "<< nodeIndex->name()<<endl;
			status = ERROR;
		}
	}
	return status;
}


/*
 * TODO
 */
int buildItem(xml_node<> * node, Item * item){
	//cout<<"TODO: buildItem"<<endl;
	int status = OK;
	for(xml_node<> * nodeIndex = node->first_node(); nodeIndex; nodeIndex = nodeIndex->next_sibling()){
		//cout<<nodeIndex->name()<<endl;
		if(strcmp(nodeIndex->name(),(char*)"name") == 0){
			item->name = nodeIndex->value();
		}
		else if(strcmp(nodeIndex->name(),(char*)"description") == 0){
			item->description = nodeIndex->value();
		}
		else if(strcmp(nodeIndex->name(),(char*)"status")==0){
			item->status = nodeIndex->value();
		}
		else if(strcmp(nodeIndex->name(),(char*)"writing")==0){
			item->writing = nodeIndex->value();
		}
		else if(strcmp(nodeIndex->name(),(char*)"turnon")==0){
			//std::cout<<"ERROR: item turnon"<<std::endl;
			for(xml_node<> * nodeTurnon = nodeIndex->first_node(); nodeTurnon; nodeTurnon = nodeTurnon->next_sibling()){
				if(strcmp(nodeTurnon->name(),(char*)"print") == 0){
					item->turn_on_Print = nodeTurnon->value();
				}
				else if(strcmp(nodeTurnon->name(),(char*)"action")==0){
					item->turn_on_Action = nodeTurnon->value();
				}
				else{
					cout<<"ERROR: turnon: "<<node->name()<< " in builder.cpp: "<< nodeIndex->name()<<endl;
					status = ERROR;
				}
			}
		}
		else{
			cout<<"ERROR: Undefined field for "<<node->name()<< " in builder.cpp: "<< nodeIndex->name()<<endl;
			status = ERROR;
		}
	}
	return status;
}


/*
 * TODO
 */
int buildContainer(xml_node<> * node, Container * container){
	//cout<<"TODO: buildContainer"<<endl;
	int status = OK;
	for(xml_node<> * nodeIndex = node->first_node(); nodeIndex; nodeIndex = nodeIndex->next_sibling()){
		if(strcmp(nodeIndex->name(),(char*)"name") == 0){
			container->name = nodeIndex->value();
		}
		else if(strcmp(nodeIndex->name(),(char*)"description") == 0){
			container->description = nodeIndex->value();
		}
		else if(strcmp(nodeIndex->name(),(char*)"status")==0){
			container->status = nodeIndex->value();
		}
		else if(strcmp(nodeIndex->name(),(char*)"accept")==0){
			container->accepts.push_back(nodeIndex->value());
		}
		else if(strcmp(nodeIndex->name(),(char*)"item")==0){
			container->items.push_back(nodeIndex->value());
		}
		else if(strcmp(nodeIndex->name(),(char*)"trigger")==0){
			Trigger* trigger = new Trigger();
			status = buildTrigger(nodeIndex, trigger);
			container->triggers.push_back(trigger);
		}
		else{
			cout<<"ERROR: Undefined field for "<<node->name()<< " in builder.cpp: "<< nodeIndex->name()<<endl;
			status = ERROR;
		}
	}
	return status;
}

/*
 * TODO
 */
int buildCreature(xml_node<> * node, Creature * creature){
	int status = OK;
	for(xml_node<> * nodeIndex = node->first_node(); nodeIndex; nodeIndex = nodeIndex->next_sibling()){
		//cout<<nodeIndex->name()<<endl;
		if(strcmp(nodeIndex->name(),(char*)"name") == 0){
			creature->name = nodeIndex->value();
		}
		else if(strcmp(nodeIndex->name(),(char*)"description") == 0){
			creature->description = nodeIndex->value();
		}
		else if(strcmp(nodeIndex->name(),(char*)"status")==0){
			creature->status = nodeIndex->value();
		}
		else if(strcmp(nodeIndex->name(),(char*)"vulnerability")==0){
			creature->vulnerabilities.push_back(nodeIndex->value());
		}
		else if(strcmp(nodeIndex->name(),(char*)"attack")==0){
			Attack* attack = new Attack();
			status = buildAttack(nodeIndex, attack);
			creature->attacks.push_back(attack);
		}
		else if(strcmp(nodeIndex->name(),(char*)"trigger")==0){
			Trigger* trigger = new Trigger();
			status = buildTrigger(nodeIndex, trigger);
			creature->triggers.push_back(trigger);
		}
		else{
			cout<<"ERROR: Undefined field for "<<node->name()<< " in builder.cpp: "<< nodeIndex->name()<<endl;
			status = ERROR;
		}
	}
	return status;
}


/*
 * TODO
 */
int buildAttack(xml_node<> * node, Attack * attack){
	//cout<<"TODO: buildAttack"<<endl;
	int status = OK;
	for(xml_node<> * nodeIndex = node->first_node(); nodeIndex; nodeIndex = nodeIndex->next_sibling()){
		//cout<<nodeIndex->name()<<endl;
		if(strcmp(nodeIndex->name(),(char*)"action") == 0){
			attack->actions.push_back(nodeIndex->value());
		}
		else if(strcmp(nodeIndex->name(),(char*)"print") == 0){
			attack->prints.push_back(nodeIndex->value());
		}
		else if(strcmp(nodeIndex->name(),(char*)"condition")==0){
			Condition* condition = new Condition();
			status = buildCondition(nodeIndex, condition);
			attack->conditions.push_back(condition);
		}
		else{
			cout<<"ERROR: Undefined field for "<<node->name()<< " in builder.cpp: "<< nodeIndex->name()<<endl;
			status = ERROR;
		}
	}
	return status;
}


/*
 * TODO
 */
int buildBorder(xml_node<> * node, Border * border){
	int status = OK;
	for(xml_node<> * nodeIndex = node->first_node(); nodeIndex; nodeIndex = nodeIndex->next_sibling()){
		if(strcmp(nodeIndex->name(),(char*)"name") == 0){
			border->name = (nodeIndex->value());
		}
		else if(strcmp(nodeIndex->name(),(char*)"direction") == 0){
			border->direction = (nodeIndex->value());
		}
		else{
			cout<<"ERROR: Undefined field for "<<node->name()<< " in builder.cpp: "<< nodeIndex->name()<<endl;
			status = ERROR;
		}
	}
	return status;
}

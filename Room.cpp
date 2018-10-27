/*
 * Room.cpp
 *
 *  Created on: Oct 5, 2018
 *      Author: User
 */

#include "Room.hpp"
#include "util.hpp"

#include <iostream>
using namespace std;

Room::Room(){
	name = (char*)"\0";
	status = (char*)"\0";
	type = (char*)"\0";
	description = (char*)"\0";
	borders = {};
	containers = {};
	items = {};
	creatures = {};
	triggers ={};
}
Room::Room(char* name, char* status):name(name),status(status){

}

char* Room::getName(){
	return name;
}
/*
 *  Param: string direction :the direction to get the border room
 */
Room* Room::getBorderRoom(string direction){
	//std::cout<<"Room::getBorderRoom: "<<direction<<std::endl;
	std::list<Border*>::iterator it;
	for (it = borders.begin(); it != borders.end(); ++it){
		if(direction.compare((*it)->direction) == STR_EQUAL){
			return dynamic_cast<Room*>(getElement((*it)->name));
		}
	}
	return NULL;

}

/*
 * Adds item to room item list
 */
void Room::addItem(Item* item){
	items.push_back(item);
	return;
}

/* Check if any of the triggers in room are tiggered and triggers them
 *
 */
int Room::checkTriggers(){
	return this->checkTriggers("no_command");
}

/* Check if any of the triggers in room are tiggered and triggers them
 * Param: string command: command entered by user
 * Return: int: status or if trigger was activated
 */
int Room::checkTriggers(string command){
	int statusInt = OK;
	/* check room triggers*/
	if(!triggers.empty()){
		std::list<Trigger*>::iterator it;
		for (it = triggers.begin(); it != triggers.end(); ++it){
			Trigger* index = (*it);
			if(index->areAllConditionsMet() == true ){
				if(index->areAllCommandsMet(command) == true){
					//std::cout<<"Trigger activated"<<std::endl;
					if(index->activate() == true){
						statusInt = BLOCK_INPUT_COMMAND;
					}
				}
			}
		}
	}
	/* Check creature triggers */
	//std::cout<<"Check creature triggers"<<std::endl;
	if(!creatures.empty()){
		std::list<Creature*>::iterator it;
		for(it = creatures.begin(); it != creatures.end(); ++it){
			Creature* index = (*it);
			/* If input command is not already blocked*/
			if(statusInt == OK){
				statusInt = index->checkTriggers(command);
			}
			else{
				index->checkTriggers(command);
			}

		}
	}
	/* Check container triggers */
	if(!containers.empty()){
		std::list<Container*>::iterator it;
		for(it = containers.begin(); it != containers.end(); ++it){
			Container* index = (*it);
			/* If input command is not already blocked*/
			if(statusInt == OK){
				statusInt = index->checkTriggers(command);
			}
			else{
				index->checkTriggers(command);
			}

		}
	}
	return statusInt;
}

int Room::setStatus(std::string newStatus){
	std::cout<<"Room::setStatus"<<std::endl;
	status = strdup(newStatus.c_str());
	return OK;
}

/*
 * Get status of obj
 * Return: string: status
 */
std::string Room::getStatus(){
	return (string)status;
}

Item* Room::getItemAll(string item){
	Item* match = NULL;
	match = this->getItemRoom(item);
	if(match == NULL){
		std::list<Container*>::iterator it;
		for (it = containers.begin(); it != containers.end(); ++it){
			Container* index = (*it);
			if(index->opened == true){
				match = index->getItem(item);
				if( match != NULL){
					return match;
				}
			}

		}
	}
	return match;
}

/*
 * Get item from  room list items
 */
Item* Room::getItemRoom(string item){
	std::list<Item*>::iterator it;
	for (it = items.begin(); it != items.end(); ++it){
		Item* index = (*it);
		if(item.compare((string)index->name) == STR_EQUAL){
			return index;
		}
	}
	return NULL;
}

/*
 * Removes the item from the room items list
 */
Item* Room::removeItemRoom(std::string item){
	std::list<Item*>::iterator it;
	for (it = items.begin(); it != items.end(); ++it){
		Item* index = (*it);
		if(item.compare((string)index->name) == STR_EQUAL){
			items.erase(it);
			return index;
		}
	}
	return NULL;
}

/*
 * Removes item from room and any open containers in the room
 */
Item* Room::removeItemAll(std::string item){
	Item* match = NULL;
	match = this->removeItemRoom(item);
	if(match == NULL){
		std::list<Container*>::iterator it;
		for (it = containers.begin(); it != containers.end(); ++it){
			Container* index = (*it);
			if(index->opened == true){
				match = index->getItem(item);
				if( match != NULL){
					index->removeItem(item);
					return match;
				}
			}

		}
	}
	return match;
}

/*
 * Get the creature pointer from room else return NULL
 */
Creature* Room::getCreatureRoom(std::string creature){
	Creature* match = NULL;
	std::list<Creature*>::iterator it;
	for (it = creatures.begin(); it != creatures.end(); ++it){
		Creature* index = (*it);
		if(creature.compare((string)index->name) == STR_EQUAL){
			match =  index;
		}
	}
	return match;
}

int Room::print(){
	int statusInt = OK;
	if(name != NULL)
		std::cout<<"Room: "<<name<<std::endl;
	else
		statusInt = NULL_ERROR;
	if(status != NULL)
		std::cout<<"	status: "<<status<<std::endl;
	if(description != NULL)
		std::cout<<"	description: "<<description<<std::endl;
	if(type != NULL)
		std::cout<<"	type: "<<type<<std::endl;
	if(!borders.empty()){
		std::cout<<"	borders: "<<endl;
		std::list<Border*>::iterator it;
		for (it = borders.begin(); it != borders.end(); ++it){
			(*it)->print();
		}
	}
	if(!containers.empty()){
		std::cout<<"	containers: "<<endl;
		std::list<Container*>::iterator it;
		for (it = containers.begin(); it != containers.end(); ++it){
			(*it)->print();
		}
	}
	if(!items.empty()){
		std::cout<<"	items: "<<endl;
		std::list<Item*>::iterator it;
		for (it = items.begin(); it != items.end(); ++it){
			(*it)->print();
		}
	}
	if(!creatures.empty()){
		std::cout<<"	creatures: "<<endl;
		std::list<Creature*>::iterator it;
		for (it = creatures.begin(); it != creatures.end(); ++it){
			(*it)->print();
		}
	}
	if(!triggers.empty()){
		std::cout<<"	triggers: "<<endl;
		std::list<Trigger*>::iterator it;
		for (it = triggers.begin(); it != triggers.end(); ++it){
			(*it)->print();
		}
	}
	return statusInt;
}




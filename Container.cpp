/*
 * Container.cpp
 *
 *  Created on: Oct 5, 2018
 *      Author: User
 */

#include "Container.hpp"
#include "util.hpp"

#include <iostream>
#include <list>
#include <iterator>

using namespace std;

Container::Container(){
	name = (char*)"";
	status = (char*)"";
	description = (char*)"";
	opened = false;
	accepts = {};
	items = {};
	triggers = {};
}

char* Container::getName(){
	return name;
}

bool Container::hasItem(char* itemName){
	bool hasItem = false;
	std::list<char*>::iterator it;
	for (it = items.begin(); it != items.end(); ++it){
		if(strcmp(itemName, (*it)) == STR_EQUAL){
			hasItem = true;
		}
	}
	return hasItem;
}

int Container::setStatus(std::string newStatus){
	//std::cout<<"Container::setStatus"<<std::endl;
	status = strdup(newStatus.c_str());
	return OK;
}

/*
 *
 */
std::string Container::getStatus(){
	return (string)status;
}

/*
 *
 */
Item* Container::getItem(std::string item){
	Item* match = NULL;
	std::list<char*>::iterator it;
	for (it = items.begin(); it != items.end(); ++it){
		char* index = (*it);
		if(item.compare((string)index) == STR_EQUAL){
			match = dynamic_cast<Item*>(this->getElement(index));
		}
	}
	return match;
}

/*
 *
 */
/*
 *
 */
int Container::deleteElement(std::string toDelete){
	int statusInt = OK;
	Element* element = this->getElement(toDelete);
	Item* deleteItem = dynamic_cast<Item*>(element);
	if(deleteItem != NULL){
		items.remove(deleteItem->name);
		accepts.remove(deleteItem->name);
	}
	return statusInt;
}

/*
 * Removes the item from the items list. does not delete item from game
 * Param: std::string item: item to get
 * Return: Item* : item removed
 */
Item* Container::removeItem(std::string item){
	Item* match = NULL;
	std::list<char*>::iterator it;
	for (it = items.begin(); it != items.end(); ++it){
		char* index = (*it);
		if(item.compare((string)index) == STR_EQUAL){
			match = dynamic_cast<Item*>(this->getElement(index));
			items.erase(it);
			return match;
		}
	}
	return match;
}

/*
 * Adds the item to the container If accepts in present, only add if itme is on list then opens, else if opened, adds to item list
 */
int Container::addItem(std::string item){
	int statusInt = OK;
	if(!accepts.empty()){
		/* Check if item is in accept list*/
		std::list<char*>::iterator it;
		for (it = accepts.begin(); it != accepts.end(); ++it){
			char* index = (*it);
			if(item.compare((string)index) == STR_EQUAL){
				/* Item in accept list*/
				opened = true;
				char *cstr = new char[item.length() + 1];
				strcpy(cstr, item.c_str());
				items.push_back(index);
				statusInt = CONTAINER_ITEM_ADDED;
				std::cout<<"Item "<<item<<" added to "<<name<<"."<<std::endl;
			}
		}
		if(statusInt != CONTAINER_ITEM_ADDED){
			statusInt = CONTAINER_ITEM_NOT_ACCEPTED;
			std::cout<<name<<" does not accept "<<item<<std::endl;
		}
	}
	else{
		if(opened == true){
			/* Add item to list */
			char *cstr = new char[item.length() + 1];
			strcpy(cstr, item.c_str());
			items.push_back(cstr);
			statusInt = CONTAINER_ITEM_ADDED;
			std::cout<<"Item "<<item<<" added to "<<name<<"."<<std::endl;
		}
		else{
			std::cout<<name<<" needs to be opened first"<<std::endl;
		}
	}
	return statusInt;
}


/*
 * Finds type of element and adds it to the correct list of room
 */
int Container::add(Element* add){
	int statusInt = OK;
	Item* addItem = dynamic_cast<Item*>(add);
	if(addItem != NULL){
		items.push_back(addItem->name);
	}
	else{
		statusInt = ERROR;
		std::cout<<"ERROR: Container::add(Element* add)) unknown add type"<<std::endl;
	}
	return statusInt;
}


/*
 * Check the triggers of the current object to and activates them
 */
int Container::checkTriggers(std::string command){
	int statusInt = OK;
	if(!triggers.empty()){
		std::list<Trigger*>::iterator it;
		for (it = triggers.begin(); it != triggers.end(); ++it){
			Trigger* index = (*it);
			//std::cout<<"checking cond"<<std::endl;
			if(index->areAllConditionsMet() == true ){
				if(index->areAllCommandsMet(command) == true){
					//std::cout<<"Container::checkTriggers Trigger activated"<<std::endl;
					if(index->activate() == true){
						statusInt = BLOCK_INPUT_COMMAND;
					}
				}
			}
		}
	}
	return statusInt;
}

/*
 * Prints the contents of  the container in neat format
 */
void Container::printContents(){
	std::list<char*>::iterator it;
	bool printedFirstItem = false;
	std::cout<<name<<" ";
	if(items.empty()){
		std::cout<<"is empty"<<std::endl;
	}
	else{
		std::cout<<"contains ";
		for (it = items.begin(); it != items.end(); ++it){
			Item* index = NULL;
			index = dynamic_cast<Item*>(this->getElement((*it)));
			if(index != NULL){
				if(printedFirstItem == true){
					std::cout<<", "<<index->name;
				}
				else{
					std::cout<<index->name;
					printedFirstItem = true;
				}
			}
		}
		std::cout<<""<<std::endl;
	}
}


int Container::print(){
	int statusInt = OK;
	if(name != NULL)
		std::cout<<"Container: "<<name<<std::endl;
	else
		statusInt = NULL_ERROR;
	if(status != NULL)
		std::cout<<"	status: "<<status<<std::endl;
	if(description != NULL)
		std::cout<<"	description: "<<description<<std::endl;
	if(!accepts.empty()){
		std::cout<<"	accepts: "<<std::endl;
		std::list<char*>::iterator it;
		for (it = accepts.begin(); it != accepts.end(); ++it){
			std::cout<<"		"<<(*it)<<std::endl;
		}
	}
	if(!items.empty()){
		std::cout<<"	items: "<<endl;
		std::list<char*>::iterator it;
		for (it = items.begin(); it != items.end(); ++it){
			std::cout<<"		"<<(*it)<<std::endl;
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



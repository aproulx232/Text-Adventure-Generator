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
	name = '\0';
	status = '\0';
	description = '\0';
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
	std::cout<<"Container::setStatus"<<std::endl;
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
		}
	}
	return match;
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
			Item* index = dynamic_cast<Item*>(this->getElement((*it)));
			if(index != NULL){
				if(printedFirstItem == true){
					std::cout<<", "<<index->name;
				}
				else{
					std::cout<<index->name;
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



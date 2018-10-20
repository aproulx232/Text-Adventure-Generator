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



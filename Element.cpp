/*
 * Element.cpp
 *
 *  Created on: Oct 5, 2018
 *      Author: User
 */

#include "Element.hpp"
#include "Room.hpp"
#include "Container.hpp"
#include "Person.hpp"
#include "Engine.hpp"
#include "util.hpp"

#include <string.h>
#include <iostream>

using namespace std;

list<Element*> Element::mapList = {};
list<Element*> Element::deleteList = {};
bool Element::quit = false;

Element::Element(){

}
Element::~Element(){

}

Element* Element::getElement(char* name){
	std::list<Element*>::iterator it;
	for (it = mapList.begin(); it != mapList.end(); ++it){
		if(strcmp((*it)->getName(),name) == 0){
			return (dynamic_cast<Element*>(*it));
		}
	}
	return NULL;
}

Element* Element::getElement(std::string name){
	std::list<Element*>::iterator it;
	Element* match = NULL;
	for (it = mapList.begin(); it != mapList.end(); ++it){
		if(name.compare((string)(*it)->getName()) == STR_EQUAL){
			match= (dynamic_cast<Element*>(*it));
		}
	}
	if(match == NULL){
		std::cout<<"ERROR: Element::getElement(std::string name)"<<std::endl;
	}
	return match;
}

char * Element::getName(){
	cout<<"Element::getName()"<<endl;
	return NULL;
}

int Element::print(){
	std::cout<<"Element::print()"<<std::endl;
	return NULL_ERROR;
}

int Element::printMapList(){
	int statusInt = OK;
	std::cout<<"Map List: "<<std::endl;
	std::list<Element*>::iterator it;
	for (it = mapList.begin(); it != mapList.end(); ++it){
		Element* index = (dynamic_cast<Element*>(*it));
		//std::cout<<"	"<<index->getName()<<std::endl;
		statusInt = index->print();
	}
	return statusInt;
}

int Element::setStatus(std::string newStatus){
	std::cout<<"Element::setStatus"<<std::endl;
	return ERROR;
}

/*
 *
 */
std::string Element::getStatus(){
	std::cout<<"Element::getStatus"<<std::endl;
	return "ERROR";
}

/*
 * Has to be over ridden by a function
 */
int Element::add(Element* add){
	int statusInt = ERROR;
	std::cout<<"Element::add()"<<std::endl;
	return statusInt;
}

/*
 *
 */
int Element::deleteElement(std::string toDelete){
	int statusInt = ERROR;
	//std::cout<<"Element::deleteElement"<<std::endl;//rmp
	return statusInt;
}

/*
 * Does the action string of the Element
 */
int Element::doAction(std::string actionStr){
	int statusInt = OK;
	/* Parse out the action */
	std::string firstWord = actionStr.substr(0,actionStr.find(" "));
	if(firstWord.compare("Update") == STR_EQUAL){
		std::string objStr = actionStr.substr(actionStr.find(" ")+1,actionStr.find(" to ")-actionStr.find(" ")-1);
		std::string statusStr = actionStr.substr(actionStr.find("to ")+3,actionStr.length());
		//std::cout<<"Element::doAction: Update \""<<objStr<<"\" to \""<<statusStr<<"\""<<std::endl;
		Element* obj = this->getElement(objStr);
		if(obj != NULL){
			obj->setStatus(statusStr);
		}
		else{
			std::cout<<"ERROR: Element::doAction: obj == NULL: objst \""<<objStr<<"\""<<std::endl;
		}
	}
	else if(firstWord.compare("Add") == STR_EQUAL){
		std::string objStr = actionStr.substr(actionStr.find(" ")+1,actionStr.find(" to")-(actionStr.find(" ")+1));
		std::string toStr = actionStr.substr(actionStr.find("to ")+3,actionStr.length());
		//std::cout<<"Element::doAction: Add \""<<objStr<<"\" to \""<<toStr<<"\""<<std::endl;
		Element* obj = this->getElement(objStr);
		Element* to = this->getElement(toStr);
		if(obj != NULL && to != NULL){
			Room* addToRoom = dynamic_cast<Room*>(to);
			Container* addToContainer = dynamic_cast<Container*>(to);
			if(addToRoom != NULL){
				statusInt = addToRoom->add(obj);
			}
			else if(addToContainer != NULL){
				statusInt = addToContainer->add(obj);
			}
			else{
				std::cout<<"ERROR Element::doAction: Add: unknown to"<<std::endl;
			}

		}
		else{
			std::cout<<"ERROR unknown (object) to (room/container) "<<std::endl;
		}
	}
	else if(firstWord.compare("Delete") == STR_EQUAL){
		std::string toDelete = actionStr.substr(actionStr.find(" ")+1,actionStr.length());
		//std::cout<<"toDelete:"<<toDelete<<std::endl;//rmp

		//go through maplist and call delete(string) on every element
		std::list<Element*>::iterator it;
		for (it = mapList.begin(); it != mapList.end(); ++it){
			Element* index = (dynamic_cast<Element*>(*it));
			if(index != NULL){
				index->deleteElement(toDelete);
			}
		}
	}
	else if(actionStr.compare("Game Over")  == STR_EQUAL){
		std::cout<<"Victory!"<<std::endl;
		statusInt = QUIT_GAME;
		Element::quit = true;
	}
	else{
		//std::cout<<"runUserCommand!"<<std::endl;//rmp
		Person* player = dynamic_cast<Person*>(this->getElement(string("inventory")));
		if(player != NULL){
			statusInt = runUserCommand(actionStr, player);
			player->currentRoom->checkTriggers(actionStr);
		}
		else{
			std::cout<<"Element::doAction: player ==null!"<<std::endl;
		}
	}
	return statusInt;
}


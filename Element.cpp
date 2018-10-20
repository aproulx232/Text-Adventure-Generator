/*
 * Element.cpp
 *
 *  Created on: Oct 5, 2018
 *      Author: User
 */

#include "Element.hpp"
#include "util.hpp"

#include <string.h>
#include <iostream>

using namespace std;

list<Element*> Element::mapList = {};

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
	for (it = mapList.begin(); it != mapList.end(); ++it){
		if(name.compare((string)(*it)->getName()) == STR_EQUAL){
			return (dynamic_cast<Element*>(*it));
		}
	}
	return NULL;
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
 * Does the action string of the Element
 */

int Element::doAction(string actionStr){
	int statusInt = OK;
	/* Parse out the action */
	std::string firstWord = actionStr.substr(0,actionStr.find(" "));
	if(firstWord.compare("Update") == STR_EQUAL){
		std::string objStr = actionStr.substr(actionStr.find(" ")+1,actionStr.find(" to"));
		std::string statusStr = actionStr.substr(actionStr.find("to ")+1,actionStr.length());
		std::cout<<"Element::doAction: Update "<<objStr<<" to "<<statusStr<<std::endl;
		Element* obj = this->getElement(objStr);
		if(obj != NULL){
			obj->setStatus(statusStr);
		}
	}
	else if(firstWord.compare("Add") == STR_EQUAL){
		std::cout<<"ERROR TODO Add"<<std::endl;
		std::string objStr = actionStr.substr(actionStr.find(" ")+1,actionStr.find(" to"));
		std::string toStr = actionStr.substr(actionStr.find("to ")+1,actionStr.length());
		std::cout<<"Element::doAction: Add "<<objStr<<" to "<<toStr<<std::endl;
		Element* obj = this->getElement(objStr);
		Element* to = this->getElement(toStr);
		if(obj != NULL && to != NULL){
			//TODO
		}
	}
	else if(firstWord.compare("Delete") == STR_EQUAL){
		std::cout<<"ERROR TODO Delete"<<std::endl;
	}
	return statusInt;
}


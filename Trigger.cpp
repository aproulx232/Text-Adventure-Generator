/*
 * Trigger.cpp
 *
 *  Created on: Oct 5, 2018
 *      Author: User
 */

#include "Trigger.hpp"
#include "Element.hpp"
#include "Item.hpp"
#include "Person.hpp"
#include "util.hpp"


#include <iostream>
using namespace std;

#include <list>
#include <iterator>
#include <string.h>

Trigger::Trigger(){
	type = (char*)"\0";
	commands = {};
	conditions = {};
	prints = {};
	actions = {};
}

Trigger::~Trigger(){

}

/* Attempts to activate the trigger, assumes the condition is met
 * param: string command: command from  user
 * return: int: status int, OK if not activated, else activated
 */
int Trigger::activate(){

	int statusInt = OK;
	/* Check if type is null */
	if( type != NULL){
	/* Check if single is already used */
		if(((string)type).compare("used") == STR_EQUAL){
			return statusInt;
		}
		if(((string)type).compare("single") == STR_EQUAL){
			type = (char*)"used";
		}
	}
	/* Print trigger prints*/
	std::list<char*>::iterator it;
	for (it = prints.begin(); it != prints.end(); ++it){
		std::cout<<(*it)<<std::endl;
	}
	statusInt = TRIGGER_ACTIVATED;
	/* Do trigger action*/
	//std::list<char*>::iterator it; //TODO
	for (it = actions.begin(); it != actions.end(); ++it){
		//std::cout<<"action: "<<(*it)<<std::endl;
		Element action;
		statusInt = action.doAction((string)(*it));
	}
	return statusInt;
}

/*
 *
 */
bool Trigger::isCommandMet(std::string command){
	bool isMet = false;

	return isMet;
}

/*
 * If the give command is matches the trigger command, return true so that input command is blocked
 */
bool Trigger::areAllCommandsMet(std::string command){
    //std::cout<<"areAllCommandsMet: command: "<<command<<std::endl;//rmp
	bool isMet = false;
	std::list<char*>::iterator it;
	if(commands.empty()){
		if(command == "no_command"){
			isMet = true;
		}
	}
	else{
		for (it = commands.begin(); it != commands.end(); ++it){
			if(((std::string)(*it)).find(command) != std::string::npos){
				isMet = true;
			}
		}
	}
	//std::cout<<"areAllCommandsMet "<<isMet<<std::endl;//rmp
	return isMet;
}

/*
 * If the give command is matches the trigger command, return true so that input command is blocked
 */
bool Trigger::areCommandsMatched(std::string command){
	bool isBlocked = false;
	std::list<char*>::iterator it;
	for (it = commands.begin(); it != commands.end(); ++it){
		if(((std::string)(*it)).find(command) != std::string::npos){
			isBlocked = true;
		}
	}
	//std::cout<<"areAllCommandsMet "<<isMet<<std::endl;//rmp
	return isBlocked;
}

/*
 * Checks if all conditions are met for the trigger
 * Return: bool
 */
bool Trigger::areAllConditionsMet(){
	bool isMet = true;
	std::list<Condition*>::iterator it;
	for (it = conditions.begin(); it != conditions.end(); ++it){
		if(this->isConditionMet((*it)) == false){
			isMet = false;
		}
	}
	//std::cout<<"areAllConditionsMet "<<isMet<<std::endl;//rmp
	return isMet;
}

/*
 * Checks if the passed condition is met
 * Param: Condition* condition: condition to check
 */
bool Trigger::isConditionMet(Condition* condition){
	Element list;
	bool isMet = false;
	if(condition->condType == STATUS){
		Element* obj = list.getElement(condition->object);
		if(obj != NULL){
			//std::cout<<"isConditionMet: "<<condition->status<<" - "<<obj->getStatus()<<std::endl;
			if(obj->getStatus().compare((std::string)condition->status) == STR_EQUAL){
				isMet = true;
				//std::cout<<"isMet = true;"<<std::endl;
			}
		}
		else{
			std::cout<<"ERROR: Trigger::isConditionMet: obj == NULL"<<std::endl;
		}
	}
	else if(condition->condType == OWNER){
		//std::cout<<"isConditionMet: owner "<<condition->owner<<" - obj: "<<condition->object<<std::endl;
		Element* obj = list.getElement(condition->object);
		Item* objItem = dynamic_cast<Item*>(obj);
		Element* owner = list.getElement(condition->owner);//TODO clean up
		Container* ownerContainer = dynamic_cast<Container*>(owner);
		Person* ownerPlayer = dynamic_cast<Person*>(owner);
		if(objItem != NULL){
			if(ownerContainer != NULL){
				//std::cout<<"ownerContainer != NULL"<<std::endl;
				if(strcmp(condition->has,(char*)"yes") == STR_EQUAL){
					if(ownerContainer->hasItem(objItem->name) == true){
						isMet = true;
					}
				}
				else{
					if(ownerContainer->hasItem(objItem->name) == false){
						isMet = true;
					}
				}
			}
			else if(ownerPlayer != NULL){
				if(strcmp(condition->has,(char*)"yes") == STR_EQUAL){
					if(ownerPlayer->hasItem(objItem->name) == true){
						isMet = true;
					}
				}
				else{
					if(ownerPlayer->hasItem(objItem->name) == false){
						isMet = true;
					}
				}
			}
			else{
				std::cout<<"owner == NULL"<<std::endl;
			}
		}
		else{
			std::cout<<"objItem == NULL"<<std::endl;
		}
	}
	else{
		std::cout<<"Trigger::isConditionMet unknown type"<<std::endl;
	}

	return isMet;
}

/*
 *
 */
int Trigger::print(){
	int statusInt = OK;
	cout<<"		Trigger: "<<endl;
	if(type != NULL)
		std::cout<<"		type: "<<type<<std::endl;
	if(!commands.empty()){
		std::cout<<"		command: "<<std::endl;
		std::list<char*>::iterator it;
		for (it = commands.begin(); it != commands.end(); ++it){
			std::cout<<"		"<<(*it)<<std::endl;
		}
	}
	if(!conditions.empty()){
		std::cout<<"		condition: "<<std::endl;
		std::list<Condition*>::iterator it;
		for (it = conditions.begin(); it != conditions.end(); ++it){
			//std::cout<<"		"<<<<std::endl;
			(*it)->print();
		}
	}
	if(!prints.empty()){
		std::cout<<"		print: "<<std::endl;
		std::list<char*>::iterator it;
		for (it = prints.begin(); it != prints.end(); ++it){
			std::cout<<"			"<<(*it)<<std::endl;
		}
	}
	if(!actions.empty()){
		std::cout<<"		action: "<<std::endl;
		std::list<char*>::iterator it;
		for (it = actions.begin(); it != actions.end(); ++it){
			std::cout<<"		"<<(*it)<<std::endl;
		}
	}
	return statusInt;
}



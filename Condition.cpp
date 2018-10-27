/*
 * Condition.cpp
 *
 *  Created on: Oct 10, 2018
 *      Author: User
 */

#include "Condition.hpp"
#include "Element.hpp"
#include "Item.hpp"
#include "Person.hpp"
#include "Container.hpp"
#include "string.h"
#include "util.hpp"

#include <iostream>
using namespace std;

Condition::Condition(){
	condType = UN_INIT;
	// For status type
	status = '\0';
	// For owner type
	owner = '\0';
	has = '\0';
	// Both
	object = '\0';
}

Condition::~Condition(){

}

/*
 * Checks if the condition is met or not
 */
bool Condition::isConditionMet(){
	Element list;
	bool isMet = false;
	if(this->condType == STATUS){
		Element* obj = list.getElement(this->object);
		if(obj != NULL){
			std::cout<<"isConditionMet: "<<this->status<<" - "<<obj->getStatus()<<std::endl;
			if(obj->getStatus().compare((string)this->status) == STR_EQUAL){
				isMet = true;
			}
		}
		else{
			std::cout<<"ERROR: Trigger::isConditionMet: obj == NULL"<<std::endl;
		}
	}
	else if(this->condType == OWNER){
		Element* obj = list.getElement(this->object);
		Item* objItem = dynamic_cast<Item*>(obj);
		Element* owner = list.getElement(this->owner);//TODO clean up
		Container* ownerContainer = dynamic_cast<Container*>(owner);
		Person* ownerPlayer = dynamic_cast<Person*>(owner);
		if(objItem != NULL){
			if(ownerContainer != NULL){
				if(strcmp(this->has,(char*)"yes") == STR_EQUAL){
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
			else{
				if(strcmp(this->has,(char*)"yes") == STR_EQUAL){
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
		}
	}
	else{
		std::cout<<"Trigger::isConditionMet unknown type"<<std::endl;
	}

	return isMet;
}

int Condition::print(){
	int statusInt = OK;
	cout<<"			Condition: ";
	if(condType == OWNER){
		cout<<"owner"<<endl;
		cout<<"			owner: "<<owner<<endl;
		cout<<"			has: "<<has<<endl;
		cout<<"			object: "<<object<<endl;
	}
	else if(condType == STATUS){
		cout<<"status"<<endl;
		cout<<"			status: "<<status<<endl;
		cout<<"			object: "<<object<<endl;
	}
	else{
		cout<<"ERROR: Condition::print()"<<endl;
		statusInt = ERROR;
	}

	return statusInt;
}


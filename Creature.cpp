/*
 * Creature.cpp
 *
 *  Created on: Oct 5, 2018
 *      Author: User
 */

#include "Creature.hpp"
#include "util.hpp"

#include <iostream>
using namespace std;


Creature::Creature(){
	name = '\0';
	status = '\0';
	description = '\0';
	vulnerabilities = {};
	attacks = {};
	triggers = {};
}


char* Creature::getName(){
	return name;
}

/*
 *
 */
std::string Creature::getStatus(){
	return (string)status;
}

/*
 *
 */
int Creature::add(Element* add){
	int statusInt = OK;
	std::cout<<"TODO  Creature::add"<<std::endl;
	return statusInt;
}

/*
 *
 */
int Creature::deleteElement(std::string toDelete){
	int statusInt = OK;
	//std::cout<<"TODO  Creature::deleteElement("<<std::endl;
	return statusInt;
}


int Creature::setStatus(std::string newStatus){
	//std::cout<<"Container::setStatus"<<std::endl;
	status = strdup(newStatus.c_str());
	return OK;
}
/*
 * Check the triggers of the current object to and activates them
 */
int Creature::checkTriggers(std::string command){
	int statusInt = OK;
	if(!triggers.empty()){
		std::list<Trigger*>::iterator it;
		for (it = triggers.begin(); it != triggers.end(); ++it){
			Trigger* index = (*it);
			//std::cout<<"checking cond"<<std::endl;
			if(index->areAllConditionsMet() == true ){
				if(index->areAllCommandsMet(command) == true){
					//std::cout<<"Creature::checkTriggers Trigger activated"<<std::endl;
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
 * Attack the creature with the Item.
 *
 */
int Creature::attackWith(Item* item){
	int statusInt = OK;
	std::list<char*>::iterator vulIt;
	for (vulIt = vulnerabilities.begin(); vulIt != vulnerabilities.end(); ++vulIt){
		char* index = (*vulIt);
		if(strcmp(item->name, index) == STR_EQUAL){
			statusInt = START_ATTACK;
		}

	}
	if(statusInt == START_ATTACK){
		/* Iterate through all attacks */
		std::list<Attack*>::iterator attckit;
		for (attckit = attacks.begin(); attckit != attacks.end(); ++attckit){
			Attack* attack = (*attckit);
			if(!attack->conditions.empty()){
				/* Iterate through all conditions of each attack */
				std::list<Condition*>::iterator attckCond;
				for (attckCond = attack->conditions.begin(); attckCond != attack->conditions.end(); ++attckCond){
					Condition* condition = (*attckCond);
					/* Check if the condition is met */
					if(condition->isConditionMet()){
						std::cout<<"You assault the "<<name<<" with the "<<item->name<<"."<<std::endl;
						/* Do prints */
						std::list<char*>::iterator printIt;
						for (printIt = attack->prints.begin(); printIt != attack->prints.end(); ++printIt){
							std::cout<<(*printIt)<<std::endl;
						}
						/* Do action */
						std::list<char*>::iterator actionIt;
						for (actionIt = attack->actions.begin(); actionIt != attack->actions.end(); ++actionIt){
							//std::cout<<"action: "<<(*actionIt)<<std::endl;
							Element action;
							action.doAction((string)(*actionIt));
						}
					}
				}
			}else{
				std::cout<<"You assault the "<<name<<" with the "<<item->name<<"."<<std::endl;
				/* Do prints */
				std::list<char*>::iterator printIt;
				for (printIt = attack->prints.begin(); printIt != attack->prints.end(); ++printIt){
					std::cout<<(*printIt)<<std::endl;
				}
				/* Do action */
				std::list<char*>::iterator actionIt;
				for (actionIt = attack->actions.begin(); actionIt != attack->actions.end(); ++actionIt){
					//std::cout<<"action: "<<(*actionIt)<<std::endl;
					Element action;
					action.doAction((string)(*actionIt));
				}
			}
		}
	}
	else{
		std::cout<<"creature "<<name<<" not vulnerable to "<<item->name<<std::endl;
	}

	return statusInt;
}

/*
 * Print creature in readable format
 */
int Creature::print(){
	int statusInt = OK;
	if(name != NULL)
		std::cout<<"Creature: "<<name<<std::endl;
	else
		statusInt = NULL_ERROR;
	if(status != NULL)
		std::cout<<"	status: "<<status<<std::endl;
	if(description != NULL)
		std::cout<<"	description: "<<description<<std::endl;
	std::cout<<"	vulnerabilities: "<<"TODO"<<std::endl;
	std::cout<<"	attack: "<<"TODO"<<endl;

	if(!triggers.empty()){
		std::cout<<"	triggers: "<<endl;
		std::list<Trigger*>::iterator it;
		for (it = triggers.begin(); it != triggers.end(); ++it){
			//std::cout<<"		"<<(*it)<<std::endl;
			(*it)->print();
		}
	}
	return statusInt;
}



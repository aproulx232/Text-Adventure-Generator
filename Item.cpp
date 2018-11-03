/*
 * Item.cpp
 *
 *  Created on: Oct 5, 2018
 *      Author: User
 */

#include "Item.hpp"
#include "util.hpp"

#include <iostream>
using namespace std;

Item::Item(){
	name = (char*)"";
	status = (char*)"";
	description = (char*)"";
	writing = (char*)"";
	turn_on_Print = (char*)"";
	turn_on_Action = (char*)"";
	triggers ={};
}

Item::~Item(){

}

char* Item::getName(){
	//std::cout<<"Item::getName()"<<endl;
	return name;
}

int Item::setStatus(std::string newStatus){
	//std::cout<<"Item::setStatus"<<std::endl;
	status = strdup(newStatus.c_str());
	return OK;
}

/*
 *
 */
int Item::deleteElement(std::string toDelete){
	int statusInt = OK;
	//std::cout<<"TODO  Item::deleteElement("<<std::endl;
	return statusInt;
}

/*
 * Print writing on Item
 */
void Item::printWriting(){
	if(!std::string(writing).empty()){
		std::cout<<writing<<std::endl;
	}
	else{
		std::cout<<"Nothing written."<<std::endl;
	}
}
/*
 * Gets obj status
 * Return: string: status
 */
std::string Item::getStatus(){
	return (string)status;
}

/*
 *
 */
/*
 * Check the triggers of the current object to and activates them
 */
int Item::checkTriggers(std::string command){
	int statusInt = OK;
	if(!triggers.empty()){
		std::list<Trigger*>::iterator it;
		for (it = triggers.begin(); it != triggers.end(); ++it){
			Trigger* index = (*it);
			//std::cout<<"checking cond"<<std::endl;
			if(index->areAllConditionsMet() == true ){
				if(index->areAllCommandsMet(command) == true){
					//std::cout<<"Container::checkTriggers Trigger activated"<<std::endl;
					if(index->activate() != OK){
						statusInt = BLOCK_INPUT_COMMAND;
					}
				}
			}
		}
	}
	return statusInt;
}

/*
 * Check if the triggers have a command fiend that would block the input
 */
int Item::checkIfBlocked(std::string command){
	int statusInt = OK;
	if(!triggers.empty()){
		std::list<Trigger*>::iterator it;
		for (it = triggers.begin(); it != triggers.end(); ++it){
			Trigger* index = (*it);
			if(index->areCommandsMatched(command)){
				if(index->areAllConditionsMet() ){
					statusInt = BLOCK_INPUT_COMMAND;
				}
			}
		}
	}
	return statusInt;
}

int Item::print(){
	int statusInt = OK;
	if(name != NULL)
		std::cout<<"Item: "<<name<<std::endl;
	else
		statusInt = NULL_ERROR;
	if(status != NULL)
		std::cout<<"	status: "<<status<<std::endl;
	if(description != NULL)
		std::cout<<"	description: "<<description<<std::endl;
	if(writing != NULL)
		std::cout<<"	writing: "<<writing<<std::endl;
	if(turn_on_Print != NULL){
		std::cout<<"	turnon: "<<endl;
		std::cout<<"		print: "<<turn_on_Print<<std::endl;
	}
	if(turn_on_Action != NULL)
		std::cout<<"		action: "<<turn_on_Action<<std::endl;
	if(!triggers.empty())
		std::cout<<"	triggers: "<<"TODO"<<endl;
	return statusInt;
}

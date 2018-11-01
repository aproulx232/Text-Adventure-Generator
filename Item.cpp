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
	if(writing != '\0'){
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

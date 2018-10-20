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


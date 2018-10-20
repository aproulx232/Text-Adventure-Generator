/*
 * Condition.cpp
 *
 *  Created on: Oct 10, 2018
 *      Author: User
 */

#include "Condition.hpp"
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


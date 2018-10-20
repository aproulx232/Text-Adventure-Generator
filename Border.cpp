/*
 * Border.cpp
 *
 *  Created on: Oct 11, 2018
 *      Author: User
 */

#include "Border.hpp"
#include "util.hpp"

#include <iostream>
using namespace std;

Border::Border(){
	direction = '\0';
	name = '\0';
}

int Border::print(){
	int statusInt = OK;
	if(name != NULL){
		cout<<"		Border: "<<name<<endl;
		cout<<"			direction: "<<direction<<endl;
	}
	else{
		statusInt = NULL_ERROR;
	}
	return statusInt;
}

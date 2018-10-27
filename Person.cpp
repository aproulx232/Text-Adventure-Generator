/*
 * Person.cpp
 *
 *  Created on: Oct 16, 2018
 *      Author: User
 */


#include "Person.hpp"
#include "util.hpp"
#include <list>
#include <iterator>
#include <string.h>
#include <iostream>


Person::Person(){
	currentRoom = NULL;
	inventory = {};
	name = (char*)"inventory";
}

Person::Person(Element* map){
	currentRoom = NULL;
	inventory = {};
	name = (char*)"inventory";
	std::list<Element*>::iterator it;
	for (it = map->mapList.begin(); it != map->mapList.end(); ++it){
		Room* index = (dynamic_cast<Room*>(*it));
		if(index != NULL){
			if(strcmp(index->name, (char*)"Entrance")==0 ){
				std::cout<<"set curr room"<<std::endl;
				currentRoom = index;
			}
		}
	}
}

/*
 *
 */
bool Person::hasItem(char* item){
	bool hasItem = false;
	std::list<Item*>::iterator it;
	for (it = inventory.begin(); it != inventory.end(); ++it){
		if(strcmp(item, (*it)->name) == STR_EQUAL){
			hasItem = true;
		}
	}
	return hasItem;
}

/*
 * Param: Item* item: item to add
 */
void Person::addItem(Item* item){
	inventory.push_back(item);
	return;
}

/*
 * Remove item from inventory
 */
Item* Person::deleteItem(std::string item){
	Item* match = NULL;
	std::list<Item*>::iterator it;
	for (it = inventory.begin(); it != inventory.end(); ++it){
		Item* index = (*it);
		if(item.compare((string)index->name) == STR_EQUAL){
			inventory.erase(it);
		}
	}
	return match;
}
/*
 * Gets item from player's inventory
 * Param: string item: name of item pointer to return
 */
Item* Person::getItem(string item){
	std::list<Item*>::iterator it;
	for (it = inventory.begin(); it != inventory.end(); ++it){
		Item* index = (*it);
		if(index != NULL){
			if(item.compare((string)index->name) == STR_EQUAL ){
				return index;
			}
		}
	}
	return NULL;
}

char* Person::getName(){
	return name;
}

/*
 *
 */
void Person::printInventory(){
	std::list<Item*>::iterator it;
	bool printedFirstItem = false;
	std::cout<<"Inventory: ";
	if(inventory.empty()){
		std::cout<<"empty"<<std::endl;
	}
	else{
		for (it = inventory.begin(); it != inventory.end(); ++it){
			Item* index = (*it);
			if(index != NULL){
				if(printedFirstItem == true){
					std::cout<<", "<<index->name;
				}
				else{
					std::cout<<index->name;
					printedFirstItem = true;
				}
			}
		}
		std::cout<<""<<std::endl;
	}

}

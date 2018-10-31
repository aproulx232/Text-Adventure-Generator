/*
 * engine.cpp
 *
 *  Created on: Oct 16, 2018
 *      Author: User
 */

#include "engine.hpp"
#include "util.hpp"
#include "Person.hpp"
#include <string.h>

#include <iostream>

using namespace std;


int runGame(Element* map){
	int statusInt = OK;
	Person* player = new Person(map);
	map->mapList.push_back(player);
	//cout<< player->currentRoom->description<<endl;
	/* Print description of entrance*/
	if(player->currentRoom != NULL){
		std::cout<<player->currentRoom->description<<std::endl;
	}
	/* Loop for input from user*/
	bool quit = false;
	bool validCommand = false;
	while(quit == false){
		validCommand = false;
		string* input = new string();
		statusInt = getInput(input);
		if(input->compare("n") == STR_EQUAL){
			validCommand = true;
			//check curr room triggers
			//player->currentRoom->checkTriggers(*input);
			if( player->currentRoom->checkTriggers(*input) != BLOCK_INPUT_COMMAND){
				/* Execute the command*/
				//check if curr room has north
				Room* border = player->currentRoom->getBorderRoom("north");
				if(border != NULL){
					//check if south room has triggers
					player->currentRoom = border;
					std::cout<<player->currentRoom->description<<std::endl;
					if(!border->triggers.empty()){
						//check triggers if activate
						player->currentRoom->checkTriggers();
					}
				}
				else{
					std::cout<<"Can�t go that way."<<std::endl;
				}
			}
		}
		else if(input->compare("s") == STR_EQUAL){
			validCommand = true;
			//check curr room triggers
			//player->currentRoom->checkTriggers(*input);
			if( player->currentRoom->checkTriggers(*input) != BLOCK_INPUT_COMMAND){
				/* Execute the command*/
				//check if curr room has north
				Room* border = player->currentRoom->getBorderRoom("south");
				if(border != NULL){
					//check if south room has triggers
					player->currentRoom = border;
					std::cout<<player->currentRoom->description<<std::endl;
					if(!border->triggers.empty()){
						//check triggers if activate
						player->currentRoom->checkTriggers();
					}
				}
				else{
					std::cout<<"Can�t go that way."<<std::endl;
				}
			}
		}
		else if(input->compare("e") == STR_EQUAL){
			validCommand = true;
			//check curr room triggers
			//player->currentRoom->checkTriggers(*input);
			if( player->currentRoom->checkTriggers(*input) != BLOCK_INPUT_COMMAND){
				/* Execute the command*/
				//check if curr room has north
				Room* border = player->currentRoom->getBorderRoom("east");
				if(border != NULL){
					//check if south room has triggers
					player->currentRoom = border;
					std::cout<<player->currentRoom->description<<std::endl;
					if(!border->triggers.empty()){
						//check triggers if activate
						player->currentRoom->checkTriggers();
					}
				}
				else{
					std::cout<<"Can�t go that way."<<std::endl;
				}
			}
		}
		else if(input->compare("w") == STR_EQUAL){
			validCommand = true;
			//check curr room triggers
			//player->currentRoom->checkTriggers(*input);
			if( player->currentRoom->checkTriggers(*input) != BLOCK_INPUT_COMMAND){
				/* Execute the command*/
				//check if curr room has north
				Room* border = player->currentRoom->getBorderRoom("west");
				if(border != NULL){
					//check if south room has triggers
					player->currentRoom = border;
					std::cout<<player->currentRoom->description<<std::endl;
					if(!border->triggers.empty()){
						//check triggers if activate
						player->currentRoom->checkTriggers();
					}
				}
				else{
					std::cout<<"Can�t go that way."<<std::endl;
				}
			}
		}
		else if(input->compare("i") == STR_EQUAL){
			validCommand = true;
			player->printInventory();
		}
		else if(input->compare("ab") == STR_EQUAL){//TODO remove
			quit = true;
		}
		//Check that is 2 words
		else if(input->find(" ") != std::string::npos){
			std::string firstWord = input->substr(0, input->find(" "));
			//cout<<"firstword: \""<<firstWord<<"\""<<endl;
			std::string secondWord = input->substr(input->find(" ")+1, input->size());
			//cout<<"secondWord: \""<<secondWord<<"\""<<endl;

			if(firstWord.compare("take") == STR_EQUAL){
				//std::cout<<"take "<<secondWord<<std::endl;
				Item* itemToAdd = player->currentRoom->getItemAll(secondWord);
				if(itemToAdd != NULL){
					validCommand = true;
					player->addItem(itemToAdd);
					player->currentRoom->removeItemAll(secondWord);
					std::cout<<"Item "<<itemToAdd->name<<" added to inventory."<<std::endl;
				}
			}
			else if(firstWord.compare("open") == STR_EQUAL){
				if(secondWord.compare("exit") == STR_EQUAL){
					validCommand = true;
					if(((string)(player->currentRoom->type)).compare("exit") == STR_EQUAL){
						std::cout<<"Game Over"<<std::endl;
						quit = true;
					}
					else{
						std::cout<<"No exit in this room"<<std::endl;
					}

				}
				else{
					validCommand = true;
					Element temp;
					Container* container = dynamic_cast<Container*>(temp.getElement(secondWord));
					if(container != NULL){

						container->opened = true;
						container->printContents();
					}
					else{
						std::cout<<"No "<<secondWord<<" in this room"<<std::endl;
					}
				}
			}
			else if(firstWord.compare("read") == STR_EQUAL){
				Item* itemToRead = player->getItem(secondWord);
				validCommand = true;
				if(itemToRead != NULL){
					itemToRead->printWriting();
				}
				else{
					std::cout<<"No "<<secondWord<<" in your inventory"<<std::endl;
				}
			}
			else if(firstWord.compare("drop") == STR_EQUAL){
				Item* itemToDrop = player->getItem(secondWord);
				validCommand = true;
				if(itemToDrop != NULL){
					player->deleteItem((std::string)itemToDrop->name);
					Item* addToRoom = dynamic_cast<Item*>(player->getElement(secondWord));//->getName()<<std::endl;
					if(addToRoom != NULL){
						player->currentRoom->addItem(addToRoom);
						std::cout<<secondWord<<" dropped."<<std::endl;
					}
					else{
						std::cout<<"ERROR: drop: addToRoom == NULL"<<std::endl;
					}

				}
				else{
					std::cout<<"No "<<secondWord<<" in your inventory"<<std::endl;
				}
			}
			else if(firstWord.compare("put") == STR_EQUAL){
				std::string itemStr = input->substr(4, input->find(" in ") -4);
				Item* item = player->getItem(itemStr);
				validCommand = true;
				if(item != NULL){
					std::string containerStr = input->substr(input->find(" in ")+4, input->size());
					//std::cout<<"containerStr: "<<containerStr<<std::endl;
					Container* containerToAdd = dynamic_cast<Container*>(player->getElement(containerStr));
					if(containerToAdd != NULL){
						//TODO need to check if container has an accept or not, if yes, need to chek if item is correct
						statusInt = containerToAdd->addItem((std::string)item->name);
						if(statusInt == CONTAINER_ITEM_ADDED){
							player->deleteItem((std::string)item->name);
						}
						statusInt = containerToAdd->checkTriggers(*input);
					}
					else{
						std::cout<<"No "<<containerToAdd<<" in the room "<<player->currentRoom->name<<std::endl;
					}
				}
				else{
					std::cout<<"No "<<itemStr<<" in your inventory"<<std::endl;
				}
			}
			else if(firstWord.compare("attack") == STR_EQUAL){
				validCommand = true;
				std::string creatureStr = input->substr(7, input->find(" with ") -7);
				Creature* creatureToAttack = player->currentRoom->getCreatureRoom(creatureStr);
				if(creatureToAttack != NULL){
					std::string itemStr = input->substr(input->find(" with ")+6, input->size());
					Item* attackItem = player->getItem(itemStr);
					if(attackItem != NULL){
						/* Attack creature with item */
						creatureToAttack->attackWith(attackItem);
					}
					else{
						std::cout<<"No "<<itemStr<<" in your inventory"<<std::endl;
					}
				}
				else{
					std::cout<<"No creature "<<creatureStr<<" in "<<player->currentRoom->name<<std::endl;
				}
			}
			if(input->find("turn on") != std::string::npos){
				validCommand = true;
				std::string itemStr = input->substr(LEN_OF_TURN_ON, input->size());
				Element temp;
				Item* item = player->getItem(itemStr);
				if(item != NULL){
					item->doAction((string)item->turn_on_Action);
					std::cout<<"You activate the "<<itemStr<<std::endl;
					std::cout<<item->turn_on_Print<<std::endl;
				}
				else{
					std::cout<<itemStr<<" is not in your inventory"<<std::endl;
				}
				player->currentRoom->checkTriggers(*input);
				//std::cout<<item->status<<std::endl;
			}
		}
		if(validCommand ==false){
			std::cout<<"Error "<<std::endl;
		}
		//std::cout<<""<<std::endl;
	}
	return statusInt;
}

int getInput(string* input){
	int statusInt = OK;
	getline(std::cin,*input);
	return statusInt;

}



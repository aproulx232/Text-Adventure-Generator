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
	while(quit == false){
		string* input = new string();
		statusInt = getInput(input);
		if(input->compare("n") == STR_EQUAL){
			//check curr room triggers
			//player->currentRoom->checkTriggers(*input);
			if( player->currentRoom->checkTriggers(*input) != TRIGGER_ACTIVATED){
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
					std::cout<<"Can’t go that way."<<std::endl;
				}
			}

		}
		else if(input->compare("s") == STR_EQUAL){
			//check curr room triggers
			player->currentRoom;
			//check if curr room has south
			Room* borderS = player->currentRoom->getBorderRoom("south");
			if(borderS){
				//check if south room has triggers
				player->currentRoom = borderS;
				if(!borderS->triggers.empty()){
					//check triggers if activate
					//TODO
				}
			}
			else{
				std::cout<<"Can’t go that way."<<std::endl;
			}
		}
		else if(input->compare("e") == STR_EQUAL){

		}
		else if(input->compare("w") == STR_EQUAL){

		}
		else if(input->compare("i") == STR_EQUAL){
			player->printInventory();
		}
		else if(input->compare("ab") == STR_EQUAL){//TODO remove
			quit = true;
		}
		//Check that is 2 words
		else if(input->find(" ") != std::string::npos){
			std::string firstWord = input->substr(0, input->find(" "));
			cout<<"firstword: \""<<firstWord<<"\""<<endl;
			std::string secondWord = input->substr(input->find(" ")+1, input->size());
			cout<<"secondWord: \""<<secondWord<<"\""<<endl;

			if(firstWord.compare("take") == STR_EQUAL){
				std::cout<<"take "<<secondWord<<std::endl;
				Item* itemToAdd = player->currentRoom->getItemAll(secondWord);
				if(itemToAdd != NULL){
					cout<<"test name: "<<itemToAdd->name<<endl;
					player->addItem(player->currentRoom->getItemAll(secondWord));
				}
			}
			else if(firstWord.compare("open") == STR_EQUAL){
				if(secondWord.compare("exit") == STR_EQUAL){
					std::cout<<"out exit!!!"<<std::endl;
					if(((string)(player->currentRoom->type)).compare("exit") == STR_EQUAL){
						std::cout<<"Game Over"<<std::endl;
						quit = true;
					}

				}

			}
			else if(input->compare("n") == STR_EQUAL){

			}
			else if(input->compare("n") == STR_EQUAL){

			}
			else{
				std::cout<<"Error "<<std::endl;
			}
		}
		else{
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



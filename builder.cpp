/*
 * builder.cpp
 *
 *  Created on: Oct 9, 2018
 *      Author: User
 */

#include "builder.hpp"
#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "Element.hpp"
#include "Room.hpp"

#include <list>
#include <iterator>

using namespace std;
using namespace rapidxml;

int buildGame(char * buffer){
	int status = OK;
	Element* map = new Element();
	xml_document<> doc;
	doc.parse<0>(buffer);
	xml_node<> * mapNode = doc.first_node();
	//cout<< mapNode->name()<<endl;
	if(strcmp(mapNode->name(),(char*)"map") != 0){
		status = ERROR;
	}
	else{
		xml_node<> * firstNode = mapNode->first_node();
		for(xml_node<> * nodeIndex = firstNode; nodeIndex; nodeIndex= nodeIndex->next_sibling()){
				std::cout << nodeIndex->name()<<std::endl;
				if(strcmp(nodeIndex->name(),(char*)"room")==0){
					Room* room = new Room();
					map->list.push_back(room);
					status = buildRoom(nodeIndex, room);
					/*
					for(xml_node<> * roomNodeIndex = nodeIndex->first_node(); roomNodeIndex; roomNodeIndex = roomNodeIndex->next_sibling()){
						if(strcmp(roomNodeIndex->name(),(char*)"name") == 0){
							room->name = roomNodeIndex->value();
						}
						else if(strcmp(roomNodeIndex->name(),(char*)"description") == 0){
							room->description = roomNodeIndex->value();
						}
						else if(strcmp(roomNodeIndex->name(),(char*)"status")){
							room->status = roomNodeIndex->value();
						}
						else if(strcmp(roomNodeIndex->name(),(char*)"type")){
							room->type = roomNodeIndex->value();
						}
						else{
							cout<<"ERROR: Undefined field for Room in builder.cpp: "<< roomNodeIndex->name()<<endl;
						}

					}
					*/


				}
			}
	}

	return status;
}

// Reads xml node info into Room object that is passed in
int buildRoom(xml_node<> * node, Room * room){
	int status = OK;
	for(xml_node<> * roomNodeIndex = node->first_node(); roomNodeIndex; roomNodeIndex = roomNodeIndex->next_sibling()){
		cout<<roomNodeIndex->name()<<endl;
		if(strcmp(roomNodeIndex->name(),(char*)"name") == 0){
			room->name = roomNodeIndex->value();
		}
		else if(strcmp(roomNodeIndex->name(),(char*)"description") == 0){
			room->description = roomNodeIndex->value();
		}
		else if(strcmp(roomNodeIndex->name(),(char*)"status")==0){
			room->status = roomNodeIndex->value();
		}
		else if(strcmp(roomNodeIndex->name(),(char*)"type")==0){
			room->type = roomNodeIndex->value();
		}
		else if(strcmp(roomNodeIndex->name(),(char*)"container")==0){
			Container * containerObj = new Container();
			room->containers.push_back(containerObj);
			status = buildContainer(roomNodeIndex, containerObj);
		}
		else if(strcmp(roomNodeIndex->name(),(char*)"item")==0){
			Item* itemObj = new Item();
			room->items.push_back(itemObj);
			status = buildItem(roomNodeIndex, item);

		}
		else{
			cout<<"ERROR: Undefined field for Room in builder.cpp: "<< roomNodeIndex->name()<<endl;
			status = ERROR;
		}

	}
	return status;
}
/*
 * TODO
 */
int buildContainer(xml_node<> * node, Container * container){
	cout<<"TODO: buildContainer"<<endl;
	int status = OK;
	for(xml_node<> * nodeIndex = node->first_node(); nodeIndex; nodeIndex = nodeIndex->next_sibling()){
		//cout<<nodeIndex->name()<<endl;
		if(strcmp(nodeIndex->name(),(char*)"name") == 0){
			container->name = nodeIndex->value();
		}
		else if(strcmp(nodeIndex->name(),(char*)"description") == 0){
			container->description = nodeIndex->value();
		}
		else if(strcmp(nodeIndex->name(),(char*)"status")==0){
			container->status = nodeIndex->value();
		}
		else{
			cout<<"ERROR: Undefined field for "<<node->name()<< "in builder.cpp: "<< nodeIndex->name()<<endl;
			status = ERROR;
		}


	}
	return status;
}



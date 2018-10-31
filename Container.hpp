/*
 * Container.hpp
 *
 *  Created on: Oct 5, 2018
 *      Author: User
 */

#ifndef CONTAINER_HPP_
#define CONTAINER_HPP_

#include "Element.hpp"
#include "Item.hpp"

#include <list>
#include <iterator>

class Container: public Element{
public:
	char * name;
	char * status;
	char * description;
	bool opened;
	std::list <char*> accepts;
	std::list <char*> items;
	std::list <Trigger*> triggers;

	Container();
	bool hasItem(char*);
	Item* getItem(std::string item);
	int addItem(std::string item);
	void printContents();
	Item* removeItem(std::string item);
	int checkTriggers(std::string command);


	virtual char* getName();
	virtual int print();
	virtual std::string getStatus();
	virtual int setStatus(std::string newStatus);
	virtual int add(Element* add);
	virtual int deleteElement(std::string toDelete);

};




#endif /* CONTAINER_HPP_ */

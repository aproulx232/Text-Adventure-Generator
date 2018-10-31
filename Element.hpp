/*
 * Element.hpp
 *
 *  Created on: Oct 5, 2018
 *      Author: User
 */

#ifndef ELEMENT_HPP_
#define ELEMENT_HPP_
#include <list>
#include <iterator>

//#include "builder.hpp"

using namespace std;

class Element{
public:
	Element();
	virtual~Element();
	static list <Element*> mapList;
	static list <Element*> deleteList;
	Element* getElement(char* name);
	Element* getElement(std::string name);
	int printMapList();
	int doAction(string actionStr);

	virtual char* getName();
	virtual int print();
	virtual std::string getStatus();
	virtual int setStatus(std::string newStatus);
	virtual int add(Element* add);

};





#endif /* ELEMENT_HPP_ */

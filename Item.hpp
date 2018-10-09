/*
 * Item.hpp
 *
 *  Created on: Oct 5, 2018
 *      Author: User
 */

#ifndef ITEM_HPP_
#define ITEM_HPP_

#include "Element.hpp"
#include "Trigger.hpp"

class Item :public Element{
public:
	char * name;
	char * status;
	char * description;
	char * writing;
	char * turn_on;
	Trigger * triggers;
};



#endif /* ITEM_HPP_ */

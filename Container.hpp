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
	std::list <Item*> accepts;
	std::list <Item*> items;
	std::list <Trigger*> triggers;

	Container();

};




#endif /* CONTAINER_HPP_ */

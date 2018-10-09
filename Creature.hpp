/*
 * Creature.hpp
 *
 *  Created on: Oct 5, 2018
 *      Author: User
 */

#ifndef CREATURE_HPP_
#define CREATURE_HPP_

#include "Element.hpp"

class Creature: public Element{
public:
	char * name;
	char * status;
	char * description;
	char * vulnerability;//TODO may need double pointer is more than 1
	//TODO add attack class
	Trigger * triggers;

};



#endif /* CREATURE_HPP_ */

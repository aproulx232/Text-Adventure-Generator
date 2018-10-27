/*
 * Condition.hpp
 *
 *  Created on: Oct 10, 2018
 *      Author: User
 */

#ifndef CONDITION_HPP_
#define CONDITION_HPP_

class Condition{
public:
	int condType;
	// For status type
	char* status;
	// For owner type
	char* owner;
	char* has;
	// Both
	char* object;

	Condition();
	virtual~Condition();
	int print();
	bool isConditionMet();


};

enum _ConditionType{
	UN_INIT,
	STATUS,
	OWNER
};

#endif /* CONDITION_HPP_ */

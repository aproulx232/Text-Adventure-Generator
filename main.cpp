/*
 * main.cpp
 *
 *  Created on: Oct 4, 2018
 *      Author: User
 */
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include "XML_Parser/rapidxml.hpp"
#include "XML_Parser/rapidxml_print.hpp"
//#include "rapidxml_iterators.hpp"
//#include "rapidxml_utils.hpp"

#include "builder.hpp"
#include "engine.hpp"
#include "util.hpp"

using namespace std;
using namespace rapidxml;

int main(){
	FILE *fp;
	long lSize;
	char *buffer;

	//fp = fopen ( "../XML_Tests/sample.txt.xml" , "rb" );
	fp = fopen ( "../XML_Tests/creaturesample.xml" , "rb" );
	//fp = fopen ( "creaturesample.xml" , "rb" );
	//fp = fopen ( "../XML_Tests/containersample.xml" , "rb" );
	//fp = fopen ( "../XML_Tests/itemsample.xml" , "rb" );
	//fp = fopen ( "../XML_Tests/roomsample.xml" , "rb" );
	//fp = fopen ( "../XML_Tests/triggersample.xml" , "rb" );
	if( !fp ){
		perror("Invalid xml path");
	}

	fseek( fp , 0L , SEEK_END);
	lSize = ftell( fp );
	rewind( fp );

	/* allocate memory for entire content */
	buffer = (char *)calloc( 1, sizeof(char)*(lSize+1) );
	if( !buffer ){
		fclose(fp),fputs("malloc fails",stderr),exit(1);
	}

	/* copy the file into the buffer */
	if( 1!=fread( buffer , lSize, 1 , fp) ){
		fclose(fp);
		free(buffer);
	}

	buffer[lSize] = '\0';

	int status = OK;
	Element* map = new Element();
	status = buildGame(buffer, map);
	status = runGame(map);
	if(!Element::quit){
		std::cout<< "status: "<<status<<std::endl;
	}
	fclose(fp);
	free(buffer);
	return 0;
}


/*
 * TODO LIST:
 * Trigger::activate() have statusInt instead of bool so can quit game
 * check triggers on inventory
 * add check to see if input is blocked
 */



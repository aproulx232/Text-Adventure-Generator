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

	//fp = fopen ( "XML_Tests/sample.txt.xml" , "rb" );
	fp = fopen ( "XML_Tests/creaturesample.xml" , "rb" );
	if( !fp ) perror("blah.txt"),exit(1);

	fseek( fp , 0L , SEEK_END);
	lSize = ftell( fp );
	rewind( fp );

	/* allocate memory for entire content */
	buffer = (char *)calloc( 1, sizeof(char)*(lSize+1) );
	if( !buffer ) fclose(fp),fputs("memory alloc fails",stderr),exit(1);

	/* copy the file into the buffer */
	if( 1!=fread( buffer , lSize, 1 , fp) )
	  fclose(fp),free(buffer),fputs("entire read fails",stderr),exit(1);
	buffer[lSize] = '\0';
	/* do your work here, buffer is a string contains the whole text */
	//cout <<buffer<<endl;
	//cout << "parsing" <<endl;
	int status = OK;
	Element* map = new Element();
	status = buildGame(buffer, map);
	status = runGame(map);
	std::cout<< "status: "<<status<<std::endl;
	/*
	xml_document<> doc;    // character type defaults to char
	doc.parse<0>(buffer);    // 0 means default parse flags

	cout << "Name of my first node is: " << doc.first_node()->name() << "\n"<<endl;
	xml_node<> *node = doc.first_node("map");
	cout << "Node map has node " << node->first_node()->name() << "\n"<<endl;
	xml_node<> *node1 = node->first_node();
	cout << "Node room has node " << node1->next_sibling()->name()<<": room as child"<<node1->first_node()->name()<<endl;
	node1 = node1->first_node();
	cout<< "name of room"<<node1->value()<<endl;
	for (xml_node<> *node_inx = node1;node_inx; node_inx = node_inx->next_sibling())
	{
	    cout << "Node " << node1->name()<<" has sibling " << node_inx->name() << endl;
	    //cout << "with value " << attr->value() << "\n";
	}
	cout <<"done"<<endl;
*/


	fclose(fp);
	free(buffer);
/*
	string line;
	  ifstream myfile ("sample.txt.xml");
	  if (myfile.is_open())
	  {
	    while ( getline (myfile,line) )
	    {
	      cout << line << '\n';
	    }
	    myfile.close();
	  }

	  else cout << "Unable to open file";
*/


	return 0;
}


/*
 * TODO LIST:
 * Trigger::activate() have statusInt instead of bool so can quit game
 */



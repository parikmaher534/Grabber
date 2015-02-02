#include<iostream>
#include<string>
#include<stdlib.h>

using namespace std;


int downloadFile(string address, string filename) {
	FILE *pipe;
	
	errno = 0;

	string commandName = "curl -s -o";

	//If file name has GET params remove them
	int paramsPos;
	if( 
		(paramsPos = filename.find("?")) != string::npos 
	) {
		filename = filename.substr(0,paramsPos);
	}

	string command = commandName+ " " +filename+ " '" +address+ "'";

    if( !(pipe = popen(command.c_str(), "r")) ) {
        exit(1);
		cout << "Can't init pipe." << endl;
    } 

    pclose(pipe);

	return errno;
}

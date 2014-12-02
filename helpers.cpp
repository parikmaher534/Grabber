#include<iostream>
#include<string>
#include<stdlib.h>

using namespace std;


int downloadFile(string address, string filename) {
	FILE *pipe;
	
	string commandName = "curl -s -o";
	string command = commandName+ " " +filename+ " " +address;

    if( !(pipe = popen(command.c_str(), "r")) ) {
        exit(1);
		cout << "Can't init pipe." << endl;
    } 

    pclose(pipe);

	return errno;
}

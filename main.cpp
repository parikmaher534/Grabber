#include "main.h"

#include <regex>

int main(int argc, char *argv[]) 
{
	/* First argument must be the site URL */
	try {
		if( argv[1] ) {
			currentProject = new Project(argv[1]);
		}
		else {
			cout << "Please set site URL." << endl;
		}
	} catch(exception& e) {
		cout << "ERROR: " << e.what() << endl;	
	}

	return 0;	
}


#include "main.h"

int main(int argc, char *argv[]) 
{
	/* First argument must be the site URL */
	if( argv[1] ) {
		new Project(argv[1]);
	}
	else {
		cout << "Please set site URL." << endl;
	}

	return 0;	
}


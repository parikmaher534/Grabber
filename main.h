#include <iostream>
#include <exception>
#include <vector>
#include <regex>
#include <sys/stat.h>

#include "helpers.cpp"
#include "items/file.cpp"
#include "items/page.cpp"
#include "items/site.cpp"

using namespace std;

static Project* currentProject;

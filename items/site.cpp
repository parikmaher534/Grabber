#include <regex>

class Project 
{
	public:
		Project(char* url);
		string name;
		string url;
		vector<Page*> Pages;
	private:
		string GetProjectName();
};


Project::Project(char* url) 
{
	cout << "Site project: <" << url << "> was created." << endl;
	
	Project::url = url;
	Project::name = Project::GetProjectName();
	Project::Pages.push_back(new Page(url));
}


string Project::GetProjectName()
{
	cmatch _match;

	regex_match(url.c_str(), _match, regex("(https://|http://)www.?(.*)"));

	for( int i = 0; i < _match.size(); i++ ){
		cout << ": " << _match[i] << endl;	
	}

	return url;	
}

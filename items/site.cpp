class Project 
{
	public:
		Project(char* url);
		string name;
		string url;
		vector<Page*> Pages;
	private:
		string GetProjectName();
		void CreateProjectDir();
};


Project::Project(char* url) 
{
	cout << "---| Site project: " << url << " was created." << endl;
	
	Project::url = url;
	Project::name = Project::GetProjectName();

	Project::CreateProjectDir();
	Project::Pages.push_back(new Page(url, name));
}

/* Parse url and return site name */
string Project::GetProjectName()
{
	cmatch _match;

	regex_match(url.c_str(), _match, regex("[a-z:/]+/([a-z.]+).*"));

	return _match[1];	
}

/* Check and create project root directory */
void Project::CreateProjectDir()
{
	int status = mkdir(name.c_str(), S_IRWXU);

	if( status == -1 ) {
		cout << "-----| Create project directory error: " << strerror(errno) << endl;
	}
}



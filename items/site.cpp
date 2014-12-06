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
	cout << "Site project: <" << url << "> was created." << endl;
	
	Project::url = url;
	Project::name = Project::GetProjectName();

	Project::CreateProjectDir();
	Project::Pages.push_back(new Page(url));
}

/* Parse url and return site name */
string Project::GetProjectName()
{
	cmatch _match;

	regex_match(url.c_str(), _match, regex("[a-z:/]+/([a-z.]+)[a-z./]+"));

	return _match[1];	
}

/* Check and create project root directory */
void Project::CreateProjectDir()
{
	int status = mkdir(name.c_str(), S_IRWXU);

	if( status == -1 ) {
		switch(errno) {
			case 17:
				cerr << "Directory already exist." << endl;
				break;
			default:
				throw "Can't create directory.";
		}
	}
}



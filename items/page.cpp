class Page 
{
	public:
		Page(char* projectUrl, string projectName);
		string url;
		string projectName;
		string name;
		string HTML;
		
		vector<HTMLFile*> Images;
		vector<HTMLFile*> Scripts;
		vector<HTMLFile*> Styles;
	private:
	    string GetPageName();
		void CreatePageDir();
		void GetPageHTML();
		void DownloadPage();
	    void ParseHTML();
};


Page::Page(char* projectUrl, string projectName) 
{
	Page::url = projectUrl;
	Page::projectName = projectName;
	Page::name = Page::GetPageName();
	Page::CreatePageDir();
	
	cout << "---| Page: " << name << " was added to project" << endl;
}

string Page::GetPageName() 
{
	string s_match;
	cmatch _match;

	regex_match(url.c_str(), _match, regex("[a-z:/]+/([a-z.]+)([a-z./_-]+)"));
	s_match += _match[2];

	return regex_replace(s_match, regex("(/)"), "_");
}

void Page::CreatePageDir()
{
	int status = mkdir((projectName + "/" + name).c_str(), S_IRWXU);

	if( status == -1 ) {
		cout << "-----| Create page directory error: " << strerror(errno) << endl;
	}
}

void Page::DownloadPage()
{
	if( downloadFile(url, "ssfs") == 0 ) {
		throw("Can't download file");	
	};
}

void Page::GetPageHTML() 
{
	cout << url;	
}

void Page::ParseHTML() 
{
	cout << "Start parsing page..." << endl;
}

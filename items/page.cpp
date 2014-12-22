#include <fstream>
#include <streambuf>

class Page 
{
	public:
		Page(char* projectUrl, string projectName);
		string url;
		string projectName;
		string filePath;
		string name;
		string HTML;
		
		vector<HTMLFile*> Images;
		vector<HTMLFile*> Scripts;
		vector<HTMLFile*> Styles;
	private:
	    string GetPageName();
		void CreatePageDir();
		void DownloadPage();
	    void ParseHTML();
};


Page::Page(char* projectUrl, string projectName) 
{
	Page::url = projectUrl;
	Page::projectName = projectName;
	Page::name = Page::GetPageName();
	
	Page::CreatePageDir();
	Page::DownloadPage();
	Page::ParseHTML();
	
	cout << "---| Page: " << name << " was added to project" << endl;
}

string Page::GetPageName() 
{
	string s_match;
	cmatch _match;

	regex_match(url.c_str(), _match, regex("[a-z:/]+/([a-z.]+)([a-z0-9./_-]+)"));
	s_match += _match[2];

	return regex_replace(s_match, regex("(/)"), "_");
}

void Page::CreatePageDir()
{
	int status = mkdir((projectName + "/" + name).c_str(), S_IRWXU);
	
	if( status == -1 ) {
		cout << "-----| Create page directory error: " << strerror(errno) << endl;
	} else {
		cout << "-----| Page directory was succesfuly created. " << endl;
	}
}

void Page::DownloadPage()
{
	string pathToFile = (projectName + "/" + name);

	if( name.find(".") == string::npos ) pathToFile += "/index.html";

	Page::filePath = pathToFile;

	if( downloadFile(url, pathToFile.c_str()) == 0 ) {
		cout << "-----| Page file download error."<< endl;
	};
}

void Page::ParseHTML() 
{
	cout << "Start parsing page..." << endl;

	ifstream htmlSource(filePath);
    string html((istreambuf_iterator<char>(htmlSource)), istreambuf_iterator<char>());

	/* Get all CSS files */
	regex pattern("<link.+>");
	regex_iterator<string::iterator> it(html.begin(), html.end(), pattern);
	regex_iterator<string::iterator> end;

	for( ; it != end; ++it ) {
		string temp = it->str();
		string hrefSign = "href=\"";

		int hrefSignPos = temp.find(hrefSign);
		int hrefSignPosEnd;

		//Do we have HREF attr
		if( hrefSignPos != string::npos ) {
			temp = temp.substr(hrefSignPos + hrefSign.size(), -1);
			hrefSignPosEnd = temp.find("\"");

			//Is href attr valid
			if( hrefSignPosEnd != string::npos ) {
				temp = temp.substr(0, hrefSignPosEnd);
			}
		}
	}
}




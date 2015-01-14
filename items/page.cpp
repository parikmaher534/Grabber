#include <fstream>
#include <streambuf>

class Page 
{
	public:
		Page(char* projectUrl, string projectName);
		string url;
		string pageDir;
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
		void FindStyles(GumboNode* node);
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

	if( s_match == "/" ) return "index";

	s_match = s_match.substr(1, s_match.length());	

	return regex_replace(s_match, regex("(/)"), "_");
}

void Page::CreatePageDir()
{
	Page::pageDir = projectName + "/" + name;
	int status = mkdir(Page::pageDir.c_str(), S_IRWXU);
	
	if( status == -1 ) {
		cout << "-----| Create page directory error: " << strerror(errno) << endl;
	} else {
		cout << "-----| Page directory was successfully created. " << endl;
	}
}

void Page::DownloadPage()
{
	if( name.find(".") == string::npos ) Page::filePath = Page::pageDir + "/index.html";

	if( downloadFile(url, Page::filePath.c_str()) != 0 ) {
		cout << "-----| Page file download error."<< endl;
	};
}


void Page::FindStyles(GumboNode* node) {
	if( node->type != GUMBO_NODE_ELEMENT ) {
		return;
	}

	if( node->v.element.tag == GUMBO_TAG_LINK ) {
		GumboAttribute* href = gumbo_get_attribute(&node->v.element.attributes, "href");
		GumboAttribute* type = gumbo_get_attribute(&node->v.element.attributes, "type");
	
		if( type ) {
			string typeVal = type->value;
			string value = href->value;
			string cssPath, cssName;

			if( typeVal == "text/css" ) {
				
				//If absolute path
				if( value.compare(0,1, "/") == 0 ) {
					cssPath = projectName + value;
				
				//If path to styles relative
				} else {
					if( name == "index" ) {
						cssPath = projectName + value;	
					} else {
						cssPath = projectName + name + value;	
					}
				}

				//Get CSS file name
				cmatch _match;
				regex_match(href->value, _match, regex(".+/(.+)$"));
				cssName = _match[1];

				//Load css file
				if( downloadFile(cssPath, (Page::pageDir + "/css/" + cssName ).c_str() ) != 0 ) {
					cout << "-----| Page file download error."<< endl;
				};
			}
		}
	}

	GumboVector* children = &node->v.element.children;

	for( int i = 0; i < children->length; i++ ) {
		Page::FindStyles(static_cast<GumboNode*>(children->data[i]));	
	}
}


void Page::ParseHTML() 
{
	ifstream htmlSource(filePath);
    string html((istreambuf_iterator<char>(htmlSource)), istreambuf_iterator<char>());

	//Create CSS dir
	if( mkdir((Page::pageDir + "/css").c_str(), S_IRWXU) == -1 ) {
		cout << "-----| Create CSS directory error: " << strerror(errno) << endl;
	};
	
	/* Use GUMBO to parse and load styles */
    GumboOutput* out = gumbo_parse(html.c_str());	
	Page::FindStyles(out->root);
	//TODO: find and load images
}




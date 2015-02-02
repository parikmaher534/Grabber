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
		void FindImages(GumboNode* node);
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

	regex_match(url.c_str(), _match, regex("(https?://)*(www.)*([a-zA-Z0-9.]+)/*([a-zA-Z0-9/.]*)"));
	s_match += _match[4];

	if( s_match == "/" || s_match == "" ) return "index";

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


//TODO: make common function fot FindStyles and FindImages

void Page::FindStyles(GumboNode* node) {
	if( node->type != GUMBO_NODE_ELEMENT ) {
		return;
	}

	//TODO: parse STYLE tag. GUMBO can't get this tag content

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
				}	
				//If file from another domain | current but with full path
				else if(  
					value.find("http") != string::npos ||
					value.find("www") != string::npos
				) {
					cssPath = value;	
				}
				//If path to styles relative
				else {
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

void Page::FindImages(GumboNode* node) {
	if( node->type != GUMBO_NODE_ELEMENT ) {
		return;
	}

	if( node->v.element.tag == GUMBO_TAG_IMG ) {
		GumboAttribute* src = gumbo_get_attribute(&node->v.element.attributes, "src");
	
		string value = src->value;
		string imgPath, imgName;

		//If absolute path
		if( value.compare(0,1, "/") == 0 ) {
			imgPath = projectName + value;
	
		}
		//If file from another domain | current but with full path
		else if(  
			value.find("http") != string::npos ||
			value.find("www") != string::npos
		) {
			imgPath = value;	
		}
		//If path to iameg is relative
		else {
			if( name == "index" ) {
				imgPath = projectName + value;	
			} else {
				imgPath = projectName + name + value;	
			}
		}

		//Get image name
		cmatch _match;
		regex_match(src->value, _match, regex(".+/(.+)$"));
		imgName = _match[1];

		//Load image
		if( downloadFile(imgPath, (Page::pageDir + "/images/" + imgName ).c_str() ) != 0 ) {
			cout << "-----| Page file download error."<< endl;
		};
	}

	GumboVector* children = &node->v.element.children;

	for( int i = 0; i < children->length; i++ ) {
		Page::FindImages(static_cast<GumboNode*>(children->data[i]));	
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
	
	//Create IMG dir
	if( mkdir((Page::pageDir + "/images").c_str(), S_IRWXU) == -1 ) {
		cout << "-----| Create IMAGES directory error: " << strerror(errno) << endl;
	};
	
	/* Use GUMBO to parse and load styles */
    GumboOutput* out = gumbo_parse(html.c_str());	
	Page::FindStyles(out->root);
	Page::FindImages(out->root);
}




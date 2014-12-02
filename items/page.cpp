class Page 
{
	public:
		Page(char* url);
		string url;
		string pageFilePath;
		string HTML;
		
		vector<HTMLFile*> Images;
		vector<HTMLFile*> Scripts;
		vector<HTMLFile*> Styles;
	private:
		void GetPageHTML();
	    void ParseHTML();
};


Page::Page(char* url) 
{
	cout << "Page <" << url << "> was added to project" << endl;
	
	Page::url = url;
	Page::GetPageHTML();
}


void Page::GetPageHTML() 
{
	cout << url;	

	/*if( downloadFile(url, pageFilePath) != 0 ) {
		Page::ParseHTML();
	} else {
		throw("Can't download file");	
	}*/
}


void Page::ParseHTML() 
{
	cout << "Start parsing page..." << endl;

}

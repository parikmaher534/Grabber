class HTMLFile
{
	public:
		HTMLFile(char* path);
		string name;
};

HTMLFile::HTMLFile(char* path) {
	cout << "File <" << path << "> was created" << endl;	
}

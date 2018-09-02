class Message
{
pubic:
	//folders is initialized to the empty set automatically
	Message(const std::string &str="") 
	  : contents(str)
	{		
	}
	//copy control:we must manage pointers to this Message
	//from the Folders pointed to by folders
	Message(const Message&);
	Message& operator=(const Message&);
	~Message();
	//save/remove this Message from specified Folder's set of messages
	void save(Folder&);
	void remove(Folder&);
private:
	std::string contents;
	std::set<Folder*> folders;
	void putMsgInFolders(const std::set<Folder*> &);
	void removeMsgFromFolders();
};
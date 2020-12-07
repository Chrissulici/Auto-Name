//search:
		bool		Connect(const char * host, const int port, const char * user, const char * pwd, const char * db);

//add:
#ifdef ENABLE_AUTONAME_SYSTEM
		void		ChangeNameLog(const char* old_name, const char* new_name, const char* gm);
#endif
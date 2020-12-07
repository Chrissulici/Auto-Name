//search:
extern int (*check_name) (const char * str);

//add:
#ifdef ENABLE_AUTONAME_SYSTEM
extern int (*check_auto_name) (const char * str);
#endif
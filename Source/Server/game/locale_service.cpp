//search:
int (*check_name) (const char * str) = NULL;

//add:
#ifdef ENABLE_AUTONAME_SYSTEM
int (*check_auto_name) (const char * str) = NULL;
#endif

//search:
int check_name_alphabet(const char * str)
{
	[...]
}

//add:
#ifdef ENABLE_AUTONAME_SYSTEM
int check_auto_name_alphabet(const char * str)
{
	const char*	tmp;

	if (!str || !*str)
		return 0;

	if (strlen(str) < 2)
		return 0;

	for (tmp = str; *tmp; ++tmp)
	{
		if (isdigit(*tmp) || isalpha(*tmp) || *tmp == '_' || *tmp == '-' || *tmp == '.'  || *tmp == '#' || *tmp == '^' || *tmp == '*' 
				|| *tmp == '~' || *tmp == '<' || *tmp == '>' || *tmp == '/' || *tmp == '[' || *tmp == ']'
			)
			continue;
		else
			return 0;
	}

	return check_name_independent(str);
}
#endif


//search static void __LocaleService_Init_Romania() or your locale:
	check_name = check_name_alphabet;

//add:
#ifdef ENABLE_AUTONAME_SYSTEM
	check_auto_name = check_auto_name_alphabet;
#endif


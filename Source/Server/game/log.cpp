//add at the end of file:
#ifdef ENABLE_AUTONAME_SYSTEM
void LogManager::ChangeNameLog(const char* old_name, const char* new_name, const char* gm)
{
	static char	__escape_old_name[30 * 2];
	static char	__escape_new_name[30 * 2];
	m_sql.EscapeString(__escape_old_name, sizeof(__escape_old_name), old_name, strlen(old_name));
	m_sql.EscapeString(__escape_new_name, sizeof(__escape_new_name), new_name, strlen(new_name));
	Query("INSERT INTO log.log_change_name (old_name, new_name, date, gm) VALUES('%s', '%s', NOW(), '%s')", __escape_old_name, __escape_new_name, gm);
}
#endif


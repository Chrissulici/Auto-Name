//search:
	HEADER_CG_SCRIPT_SELECT_ITEM					= 114,

//add:
#ifdef ENABLE_AUTONAME_SYSTEM
	HEADER_CG_AUTONAME								= 119,
#endif

//add at the end of file:
#ifdef ENABLE_AUTONAME_SYSTEM
typedef struct packet_set_autoname
{
	BYTE	header;
	char	szName[CHARACTER_NAME_MAX_LEN + 1];
} TPacketCGSetAutoName;
#endif


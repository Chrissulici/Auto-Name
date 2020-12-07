//search:
	Set(HEADER_CG_STATE_CHECKER, 			sizeof(BYTE), 							"ServerStateCheck"

//add:
#ifdef ENABLE_AUTONAME_SYSTEM
	Set(HEADER_CG_AUTONAME,					sizeof(TPacketCGSetAutoName),			"ChangeAutoName",		true	);
#endif
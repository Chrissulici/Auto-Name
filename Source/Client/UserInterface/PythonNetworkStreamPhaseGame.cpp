//add at the end of file:
#ifdef ENABLE_AUTONAME_SYSTEM
bool CPythonNetworkStream::SendAutoNamePacket(const char* name)
{
	TPacketCGSetAutoName pack;
	pack.header = HEADER_CG_AUTONAME;
	strcpy(pack.szName, name);

	if (!Send(sizeof(pack), &pack))
	{
		Tracen("CPythonNetworkStream::SendAutoNamePacket - ERROR");
		return false;
	}
	
	return SendSequence();
}
#endif


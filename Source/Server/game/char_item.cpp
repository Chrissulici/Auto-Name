//search:
	switch (item->GetType())
	{
		case ITEM_HAIR:
			return ItemProcess_Hair(item, wDestCell);

//add before:
#ifdef ENABLE_AUTONAME_SYSTEM
	if (item->GetVnum() == AUTONAME_SCROLL_VNUM)
		ChatPacket(CHAT_TYPE_COMMAND, "OpenAutoNameSystem");
#endif
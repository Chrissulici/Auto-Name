//search:
		case HEADER_CG_REFINE:
			Refine(ch, c_pData);
			break;

//add:
#ifdef ENABLE_AUTONAME_SYSTEM
		case HEADER_CG_AUTONAME:
			ChangeAutoName(ch, c_pData);
			break;
#endif

//add at the end of file:
#ifdef ENABLE_AUTONAME_SYSTEM
void CInputMain::ChangeAutoName(LPCHARACTER ch, const char* c_pData)
{
	if (!ch)
		return;
	
	if (ch->IsDead() || ch->IsStun())
		return;
	
	TPacketCGSetAutoName* p = (TPacketCGSetAutoName*)c_pData;

	char szName[CHARACTER_NAME_MAX_LEN * 2 + 1];
	DBManager::instance().EscapeString(szName, sizeof(szName), p->szName, strlen(p->szName));
	
	LPITEM item = ch->FindSpecifyItem(AUTONAME_SCROLL_VNUM);
	
	if (!item)
		return;
	
	if (!*szName)
		return;
	
	if (!check_auto_name(szName))
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("This name is invalid."));
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("Special characters accepted: '_' / '-' / '.' / '#' / '^' / '*' / '~' / '<' '>' / '/' / '[' / ']'"));
		return;
	}
	
	const std::string & stName = szName;
	
	if (stName.find("[SA]") != std::string::npos || stName.find("[GA]") != std::string::npos || stName.find("[GM]") != std::string::npos || stName.find("[H]") != std::string::npos
		|| stName.find("[MOD]") != std::string::npos || stName.find("[SGA]") != std::string::npos || stName.find("[SGM]") != std::string::npos || stName.find("OWNER") != std::string::npos
		|| stName.find("OwN") != std::string::npos || stName.find("Owner") != std::string::npos || stName.find("owner") != std::string::npos || stName.find("[TM]") != std::string::npos
		|| stName.find("[TGA]") != std::string::npos || stName.find("[TGM]") != std::string::npos || stName.find("[CM]") != std::string::npos || stName.find("[TM]") != std::string::npos
		|| stName.find("[ADM]") != std::string::npos || stName.find("Admin") != std::string::npos || stName.find("admin") != std::string::npos || stName.find("ADMIN") != std::string::npos
		|| stName.find("[INT]") != std::string::npos || stName.find("[I]") != std::string::npos || stName.find("[D]") != std::string::npos || stName.find("GFX") != std::string::npos
		|| stName.find("YT") != std::string::npos || stName.find("[Miss]") != std::string::npos || stName.find("[Mister]") != std::string::npos)
	{
		char szText[256];
		sprintf(szText, "You can't use that word for the name: %s", stName.c_str());
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT(szText));
		return;
	}
	
	if (stName.find("__") != std::string::npos || stName.find("--") != std::string::npos || stName.find("..") != std::string::npos || stName.find("##") != std::string::npos
		|| stName.find("^^") != std::string::npos || stName.find("**") != std::string::npos || stName.find("~~") != std::string::npos || stName.find("<<") != std::string::npos
		|| stName.find(">>") != std::string::npos || stName.find("//") != std::string::npos || stName.find("[[") != std::string::npos || stName.find("]]") != std::string::npos)
	{
		char szText[256];
		sprintf(szText, "You can't use two consecutive special characters: %s", stName.c_str());
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT(szText));
		return;
	}
	
	char szQuery[1024];
	snprintf(szQuery, sizeof(szQuery), "SELECT COUNT(*) FROM player%s WHERE name='%s'", get_table_postfix(), szName);
	std::unique_ptr<SQLMsg> pmsg(DBManager::instance().DirectQuery(szQuery));

	if (pmsg->Get()->uiNumRows > 0)
	{
		MYSQL_ROW row = mysql_fetch_row(pmsg->Get()->pSQLResult);
		int	count = 0;
		str_to_number(count, row[0]);

		if (count != 0)
		{
			ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("This name already exists."));
			return;
		}
	}
	
	if (ch->GetGuild())
	{
		ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("You can't change the name because you are a guild member."));
		return;
	}
	
	DWORD pid = ch->GetPlayerID();
	LPPARTY pParty = ch->GetParty();

	if (pParty != NULL)
	{
		if (pParty->GetMemberCount() == 2)
			CPartyManager::instance().DeleteParty(pParty);
		else
		{
			ch->ChatPacket(CHAT_TYPE_INFO, LC_TEXT("<Group> You left the Group."));
			pParty->Quit(pid);
		}
	}
	
	LogManager::instance().ChangeNameLog(ch->GetName(), szName, ch->IsGM() ? "Yes" : "No");
	
	MessengerManager::instance().RemoveAllList(ch->GetName());
	snprintf(szQuery, sizeof(szQuery), "UPDATE player.player SET name='%s' WHERE id=%u", szName, pid);
	SQLMsg * msg = DBManager::instance().DirectQuery(szQuery);
	M2_DELETE(msg);
	ch->SetNewName(szName);
	ch->ChatPacket(CHAT_TYPE_INFO, "Succes -> New Name: '%s'", szName);
	ch->RemoveSpecifyItem(AUTONAME_SCROLL_VNUM, 1);
	ch->GetDesc()->DelayedDisconnect(1);
	db_clientdesc->DBPacketHeader(HEADER_GD_FLUSH_CACHE, 0, sizeof(DWORD));
	db_clientdesc->Packet(&pid, sizeof(DWORD));
}
#endif



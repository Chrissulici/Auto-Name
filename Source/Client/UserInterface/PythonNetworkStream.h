//search:
		void __BettingGuildWar_SetBettingMoney(UINT uBettingMoney);

//add:
#ifdef ENABLE_AUTONAME_SYSTEM
	public:
		bool SendAutoNamePacket(const char* name);
#endif
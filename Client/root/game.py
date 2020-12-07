#add:
if app.ENABLE_AUTONAME_SYSTEM:
	import autoName

#search:
		self.serverCommander = stringCommander.Analyzer()
		for serverCommandItem in serverCommandList.items():
			self.serverCommander.SAFE_RegisterCallBack(serverCommandItem[0], serverCommandItem[1])

#add:
		if app.ENABLE_AUTONAME_SYSTEM:
			self.serverCommander.SAFE_RegisterCallBack("OpenAutoNameSystem", self.OpenAutoNameSystem)

#add at the end of file:
	if app.ENABLE_AUTONAME_SYSTEM:
		def OpenAutoNameSystem(self):
			self.wndAutoName = autoName.AutoNameDialog()
			self.wndAutoName.Show()
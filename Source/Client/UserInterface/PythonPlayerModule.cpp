//search:
void initPlayer()

//add before:
#ifdef ENABLE_AUTONAME_SYSTEM
PyObject* playerSetAutoName(PyObject* poSelf, PyObject* poArgs)
{
	char* szName;
	if (!PyTuple_GetString(poArgs, 0, &szName))
		return Py_BadArgument();

	CPythonNetworkStream::Instance().SendAutoNamePacket(szName);
	return Py_BuildNone();
}
#endif

//search:
		{ NULL,							NULL,								NULL },

//add before:
#ifdef ENABLE_AUTONAME_SYSTEM
		{ "SetAutoName",				playerSetAutoName,					METH_VARARGS },
#endif


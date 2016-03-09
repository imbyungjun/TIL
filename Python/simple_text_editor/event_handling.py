import wx

class MainWindow(wx.Frame):
	def __init__(self, parent, title):
		wx.Frame.__init__(self, parent, title=title, size=(200, 100))
		self.control = wx.TextCtrl(self, style=wx.TE_MULTILINE)
		self.CreateStatusBar()
		
		filemenu = wx.Menu()
		
		menuAbout = filemenu.Append(wx.ID_ABOUT, "&About", " Information about htis program")
		#filemenu.AppendSeparator()
		menuExit = filemenu.Append(wx.ID_EXIT, "&Exit", " Terminate the program")
		
		# Creating menubar.
		menuBar = wx.MenuBar()
		menuBar.Append(filemenu, "&File")
		
		self.SetMenuBar(menuBar)
		
		# Set events.
		self.Bind(wx.EVT_MENU, self.OnAbout, menuAbout)
		self.Bind(wx.EVT_MENU, self.OnExit, menuExit)
		
		self.Show(True)
		
	def OnAbout(self, event):
		dlg = wx.MessageDialog(self, "A small text editor", "About Sample Editor", wx.OK)
		dlg.ShowModal()
		dlg.Destroy()
		
	def OnExit(self, event):
		self.Close(True)
		
app = wx.App(False)
frame = MainWindow(None, "Sample editor")
app.MainLoop()

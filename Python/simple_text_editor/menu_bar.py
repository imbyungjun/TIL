import wx

class MainWindow(wx.Frame):
	def __init__(self, parent, title):
		wx.Frame.__init__(self, parent, title=title, size=(200,100))
		self.control = wx.TextCtrl(self, style=wx.TE_MULTILINE)
		self.CreateStatusBar()	# Statusbar in the bottom of the window
		
		# Setting up the menu.
		filemenu = wx.Menu()
		
		# wx.ID_ABOUT ad wx.ID_EXIT are standard IDs.
		# Third parameter will be shown in the bottom statusbar.
		filemenu.Append(wx.ID_ABOUT, "&About", " Informaton about this program")
		filemenu.AppendSeparator()
		filemenu.Append(wx.ID_EXIT, "&Exit", " Terminate the program")
		
		# Creating the menubar.
		menuBar = wx.MenuBar()
		# Add "filemenu" to the MenuBar
		menuBar.Append(filemenu, "&File")
		self.SetMenuBar(menuBar)
		self.Show(True)
		
app = wx.App(False)
frame = MainWindow(None, "Sample")
app.MainLoop()	

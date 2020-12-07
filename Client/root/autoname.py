import ui
import dbg
import chat
import grp
import player
import net
import app
import playersettingmodule

FACE_IMAGE_DICT = {
	playersettingmodule.RACE_WARRIOR_M	: "icon/face/warrior_m.tga",
	playersettingmodule.RACE_WARRIOR_W	: "icon/face/warrior_w.tga",
	playersettingmodule.RACE_ASSASSIN_M	: "icon/face/assassin_m.tga",
	playersettingmodule.RACE_ASSASSIN_W	: "icon/face/assassin_w.tga",
	playersettingmodule.RACE_SURA_M		: "icon/face/sura_m.tga",
	playersettingmodule.RACE_SURA_W		: "icon/face/sura_w.tga",
	playersettingmodule.RACE_SHAMAN_M	: "icon/face/shaman_m.tga",
	playersettingmodule.RACE_SHAMAN_W	: "icon/face/shaman_w.tga",
}

class AutoNameDialog(ui.Window):
	def __init__(self):
		ui.Window.__init__(self)
		self.BuildWindow()

	def __del__(self):
		ui.Window.__del__(self)

	def BuildWindow(self):
		self.Board = ui.BoardWithTitleBar()
		self.Board.SetSize(200, 93)
		self.Board.SetCenterPosition()
		self.Board.AddFlag('movable')
		self.Board.AddFlag('float')
		self.Board.SetTitleName('Personalized Name')
		self.Board.SetCloseEvent(self.Close)
		self.Board.Show()
		self.comp = Component()
		
		self.raceImage = ui.ImageBox()
		self.raceImage.SetParent(self.Board)
		self.raceImage.LoadImage(FACE_IMAGE_DICT[net.GetMainActorRace()])
		self.raceImage.SetPosition(12, 36)
		self.raceImage.Show()

		self.confirm = self.comp.Button(self.Board, 'Set', '', 64, 57, self.confirm_func, 'd:/ymir work/ui/button_01_brown.png', 'd:/ymir work/ui/button_02_brown.png', 'd:/ymir work/ui/button_03_brown.png')
		self.slotbar_input, self.input = self.comp.EditLine(self.Board, '', 62, 35, 125, 15, 24)

		self.input.SetText("")
		self.Show()

	def confirm_func(self):
		player.SetAutoName(self.input.GetText())
		self.Close()
		self.Board.Hide()

	def OpenWindow(self):
		if self.Board.IsShow():
			self.Board.Hide()
			self.Hide()
		else:
			self.Board.Show()
			self.Show()
	
	def Close(self):
		self.Board.Hide()

class Component:
	def Button(self, parent, buttonName, tooltipText, x, y, func, UpVisual, OverVisual, DownVisual):
		button = ui.Button()
		if parent != None:
			button.SetParent(parent)
		button.SetPosition(x, y)
		button.SetUpVisual(UpVisual)
		button.SetOverVisual(OverVisual)
		button.SetDownVisual(DownVisual)
		button.SetText(buttonName)
		button.SetToolTipText(tooltipText)
		button.Show()
		button.SetEvent(func)
		return button

	def ToggleButton(self, parent, buttonName, tooltipText, x, y, funcUp, funcDown, UpVisual, OverVisual, DownVisual):
		button = ui.ToggleButton()
		if parent != None:
			button.SetParent(parent)
		button.SetPosition(x, y)
		button.SetUpVisual(UpVisual)
		button.SetOverVisual(OverVisual)
		button.SetDownVisual(DownVisual)
		button.SetText(buttonName)
		button.SetToolTipText(tooltipText)
		button.Show()
		button.SetToggleUpEvent(funcUp)
		button.SetToggleDownEvent(funcDown)
		return button

	def EditLine(self, parent, editlineText, x, y, width, heigh, max):
		SlotBar = ui.SlotBar()
		if parent != None:
			SlotBar.SetParent(parent)
		SlotBar.SetSize(width, heigh)
		SlotBar.SetPosition(x, y)
		SlotBar.Show()
		Value = ui.EditLine()
		Value.SetParent(SlotBar)
		Value.SetSize(width, heigh)
		Value.SetPosition(1, 1)
		Value.SetMax(max)
		Value.SetLimitWidth(width)
		Value.SetMultiLine()
		Value.SetText(editlineText)
		Value.Show()
		return SlotBar, Value

	def TextLine(self, parent, textlineText, x, y, color):
		textline = ui.TextLine()
		if parent != None:
			textline.SetParent(parent)
		
		if app.WJ_MULTI_TEXTLINE:
			textline.DisableEnterToken()

		textline.SetPosition(x, y)
		if color != None:
			textline.SetFontColor(color[0], color[1], color[2])
		textline.SetText(textlineText)
		textline.Show()
		return textline

	def RGB(self, r, g, b):
		return (r*255, g*255, b*255)

	def SliderBar(self, parent, sliderPos, func, x, y):
		Slider = ui.SliderBar()
		if parent != None:
			Slider.SetParent(parent)
		Slider.SetPosition(x, y)
		Slider.SetSliderPos(sliderPos)
		Slider.Show()
		Slider.SetEvent(func)
		return Slider

	def ExpandedImage(self, parent, x, y, img):
		image = ui.ExpandedImageBox()
		if parent != None:
			image.SetParent(parent)
		image.SetPosition(x, y)
		image.LoadImage(img)
		image.Show()
		return image

	def ComboBox(self, parent, text, x, y, width):
		combo = ui.ComboBox()
		if parent != None:
			combo.SetParent(parent)
		combo.SetPosition(x, y)
		combo.SetSize(width, 15)
		combo.SetCurrentItem(text)
		combo.Show()
		return combo

	def ThinBoard(self, parent, moveable, x, y, width, heigh, center):
		thin = ui.ThinBoard()
		if parent != None:
			thin.SetParent(parent)
		if moveable == TRUE:
			thin.AddFlag('movable')
			thin.AddFlag('float')
		thin.SetSize(width, heigh)
		thin.SetPosition(x, y)
		if center == TRUE:
			thin.SetCenterPosition()
		thin.Show()
		return thin

	def Gauge(self, parent, width, color, x, y):
		gauge = ui.Gauge()
		if parent != None:
			gauge.SetParent(parent)
		gauge.SetPosition(x, y)
		gauge.MakeGauge(width, color)
		gauge.Show()
		return gauge

	def ListBoxEx(self, parent, x, y, width, heigh):
		bar = ui.Bar()
		if parent != None:
			bar.SetParent(parent)
		bar.SetPosition(x, y)
		bar.SetSize(width, heigh)
		bar.SetColor(0x77000000)
		bar.Show()
		ListBox=ui.ListBoxEx()
		ListBox.SetParent(bar)
		ListBox.SetPosition(0, 0)
		ListBox.SetSize(width, heigh)
		ListBox.Show()
		scroll = ui.ScrollBar()
		scroll.SetParent(ListBox)
		scroll.SetPosition(width-15, 0)
		scroll.SetScrollBarSize(heigh)
		scroll.Show()
		ListBox.SetScrollBar(scroll)
		return bar, ListBox

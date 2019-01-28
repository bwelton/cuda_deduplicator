from __future__ import print_function, unicode_literals
from pprint import pprint
from PyInquirer import style_from_dict, Token, prompt, Separator
from examples import custom_style_2
import os

class TextRow:
	def __init__(self, text, depth, linkIDs=None):
		self._data = {"Text" : text, "depth" : depth, "LinkIDs" : linkIDs}

	def GenerateRow(self):
		ret = ""
		for x in range(0,len(self._data["Text"])):
			if x > 0:
				ret += "    " + self._data["depth"] * "  " + self._data["Text"][x] + "\n"
			else:
				ret += self._data["depth"] * "  " + self._data["Text"][x] + "\n"
		ret = ret[:-1]
		if self._data["LinkIDs"] == None:
			ret = Separator(ret)
		return ret

	def GetLinkID(self):
		return self._data["LinkIDs"]

class DisplayFormatter:
	def __init__(self):
		self._data = {}
		self._globalID = 2

	def GetID(self):
		ret = self._globalID
		self._globalID += 1
		return ret

	def AddElement(self, myID, textRows):
		assert myID not in self._data
		self._data[myID] = textRows 

	def SetStart(self, ident):
		self._data["Start"] = ident

	def GetRowEntry(self, ident, questions):
		ret = [{},questions]
		ret[1][0]["choices"] = [Separator("Time(secs) (% of execution time)")]
		alwaysDisplay = [Separator(), "Back/Previous", "Exit"]
		assert ident in self._data
		for x in self._data[ident]:
			ret[0][x.GenerateRow()] = x.GetLinkID()
			ret[1][0]["choices"].append(x.GenerateRow())
		ret[1][0]["choices"] += alwaysDisplay
		return ret

	def BeginDisplay(self):
		displayChain = [self._data["Start"]]
		while 1:
			questions = [{'type': 'list', 'name' : "MyChoice", "message": "", 'choices': []}]
			ret = self.GetRowEntry(displayChain[-1], questions)
			os.system('clear')
			answers = prompt(ret[1], style=custom_style_2)
			if answers["MyChoice"] == "Exit":
				print("Exiting Now - Bye")
				return

			if answers["MyChoice"] == "Back/Previous":
				if len(displayChain) > 1:
					displayChain.pop()
			else:
				displayChain.append(ret[0][answers["MyChoice"]])

			



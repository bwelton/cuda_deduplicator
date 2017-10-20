import os
from Iterators import PacketCorrectionIterator, TimelineIterator, TimingInfoIterator
from pprint import pprint
class BaseRecord:
	def __init__(self, *args):
		if len(args) < len(self._parseParameters):
			print "Argument length differs from parameters!"
			print len(args)
			print len(self._parseParameters)
			print args
			exit(-1)
		for x in range(0, len(self._parseParameters)):
			setattr(self, self._parseParameters[x][0], self._parseParameters[x][1](args[x]))

	def GetAttr(self, attr):
		return getattr(self, attr, None)

	def GetGPUTime(self):
		if self.GetAttr("type") != None:
			if self.GetAttr("type") == "CPY":
				return self.GetAttr("etime") - self.GetAttr("stime")
		return 0.0

	def GetCPUTime(self):
		if self.GetAttr("type") != None:
			if self.GetAttr("type") == "RR" or self.GetAttr("type") == "DR":
				return self.GetAttr("etime") - self.GetAttr("stime")
		return 0.0

	def IsSynchronization(self):
		name = self.GetAttr("cname")
		t = self.GetAttr("type")

		if name == None or t == None:
			return False
		if t != "DR" or t != "RR":
			return False
		if "Async" not in name:
			return True
		else:
			return False

	def __str__(self):
		pprint(vars(self))
		return ""
class TimingInfoCall(BaseRecord):
	_parseParameters =  [("type", str), ("cname", str),
						 ("corrid", int), ("stime", int), 
						 ("etime",int), ("procid",int), 
						 ("threadid",int)]
	def __init__(self, *args):
		BaseRecord.__init__(self,*args)
		self._parseParameters = []

class TimingInfoCPY(BaseRecord):
	_parseParameters =  [("type", str), ("cname", str),
						 ("corrid", int), ("stime", int), 
						 ("etime",int), ("size",int), 
						 ("runcorr",int), ("ctx", int), 
						 ("dev",int), ("stream", int)]
	def __init__(self, *args):
		BaseRecord.__init__(self,*args)
		self._parseParameters = []

class DedupTimeline(BaseRecord):
	_parseParameters =  [("timelineid", int), ("hash", int),
						 ("size", int), ("ttype", str), 
						 ("dupid",int)]
	def __init__(self, *args):
		BaseRecord.__init__(self,*args)
		self._parseParameters = []

class PacketCorrection(BaseRecord):
	_parseParameters = [("timelineid", int), ("size", int), ("stream", int),
						("procid", int), ("threadid", int)]
	def __init__(self, *args):
		BaseRecord.__init__(self,*args)	
		self._parseParameters = []

class ReadDatFiles:
	def __init__(self, timeline, timingInfo, timingCorrection):
		self.ReadTimeline(timeline)
		self.ReadTimingInfo(timingInfo)
		self.ReadTimingCorrection(timingCorrection)

	def ReadTimeline(self, timeline):
		f = open(timeline,"r")
		data = f.readlines()
		f.close()
		self._timeline = []
		for x in data:
			tmp = x.replace('\n',"")
			tmp = tmp.split(",")
			self._timeline.append(DedupTimeline(*tmp))

	def ReadTimingInfo(self, timingInfo):
		f = open(timingInfo,"r")
		data = f.readlines()
		f.close()
		self._timingInfo = []
		for x in data:
			tmp = x.replace('\n',"")
			tmp = tmp.split(",")
			if "RR" in tmp[0] or "DR" in tmp[0]:
				self._timingInfo.append(TimingInfoCall(*tmp))
			elif "CPY" in tmp[0]:
				self._timingInfo.append(TimingInfoCPY(*tmp))
			elif "TET" in tmp[0]:
				self._totalTime = float(tmp[1])
			else:
				print "Could not id record"
				print x
				exit(-1)

	def ReadTimingCorrection(self, timingCorrection):
		f = open(timingCorrection,"r")
		data = f.readlines()
		f.close()
		self._timingCorr = []
		for x in data:
			tmp = x.replace('\n',"")
			tmp = tmp.split(",")
			self._timingCorr.append(PacketCorrection(*tmp))		

	def GetIterators(self):
		return [TimelineIterator(self._timeline), TimingInfoIterator(self._timingInfo), PacketCorrectionIterator(self._timingCorr)]
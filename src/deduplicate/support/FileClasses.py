import os

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

class TimingInfoCall(BaseRecord):
	_parseParameters =  [("type", str), ("cname", str),
						 ("corrid", int), ("stime", int), 
						 ("etime",int), ("procid",int), 
						 ("tid",int)]
	def __init__(self, *args):
		BaseRecord.__init__(self,*args)

class TimingInfoCPY(BaseRecord):
	_parseParameters =  [("type", str), ("cname", str),
						 ("corrid", int), ("stime", int), 
						 ("etime",int), ("size",int), 
						 ("runcorr",int), ("ctx", int), 
						 ("dev",int), ("stream", int)]
	def __init__(self, *args):
		BaseRecord.__init__(self,*args)

class DedupTimeline(BaseRecord):
	_parseParameters =  [("timelineid", int), ("hash", int),
						 ("size", int), ("ttype", str), 
						 ("dupid",int)]
	def __init__(self, *args):
		BaseRecord.__init__(self,*args)

class PacketCorrection(BaseRecord):
	_parseParameters = [("timelineid", int), ("size", int), ("stream", int),
						("procid", int), ("threadid", int)]
	def __init__(self, *args):
		BaseRecord.__init__(self,*args)	


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


if __name__ == "__main__":
	x = ReadDatFiles("dedup_timeline.txt", "timing_info.txt", "timing_packet_corr.txt")

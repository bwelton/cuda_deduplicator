import sys
import os
from  ReadStackFiles import StackReader
class Driver:
    def __init__(self):
        self._inDir = sys.argv[1]
        self._outDir = sys.argv[2]

    def Run(self):
        self._stackStore = {}
        stack_files = ["LS_stackkey.txt", "LS_tracekey.txt", "TF_timekey.txt"]

        for x in stack_files:
            self._stackStore[x] = StackReader(os.path.join(self._inDir, x))

        for x in self._stackStore:
            print str(self._stackStore[x])


if __name__ == "__main__":
    d = Driver()
    d.Run()
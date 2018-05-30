import threading
import time
import random

rmutex=threading.Semaphore(1)
wmutex=threading.Semaphore(1)
global readcount
readcount=0
global txt
txt="0"

class readerLock(threading.Thread):
	def __init__(self,num):
		threading.Thread.__init__(self)
		self.num=num
		self.runtime=2
	def run(self):
		global rmutex
		global wmutex
		global readcount
		global txt
		rmutex.acquire()
		if readcount==0:
			wmutex.acquire()
		readcount=readcount+1
		rmutex.release()
		i=0
		while i<1024*self.runtime:
			i=i+1
		print("%d读取的结果："%self.num,end='')
		print(txt)
		rmutex.acquire()
		readcount=readcount-1
		if readcount==0:
			wmutex.release()
		rmutex.release()

class writerLock(threading.Thread):
	def __init__(self,num,runtime):
		threading.Thread.__init__(self)
		self.num=num
		self.runtime=runtime
	def run(self):
		global rmutex
		global wmutex
		global txt
		wmutex.acquire()
		print("%d开始写入"%self.num)
		i=0
		while i<1024*self.runtime:
			i=i+1
		txt=str(self.num)
		print("%d写入结束"%self.num)
		wmutex.release()

readL1=readerLock(4)
readL2=readerLock(2)
readL3=readerLock(7)
readL4=readerLock(1)
readL5=readerLock(9)
readL6=readerLock(8)
readL7=readerLock(3)
readL8=readerLock(10)
readL9=readerLock(5)
readL10=readerLock(6)

writeL1=writerLock(1,2)
writeL2=writerLock(2,7)


writeL2.start()
readL6.start()
readL3.start()
readL2.start()
readL10.start()
readL5.start()
writeL1.start()
readL1.start()
readL7.start()
readL8.start()
readL4.start()
readL9.start()

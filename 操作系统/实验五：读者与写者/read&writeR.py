import threading
import time
import random

global txtR
txtR=0


class reader(threading.Thread):
	def __init__(self,num):
		threading.Thread.__init__(self)
		self.num=num
		self.runtime=2
	def run(self):
		global txtR
		i=0
		while i<1024*self.runtime:
			i=i+1
		print("%d读取的结果："%self.num,end='')
		print(txtR)

class writer(threading.Thread):
	def __init__(self,num,runtime):
		threading.Thread.__init__(self)
		self.num=num
		self.runtime=runtime
	def run(self):
		global txtR
		print("%d开始写入"%self.num)
		i=0
		while i<1024*self.runtime:
			i=i+1
		txtR=self.num
		print("%d写入结束"%self.num)

read1=reader(4)
read2=reader(2)
read3=reader(7)
read4=reader(1)
read5=reader(9)
read6=reader(8)
read7=reader(3)
read8=reader(10)
read9=reader(5)
read10=reader(6)

write1=writer(1,2)
write2=writer(2,7)

write2.start()
read6.start()
read3.start()
read2.start()
read10.start()
read5.start()
write1.start()
read1.start()
read7.start()
read8.start()
read4.start()
read9.start()

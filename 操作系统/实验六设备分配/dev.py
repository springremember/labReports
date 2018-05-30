class dev():
	def __init__(self,dtype,deviceid,busy,counter):
		self.dtype=dtype
		self.id=deviceid
		self.busy=busy
		self.counter=counter
		self.queue={}
	def printIt(self):
		if self.busy==0:
			busyStr="空闲"
		else:
			busyStr="忙碌"
		print("设备类型：%-15s\t编号：%-4d\t %-10s"%(self.dtype,self.id,busyStr))

class devClass():
	def __init__(self,dtype,amount,counter,number):
		self.dtype=dtype
		self.amount=amount
		self.counter=counter
		self.number=number
		
class devSystem():
	def __init__(self,dtype,id,DCT):
		self.dtype=dtype
		self.id=id
		self.DCT=DCT

global DCT
DCT=[]
global SDT
SDT=[]
global DCCT
DCCT={}
global workList
workList=[]

screen=devClass("screen",2,6,2)
DVD=devClass("DVD",3,12,3)
printer=devClass("printer",4,20,4)
DCCT["screen"]=screen
DCCT["DVD"]=DVD
DCCT["printer"]=printer

dev1=dev("screen",1,0,6)
dev2=dev("screen",2,0,6)
dev3=dev("DVD",3,0,12)
dev4=dev("DVD",4,0,12)
dev5=dev("DVD",5,0,12)
dev6=dev("printer",6,0,20)
dev7=dev("printer",7,0,20)
dev8=dev("printer",8,0,20)
dev9=dev("printer",9,0,20)
DCT.append(dev1)
DCT.append(dev2)
DCT.append(dev3)
DCT.append(dev4)
DCT.append(dev5)
DCT.append(dev6)
DCT.append(dev7)
DCT.append(dev8)
DCT.append(dev9)

dS1=devSystem("screen",1,"dev1")
dS2=devSystem("screen",2,"dev2")
dS3=devSystem("DVD",3,"dev3")
dS4=devSystem("DVD",4,"dev4")
dS5=devSystem("DVD",5,"dev5")
dS6=devSystem("printer",6,"dev6")
dS7=devSystem("printer",7,"dev7")
dS8=devSystem("printer",8,"dev8")
dS9=devSystem("printer",9,"dev9")
SDT.append(dS1)
SDT.append(dS2)
SDT.append(dS3)
SDT.append(dS4)
SDT.append(dS5)
SDT.append(dS6)
SDT.append(dS7)
SDT.append(dS8)
SDT.append(dS9)

def addDev(DCT,SDT,DCCT):
	dtype=input("请输入设备类型")
	num=len(DCT)+1
	tempdev=dev(dtype,num,0,DCCT[dtype].counter)
	DCT.append(tempdev)
	temp="dev"+str(num)
	tempdS=devSystem(dtype,num,temp)
	DCCT[dtype].amount=DCCT[dtype].amount+1
	DCCT[dtype].number=DCCT[dtype].number+1

class work():
	def __init__(self,wid,dtype1,dtype2,dtype3):
		self.wid=wid
		self.dtype1=dtype1
		self.dtype2=dtype2
		self.dtype3=dtype3
		self.devList=[]

def addWork(workList,DCT,DCCT):
	while True:
		workStr=input("请输入作业编号 使用screen数量 使用DVD数量 使用printer数量:")
		tempList=workStr.split(" ")
		for i in workList:
			if i.wid==int(tempList[0]):
				print("与已存在作业编号相同")
				break
		if int(tempList[1])<DCCT["screen"].amount and int(tempList[2])<DCCT["DVD"].amount and int(tempList[3])<DCCT["printer"].amount:	
			tempWork=work(int(tempList[0]),int(tempList[1]),int(tempList[2]),int(tempList[3]))
			DCCT["screen"].amount=DCCT["screen"].amount-int(tempList[1])
			DCCT["DVD"].amount=DCCT["DVD"].amount-int(tempList[2])
			DCCT["printer"].amount=DCCT["printer"].amount-int(tempList[3])
			for i in range(0,int(tempList[1])):
				for i in DCT:
					if i.busy==0 and i.dtype=="screen":
						tempWork.devList.append(i.id)
						i.busy=1
						break
			for i in range(0,int(tempList[2])):
				for i in DCT:
					if i.busy==0 and i.dtype=="DVD":
						tempWork.devList.append(i.id)
						i.busy=1
						break
			for i in range(0,int(tempList[3])):
				for i in DCT:
					if i.busy==0 and i.dtype=="printer":
						tempWork.devList.append(i.id)
						i.busy=1
						break
			workList.append(tempWork)
			break
		else:
			print("作业暂时无法分配，已经加入等待队列")
			break


def deleteWork(workList,DCT,DCCT):
	workInt=int(input("请输入要结束的作业编号："))
	for i in workList:
		if workInt==i.wid:
			choose=i
			break
	DCCT["screen"].amount=DCCT["screen"].amount+choose.dtype1
	DCCT["DVD"].amount=DCCT["DVD"].amount+choose.dtype2
	DCCT["printer"].amount=DCCT["printer"].amount+choose.dtype3
	for i in DCT:
		if i.id in choose.devList:
			i.busy=0



def main():
	global DCT
	global SDT
	global DCCT
	print("设备控制台")
	while True:
		print("1.查看当前设备情况")
		print("2.添加设备")
		print("3.分配设备")
		print("4.结束作业")
		print("其他输入退出系统")
		choose=int(input("请选择功能："))
		if choose==1:
			for i in DCT:
				i.printIt()
			print("")
		elif choose==2:
			addDev(DCT,SDT,DCCT)
			print("")
		elif choose==3:
			addWork(workList,DCT,DCCT)
			print("")
		elif choose==4:
			deleteWork(workList,DCT,DCCT)
			print("")
		else:
			print("退出")
			break

main()

#一下进行数据结构初始化
terminal={"d":0,"+":1,"*":2,"#":3}

noterminal={"E":0,"T":1}

ACTION=[(["0"]*4) for i in range(0,8)]
GOTO=[(["0"]*2) for i in range(0,8)]

G={"r1":"L->E","r2":"E->E+T","r3":"E->T","r4":"T->T*d","r5":"T->d"}
ACTION[0][0]="S3"

ACTION[1][1]="S4"
ACTION[1][3]="acc"

ACTION[2][1]="r3"
ACTION[2][2]="S5"
ACTION[2][3]="r3"

ACTION[3][1]="r5"
ACTION[3][2]="r5"
ACTION[3][3]="r5"

ACTION[4][0]="S3"

ACTION[5][0]="S6"

ACTION[6][1]="r4"
ACTION[6][2]="r4"
ACTION[6][3]="r4"

ACTION[7][1]="r2"
ACTION[7][2]="S5"
ACTION[7][3]="r2"


GOTO[0][0]="1"
GOTO[0][1]="2"
GOTO[2][1]="3"
GOTO[4][1]="7"

#状态栈
# state="0"

#符号栈
# symbal="#"

#输入串
# inputStr="abbcde#"
# counter=1

def calculate(list):
	calculateStr='';
	for i in list:
		calculateStr=calculateStr+str(i)
	return eval(calculateStr)


def LR(terminal,noterminal,ACTION,GOTO,inputStr):
	E=0
	T=0
	#计数变量
	counter=1
	#状态栈
	state="0"
	#符号栈
	symbal="#"
	mean=["-"]
	extre=["-"]
	print("步骤"+'\t'+"状态栈"+'\t\t\t'+"语义栈"+'\t\t\t'+"符号栈"+'\t\t\t'+"输入串"+'\t\t\t'+"ACTION"+'\t\t'+"GOTO")
	while 1:
		print("%- 4d"%(counter),end='\t')
		print("%- 20s"%(state),end='\t')
		for i in mean:
			print(i,end='')
		print('',end='\t\t\t')
		print("%- 20s"%(symbal),end='\t')
		print("%- 20s"%(inputStr),end='\t')
		X=state[-1:]
		Y=symbal[-1:]
		Z=inputStr[:1]
		if Z.isdigit():
			tempZ=Z
			Z="d"
		else:
			tempZ=Z
		#当action表中查不到值的时：
		if ACTION[int(X)][int(terminal[Z])]=="0":
			print("错误的输入串")
			break
		#字符串可以被接受时：
		elif ACTION[int(X)][int(terminal[Z])]=="acc":
			print("acc")
			break
		#遇到移入操作
		elif "S" in ACTION[int(X)][int(terminal[Z])]:
			state=state+ACTION[int(X)][int(terminal[Z])][-1:]
			symbal=symbal+tempZ
			inputStr=inputStr[1:]
			if tempZ.isdigit():
				mean.append(tempZ)
			else:
				mean.append("-")
			extre.append(tempZ)
			print("%- 12s"%(ACTION[int(X)][int(terminal[Z])]))
		#遇到归约操作
		else:
			print("%- 12s"%(ACTION[int(X)][int(terminal[Z])]),end='\t')
			tempList=G[ACTION[int(X)][int(terminal[Z])]].split("->")
			state=state[:len(state)-len(tempList[1])]
			symbal=symbal[:len(symbal)-len(tempList[1])]
			tempForMean=extre[-len(tempList[1]):]
			calculateInt=calculate(tempForMean)
			extre=extre[:len(mean)-len(tempList[1])]
			mean=mean[:len(mean)-len(tempList[1])]
			mean.append(calculateInt)
			extre.append(calculateInt)
			temp=state[-1:]
			state=state+GOTO[int(temp)][int(noterminal[tempList[0]])]
			print("%- 4s"%(GOTO[int(temp)][int(noterminal[tempList[0]])]))
			symbal=symbal+tempList[0]
		counter=counter+1


print("欢迎使用LL分析器！")
spring=input("请输入要检查的输入串(enter使用默认输入串)：")
if spring=="":
	LR(terminal,noterminal,ACTION,GOTO,"2+3*5#")
else:
	spring=spring+"#"
	LR(terminal,noterminal,ACTION,GOTO,spring)


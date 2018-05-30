#一下进行数据结构初始化
terminal={"a":0,"c":1,"e":2,"b":3,"d":4,"#":5}

noterminal={"S":0,"A":1,"B":2}

ACTION=[(["0"]*6) for i in range(0,10)]
GOTO=[(["0"]*3) for i in range(0,10)]

G={"r1":"S->aAcBe","r2":"A->b","r3":"A->Ab","r4":"B->d"}

ACTION[0][0]="S2"
ACTION[1][5]="acc"
ACTION[2][3]="S4"
ACTION[3][1]="S5"
ACTION[3][3]="S6"

for i in range(0,6):
	ACTION[4][i]="r2"
	

ACTION[5][4]="S8"

for i in range(0,6):
	ACTION[6][i]="r3"

ACTION[7][2]="S9"

for i in range(0,6):
	ACTION[8][i]="r4"

for i in range(0,6):
	ACTION[9][i]="r1"

GOTO[0][0]="1"
GOTO[2][1]="3"
GOTO[5][2]="7"

#状态栈
# state="0"

#符号栈
# symbal="#"

#输入串
# inputStr="abbcde#"
# counter=1


def LR(terminal,noterminal,ACTION,GOTO,inputStr="abbcde#"):
	#计数变量
	counter=1
	#状态栈
	state="0"
	#符号栈
	symbal="#"
	print("步骤"+'\t\t'+"状态栈"+'\t\t\t'+"符号栈"+'\t\t\t'+"输入串"+'\t\t\t'+"ACTION"+'\t\t'+"GOTO")
	while 1:
		print("%- 4d"%(counter),end='\t\t')
		print("%- 20s"%(state),end='\t')
		print("%- 20s"%(symbal),end='\t')
		print("%- 20s"%(inputStr),end='\t')
		X=state[-1:]
		Y=symbal[-1:]
		Z=inputStr[:1]
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
			symbal=symbal+Z
			inputStr=inputStr[1:]
			print("%- 12s"%(ACTION[int(X)][int(terminal[Z])]))
		#遇到归约操作
		else:
			print("%- 12s"%(ACTION[int(X)][int(terminal[Z])]),end='\t')
			tempList=G[ACTION[int(X)][int(terminal[Z])]].split("->")
			state=state[:len(state)-len(tempList[1])]
			symbal=symbal[:len(symbal)-len(tempList[1])]
			temp=state[-1:]
			state=state+GOTO[int(temp)][int(noterminal[tempList[0]])]
			print("%- 4s"%(GOTO[int(temp)][int(noterminal[tempList[0]])]))
			symbal=symbal+tempList[0]
		counter=counter+1


print("欢迎使用LL分析器！")
spring=input("请输入要检查的输入串(enter使用默认输入串)：")
if spring=="":
	LR(terminal,noterminal,ACTION,GOTO)
else:
	spring=spring+"#"
	LR(terminal,noterminal,ACTION,GOTO,spring)


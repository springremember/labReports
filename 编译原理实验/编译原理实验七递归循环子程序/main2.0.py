import sys

keywords={"begin":'a',"end":'b',"if":'e',"then":'f'}
opration=["+","-","*","/",">","<",";"]
format=[' ','\n','\t']


global spring
spring=[]
global word
word=''

def forword():
	global spring
	global word
    #flag用于标记字符串是否为开头数字中间字母的错误
	flag=0
	#判断word是否为空
	if(len(word)!=0):
		#判断第一个字符是否字母
		if word[0].isalpha():
			#判断字符串是否为关键词
			if word in keywords:
				spring.append(keywords[word])
			else:
				spring.append("c")
		else:
			#对于数字开头的字符串，判断其中是否夹杂字母
			for xyz in word:
				if xyz.isalpha():
					flag=1
					break
			#根据flag判断字符串是否错误
			if flag==1:
				print('第'+str(num+1)+'行，出现词法错误')
			else:
				spring.append("d")
	word=''

def deal(work):
	global word
	global spring
	for i in range(0,len(work)):
		#判断字符是否为字母，如果是拼接word
		if work[i].isalpha() or work[i].isdigit():
			word=word+work[i]
		elif work[i] in opration:
			forword()
			spring.append(work[i])
		elif work[i]==':':
			forword()
			if work[i+1]=='=':
				spring.append(":=")
			else:
				print('第'+str(num+1)+'行，出现词法错误')	
		elif work[i]=='=':
			if work[i-1]==':':
				pass
			else:
				print('第'+str(num+1)+'行，出现词法错误')
		elif work[i] in format:
			forword()
		elif work[i]=="#":
			forword()
			break
		else:
			print('第'+str(num+1)+'行：未规定字符')




temp=[]
work=[]
#打开文件
with open('test1.txt','r') as f:
    temp.extend(f.readlines())
#对于每一行使用deal函数，num用于错误提示表示行数
for num in range(0,len(temp)):
	deal(temp[num])


# global spring
# spring=['a', 'c', ':=', 'd', ';', 'e', 'c', '>', 'd', 'f', 'c', ':=', 'd', '*', 'c', '+', 'd', '/', 'd', 'b']
global lookahead
lookahead=spring[0]
global counter
counter=1

def getToken():
	global lookahead
	global counter
	global spring
	if counter==len(spring):
		pass
	else:
		lookahead=spring[counter]
		counter=counter+1

def MatchToken(word):
	if lookahead!=word:
		print("error!")
		sys.exit()
	else:
		getToken()


def ParseS():
	print("S->",end='')
	MatchToken("a")
	ParseA()
	MatchToken("b")
	print("end")
	print("success!")


def ParseA():
	print("A->",end='')
	ParseB()
	ParseA7()

def ParseA7():
	print("A7->",end='')
	if lookahead==";":
		MatchToken(";")
		ParseA()
	elif lookahead=="b":
		pass
	else:
		print("error!")
		sys.exit()


def ParseB():
	print("B->",end='')
	if lookahead=="c":
		ParseC()
	elif lookahead=="e":
		ParseD()
	else:
		print("error!")
		sys.exit()

def ParseC():
	print("C->",end='')
	MatchToken("c")
	MatchToken(":=")
	ParseE()

def ParseD():
	print("D->",end='')
	MatchToken("e")
	ParseE()
	MatchToken("f")
	ParseB()

def ParseE():
	print("E->",end='')
	ParseF()
	ParseE7()

def ParseE7():
	print("E7->",end='')
	if lookahead=="+":
		MatchToken("+")
		ParseE()
	elif lookahead=="-":
		MatchToken("-")
		ParseE()
	elif lookahead=="<":
		MatchToken("<")
		ParseE()
	elif lookahead==">":
		MatchToken(">")
		ParseE()
	elif lookahead=="f":
		pass
	elif lookahead==";":
		pass
	elif lookahead=="b":
		pass
	else:
		print("error!")
		sys.exit()

def ParseF():
	print("F->",end='')
	ParseG()
	ParseF7()

def ParseF7():
	print("F7->",end='')
	if lookahead=="*":
		MatchToken("*")
		ParseF()
	elif lookahead=="/":
		MatchToken("/")
		ParseF()
	elif lookahead in "+-<>f;b":
		pass
	else:
		print("error!")
		sys.exit()

def ParseG():
	print("G->",end='')
	if lookahead=="c":
		MatchToken("c")
	elif lookahead=="d":
		MatchToken("d")
	elif lookahead=="(":
		MatchToken("(")
		ParseE()
		MatchToken(")")
	else:
		print("error!")
		sys.exit()

ParseS()
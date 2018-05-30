import sys

#spring为一个列表，保存了要分析的句子
global spring
spring=[]
# spring=['(', 'a', ',', 'a', ')']
global lookahead
# lookahead=spring[0]

#counter用于控制列表的访问
global counter
counter=1
#flag用于判断是否一个句子完全被分析，例如aa可能在判断开头的“a”之后就退出了，不会输出error
global flag
flag=0

#当最后一个句子元素被MatchToken那就输出success，并且flag=1表示整个句子都被分析
def getToken():
	global lookahead
	global counter
	global spring
	global flag
	if counter==len(spring):
		flag=1
		print("success")
	else:
		lookahead=spring[counter]
		counter=counter+1

#错误那就退出，不错那就取得下一个字符
def MatchToken(word):
	if lookahead!=word:
		print("error!")
		sys.exit()
	else:
		getToken()

#S的分析程序
def ParseS():
	print("S->",end='')
	if lookahead=="a":
		MatchToken("a")
	elif lookahead=="^":
		MatchToken("^")
	elif lookahead=="(":
		MatchToken("(")
		ParseT()
		MatchToken(")")
	else:
		print("error")
		sys.exit()

#T的分析程序
def ParseT():
	print("T->",end='')
	ParseS()
	ParseT7()

#T'的分析程序
def ParseT7():
	if lookahead==",":
		MatchToken(",")
		ParseS()
		ParseT7()
	elif lookahead==")":
		pass
	else:
		print("error")
		sys.exit()


springStr=input("请输入要分析的句子(不输入使用默认句子：(a,a))：")
if springStr=="":
	spring=['(', 'a', ',', 'a', ')']
else:
	for i in springStr:
		spring.append(i)
lookahead=spring[0]
ParseS()
if flag==0:
	print("error")
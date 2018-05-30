import sys

global spring
spring=input("请输入要转化的小数：")
spring=spring+"#"
global lookahead
lookahead=spring[0]
global counter
counter=1

def getToken():
	global lookahead
	global counter
	global spring
	lookahead=spring[counter]
	counter=counter+1

def MatchToken(word):
	if lookahead!=word:
		print("error!")
		sys.exit()
	else:
		getToken()

def ParseN():
	print("N->",end="")
	MatchToken(".")
	sf=1
	sv=ParseS(sf)
	print("end")
	print(sv)

def ParseS(sf):
	print("S->",end="")
	if lookahead=="0" or lookahead=="1":
		bf=sf
		bv=ParseB(bf)
		s1f=sf+1
		s1v=ParseS(s1f)
		sv=s1v+bv
	elif lookahead=="#":
		sv=0
	else:
		print("error")
		sys.exit()
	return sv

def ParseB(bf):
	print("B->",end="")
	if lookahead=="0":
		MatchToken("0")
		bv=0
	elif lookahead=="1":
		MatchToken("1")
		bv=2**(-bf)
	else:
		print("error")
		sys.exit()
	return bv

ParseN()
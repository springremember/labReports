keywords={"begin":'a',"end":'b',"if":'e',"then":'f'}
opration=["+","-","*","/",">","<",";"]
format=[' ','\n','\t']

#结果：ac:=d;ec>dfc:=d*c+d/db

wholeStr=[]
word=''

def forword():
	global wholeStr
	global word
    #flag用于标记字符串是否为开头数字中间字母的错误
	flag=0
	#判断word是否为空
	if(len(word)!=0):
		#判断第一个字符是否字母
		if word[0].isalpha():
			#判断字符串是否为关键词
			if word in keywords:
				wholeStr.append(keywords[word])
			else:
				wholeStr.append("c")
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
				wholeStr.append("d")
	word=''

def deal(work):
	global word
	global wholeStr
	for i in range(0,len(work)):
		#判断字符是否为字母，如果是拼接word
		if work[i].isalpha() or work[i].isdigit():
			word=word+work[i]
		elif work[i] in opration:
			forword()
			wholeStr.append(work[i])
		elif work[i]==':':
			forword()
			if work[i+1]=='=':
				wholeStr.append(":=")
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
with open('test.txt','r') as f:
    temp.extend(f.readlines())
#对于每一行使用deal函数，num用于错误提示表示行数
for num in range(0,len(temp)):
	deal(temp[num])

print(wholeStr)
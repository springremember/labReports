#关键词集合，用于判断是否是关键词
keywords={'const':'constsym','begin':'beginsym','if':'ifsym','then':'thensym','end':'endsym','var':'varsym','procedur':'procsym','odd':'oddsym','call':'callsym','while':'whilesym','do':'dosym','read':'readsym','write':'writesym'}
#运算符集合，用于判断
opration={'+':'plus','-':'minus','*':'times','/':'slash','=':'eql','#':'neq'}
#界符
border={'lparen':'(','reparen':')','comma':',','semicolon':';','period':'.'}
#word字符串，用于将字符拼接成字符串
word=''
#特殊格式字符
format=[' ','\n','\t']


#对于拼接形成的字符串进行判断
def forword():
    global word
    #flag用于标记字符串是否为开头数字中间字母的错误
    flag=0
    #判断word是否为空
    if(len(word)!=0):
        #判断第一个字符是否字母
        if word[0].isalpha():
            #判断字符串是否为关键词
            if word in keywords.keys():
                print(keywords[word])
            else:
                print('ident'+'        '+word)
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
                print('number:        '+word)
    word=''
            

#接受一个字符串，循环判断字符
def deal(work):
    global word
    for i in range(0,len(work)):
        #判断字符是否为字母，如果是拼接word
        if work[i].isalpha() or work[i].isdigit():
            word=word+work[i]
        #判断字符是否为运算符，如果是就输出
        elif work[i] in opration.keys():
            forword()
            print(opration[work[i]]+'        '+work[i])
        #判断字符是否为运算符:=，如果是就输出
        elif work[i]=='<':
            if work[i+1]=='=':
                print('gtr        <=')
            else:
                print('lss        <')
        elif work[i]=='>':
            if work[i+1]=='=':
                print('geq        >=')
            else:
                print('leq        >')
        elif work[i]==':':
            forword()
            if work[i+1]=='=':
                print('becomes        ：=')
            else:
                print('第'+str(num+1)+'行，出现词法错误')
        elif work[i]=='=':
            if work[i-1]==':':
                pass
            elif work[i-1]=='<':
                pass
            elif work[i-1]=='>':
                pass
            else:
                print('第'+str(num+1)+'行，出现词法错误')
        #判断字符是否为界符，如果是就输出
        elif work[i] in border.keys():
            forword()
            print('界符        '+border[work[i]])
        #判断字符是否是格式字符
        elif work[i] in format:
            forword()
        else:
            print('第'+str(num+1)+'行：未规定字符，null')





temp=[]
work=[]
#打开文件
with open('test1.txt','r') as f:
    temp.extend(f.readlines())
print("词法单元      属性值")
#对于每一行使用deal函数，num用于错误提示表示行数
for num in range(0,len(temp)):
    deal(temp[num])

        
    

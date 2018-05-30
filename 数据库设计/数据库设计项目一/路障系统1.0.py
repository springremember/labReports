# 代码说明
# 代码以class形式组织。
# shenbao:市民申报界面
# chaxun:市民查询界面
# work_choose:施工队功能选择界面
# dowork:施工队提交施工信息
# donework:施工队提交结束信息
# baobiao:管理员生成报表
# mainpage:主窗口用于调动其他窗口


#导入模块
from tkinter import *
import pymysql.cursors

#管理员账号密码
master={'spring':'software'}  
#施工队账号密码
worker={'swaryee':'swaryee','dawei':'dawei','tempo':'tempo','Jeptack':'Jeptack'}
workerlt=['swaryee','dawei','tempo','Jeptack']	  

#申报界面
class shenbao(Toplevel):
	"""docstring for shenbao"""
	def __init__(self):
		super(shenbao, self).__init__()
		self.title("个人申报系统")
		self.geometry("500x400")
		self.SetupUI()
	#界面设计
	def SetupUI(self):
		self.addressinfo=StringVar()
		self.e=StringVar()
		self.entryposition=StringVar()
		#第一行，欢迎语
		Label(self,text="欢迎使用个人申报系统，请按要求输入以下信息。",height=6,font = 'Helvetica -20 bold').pack()

		#第二行，输入地址
		pframe1=Frame(self,height=20)
		pframe1.pack()

		address=Label(pframe1,text="路障地址")
		address.pack(side='left')

		Entry(pframe1,textvariable=self.addressinfo).pack(side='left')

		#第三行，输入损坏大小
		pframe2=Frame(self)
		pframe2.pack()

		Label(pframe2,text="道路损坏大小").pack(side='left')
		Entry(pframe2,textvariable=self.e).pack(side='left')
		self.e.set('1到10，10最紧急')

		#第四行，输入位置（center,left,right）
		pframe3=Frame(self)
		pframe3.pack()

		Label(pframe3,text="位置").pack(side='left')
		Entry(pframe3,textvariable=self.entryposition).pack(side='left')

		#第五行，提交按钮
		Button(self,height=2,text="提交",command=self.Submit).pack()

	#申报函数，连接数据库并插入数据
	def Submit(self):
		addresscheck=str(self.addressinfo.get())
		size=int(self.e.get())
		positionsql=str(self.entryposition.get())
		connection = pymysql.connect(host='115.159.85.157',
	                             port=3306,
	                             user='root',
	                             password='spring',
	                             db='test')
		cursor = connection.cursor()
		insertsql="insert into fixroad(address,size,position,block,level,state) values('"+addresscheck+"',"+str(size)+",'"+positionsql+"','"+addresscheck+"',"+str(size)+",'no-working')"
		cursor.execute(insertsql)
		connection.commit()
		searchsql="select count(ID) from fixroad"
		cursor.execute(searchsql)
		results = cursor.fetchall()
		connection.close()
		coding=Tk()
		coding.title("感谢您的申报！")
		coding.geometry('500x400')
		Label(coding,text="您好，您的申报已经提交！识别码为：",height=7,width=70,font = 'Helvetica -20 bold').pack()
		Label(coding,text=results[0][0],font = 'Helvetica -16 bold',height=1,width=40).pack()
		coding.mainloop()

#查询界面
class chaxun(Toplevel):
	"""docstring for chaxun"""
	def __init__(self):
		super(chaxun, self).__init__()
		self.title("欢迎查询道路故障情况")
		self.geometry('500x400')
		self.SetupUI()

	#界面函数
	def SetupUI(self):
		#前两行，欢迎语
		Label(self,text="欢迎查询道路故障维修情况。",height=6,font = 'Helvetica -16 bold').pack()
		Label(self,text="请在下方输入识别码",height=1,font = 'Helvetica -16 bold').pack()
		#第三行，输入框
		self.varsearch=StringVar()
		Entry(self,textvariable=self.varsearch).pack()
		#第四行，查询按钮
		Button(self,text="查询道路维修情况",height=2,command=self.searchsql).pack()


	def searchsql(self):	#查询并显示修路状态
		searchid=int(self.varsearch.get())
		connection = pymysql.connect(host='115.159.85.157',
	                             port=3306,
	                             user='root',
	                             password='spring',
	                             db='test')
		cursor=connection.cursor()
		sql="select state from fixroad where ID="+str(searchid)
		cursor.execute(sql)
		results=cursor.fetchall()
		connection.close()
		now=Tk()
		now.title("路障修复情况")
		now.geometry=("500x400")
		Label(now,width=20,height=7,text="路障修复情况：",font = 'Helvetica -20 bold').pack()
		Label(now,text=str(results[0][0]),width=20,height=2,font = 'Helvetica -16 bold').pack()
		now.mainloop()

#施工者主界面
class work_choose(Toplevel):
	"""docstring for work_choose"""
	def __init__(self,temp):
		super(work_choose, self).__init__()
		self.title('施工管理界面')
		self.geometry('500x400')
		self.SatupUI()
		self.usertemp=temp

	#界面函数
	def SatupUI(self):
		#前两行，欢迎语
		Label(self,text="欢迎使用施工管理界面。",height=6,font = 'Helvetica -16 bold').pack()
		Label(self,text="请通过下面按钮来选择功能。",height=1,font = 'Helvetica -16 bold').pack()

		#两个按钮
		frame1=Frame(self)
		frame1.pack()
		Button(frame1,text="查询路障信息并施工",width=20,height=2,command=self.dowork).pack(side='left')
		Button(frame1,text="提交施工结束信息",width=20,height=2,command=self.handover).pack(side='right')

	#按钮响应函数
	def dowork(self):
		windowdowork=dowork(self.usertemp)
		self.destroy()
		self.wait_window(windowdowork)
	def handover(self):
		windowdone=donework(self.usertemp)
		self.destroy()
		self.wait_window(windowdone)
		

#施工队提交施工信息
class dowork(Toplevel):
	"""docstring for dowork"""
	def __init__(self,temp):
		super(dowork, self).__init__()
		self.title("查询和施工界面")
		self.geometry("600x700")
		self.SatupUI()
		self.user=temp

	#界面函数
	def SatupUI(self):
		#数据库操作，查询当前列表
		connection = pymysql.connect(host='115.159.85.157',
		                             port=3306,
		                             user='root',
		                             password='spring',
		                             db='test')
		cursor = connection.cursor()
		searchsql="select address,position,level from fixroad where state='no-working' order by level DESC"
		cursor.execute(searchsql)
		results = cursor.fetchall()
		connection.close()
		#第一行，小提示
		Label(self,text="下面显示：地址 位置 优先级",height=3,font = 'Helvetica -16 bold').pack()

		#第二行，滑动框
		self.ff=Frame(self)
		self.ff.pack()
		self.scrollbar = Scrollbar(self.ff)
		self.scrollbar.pack( side = RIGHT, fill=Y )

		self.mylist = Listbox(self.ff, yscrollcommand = self.scrollbar.set ,width=40,font = 'Helvetica -20 bold')
		for line in results:
			line=str(line)
			line=line.rstrip(')')
			line=line.lstrip('(')
			self.mylist.insert(END,line)

		self.mylist.pack( side = LEFT, fill = BOTH )
		self.scrollbar.config( command = self.mylist.yview )

		#五行输入框
		self.e1=StringVar()
		Entry(self,textvariable=self.e1,width=20,font = 'Helvetica -16 bold').pack()
		self.e1.set('请输入施工人数')

		self.e2=StringVar()
		Entry(self,textvariable=self.e2,width=20,font = 'Helvetica -16 bold').pack()
		self.e2.set('请输入施工工具')

		self.e3=StringVar()
		Entry(self,textvariable=self.e3,width=20,font = 'Helvetica -16 bold').pack()
		self.e3.set('请输入工时')

		self.e4=StringVar()
		Entry(self,textvariable=self.e4,width=20,font = 'Helvetica -16 bold').pack()
		self.e4.set('请输入材料用量')

		self.e5=StringVar()
		Entry(self,textvariable=self.e5,width=20,font = 'Helvetica -16 bold').pack()
		self.e5.set('请输入维护费用')

		Button(self,text="提交施工信息",height=2,command=self.qijiao,font = 'Helvetica -16 bold').pack()

	def qijiao(self):      #提交信息函数
		value=self.mylist.get(self.mylist.curselection())
		value=value.rstrip(")")
		value=value.lstrip("(")
		valuesql=value.split(',')
		valuesql[0]=(valuesql[0].rstrip("'")).lstrip("'")
		valuesql[1]=(valuesql[1].rstrip("'")).lstrip("'")
		inte1=int(self.e1.get())
		stre2=str(self.e2.get())
		inte3=int(self.e3.get())
		stre4=str(self.e4.get())
		inte5=int(self.e5.get())
		#施工队编号由字典变列表得到
		sqlid=self.user
		connection = pymysql.connect(host='115.159.85.157',
	                             port=3306,
	                             user='root',
	                             password='spring',
	                             db='test')
		cursor = connection.cursor()
		insertsql="update fixroad set workid="+str(sqlid)+",number="+str(inte1)+",tools='"+stre2+"',hours="+str(inte3)+",stuff='"+stre4+"',fixcost="+str(inte5)+",state='working' where address='"+valuesql[0]+"' and position="+valuesql[1]+"' and level="+valuesql[2]
		cursor.execute(insertsql)
		connection.commit()
		connection.close()
		success=Tk()
		success.title("提交成功")
		success.geometry("400x300")
		Label(success,text="提交成功！",height=6,font = 'Helvetica -24 bold').pack()
		success.mainloop()

#结束施工任务，提交损失消息
class donework(Toplevel):
	"""docstring for donework"""
	def __init__(self,temp):
		super(donework, self).__init__()
		self.title("结束施工")
		self.geometry("500x700")
		self.SatupUI()
		self.user=temp

	def SatupUI(self):
		#数据库操作，查询当前列表
		connection = pymysql.connect(host='115.159.85.157',
		                             port=3306,
		                             user='root',
		                             password='spring',
		                             db='test')
		cursor = connection.cursor()
		searchsql="select address,position,level,ID from fixroad where state='working'"
		cursor.execute(searchsql)
		results = cursor.fetchall()
		connection.close()
		#第一行，小提示
		Label(self,text="下面显示：地址 位置 优先级 编号",height=3,font = 'Helvetica -16 bold').pack()

		#第二行，滑动框
		self.ff=Frame(self)
		self.ff.pack()
		self.scrollbar = Scrollbar(self.ff)
		self.scrollbar.pack( side = RIGHT, fill=Y )

		self.mylist = Listbox(self.ff, yscrollcommand = self.scrollbar.set ,width=40,font = 'Helvetica -20 bold')
		for line in results:
			line=str(line)
			line=line.rstrip(')')
			line=line.lstrip('(')
			self.mylist.insert(END, line)

		self.mylist.pack( side = LEFT, fill = BOTH )
		self.scrollbar.config( command = self.mylist.yview )

		#五行输入框
		self.e1=StringVar()
		Entry(self,textvariable=self.e1,width=20,font = 'Helvetica -16 bold').pack()
		self.e1.set('市民姓名')

		self.e2=StringVar()
		Entry(self,textvariable=self.e2,width=20,font = 'Helvetica -16 bold').pack()
		self.e2.set('市民所住地址')

		self.e3=StringVar()
		Entry(self,textvariable=self.e3,width=20,font = 'Helvetica -16 bold').pack()
		self.e3.set('市民电话')

		self.e4=StringVar()
		Entry(self,textvariable=self.e4,width=20,font = 'Helvetica -16 bold').pack()
		self.e4.set('损失类型')

		self.e5=StringVar()
		Entry(self,textvariable=self.e5,width=20,font = 'Helvetica -16 bold').pack()
		self.e5.set('损失量(元)')

		Button(self,text="提交施工结束信息",height=2,command=self.qijiao,font = 'Helvetica -16 bold').pack()

	def qijiao(self):      #提交信息函数
		value=self.mylist.get(self.mylist.curselection())
		value=value.rstrip(")")
		value=value.lstrip("(")
		valuesql=value.split(',')
		valuesql[0]=(valuesql[0].rstrip("'")).lstrip("'")
		valuesql[1]=(valuesql[1].rstrip("'")).lstrip("'")
		stre1=str(self.e1.get())
		stre2=str(self.e2.get())
		inte3=int(self.e3.get())
		stre4=str(self.e4.get())
		inte5=int(self.e5.get())
		#施工队编号由字典变列表得到
		connection = pymysql.connect(host='115.159.85.157',
	                             port=3306,
	                             user='root',
	                             password='spring',
	                             db='test')
		cursor = connection.cursor()
		updatesql="update fixroad set state='done' where address='"+valuesql[0]+"' and position="+valuesql[1]+"' and level="+valuesql[2]
		cursor.execute(updatesql)
		connection.commit()
		connection.close()
		#插入损失表
		connection = pymysql.connect(host='115.159.85.157',
	                             port=3306,
	                             user='root',
	                             password='spring',
	                             db='test')
		cursor = connection.cursor()
		insertsql="insert into lose(ID,name,address,phonenumber,type,amount) values("+valuesql[3]+",'"+stre1+"','"+stre2+"',"+str(inte3)+",'"+stre4+"',"+str(inte5)+")"
		cursor.execute(insertsql)
		connection.commit()
		connection.close()
		success=Tk()
		success.title("提交成功")
		success.geometry("400x300")
		Label(success,text="提交成功！",height=6,font = 'Helvetica -24 bold').pack()
		success.mainloop() 

#生成损失报告
class baogao(Tk):
	"""docstring for baogao"""
	def __init__(self):
		super(baogao, self).__init__()
		self.title("管理服务")
		self.SatupUI()
	def SatupUI(self):
		#数据库操作，查询当前列表
		connection = pymysql.connect(host='115.159.85.157',
		                             port=3306,
		                             user='root',
		                             password='spring',
		                             db='test')
		cursor = connection.cursor()
		searchsql="select address,position,level,ID from fixroad where state='done'"
		cursor.execute(searchsql)
		results = cursor.fetchall()
		connection.close()

		#第一行，小提示
		Label(self,text="下面显示：地址 位置 优先级 编号",height=3,font = 'Helvetica -16 bold').pack()

		#第二行，滑动框
		self.ff=Frame(self)
		self.ff.pack()
		self.scrollbar = Scrollbar(self.ff)
		self.scrollbar.pack( side = RIGHT, fill=Y )

		self.mylist = Listbox(self.ff, yscrollcommand = self.scrollbar.set ,width=40,font = 'Helvetica -20 bold')
		for line in results:
		   self.mylist.insert(END, str(line))

		self.mylist.pack( side = LEFT, fill = BOTH )
		self.scrollbar.config( command = self.mylist.yview )

		#第三行，生成报表按钮
		Button(self,text="生成损失报表",height=2,command=self.baobiao,font = 'Helvetica -16 bold').pack()

	#生成报表函数，数据库查询+文件读写
	def baobiao(self):
		value=self.mylist.get(self.mylist.curselection())
		value=value.rstrip(")")
		value=value.lstrip("(")
		valuesql=value.split(',')
		valuesql[0]=(valuesql[0].rstrip("'")).lstrip("'")
		valuesql[1]=(valuesql[1].rstrip("'")).lstrip("'")
		connection = pymysql.connect(host='115.159.85.157',
		                             port=3306,
		                             user='root',
		                             password='spring',
		                             db='test')
		cursor = connection.cursor()
		searchsql="select * from lose where ID="+valuesql[3]
		cursor.execute(searchsql)
		info = cursor.fetchall()
		connection.close()
		with open("损失报表.txt",'w') as f:
			f.write("对应编号		市民姓名		住址		电话		损失类型 		损失量\n")
			for i in info:
				f.write(str(i)+'\n')
		success=Tk()
		success.title("报表生成成功")
		success.geometry("400x300")
		Label(success,text="报表生成成功！",height=8,font = 'Helvetica -25 bold').pack()
		success.mainloop()


#主界面
class mainpage(Tk):
	"""docstring for mainpage"""
	def __init__(self):
		super(mainpage, self).__init__()
		self.title("PHTRS系统")
		self.geometry("600x500")
		self.SetupUI()

	def masterpage(self):   #打开管理员界面
		windowmaster=baogao()
		self.wait_window(windowmaster)

	def workpage(self):		#打开施工队界面
		NO=workerlt.index(self.var1.get())
		windowworker=work_choose(NO)
		self.wait_window(windowworker)

	def errorlogin(self):	#账号密码错误，请重新登录
		error=Tk()
		error.title("登陆错误")
		Label(error,text="账号密码错误，请重新登录！",width=30,height=10).pack()
		error.mainloop()

	def declare(self):       #申报函数
		windowshenbao=shenbao()
		self.wait_window(windowshenbao)

	def search(self):        #查询函数
		windowchaxun=chaxun()
		self.wait_window(windowchaxun)



	def SetupUI(self):
		#第一行，欢迎语
		Label(self,text="欢迎使用道路故障系统",width=20,height=5,font = 'Helvetica -20 bold').pack()

		#第二行，申报按钮
		Button(self,text="我要申报道路故障",height=2,command=self.declare).pack()

		#第三行，查询按钮
		Button(self,text="道路维修情况查询",height=2,command=self.search).pack()

		Label(self,height=2).pack()

		#第四行，用户名输入框
		frame1=Frame(self)
		frame1.pack()
		Label(frame1,text="用户名",width=15).pack(side='left')
		self.var1=StringVar()
		Entry(frame1,width=20,textvariable=self.var1).pack(side='right')

		#第五行，密码输入框
		frame2=Frame(self)
		frame2.pack()
		Label(frame2,text="密码",width=15).pack(side='left')
		self.var2=StringVar()
		Entry(frame2,width=20,show="*",textvariable=self.var2).pack(side='right')

		#第六行，登录按钮
		Button(self,text="登录",width=20,command=self.login).pack()

	def login(self):
		entryusr=str(self.var1.get())
		entrypasswd=str(self.var2.get())
		if (entryusr in master.keys()) and (entrypasswd==master[entryusr]):
			self.masterpage()
		elif (entryusr in worker.keys()) and (entrypasswd==worker[entryusr]):
			self.workpage()
		else :
			self.errorlogin()

app=mainpage()
app.mainloop()





		
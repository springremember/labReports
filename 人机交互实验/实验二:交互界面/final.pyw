from tkinter import *
from tkinter import filedialog
import webbrowser
import os

class mainpage(Tk):
	def __init__(self):
		super(mainpage,self).__init__()
		self.title("windows tools")
		self.geometry("600x500")
		self.SetupUI()

	def handover(self):
		url=str(self.var1.get())
		webs=[]
		#newwebs保存最后结果
		newwebs=[]
		with open('collection.txt','r') as f:
			webs.extend(f.readlines())
		for line in webs:
			line=line.rstrip('\n')
			newwebs.append(line)
		if url in newwebs:
			error=Tk()
			error.title("已经存在的网址")
			error.geometry("400x300")
			Label(error,text='您输入的网址已经存在！',height=5,font = 'Helvetica -24 bold').pack()
			error.mainloop()
		else:
			newurl=url+'\n'
			with open('collection.txt','a') as f:
				f.write(newurl)
			success=Tk()
			success.title("已经存在的网址")
			success.geometry("400x300")
			Label(success,text='网址成功添加',height=5,font = 'Helvetica -24 bold').pack()
			success.mainloop()


	def openvideo(self):
		r = filedialog.askopenfilename()
		print(os.getcwd())
		os.popen("PotPlayer\PotPlayerMini.exe "+r)

	def internet(self):
		url='http://172.16.253.3/'
		webbrowser.open(url)
	
	def showcollection(self):
		def openweb():
			value=mylist.get(mylist.curselection())
			url=str(value)
			webbrowser.open(url)

		def del_collection():
			value=mylist.get(mylist.curselection())
			url=str(value)
			url=url+'\n'
			webs.remove(url)
			with open('collection.txt','w') as f:
				for line in webs:
					f.write(line)
			

		webs=[]
		#newwebs保存最后结果
		newwebs=[]
		with open('collection.txt','r') as f:
			webs.extend(f.readlines())
		for line in webs:
			line=line.rstrip('\n')
			newwebs.append(line)
		showpage=Toplevel()
		showpage.title("网页收藏夹")
		showpage.geometry("700x500")
		Label(showpage,text="下面显示收藏的网页",height=3,font = 'Helvetica -16 bold').pack()
		ff=Frame(showpage)
		ff.pack()
		scrollbar = Scrollbar(ff)
		scrollbar.pack( side = RIGHT, fill=Y )

		mylist = Listbox(ff, yscrollcommand = scrollbar.set ,width=40,font = 'Helvetica -20 bold')
		for line in newwebs:
		   mylist.insert(END, str(line))

		mylist.pack( side = LEFT, fill = BOTH )
		scrollbar.config( command = mylist.yview )

		#第三行，生成报表按钮
		fff=Frame(showpage,width=30)
		fff.pack()
		Button(showpage,text="打开网页",height=2,font = 'Helvetica -16 bold',command=openweb,width=20).pack(side='left')
		Button(showpage,text="删除书签",height=2,font = 'Helvetica -16 bold',command=del_collection,width=20).pack(side='right')
		showpage.mainloop()


	def SetupUI(self):
		Label(self,text="欢迎使用windows工具箱",width=20,height=4,font = 'Helvetica -24 bold').pack()
		frame1=Frame(self,height=3)
		frame1.pack()
		self.var1=StringVar()
		Entry(frame1,font = 'Helvetica -24 bold',width=20,textvariable=self.var1).pack(side='left')
		Button(frame1,width=10,height=2,text='添加到收藏夹',command=self.handover).pack(side='right')

		Label(self,height=2).pack()

		Button(self,text="网页收藏夹",height=2,font = 'Helvetica -16 bold',width=20,command=self.showcollection).pack()
		Button(self,text="打开影音文件",height=2,font = 'Helvetica -16 bold',width=20,command=self.openvideo).pack()
		Button(self,text="校园网登陆",height=2,font = 'Helvetica -16 bold',width=20,command=self.internet).pack()

app=mainpage()
app.mainloop()


from tkinter import *
import pymysql.cursors

user={'spring':'software','swaryee':'swaryee','dawei':'dawei','tempo':'tempo','Jeptack':'Jeptack'}
bloodType=('a','A','b','B','ab','AB','o','O')

#志愿者注册界面
class volunteerUI(Toplevel):
    def __init__(self):
        super(volunteerUI,self).__init__()
        self.title("志愿者注册")
        self.geometry('600x500')
        self.SetupUI()
    #界面设计
    def SetupUI(self):
        self.name=StringVar()
        self.IDnumber=StringVar()
        self.phone=StringVar()
        self.bloodType=StringVar()

        Label(self,text='欢迎来到志愿者注册界面，请您按照要求输入以下信息，谢谢！',height=6,font='Helvetica -20 bold').pack()

        #输入姓名
        vframe1=Frame(self,height=20)
        vframe1.pack()
        Label(vframe1,text='姓名',width=15).pack(side='left')
        Entry(vframe1,width=20,textvariable=self.name).pack(side='left')

        #输入省份证号码
        vframe2=Frame(self,height=20)
        vframe2.pack()
        Label(vframe2,text='身份证号码',width=15).pack(side='left')
        Entry(vframe2,width=20,textvariable=self.IDnumber).pack(side='left')

        #输入电话号码
        vframe3=Frame(self,height=20)
        vframe3.pack()
        Label(vframe3,text='电话号码',width=15).pack(side='left')
        Entry(vframe3,width=20,textvariable=self.phone).pack(side='left')
        
        #输入血型
        vframe4=Frame(self,height=20)
        vframe4.pack()
        Label(vframe4,text='血型',width=15).pack(side='left')
        Entry(vframe4,width=20,textvariable=self.bloodType).pack(side='left')
        Label(self,height=5).pack()

        #提交按钮
        Button(self,height=2,width=10,text='提交',command=self.judgeError).pack()
        
    #输入异常处理（容错性）
    def judgeError(self):
        symbol=0
        judgeName=str(self.name.get())
        judgeID=str(self.IDnumber.get())
        judgePhone=str(self.phone.get())
        judgeBloodType=str(self.bloodType.get())
        
        if (len(judgeID)==3 and judgeID.isdigit()==True):
            symbol=symbol+1
        else:
            self.errorInput()
        if (len(judgePhone)==2 and judgePhone.isdigit()==True):
            symbol=symbol+1
        else:
            self.errorInput()
        if (judgeBloodType in bloodType):
            symbol=symbol+1
        else:
            self.errorInput()

        if symbol==3:  #所有信息输入正确
            print('调用连接数据库函数')
            self.Submit()
 
    def errorInput(self):
        error=Tk()
        error.title('输入信息错误')
        Label(error,text='您输入的相关信息有误，请重新输入！',width=30,height=10).pack()
        error.mainloop()

        
    #连接数据库并插入数据
    def Submit(self):
        print('志愿者注册成功')
        judgeName=str(self.name.get())
        judgeID=str(self.IDnumber.get())
        judgePhone=str(self.phone.get())
        judgeBloodType=str(self.bloodType.get())
        connection=pymysql.connect(host='root',
                                   port=3306,
                                   user='root',
                                   password='spring',
                                   db='test')
        cuesor=connection.cursor()
        insertSql="insert into volunteer(name,ID,phone,bloodType) values('"+judgeName+"','"+judgeID+"','"+judgePhone+"','"+judgeBloodType+"')"
        #table() 表  values() 表中属性值
        cursor.execute(insertSql)
        connection.commit()  #插入需要commit  查找不需要  commit 更新数据库
##        searchSql='select name from volunteer'
##        cursor.execute(searchSql)
##        result=cursor.fetchone()
        connection.close()
        success=Tk()
        success.title("感谢您的注册")
        success.geometry('600x500')
        #t=('尊敬的 %s ,您已成功完成志愿者注册',result)  #可能出错！！！！！！！
        #Label(success,text=t,height=7,width=70,font = 'Helvetica -20 bold').pack()
        Label(success,text='您已成功完成志愿者注册',height=7,width=70,font = 'Helvetica -20 bold').pack()
        success.mainloop()
        

#献血记录界面
class givebloodUI(Toplevel):
    def __init__(self):
        super(givebloodUI,self).__init__()
        self.title("献血记录界面")
        self.geometry('600x500')
        self.SetupUI()
    #界面设计
    def SetupUI(self):
        self.IDnumber=StringVar()
        self.bloodNum=StringVar()
        self.bloodType=StringVar()
        self.address=StringVar()
        self.time=StringVar()

        Label(self,text='欢迎来到献血登记界面，请您按照要求输入以下信息，谢谢！',height=6,font='Helvetica -20 bold').pack()


        #输入省份证号码
        vframe1=Frame(self,height=20)
        vframe1.pack()
        Label(vframe1,text='身份证号码',width=15).pack(side='left')
        Entry(vframe1,width=20,textvariable=self.IDnumber).pack(side='left')

        #输入血量
        vframe4=Frame(self,height=20)
        vframe4.pack()
        Label(vframe4,text='献血量',width=15).pack(side='left')
        Entry(vframe4,width=20,textvariable=self.bloodNum).pack(side='left')
        
        #输入血型
        vframe5=Frame(self,height=20)
        vframe5.pack()
        Label(vframe5,text='血型',width=15).pack(side='left')
        Entry(vframe5,width=20,textvariable=self.bloodType).pack(side='left')

        #输入献血地点
        vframe3=Frame(self,height=20)
        vframe3.pack()
        Label(vframe3,text='献血地点',width=15).pack(side='left')
        Entry(vframe3,width=20,textvariable=self.address).pack(side='left')

        #输入献血时间
        vframe2=Frame(self,height=20)
        vframe2.pack()
        Label(vframe2,text='献血时间',width=15).pack(side='left')
        Entry(vframe2,width=20,textvariable=self.time).pack(side='left')

        vframe=Frame(self,height=20)
        vframe.pack()
        Label(vframe,text='* 献血时间输入格式为：20170101  2017年1月1日 ',height=1).pack(side='left')
        
        Label(self,height=5).pack()

        #提交按钮
        Button(self,height=2,width=10,text='提交',command=self.judgeError).pack()

    #连接数据库并插入数据
    def Submit(self):
        print('献血信息录入成功')
        judgeID=str(self.IDnumber.get())
        judgeBloodNum=int(self.bloodNum.get())
        judgeBloodType=str(self.bloodType.get())
        judgeAddress=str(self.address.get())
        judgeTime=str(self.time.get())
        connection=pymysql.connect(host='root',
                                   port=3306,
                                   user='root',
                                   password='spring',
                                   db='test')
        cuesor=connection.cursor()
        insertSql="insert into giveBlood(ID,giveTime,giveAddress,bloodType,bloodNum) values('"+judgeID+"','"+judgeTime+"','"+judgeAddress+"','"+judgeBloodType+"',"+str(judgeBloodNum)+")"
        #table() 表  values() 表中属性值
        cursor.execute(insertSql)
        connection.commit()  #插入需要commit  查找不需要  commit 更新数据库
##        searchSql='select name from table where ID=judgeID'
##        cursor.execute(searchSql)
##        result=cursor.fetchone()
        connection.close()
        success=Tk()
        success.title("感谢您的使用")
        success.geometry('600x500')
        Label(success,text='您已成功完成血液记录信息录入',height=7,width=70,font = 'Helvetica -20 bold').pack()
        success.mainloop()

    #输入异常处理（容错性）
    def judgeError(self):
        symbol=0
        judgeID=str(self.IDnumber.get())
        judgeBloodNum=int(self.bloodNum.get())
        judgeBloodType=str(self.bloodType.get())
        judgeAddress=str(self.address.get())
        judgeTime=str(self.time.get())
        
        if (len(judgeID)==3 and judgeID.isdigit()==True):
            symbol=symbol+1
        else:
            self.errorInput()
        if (judgeBloodType in bloodType):
            symbol=symbol+1
        else:
            self.errorInput()
        if (judgeBloodNum.isdigit()==True):
            symbol=symbol+1
        else:
            self.errorInput()
        if (len(judgeTime)==8 and judgeTime.isdigit()==True):
            symbol=symbol+1
        else:
            self.errorInput()

        if symbol==4:  #所有信息输入正确
            print('调用连接数据库函数')
            self.Submit()
            
    def errorInput(self):
        error=Tk()
        error.title('输入信息错误')
        Label(error,text='您输入的相关信息有误，请重新输入！',width=30,height=10).pack()
        error.mainloop()

#血液配送界面
class carrybloodUI(Toplevel):
    symbol=0
    def __init__(self):
        super(carrybloodUI,self).__init__()
        self.title("血液配送界面")
        self.geometry('600x500')
        self.SetupUI()
    #界面设计
    def SetupUI(self):
        self.bloodNum=StringVar()
        self.bloodType=StringVar()
        self.address=StringVar()
        self.goTime=StringVar()
        self.comeTime=StringVar()

        Label(self,text='欢迎来到血液配送界面，请您按照要求输入以下信息，谢谢！',height=6,font='Helvetica -20 bold').pack()

        #输入配送地点
        vframe3=Frame(self,height=20)
        vframe3.pack()
        Label(vframe3,text='配送地点',width=15).pack(side='left')
        Entry(vframe3,width=20,textvariable=self.address).pack(side='left')

        #输入配送血量
        vframe4=Frame(self,height=20)
        vframe4.pack()
        Label(vframe4,text='配送血量',width=15).pack(side='left')
        Entry(vframe4,width=20,textvariable=self.bloodNum).pack(side='left')
        
        #输入血型
        vframe5=Frame(self,height=20)
        vframe5.pack()
        Label(vframe5,text='配送血型',width=15).pack(side='left')
        Entry(vframe5,width=20,textvariable=self.bloodType).pack(side='left')

        #输入配送血液入库时间
        vframe1=Frame(self,height=20)
        vframe1.pack()
        Label(vframe1,text='入库时间',width=15).pack(side='left')
        Entry(vframe1,width=20,textvariable=self.comeTime).pack(side='left')

        #输入配送时间
        vframe2=Frame(self,height=20)
        vframe2.pack()
        Label(vframe2,text='配送时间',width=15).pack(side='left')
        Entry(vframe2,width=20,textvariable=self.goTime).pack(side='left')
        vframe=Frame(self,height=20)
        vframe.pack()
        Label(vframe,text='* 献血时间输入格式为：20170101  2017年1月1日 ',height=1).pack(side='left')
        
        Label(self,height=5).pack()

        #提交按钮
        Button(self,height=1,width=10,text='提交',command=self.judgeError).pack()

    #连接数据库并插入数据
    def Submit(self):
        print('血液配送完毕')
        judgeBloodNum=int(self.bloodNum.get())
        judgeBloodType=str(self.bloodType.get())
        judgeAddress=str(self.address.get())
        judgeComeTime=str(self.comeTime.get())
        judgeGoTime=str(self.goTime.get())
        connection=pymysql.connect(host='root',
                                   port=3306,
                                   user='root',
                                   password='spring',
                                   db='test')
        cuesor=connection.cursor()
        insertSql="insert into carryBlood(bloodType,bloodNum,carryAddress,comeTime,carryTime) values('"+judgeBloodType+"',"+str(judgeBloodNum)+",'"+judgeAddress+"','"+judgeComeTime+"','"+judgeGoTime+"')"
        #table() 表  values() 表中属性值
        cursor.execute(insertSql)
        connection.commit()  #插入需要commit  查找不需要  commit 更新数据库
        updateSql="update giveBlood set bloodNum=bloodNum-judgeBloodNum where bloodType=judgeBloodType"
        cursor.execute(updateSql)
        connection.commit()
        #未对配送血量是否超出库存进行判断
        connection.close()
        success=Tk()
        success.title("感谢您的使用")
        success.geometry('600x500')
        Label(success,text='您已成功完成血液配送信息录入,及相关数据更新！',height=7,width=70,font = 'Helvetica -20 bold').pack()
        success.mainloop()

    #输入异常处理（容错性）
    def judgeError(self):
        symbol=0
        judgeBloodNum=str(self.bloodNum.get())
        judgeBloodType=str(self.bloodType.get())
        judgeAddress=str(self.address.get())
        judgeComeTime=str(self.comeTime.get())
        judgeGoTime=str(self.goTime.get())
        
        if (judgeBloodType in bloodType):
            symbol=symbol+1
        else:
            self.errorInput()
        if (judgeBloodNum.isdigit()==True):
            symbol=symbol+1
        else:
            self.errorInput()
        if (len(judgeComeTime)==8 and judgeComeTime.isdigit()==True):
            symbol=symbol+1
        else:
            self.errorInput()
        if (len(judgeGoTime)==8 and judgeGoTime.isdigit()==True):
            symbol=symbol+1
        else:
            self.errorInput()

        if symbol==4:  #所有信息输入正确
            print('调用连接数据库函数')
            self.Submit()
            
    def errorInput(self):
        error=Tk()
        error.title('输入信息错误')
        Label(error,text='您输入的相关信息有误，请重新输入！',width=30,height=10).pack()
        error.mainloop()
    
#血库查询界面
class managebloodUI(Toplevel):
    def __init__(self):
        super(managebloodUI,self).__init__()
        self.title("欢迎使用血库信息查询界面")
        self.geometry('600x500')
        self.SetupUI()

    #界面函数
    def SetupUI(self):
        Label(self,text='欢迎来到血库信息查询界面，请您按照要求输入相关信息完成查询，谢谢！')

        
        Label(self,text='请输入血型，查询对应血量，输入aa查询库存总量',height=6,font = 'Helvetica -16 bold').pack()
        self.information=StringVar()
        Entry(self,textvariable=self.information).pack()
        Label(self,height=10).pack()
        Button(self,text="库存情况",height=1,width=10,command=self.searchNum).pack()

    def judgeError(self):
        searchCall=str(self.information.get())

        '''
        if (searchCall=='A' or searchCall=='a'):
            print(100)
        elif (searchCall=='B' or searchCall=='b'):
            print(200)
        elif (searchCall=='AB' or searchCall=='ab'):
            print(300)
        elif (searchCall=='O' or searchCall=='o'):
            print(400)
        elif (searchCall=='aa' or searchCall=='AA'):
            print(1000)
        '''
        if (searchCall in bloodType):
            self.searchNum()
        else:
            self.errorInput()
    def searchNum(self):
        print('成功完成血液查询')
        searchCall=str(self.information.get())
        connection=pymysql.connect(host='root',
                                   port=3306,
                                   user='root',
                                   password='spring',
                                   db='test')
        cuesor=connection.cursor()
        searchSql='select sum(bloodNum) from giveBlood where bloodType=searchCall'
        cursor.execute(searchSql)
        result=cursor.fetchone()
        connection.close()
        success=Tk()
        success.title("感谢您的使用")
        success.geometry('600x500')
        Label(success,text=searchCall,height=7,width=7,font = 'Helvetica -20 bold').pack()
        Label(success,text='型血的库存量为：',height=7,width=30,font = 'Helvetica -20 bold').pack()
        Label(success,text=result,height=7,width=50,font = 'Helvetica -20 bold').pack()
        success.mainloop()
        
            
    def errorInput(self):
        error=Tk()
        error.title('输入信息错误')
        Label(error,text='您输入的相关信息有误，请重新输入！',width=30,height=10).pack()
        error.mainloop()

            
# 主界面
class mainSurface(Tk):
    #调用志愿者注册界面
    def conVolunteer(self):
        volunteer=volunteerUI()   #volunteerUI 为志愿者注册界面
        self.wait_window(volunteer)

    def conGiveblood(self):
        blood=givebloodUI()
        self.wait_window(blood)  #givebloodUI 为献血记录界面

    def conCarryblood(self):
        blood=carrybloodUI()
        self.wait_window(blood) #carrybloodUI 为血液配送界面

    def conManageblood(self):
        blood=managebloodUI()
        self.wait_window(blood) #managebloodUI 为血库查询界面

    def errorlogin(self):
        error=Tk()
        error.title("登陆错误")
        Label(error,text='账号或密码错误，请重新登录！',width=30,height=10).pack()
        error.mainloop()
   
    
    def __init__(self):
        super(mainSurface,self).__init__()
        self.title("无偿献血管理系统")
        self.geometry('600x500')
        self.SetupUI()


    def SetupUI(self):
        Label(self,text='欢迎使用无偿献血管理系统',width=20,height=5,font = 'Helvetica -20 bold').pack()
        Button(self,text='志愿者注册',width=20,height=2,command=self.conVolunteer).pack()
        Button(self,text='献血记录',width=20,height=2,command=self.conGiveblood).pack()
        Button(self,text='血库配送',width=20,height=2,command=self.conCarryblood).pack()
        Button(self,text='信息查询',width=20,height=2,command=self.conManageblood).pack()

        Label(self,width=20,height=3).pack()
        

        #用户名输入

        frame1=Frame(self)
        frame1.pack()
        Label(frame1,text='用户名',width=15).pack(side='left')
        self.var1=StringVar()
        entry1=Entry(frame1,width=20,textvariable=self.var1)
        entry1.pack(side='right')

        #密码输入框
        frame2=Frame(self)
        frame2.pack()
        Label(frame2,text="密码",width=15).pack(side='left')
        self.var2=StringVar()
        entry2=Entry(frame2,width=20,show='*',textvariable=self.var2)
        entry2.pack(side='right')
        Label(self,height=2).pack()
   
	#登录按钮
        Button(self,text='登录',width=20,command=self.login).pack()

    def login(self):
        entryuser=str(self.var1.get())
        entrypassword=str(self.var2.get())
        if(entryuser in user.keys()) and (entrypassword==user[entryuser]):
            #self.mainSurface()  #转入志愿者注册界面
            print('转入志愿者注册界面')
            self.conVolunteer()
        else:
            self.errorlogin()
            
app=mainSurface()
app.mainloop()

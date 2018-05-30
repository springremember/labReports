from __future__ import division
#读取文件
with open("test1219.txt",'r') as f:
    visit=f.readline()

tempList=visit.split(" ")
tempList1=tempList[:]
tempList2=tempList[:]
output=[]
output.append(visit)
output.append("\n")
for i in range(0,len(tempList1)):
    tempList1[i]=int(tempList1[i])
    tempList2[i]=int(tempList2[i])

def SSTF(tempList):
    orderList=[]
    orderList.append(tempList[0])
    tempList.remove(tempList[0])
    while True:
        if len(tempList)==0:
            break
        choose=0
        distance=abs(orderList[-1]-tempList[choose])
        for i in range(1,len(tempList)):
            newDistance=abs(orderList[-1]-tempList[i])
            if newDistance<distance:
                choose=i
                distance=newDistance
        orderList.append(tempList[choose])
        tempList.remove(tempList[choose])
    return orderList
        

def SCAN(tempList):
    orderList=[]
    orderList.append(tempList[0])
    tempList.remove(tempList[0])
    tempList.sort()
    flag=1
    while True:
        if len(tempList)==0:
            break
        choose=-1
        distance="none"
        for i in range(0,len(tempList)):
            newdistance=tempList[i]-orderList[-1]
            newdistance=newdistance*flag
            if newdistance<0:
                pass
            else:
                if distance=="none" or newdistance<distance:
                    distance=newdistance
                    choose=i
        if choose=="none":
            flag=flag*(-1)
        else:
            orderList.append(tempList[choose])
            tempList.remove(tempList[choose])
    return orderList


def show(showList,output):
    print("从%d号磁道开始"%showList[0])
    temp="从"+str(showList[0])+"号磁道开始"
    output.append(temp)
    print("下一个磁道号\t移动距离")
    output.append("下一个磁道号\t移动距离")
    last=0
    now=1
    sum=0
    while True:
        if now==len(showList):
            break
        else:
            print(showList[now],end='\t\t')
            distance=abs(showList[last]-showList[now])
            temp=str(showList[now])+"\t\t"+str(distance)
            print(distance)
            output.append(temp)
            sum=sum+distance
            last=now
            now=now+1
    num=len(showList)-1
    avg=sum/num
    print("平均寻道长度：%f"%avg)
    temp="平均寻道长度："+str(avg)
    output.append(temp)
    output.append("\n")
    
            

orderList1=SSTF(tempList1)
orderList2=SCAN(tempList2)
print("以下是最短寻道时间优先：")
output.append("以下是最短寻道时间优先：")
show(orderList1,output)
print("")
print("以下是扫描算法：")
output.append("以下是扫描算法：")
show(orderList2,output)
with open("test1219.txt","w") as f:
    for i in output:
        temp=i+"\n"
        f.write(temp)

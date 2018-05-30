import sys

def hello():
	sayhello()
	sayhell()

def sayhello():
	print("hello")
	sys.exit()



def sayhell():
	print("hell")


hello()


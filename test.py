class A:
	def __init__(self):
		self.a = self.func()
	def func(self):
		self.a = 1
		return self.a

a = A()
print(a.a)

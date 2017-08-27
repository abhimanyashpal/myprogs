
class Employee:

	raise_pay = 1.04

	def __init__(self, first, last, pay):
		self.first = first
		self.last = last
		self.pay = pay
		self.email = first + "." + last + "@company.com"

	def get_info(self):
		return "{} {} {} {}".format(self.first,self.last,self.email, self.pay)

	def apply_per_emp_raise(self,raise_val):
		self.raise_pay = raise_val

	def apply_raise(self):
		self.pay = self.pay* self.raise_pay

	@classmethod
	def set_raise(cls,raise_val):
		cls.raise_pay = raise_val
 




emp1 = Employee("Abhiman","Karkera",50000)
emp2 = Employee("Test","User",50000)
emp3 = Employee("John","Doe",50000)

#print emp1.get_info()

#Another way of invoking using the class name
print Employee.get_info(emp1)
print Employee.get_info(emp2)
print Employee.get_info(emp3)

#Invokes a class method to set a class variable, in this case
# raise_pay which is applicable to all the instances of the class
Employee.set_raise(1.05)


#Assume we want to override the pay raise for one of the employees
emp1.apply_per_emp_raise(2)

emp1.apply_raise()
emp2.apply_raise()
emp3.apply_raise()

print Employee.get_info(emp1)
print Employee.get_info(emp2)
print Employee.get_info(emp3)







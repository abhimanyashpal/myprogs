
class list_node:
	def __init__ (self, data):
		self.data = data
		self.next = None

	def get_data(self):
		return self.data

	def get_next(self):
		return self.next

	def set_next(self,nxt_node):
		self.next = nxt_node


class mylist:
	def __init__(self):
		self.head = None

	def insert(self, data):
		node = list_node(data)

		if not self.head:
			self.head = node
		else:
			node.set_next(self.head)
			self.head = node

	def remove(self):
		node = self.head

		if not node:
			return None

		self.head = node.get_next()
		node.set_next("None")
		return node

	def search(self,key):
		node = self.head
		
		if not node:
			return None

		while node is not None:
			if key is node.get_data():
				return "Found"
				

			node = node.get_next()

		return "Not found"

	def remove_node(self,key):
		node = self.head

		if not node:
			return

		prev = ""

		while node is not None:
			if key is node.get_data():
				#Match found
				temp = node

				if not prev:
					self.head = temp.get_next()
					node = temp.get_next()
					continue
				else:
					temp = node
					prev.set_next(temp.get_next())
					node = temp.get_next()
					continue

			prev = node
			node = node.get_next()

		return





	def print_rec_help(self,node):
		if not node:
			return

		print node.get_data()
		return self.print_rec_help(node.get_next())

	def print_rec(self):
		node = self.head
		return self.print_rec_help(node)


	def print_nodes(self):

		curr = self.head

		while curr is not None:
			print curr.get_data()
			curr = curr.get_next()

	def get_head(self):
		return self.head



lista = mylist()

lista.insert(10)
lista.insert(20)
lista.insert(30)
lista.insert(40)
lista.insert(50)

print "Printing nodes"
print "=============="
lista.print_nodes()

print"================"
print "removing a node"
print"================"

#Just keeps popping from the head
ret_node = lista.remove()
ret_node = lista.remove()
ret_node = lista.remove()
ret_node = lista.remove()
ret_node = lista.remove()

if ret_node is not None:
	print "{} {}".format(ret_node.get_data(),ret_node.get_next())




print "Printing nodes"
print "=============="
lista.print_nodes()


print "Head: " + str(mylist.get_head(lista))


lista.insert(100)
lista.insert(200)
lista.insert(300)
lista.insert(400)
lista.insert(500)


print "Printing nodes"
print "=============="
lista.print_nodes()


print lista.search(400)

lista.print_rec()


print "DELETING A NODE"
print "==============="
lista.remove_node(100)

lista.print_rec()

t = lista.get_head()

print t.get_next().get_next().get_data()




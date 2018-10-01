
import Queue

#list of vertices
v_db = [1,2,3,4,5]

#Mapping of vertex to list of other vertices
#which signify a edge
vertex = {  
           1 : [3, 2] ,
           2 : [3] ,
           3 : [4],
           4 : [5],  #Put 1 here to introduce a cycle
           5 : []
         }

state = {}
visited = {}
parent = {}


def bfs_helper(v):
   q = Queue.Queue()
   level = 0

   q.put(v)

   while not q.empty():
       sz = q.qsize()

       while sz != 0:
           elem = q.get()
           edges = vertex[elem]

           #Visit the adjacent vertices
           for edge in edges:
              print "Visiting " + str(elem) + " ===> " + str(edge) + " Level: " + str(level)
              parent[edge] = elem
              if state[edge] != 3:
                q.put(edge)

           state[elem] = 3
           sz = sz - 1

       level = level + 1
           
for v in v_db:
   #Mark all vertices as unvisted
   state[v] = 1;

bfs_helper(1)


print "Parent db"
print parent

print "State db"
print state

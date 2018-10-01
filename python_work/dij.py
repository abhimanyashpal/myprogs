
import Queue

#list of vertices
v_db = [1,2,3,4,5]

#Mapping of vertex to list of other vertices
#which signify a edge

#In the list of each vertex we will represent it with
# 2 variables which signify the weight of the edge
# (vertex, wt-of-edge-to-vertex)
vertex = {  
           1 : [ (3,7),(2,1)] ,
           2 : [ (3,4),(5,70)] ,
           3 : [ (4,5)],
           4 : [ (5,2)],
           5 : []
         }

state = {}
visited = {}
cumm_cost = {} #Cummulative cost of this vertex from source
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
              print "Visiting " + str(elem) + " ===> " + str(edge[0]) + " Level: " + str(level)
              if ((cumm_cost[elem] + edge[1]) < cumm_cost[edge[0]]):
                parent[edge[0]] = elem
                cumm_cost[edge[0]] = cumm_cost[elem] + edge[1]
                q.put(edge[0]) 

           state[elem] = 3
           sz = sz - 1

       level = level + 1
           
for v in v_db:
   #Mark all vertices as unvisted
   state[v] = 1;
   cumm_cost[v] = 32767 #signifying infinity

# assume source is 1

cumm_cost[1] = 0

bfs_helper(1)


print "Parent db"
print parent

print "State db"
print state

print "Cost"
print cumm_cost

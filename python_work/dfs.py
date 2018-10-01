
#list of vertices
v_db = [1,2,3,4,5]

#Mapping of vertex to list of other vertices
#which signify a edge
vertex = {  
           1 : [2, 3] ,
           2 : [3] ,
           3 : [4],
           4 : [1,5],
           5 : []
         }

state = {}
visited = {}
parent = {}


def dfs_helper(v):
  
   #mark as visiting 
   state[v] = 2;

   edges = vertex[v]

   for edge in edges:
      if state[edge] == 1:
        parent[edge] = v
        print "Visiting " + str(v) + " to " + str(edge)
        dfs_helper(edge)
      elif state[edge] == 2:
          print "Cycle " + str(v) + " ===> " + str(edge)
          continue

   #mark as VISITED
   state[v] = 3


for v in v_db:
   #Mark all vertices as unvisted
   state[v] = 1;

for v in v_db:
     dfs_helper(v)


print "Parent db"
print parent

print "State db"
print state

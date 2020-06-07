
grid = [ [1,0,0,0],
         [1,1,0,1],
         [1,0,1,0],
         [1,0,1,0],
         [0,1,0,1]
       ]


def dfs(row,col):
    if row < 0 or col < 0 or row >= len(grid) or col >= len(grid[0]) or grid[row][col] == 0:
        print "error"
        return 0

    # Mark cell as visited by setting him to 0
    grid[row][col] = 0

    dfs(row-1,col)
    dfs(row+1,col)
    dfs(row,col-1)
    dfs(row,col+1)

    return 1

def count_islands():
    print len(grid)
    print len(grid[0])

    numIslands = 0

    # Do DFS for each cell
    for row in range(0,len(grid)):
        for col in range(0,len(grid[row])):
            print grid[row][col]

            # Exploration
            numIslands += dfs(row, col)

    print "Number of islands ::" + str(numIslands)

if __name__ == "__main__":
    print grid
    count_islands()

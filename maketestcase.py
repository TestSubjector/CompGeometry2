import random

print("Give data points")
x = int(input())
y = x//2

f = open("testcase.txt", "w")
f.write(str(x))
f.write("\n")
for i in range(0,x):
    xi = i
    yi = random.randrange(-y,y+1,2)
    f.write(str(xi))
    f.write(" ")
    f.write(str(yi))
    f.write("\n")
f.close()

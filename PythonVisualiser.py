## Takes input from a text file and plots all points.
## Connects the points in order read and connects last point to first one.
import argparse
import matplotlib.pyplot as plt

def getArgParser():
    ''' Returns ArgParser object to handle command-line args'''
    parser = argparse.ArgumentParser()
    parser.add_argument("filepath",default="./input.ch",nargs="?",help="path of the input file")
    return parser

if __name__ == '__main__':
    parser = getArgParser()
    args = parser.parse_args()
    inputfile = open(args.filepath,"r")
    storeType = inputfile.readline(); # Discarding CH
    print(storeType)
    numberOfPoints, ch_indices = [int(a) for a in inputfile.readline().split()]
    # print(numberOfPoints)
    # print(ch_indices)
    points = []

    for i in range(numberOfPoints):
        x,y,z = inputfile.readline().split()
        points.append([float(x), float(y)])

    if storeType == "CH\n":
        ch_indices = [element for element in map(int,inputfile.readline().split())]

        for point in points:
            plt.plot(point[0],point[1],'bo')
        for i in range(len(ch_indices)-1):
            plt.plot([points[ch_indices[i]][0],points[ch_indices[i+1]][0]],[points[ch_indices[i]][1],points[ch_indices[i+1]][1]],'g-')
        plt.plot([points[ch_indices[0]][0],points[ch_indices[len(ch_indices)-1]][0]],[points[ch_indices[0]][1],points[ch_indices[len(ch_indices)-1]][1]],'g-')
        plt.show()

    if storeType == "CHK\n":
        ch_points = [element for element in map(str,inputfile.readline().split())]
        ch_indices = []
        for item in ch_points:
            x,y = item.split(",")
            ch_indices.append([float(x), float(y)])
        for point in points:
            plt.plot(point[0],point[1],'bo')

        for i in range(len(ch_indices)-1):
            plt.plot([ch_indices[i][0], ch_indices[i+1][0]],[ch_indices[i][1], ch_indices[i+1][1]],'g-')
        plt.plot([ch_indices[0][0], ch_indices[len(ch_indices)-1][0]], [ch_indices[0][1], ch_indices[len(ch_indices)-1][1]],'g-')
        plt.show()

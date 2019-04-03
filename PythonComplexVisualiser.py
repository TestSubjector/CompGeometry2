## Takes input from a text file and plots all points.
## Connects the points in order read and connects last point to first one.

from matplotlib.lines import Line2D
import matplotlib.animation as animation
import time
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
    mng = plt.get_current_fig_manager()
    mng.resize(*mng.window.maxsize())
    inputfile = open(args.filepath,"r")
    storeType = inputfile.readline();
    # print(storeType)
    numberOfPoints, ch_indices = [int(a) for a in inputfile.readline().split()]
    # print(numberOfPoints)
    # print(ch_indices)
    points = []

    for i in range(numberOfPoints):
        x,y,z = inputfile.readline().split()
        points.append([float(x), float(y)])


    # Jarvis
    if storeType == "CHJ\n":
        ch_indices = [element for element in map(int,inputfile.readline().split())]

        for point in points:
            plt.plot(point[0],point[1],'bo')

        for i in range(len(ch_indices)-1):
            for j,point in enumerate(points):
                temp_line = plt.plot([points[ch_indices[i]][0], point[0]],[points[ch_indices[i]][1], point[1]],linewidth = 2,color = 'yellow',alpha = 0.6)
                plt.pause(0.03)
                temp_line[0].remove()
            plt.plot([points[ch_indices[i]][0],points[ch_indices[i+1]][0]],[points[ch_indices[i]][1],points[ch_indices[i+1]][1]],'g-')
        plt.pause(0.03)
        plt.plot([points[ch_indices[0]][0],points[ch_indices[len(ch_indices)-1]][0]],[points[ch_indices[0]][1],points[ch_indices[len(ch_indices)-1]][1]],'g-')
        plt.show()

    if storeType == "CHG\n":
        ch_indices = [element for element in map(int,inputfile.readline().split())]

        for point in points:
            plt.plot(point[0],point[1],'bo')

        stackFile = open("output/output_grahamstack.ch")
        stackPoints = []
        readLine = stackFile.readline()
        while readLine:
            x,y = readLine.split(",")
            stackPoints.append([float(x), float(y)])
            readLine = stackFile.readline()

        returnTracker = []
        count = 0
        for i in range(0, len(stackPoints)-1):
            # if i > 1 and stackPoints[i][0] ==
            if [stackPoints[i][0],stackPoints[i][1]] in returnTracker:
                for j in range(i, returnTracker.index([stackPoints[i][0],stackPoints[i][1]]), -1):
                    plt.plot([stackPoints[j][0],stackPoints[j-1][0]],[stackPoints[j][1], stackPoints[j-1][1]],'w', linewidth=2.0)
                    plt.savefig('figure/image'+str(count)+'.png')
                    count+=1
                    plt.pause(0.5)
            plt.savefig('figure/image'+str(count)+'.png')
            count+=1
            plt.plot([stackPoints[i][0],stackPoints[i+1][0]],[stackPoints[i][1], stackPoints[i+1][1]],'g-')
            returnTracker.append([stackPoints[i][0],stackPoints[i][1]])
            plt.pause(0.5)
        plt.savefig('figure/image'+str(count)+'.png')
        count+=1
        plt.plot([stackPoints[0][0],stackPoints[len(stackPoints)-1][0]],[stackPoints[0][1], stackPoints[len(stackPoints)-1][1]],'g-')
        plt.savefig('figure/image'+str(count)+'.png')
        count+=1
        plt.show()

    if storeType == "CHK\n":
        for point in points:
            plt.plot(point[0],point[1],'bo')

        bridgeFile = open("output/output_kpsbridge.ch")
        bridgePoints = []
        readLine = bridgeFile.readline()
        while readLine:
            x,y = readLine.split(",")
            bridgePoints.append([float(x), float(y)])
            readLine = bridgeFile.readline()
        for i in range(0, len(bridgePoints), 2):
            plt.savefig('figure/image'+str(i)+'.png')
            temp_line = plt.plot([bridgePoints[i][0], bridgePoints[i+1][0]],[bridgePoints[i][1], bridgePoints[i+1][1]],'g-')
            plt.pause(0.5)
        plt.savefig('figure/image'+str(i+2)+'.png')
        plt.plot([ch_indices[0][0], ch_indices[len(ch_indices)-1][0]], [ch_indices[0][1], ch_indices[len(ch_indices)-1][1]],'g-')
        plt.savefig('figure/image'+str(i+4)+'.png')
        plt.show()
        bridgeFile.close()
    inputfile.close()

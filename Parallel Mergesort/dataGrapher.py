import matplotlib.pyplot as plt

# this program is for graphing the data generated by
# my multithreaded mergesort program
# Programmer: Matthew Stroble

if __name__ == "__main__":
    # Settings - Adjust if needed
    # sets the size of the starting array to be tested
    arrayStart = 0

    # last array size to be tested
    arrayMax = 500000000

    # How much to grow the array for the next set of array size to be tested
    stepSize = 1000

    # Y-axis time scale for output graph, if array size being tested < 1000 use 0.01 if arrayMax > 5000 use 1
    # TODO allows system to auto set time scale based on arrayMax.
    timeScaleFactor = 1



    RUNRANGE = o
    # setting up data storage
    serialmergesortData = []
    multithreadedMergesortData = []
    currentMultiThreadFile = []

    print("Reading Data from files")

    serialFile = open("serialData.txt", 'r')

    for i in serialFile:
        serialmergesortData.append(i)
        RUNRANGE += 1

    serialFile.close()

    # reading all multithreaded data files and storing them into a list
    for counter in range(2, 9):
        multithreadedFiles = open("multiThreadedData_" + str(counter) + ".txt", 'r')
        for line in multithreadedFiles:
            currentMultiThreadFile.append(line)

        multithreadedMergesortData.append(currentMultiThreadFile)
        currentMultiThreadFile = []
        multithreadedFiles.close()


    # printing plots of data
    plt.plot(RUNRANGE, serialmergesortData, 'c-', label='Serial Merge Sort')

    
    plt.plot(RUNRANGE, multithreadedMergesortData[0], 'm-', label='2 Threaded Mergesort')
    plt.plot(RUNRANGE, multithreadedMergesortData[1], 'g-', label='3 Threaded Mergesort')
    plt.plot(RUNRANGE, multithreadedMergesortData[2], 'r-', label='4 Threaded Mergesort')
    plt.plot(RUNRANGE, multithreadedMergesortData[3], 'y-', label='5 Threaded Mergesort')
    plt.plot(RUNRANGE, multithreadedMergesortData[4], 'b-', label='6 Threaded Mergesort')
    plt.plot(RUNRANGE, multithreadedMergesortData[5], 'm-', label='7 Threaded Mergesort')
    plt.plot(RUNRANGE, multithreadedMergesortData[6], 'g-', label='8 Threaded Mergesort')

    plt.axis([arrayStart, arrayMax, 0, timeScaleFactor])
    plt.xlabel("Worst Case Decending Order")
    plt.ylabel("Time from default_timer (walltime)")
    plt.title("Matthew Stroble")
    plt.legend(loc='upper left', shadow=False, fontsize='small')
    plt.show()

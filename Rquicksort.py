import numpy as np
import timeit

def partition(arr, low, high):

    size = len(arr)

    random_id = np.random.randint(low, high + 1)
    pivot = arr[random_id]
    swap(arr, random_id, high)

    # Index of smaller element and indicates 
    # the position of pivot found so far
    i = low - 1
    
    # Traverse arr[low..high] and move all smaller
    # elements to the left side. Elements from low to 
    # i are smaller after every iteration
    for j in range(low, high):
        if arr[j] < pivot:
            i += 1
            swap(arr, i, j)
    
    # Move pivot after smaller elements and
    # return its position
    swap(arr, i + 1, high)
    return i + 1

# Swap function
def swap(arr, i, j):
    arr[i], arr[j] = arr[j], arr[i]

def quickSort(arr, low, high):
    if low < high:
        
        # pi is the partition return index of pivot
        pi = partition(arr, low, high)
        
        # Recursion calls for smaller elements
        # and greater or equals elements
        quickSort(arr, low, pi - 1)
        quickSort(arr, pi + 1, high)

# Main driver code
if __name__ == "__main__":
    # arr = np.random.randint(low=0, high=1000, size=5)
    # arr = np.random.randint(low=0, high=10000, size=20)
    # arr = np.random.randint(low=0, high=100000, size=100)
    # arr = np.random.randint(low=0, high=100000, size=300)
    # arr = np.random.randint(low=0, high=100000, size=500)
    # arr = np.random.randint(low=0, high=100000, size=750)
    # arr = np.random.randint(low=0, high=100000, size=1000)
    size = 1000  # specify your array size
    arr = np.arange(size, 0, -1)

    n = len(arr)

    run_time = timeit.timeit(lambda: quickSort(arr, 0, n-1), number=1)
    print(f"Average runtime of 3 runs using 20 values: {run_time:.6f}")

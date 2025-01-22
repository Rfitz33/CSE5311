
# Insertion sort
def insertion_sort(arr):
    # Iterate array
    for i in range(1, len(arr)):
        # Key is current index
        key = arr[i]
        # j is index prior to key
        j = i - 1
        # Move smaller value up in array until it is sorted
        while j >= 0 and key < arr[j]:
            arr[j + 1] = arr[j]
            j -= 1
            arr[j + 1] = key
            return arr

# Selection sort
def selection_sort(arr):
    # Iterate array
    for i in range(len(arr)):
        # Begin with assumption current index is smallest value
        min_idx = i
        # Iterate remaining unsorted to find true min value
        for j in range(i + 1, len(arr)):
            if arr[j] < arr[min_idx]:
                # Update if smaller element discovered
                min_idx = j
        # Move min value to correct position and swap values
        arr[i], arr[min_idx] = arr[min_idx], arr[i]

def bubble_sort(arr):
    # Iterate array
    for i in range(len(arr)):
        # Iterate array again to check for swaps
        for j in range(len(arr) - 1):
            # If current element is greater than next, swap
            if arr[j] > arr[j + 1]:
                arr[j], arr[j + 1] = arr[j + 1], arr[j]
                return arr
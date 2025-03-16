import random
import numpy as np

def partition(arr, low, high):
    # Choose a random pivot index between low and high
    pivot_index = random.randint(low, high)
    pivot_value = arr[pivot_index]
    # Move pivot to the end
    arr[pivot_index], arr[high] = arr[high], arr[pivot_index]
    store_index = low
    for i in range(low, high):
        if arr[i] < pivot_value:
            arr[i], arr[store_index] = arr[store_index], arr[i]
            store_index += 1
    # Move pivot to its final place
    arr[store_index], arr[high] = arr[high], arr[store_index]
    return store_index

def quickselect(arr, low, high, k):
    """
    Returns the kth smallest element (0-indexed) in arr[low:high+1]
    """
    if low == high:
        return arr[low]
    
    pivot_index = partition(arr, low, high)
    
    if k == pivot_index:
        return arr[k]
    elif k < pivot_index:
        return quickselect(arr, low, pivot_index - 1, k)
    else:
        return quickselect(arr, pivot_index + 1, high, k)

# Example usage:
if __name__ == "__main__":
    # Create a sample array
    arr = np.random.randint(low=0, high=50, size=20)
    k = 9  # For example, find the 10th smallest element (0-indexed: k=10-1)
    print(f"Original array: {arr}")
    
    result = quickselect(arr, 0, len(arr) - 1, k)
    print(f"The {k+1}th smallest element is {result}")

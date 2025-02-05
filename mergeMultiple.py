k = int(input("Enter number of arrays: "))
n = int(input("Enter array size: "))
# Read in the k arrays
arrays = []
for i in range(k):
    print(f"Enter {n} elements for array {i+1}, separated by spaces:")
    arr = list(map(int, input().split()))
    # Make sure we only take the first n elements
    arr = arr[:n]
    arrays.append(arr)

# Keep track of a "current index" into each array
indices = [0] * k  # All pointers start at index 0
sorted_array = []

# Continue merging until all arrays are exhausted
while True:
    # Check if all arrays are completely traversed
    exhausted = True
    for i in range(k):
        if indices[i] < n:  # array still has elements left
            exhausted = False
            break
    if exhausted:
        break
    # Find the smallest element among the unexhausted arrays
    min_val = None
    min_array_index = -1

    for i in range(k):
        if indices[i] < n:  # array i has elements left
            current_val = arrays[i][indices[i]]
            if min_val is None or current_val < min_val:
                min_val = current_val
                min_array_index = i
    # Append the smallest found to the final sorted list
    sorted_array.append(min_val)
    # Increment the index in the array we took the element from
    indices[min_array_index] += 1

print("Sorted array:", sorted_array)
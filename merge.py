import timeit

def merge_sort(arr):
    # Base case: already sorted
    if len(arr) <= 1:
        return arr

    # Divide step: split array in two parts (equal size)
    mid = len(arr) // 2
    left = merge_sort(arr[:mid])
    right = merge_sort(arr[mid:])

    # Conquer step: merge the two sorted parts
    return merge(left, right)

def merge(left, right):
    merged = []
    i, j = 0, 0

    # Merge the two sorted lists
    while i < len(left) and j < len(right):
        if left[i] <= right[j]:
            merged.append(left[i])
            i += 1
        else:
            merged.append(right[j])
            j += 1

    # If elements remain in 'left' or 'right', add them to the list
    merged.extend(left[i:])
    merged.extend(right[j:])

    return merged

if __name__ == "__main__":
    my_list = [5,2,4,7,1,3,2,6]  
    sorted_list = merge_sort(my_list)
    print("Sorted:", sorted_list)
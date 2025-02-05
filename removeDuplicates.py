
print("Please input array elements, separate by commas. Press enter/return when finished.")
user_input = input()
#split input into unique values and fill array
sorted_arr = list(map(int, user_input.split(",")))
# output array
unique_values = []

i = 0
while i < len(sorted_arr):
    current_val = sorted_arr[i]
    unique_values.append(current_val)
    # Move forward in the array as long as the next value is the same
    j = i + 1
    while j < len(sorted_arr) and sorted_arr[j] == current_val:
        j += 1
    # Now 'j' is at the next new value
    i = j
print("Unique Values:", unique_values)

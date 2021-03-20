def get_order_and_ordered_list(element, list0):
    length = len(list0)
    if length == 0:
        list0.append(element)
        return 0, list0
    else:
        up = length - 1
        down = 0
        
        while True:
            mid = (up + down) // 2
            if element > list0[mid]:
                down = mid + 1
            elif element < list0[mid]:
                up = mid - 1
            else:
                j = 0
                while True:
                    j += 1
                    if mid + j >= length:
                        list0.insert(length, element)
                        return length, list0

                    if element != list0[mid + j]:
                        list0.insert(mid + j, element)
                        return (mid + j), list0
            if down > up:
                break
        mid = down
        list0.insert(mid, element)
        return (mid), list0


def get_list_of_other_idx(ordered_list, max_num):
    a_idx = 0
    new_list = []
    for idx in ordered_list:
        a_idx += 1
        if a_idx >= idx:
            continue
        while a_idx != idx:
            new_list.append(str(a_idx))
            a_idx += 1
    a_idx = ordered_list[-1] + 1
    while a_idx < max_num + 1:
        new_list.append(str(a_idx))
        a_idx += 1
    return new_list

    
line1 = (input())
list1 = line1.split(' ')
A = int(list1[0])
B = int(list1[1])
N = int(list1[2])

timeA = 0
dutyA = []
timeB = 0
dutyB = []
for i in range(N):
    line = (input())
    list1 = line.split(' ')
    time = int(list1[0])
    color = list1[1]
    number = int(list1[2])
    if color == 'B':
        if timeA <= time:
            timeA = time
        for j in range(number):
            dutyA.append(timeA)
            timeA += A


    elif color == 'R':
        if timeB <= time:
            timeB = time
        for k in range(number):
            dutyB.append(timeB)
            timeB += B

    else:
        raise Exception('Color should be "R" or "B"!')
    
orderA = []
orderB = []
s_orderB = []

new_dutyA = list(dutyA)
for idx_b, db in enumerate(dutyB):
    idx, _ = get_order_and_ordered_list(db, new_dutyA)
    orderB.append(idx + 1)
    s_orderB.append(str(idx + 1))

orderA = get_list_of_other_idx(orderB, len(dutyA) + len(dutyB))

    
print(len(dutyA))
print(" ".join(orderA))
print(len(dutyB))
print(" ".join(s_orderB))
import sys
string = sys.stdin.readlines()
answer_list = []
stack = []

for i in string[:-1]:
    if i=='.':
        break
    stack.clear()
    for j in i:
        
        if j in '([':
            stack.append(j)

        elif j == ']':
            if len(stack) == 0 or stack.pop()!='[':
                print('no')
   
                break
        if j == ')':
            if len(stack) == 0 or stack.pop()!='(':
                print('no')
       
                break
        elif j=='.':
            if len(stack) == 0:
                print('yes')
            else:
                print('no')


    

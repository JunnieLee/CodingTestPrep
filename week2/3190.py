from collections import deque
import sys
from typing import *

def Rotate(dir: str) -> List[int]:
    if dir=='L': #왼쪽으로 회전
        if cur_dir==[1,0]:
            return [0,-1]
        elif cur_dir==[0,1]:
            return [1,0]
        elif cur_dir==[-1,0]:
            return [0,1]
        elif cur_dir==[0,-1]:
            return [-1,0]
    elif dir=='D': #오른쪽으로 회전
        if cur_dir==[1,0]:
            return [0,1]
        elif cur_dir==[0,1]:
            return [-1,0]
        elif cur_dir==[-1, 0]:
            return [0,-1]
        elif cur_dir==[0, -1]:
            return [1,0]

n=int(sys.stdin.readline())
k=int(sys.stdin.readline())
board=[[0]*(n+1) for _ in range(n+1)]
#print(board)
for _ in range(k):
    apple_y, apple_x = map(int, sys.stdin.readline().split())
    board[apple_x][apple_y]=1
#print(board)
l=int(sys.stdin.readline())
cur_dir=[1,0]
cur_pos=[1,1]
prev_time=0
body=deque()
moves=[] #0:t 1:dir
for _ in range(l):
    t,c = sys.stdin.readline().split()
    moves.append([int(t),c])
for i in range(len(moves)+1):
    if i<len(moves):
        moving_time=moves[i][0]-prev_time
        for j in range(moving_time):
            x=cur_pos[0]
            y=cur_pos[1]
            body.append([x,y])
            cur_pos[0]+=cur_dir[0]
            cur_pos[1]+=cur_dir[1]
            #print(cur_pos, body)
            if cur_pos[0]<=0 or cur_pos[0]>n or cur_pos[1]<=0 or cur_pos[1]>n or cur_pos in body:
                print(prev_time+j+1)
                sys.exit()
            if board[cur_pos[0]][cur_pos[1]]==0:
                body.popleft()
            elif board[cur_pos[0]][cur_pos[1]]==1:
                board[cur_pos[0]][cur_pos[1]]=0
                #print('eat apple')
        prev_time+=moving_time
        cur_dir=Rotate(moves[i][1])
    else:
        moving_time=0
        while True:
            moving_time+=1
            cur_pos[0] += cur_dir[0]
            cur_pos[1] += cur_dir[1]
            if cur_pos[0]<=0 or cur_pos[0]>n or cur_pos[1]<=0 or cur_pos[1]>n or cur_pos in body:
                print(prev_time+moving_time)
                break
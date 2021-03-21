# https://www.acmicpc.net/problem/3190

# point : 되게 복잡해보이지만, 문제가 요구하는 조건들을 하나하나 충족시키도록 시뮬레이션 가능케 코드를 작성해나가다 보면 풀 수 있음.

'''
state 정리
0 : 초기화 값 (default) / 사과가 없는곳
1 : 사과가 있는곳
'
** 뱀은 (0, 0)에서 시작
'''

from collections import deque
# 뱀 좌표는 앞, 뒤 가 계속 업데이트 되어야 하니 양쪽으로 넣고 뺄 수 있는 deque가 적절

# [1] input들 쭉 받고 필요한 변수들 선언 --------------------------------

N = int(input())  # 보드 크기 input 받기
K = int(input())  # 사과 갯수 input 받기
# 0으로 초기화된 2차원 배열(N x N)을 만들기
arr = [[0] * N for _ in range(N)] # map
# 사과 위치 input 받기
for _ in range(K):
    a, b = map(int, input().split())  # 행, 열
    arr[a - 1][b - 1] = 1  # 사과 위치 저장
# 뱀의 방향 변환 횟수 input 받기
L = int(input())
d_change_info = {}  # 방향관련 정보 저장용 dict
for i in range(L):
    X, C = input().split()  # X - 초, C -방향 (L/D)  # 둘다 char 로 저장됨
    d_change_info[int(X)] = C  # X가 key, C가 value

# [2]   --------------------------------

# 뱀 위치
snake = deque([(0, 0)])

# ********** 이부분의 abstraction 이 이문제 최대 포인트!!! **********
# 동서남북 좌표변화
move = [(0,1),(1,0),(0,-1),(-1,0)] # 동남서북 (시계방향~) -----------> 이 부분도 유의!!!
d = 0  # 처음엔 동쪽 방향
time = 0  # 초
x, y = 0, 0  # 뱀 머리부분 좌표값
# **********************************************************************


# [3]   --------------------------------
# 방향 전환 해주는 함수
def change (direction) :
    global d  # global 변수 d를 사용해줄꺼니까 이렇게 해준다
    if direction == 'D':  # 오른쪽
        d = (d+1) % 4
    else:  # 왼쪽
        d = (d-1) % 4
    return d

# N x N 범위를 벗어나지 않았는지 확인하는 함수
def check_valid (nx,ny) :  # 얘가 false라고 뜨면 벽에 부딛친거겠지
    if (0 <= nx < N) and (0 <= ny < N):
        return True
    else:
        return False

# main 실행 코드
while True:
    # 1초씩 시간 증가 (한 cycle)
    time += 1
    # 최신 업데이트된 d 정보를 이용해 head 이동 관리
    x += move[d][0]
    y += move[d][1]
    # 만약 방향을 바꿔야 하는 time 일 경우 --> 정확히 info check 해서 방향 바꿔줌
    # (다음 cycle 에서 활용할 d값 먼저 update 시켜줌)
    if time in d_change_info.keys() :
        d = change(d_change_info[time])

    if check_valid(x, y): # 벽에 부딛치지 않았다는 전제 하에
        # (*) 뱀이 자기 몸에 부딛힌 경우 -> game over
        if (x, y) in snake : break
        # (1) 다음 위치에 사과가 있는 경우 : 길이 + 1
        elif arr[x][y] == 1:
            arr[x][y] = 0  # 그 자리에 있는 사과를 먹어치워버림!
            snake.append((x, y))
        # (2) 다음 위치에 사과가 없는 경우 : 길이 유지
        elif arr[x][y] == 0:
            snake.append((x, y))
            snake.popleft()
    else :
        break # 벽에 부딛혔다면 -> game over


print(time)

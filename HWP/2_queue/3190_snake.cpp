#include <iostream>
#include <vector>
#include <queue>
using namespace std;
int N, K, L;
int map[101][101];
int Dir[4][2] = { {-1 ,0}, { 0,1} , {1,0}, {0,-1} }; // 방향 위 오른쪽 아래 왼쪽으로 90도씩 회전 고려 
class Snake {
public:
	Snake() {
		this->body.push_back(make_pair(this->headx, this->heady)); // 최초 뱀 바디길이 1로 
	}
	bool move() { // 움직이고나서 true이면 계속 진행, false면 게임 끝남 
		int nx = this->headx + Dir[d][0];  // 다음 x 좌표
		int ny = this->heady + Dir[d][1]; // 다음 y 좌표 
		for (int i = 0; i < body.size(); ++i) { // 다음 x y 좌표가 body와 만날 경우 종료 
			if (nx == body[i].first && ny == body[i].second) return false;
		}
		if (nx < 0 || nx >= N || ny < 0 || ny >= N) { // 경계와 닿을 경우 종료 
			return false;
		}
		if (map[nx][ny] == 1) { // 사과 일 경우 몸 늘린다.
			body.push_back(make_pair(nx, ny));
			this->headx = nx;
			this->heady = ny;
			map[nx][ny] = 0;
			return true;
		}
		else { // 사과가 아닐 경우 머리는 다음위치로 가고 나머지는 그 전 몸 위치로 따라간다 
			this->body = vector<pair<int, int>>(this->body.begin() + 1, this->body.end());
			body.push_back(make_pair(nx, ny));
			this->headx = nx;
			this->heady = ny;
			return true;
		}
	}
	int headx = 0;
	int heady = 0;
	int d = 1;
	vector<pair<int, int>> body;
};
void PrintSnake(Snake s) { // 로그를 위한 프린트 코드 
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			bool isBody = false;
			for (int k = 0; k < s.body.size(); ++k) {
				if (s.body[k].first == i && s.body[k].second == j) {
					isBody = true;
					break;
				}
			}
			if (isBody) printf("* ");
			else printf("0 ");
		}
		printf("\n");
	}
	printf("\n");
}
int main(int argc, const char* argv[]) {
	scanf("%d", &N);
	scanf("%d", &K);
	for (int i = 0; i < K; ++i) {
		int x, y;
		scanf("%d %d", &x, &y);
		map[x - 1][y - 1] = 1;
	}
	queue<pair<int, char>> q; // q를 이용해서 사과 먹으면 뺄 수 있도록 
	scanf("%d", &L);
	for (int i = 0; i < L; ++i) {
		int t;
		char c;
		scanf("%d %c", &t, &c);
		q.push(make_pair(t, c)); // 시간, 방향으로 큐에 푸시 
	}
	Snake s;
	int time = 0;
	bool result = true;
	while (true) {
		time++;
		result = s.move(); // 움직이고 
		//printf("%d\n", time);
		//PrintSnake(s);
		if (!result) break;		// 실패이면 게임 종료
		if (!q.empty()) { // 큐가 비어있지 않을 경우 
			int timeTurn = q.front().first; // 시간이 되었는지 확인하고 
			if (time == timeTurn) { // 시간 이 되었으면 
				if (q.front().second == 'D') { // 방향에 맞게 D 
					s.d += 1;
					if (s.d >= 4) s.d = 0;
				}
				else if (q.front().second == 'L') { // L로 회전 하여 다음 턴에 적용될 수 있도록.
					s.d -= 1;
					if (s.d < 0) s.d = 3;
				}
				q.pop();
			}
		}
	}
	printf("%d\n", time);
	return 0;
}
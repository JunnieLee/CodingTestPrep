#include <iostream>
#include <deque>
using namespace std;

int **map;
int N;
int K;
int L;
char head_c='E';
char tail_c='E';
char* head_dir=&head_c;
char* tail_dir=&tail_c;

int time_cnt = 0;

int x_head = 0, y_head = 0;
int x_tail = 0, y_tail = 0;
int len = 0;





// move function
void move(char* dir, int &x, int &y)
{
    switch (*dir)
    {

    case 'N':
        x = x - 1;
        break;

    case 'W':
        y = y - 1;
        break;

    case 'S':
        x = x + 1;
        break;

    case 'E':
        y = y + 1;
        break;

    default:
        cout << "error"
             << "\n";
        break;
    }
    return;
}

// turn function
void turn(char *dir, char &rot)
{
    switch (*dir)
    {

    case 'N':
        if (rot == 'L')
            *dir = 'W';
        else
            *dir = 'E';
        break;

    case 'W':
        if (rot == 'L')
            *dir = 'S';
        else
            *dir = 'N';
        break;

    case 'S':
        if (rot == 'L')
            *dir = 'E';
        else
            *dir = 'W';
        break;

    case 'E':
        if (rot == 'L')
        {
            *dir = 'N';
        }
        else
            *dir = 'S';
        break;

    default:
        cout << "error"
             << "\n";
        break;
    }
    return;
}

int main()
{
    
    cin >> N >> K;

    // initializing map data
    // 0:normal
    // 1:snake
    // 2:apple
    map = new int *[N];
    for (int i = 0; i < N; i++)
    {
        map[i] = new int[N];
        for (int j = 0; j < N; j++)
        {
            map[i][j] = 0;
        }
    }
    map[0][0] = 1;
    if (K >= 1)
    {
        for (int i = 0; i < K; i++)
        {
            int row, col;
            cin >> row >> col;
            map[row - 1][col - 1] = 2;
        }
    }
    cin >> L;

    deque<pair<int, char>> head_info;
    deque<pair<int, char>> tail_info;
    // pushing information about rotation of head
    for (int i = 0; i < L; i++)
    {
        int a;
        char b;
        cin >> a >> b;
        pair<int, char> p = make_pair(a, b);
        head_info.push_back(p);
    }

    while (1)
    {
        move(head_dir, x_head, y_head);

        time_cnt++;

        if (x_head < 0 || x_head >= N || y_head < 0 || y_head >= N)
        {
            // checking edge condition
            break;
        }
        if (map[x_head][y_head] == 0)
        { // blank, move tail
            map[x_head][y_head] = 1;
            map[x_tail][y_tail] = 0;
            move(tail_dir, x_tail, y_tail);
        }
        else if (map[x_head][y_head] == 1)
        { // snake it self, die
            break;
        }
        else if (map[x_head][y_head] == 2)
        { // apple, dont move tail
          // we have to refresh when tail starts to rotate, so we use deque instead of queue
            map[x_head][y_head] = 1;
            for(int i=0; i<tail_info.size();i++)
            {
                tail_info[i].first++;
            }
            len++;
        }

        if (!head_info.empty() && time_cnt == head_info.front().first)
        {
            // rotate head and push information about rotation of tail
            turn(head_dir, head_info.front().second);
            pair<int, char> p = make_pair(len + time_cnt, head_info.front().second);
            head_info.pop_front();
            tail_info.push_back(p);
        }
        if (!tail_info.empty() && time_cnt == tail_info.front().first)
        {
            // rotate tail
            turn(tail_dir, tail_info.front().second);
            tail_info.pop_front();
        }
    }
    cout << time_cnt << endl;
    return 0;
}
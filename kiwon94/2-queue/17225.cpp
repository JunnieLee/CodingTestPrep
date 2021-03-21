#include <iostream>
#include <stdio.h>
#include <queue>
#include <vector>

int A, B, N;

int time_now = 1;
int gift_num = 1;

bool s_ready = true;
bool j_ready = true;

int s_ready_time = -1;
int j_ready_time = -1;

using namespace std;

int main()
{
    vector<int> sang;
    vector<int> jisu;

    queue<int> blue;
    queue<int> red;

    scanf("%d %d %d", &A, &B, &N);
    //cin >> A >> B >> N;
    for (int i = 0; i < N; i++)
    {
        int time_coming;
        char color;
        int count;
        scanf("%d %c %d", &time_coming, &color, &count);
        //cin >> time_coming >> color >> count;
        if (color == 'B')
        {
            for (int j = 0; j < count; j++)
            {

                blue.push(time_coming);
            }
        }
        else if (color == 'R')
        {
            for (int j = 0; j < count; j++)
            {

                red.push(time_coming);
            }
        }
    }

    while (!blue.empty() || !red.empty())
    {
        if (time_now == s_ready_time && s_ready == false)
        {
            s_ready = true;
        }
        if (time_now == j_ready_time && j_ready == false)
        {
            j_ready = true;
        }


        if (A == 0)
        {
            while (blue.front() == time_now)
            {
                sang.push_back(gift_num);
                gift_num++;

                blue.pop();

            }
        }
        else if (blue.front() == time_now && s_ready == true)
        {
            sang.push_back(gift_num);
            gift_num++;

            s_ready = false;
            s_ready_time = time_now + A;

            blue.pop();
            if ((!blue.empty()) && (blue.front() < time_now + A))
                blue.front() = time_now + A;
        }

        if (B == 0)
        {
            while (red.front() == time_now)
            {
                jisu.push_back(gift_num);
                gift_num++;

                red.pop();

            }
        }

        else if (red.front() == time_now && j_ready == true)
        {
            jisu.push_back(gift_num);
            gift_num++;

            j_ready = false;
            j_ready_time = time_now + B;

            red.pop();
            if ((!red.empty()) && (red.front() < time_now + B))
                red.front() = time_now + B;
        }
        //cout<<time_now<<endl;
        time_now++;
    }

    cout << sang.size() << endl;
    for (int i = 0; i < sang.size(); i++)
    {
        printf("%d ", sang[i]);
    }

    printf("\n");
    cout << jisu.size() << endl;
    for (int i = 0; i < jisu.size(); i++)
    {
        printf("%d ", jisu[i]);
    }

    return 0;
}
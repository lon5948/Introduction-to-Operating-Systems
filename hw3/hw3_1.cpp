#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct process_info {
    int arrival_time;
    int burst_time;
    int finish_time;
};

int main() {
    int process_num;
    cin >> process_num;
    vector<process_info> process(process_num);
    vector<int> remaining_burst(process_num);
    for(int i = 0; i < process_num; i++) {
        cin >> process[i].arrival_time;
    }
    for(int i = 0; i < process_num; i++) {
        cin >> process[i].burst_time;
        remaining_burst[i] = process[i].burst_time;
    }

    int current_time = 0;
    int completed_num = 0;
    int prev = -1;
    int start = 0;
    priority_queue< pair<int, int>, vector< pair<int, int> >, greater< pair<int, int> > > pq;
    while(completed_num != process_num) {
        for(int i = start; i < process_num; i++) {
            if(process[i].arrival_time <= current_time) {
                pq.push(make_pair(remaining_burst[i] ,i));
                start++;
            }
        }

        if(pq.empty()) {
            current_time++;
        }
        else {
            int min_burst = pq.top().first;
            int index = pq.top().second;
            pq.pop();
            if (!pq.empty()) {
                if (pq.top().first == min_burst && pq.top().second == prev) {
                    int back1 = min_burst;
                    int back2 = index;
                    min_burst = pq.top().first;
                    index = pq.top().second;
                    pq.pop();
                    pq.push(make_pair(back1 ,back2));
                }
            }
            prev = index;
            current_time++;
            remaining_burst[index]--;
            
            if(remaining_burst[index] == 0) {
                process[index].finish_time = current_time;
                completed_num++;
            }
            else {
                pq.push(make_pair(remaining_burst[index] ,index));
            }
        }  
    }
    int total_waiting_time = 0;
    int total_turnaround_time = 0;

    for (int i=0; i<process_num; i++) {
        int waiting = process[i].finish_time - process[i].arrival_time - process[i].burst_time;
        int turnaround = process[i].finish_time - process[i].arrival_time;
        cout << waiting << " " << turnaround << endl;
        total_waiting_time += waiting;
        total_turnaround_time += turnaround;
    }
    cout << total_waiting_time << endl;
    cout << total_turnaround_time << endl;

    return 0;
}

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
    int process_num, time_quantum;;
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
    cin >> time_quantum;

    int current_time = 0;
    int completed_num = 0;
    int start = 0;
    int prev = -1;
    queue<int> RRq;
    queue<int> FCFSq;
    while(completed_num != process_num) {
        for(int i = start; i < process_num; i++) {
            if(process[i].arrival_time <= current_time) {
                RRq.push(i);
                start++;
                if (prev != -1) {
                    if (remaining_burst[prev] > 0) {
                        FCFSq.pop();
                        FCFSq.push(prev);
                    }
                }
            }
        }

        if(RRq.empty() && FCFSq.empty()) {
            current_time++;
        }
        else if (RRq.empty()) {
            int FCFS_index = FCFSq.front();
            current_time++;
            remaining_burst[FCFS_index]--;
            if (remaining_burst[FCFS_index] == 0) {
                FCFSq.pop();
                process[FCFS_index].finish_time = current_time;
                completed_num++;
            }
            prev = FCFS_index;
        }
        else {
            int index = RRq.front();
            RRq.pop();
            if (remaining_burst[index] <= time_quantum) {
                current_time += remaining_burst[index];
                remaining_burst[index] = 0;
                process[index].finish_time = current_time;
                completed_num++;
            }
            else {
                current_time += time_quantum;
                remaining_burst[index] -= time_quantum;
                FCFSq.push(index);
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

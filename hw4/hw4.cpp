#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <unordered_map>
#include <list>
using namespace std;

int main() {
    int frame_num, rs_length, reference, victim;
    cin >> frame_num >> rs_length;

    vector<int> rs_vec(rs_length);
    vector<int> count(3, 0);

    for (int i = 0; i < rs_length; i++) {
        cin >> rs_vec[i];
    }
    
    // FIFO
    queue<int> q1;
    vector<int> frame1;
    for (int i = 0; i < rs_length; i++) {
        reference = rs_vec[i];
        if (find(frame1.begin(), frame1.end(), reference) == frame1.end()) { 
            count[0]++;
            if (frame1.size() < frame_num) { 
                frame1.push_back(reference);
                q1.push(reference);
            }
            else {
                victim = q1.front();
                vector<int>::iterator it = find(frame1.begin(), frame1.end(), victim);
                q1.pop();
                frame1[distance(frame1.begin(), it)] = reference;
                q1.push(reference);
            }
        }
    }
    
    // LRU
    list<int> cache2;
    unordered_map< int, list<int>::iterator > record2;
    for (int i = 0; i < rs_length; i++) {
        reference = rs_vec[i];
        if (record2.find(reference) == record2.end()) { // not hit
            count[1]++;
            if (record2.size() == frame_num) {
                victim = cache2.back();
                record2.erase(victim);
                cache2.pop_back();
            }
            cache2.push_front(reference);
            record2[reference] = cache2.begin();
        }
        else { // hit
            cache2.splice(cache2.begin(), cache2, record2[reference]);
            record2[reference] = cache2.begin();
        }
    }
    
    // LFU
    vector<int> m3; 
    vector<int> frequency;
    for (int i = 0; i < rs_length; i++) {
        reference = rs_vec[i];
        vector<int>::iterator itr = find(m3.begin(),m3.end(),reference);
        if (itr == m3.end()) { 
            count[2]++;
            if (m3.size() < frame_num) { 
                m3.push_back(reference);
                frequency.push_back(1);
            }
            else {
                int min_freq = *min_element(frequency.begin(), frequency.end(), [](const auto& l, const auto& r) {
                    return l <= r; 
                });
                vector<int>::iterator it = find(frequency.begin(), frequency.end(), min_freq);
                frequency.erase(it);
                m3.erase(m3.begin()+distance(frequency.begin(), it));
                m3.push_back(reference);
                frequency.push_back(1);
            }
        }
        else {
            frequency[distance(m3.begin(), itr)] += 1;
        }
    }
    
    for (int c = 0; c < 3; c++) 
        cout << count[c] << endl;

    return 0;
}

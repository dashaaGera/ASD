#include "../lib_priority_queue/priority_queue.h"
#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>

int main() {
    PriorityQueue<string> queue;
    std::vector<string> times = { "12.30", "12.35", "12.50", "12.55", "13.10", "13.15",
                      "14.05", "14.07", "14.30",  "14.50" };
    std::vector<string>  names = { "Ivanov", "Petrov", "Voronin", "Sidorov", "Vasilev", "Mihajlov",
                      "Borisov", "Vladimirov", "Fedorov", "Nesterov" };
    std::vector<int > priors = { 2, 3, 2, 1, 2, 3, 1, 1, 2, 2 };

    int n = names.size();
    int idx = 0;


    cout << "Result: " << endl;

    // 12:30 -15:50  20 min
    for (int time = to_minutes("12.30"); time <= to_minutes("15.50"); time += 20) {
        while (idx < n && to_minutes(times[idx]) <= time) {
            queue.push(names[idx], priors[idx]);
            idx++;
        }

        if (!queue.is_empty()) {
            cout << queue.pop() << endl;
        }
    }

    return 0;
}
#include <bits/stdc++.h>


using namespace std;
using namespace chrono;

// O(n^3)
int n3(const vector<int>& numbers) {
    int n = numbers.size();
    int best = 0;

    for (int a = 0; a < n; a++) {
        for (int b = a; b < n; b++) {
            int sum = 0;

            for (int k = a; k <= b; k++) {
                sum += numbers[k];
            }

            best = max(best, sum);
        }
    }
    return best;
}

// O(n^2)
int n2(const vector<int>& numbers) {
    int n = numbers.size();
    int best = 0;

    for (int a = 0; a < n; a++) {
        int sum = 0;

        for (int b = a; b < n; b++) {
            sum += numbers[b];
            best = max(best, sum);
        }
    }
    return best;
}

// O(n) - Kadane's Algorithm
int n1(const vector<int>& numbers) {
    int best = 0, sum = 0;

    for (int k = 0; k < numbers.size(); k++) {
        sum = max(numbers[k], sum + numbers[k]);
        best = max(best, sum);
    }
    return best;
}

// Benchmarking function
template <typename Function>
long long benchmark(Function func, const vector<int>& numbers,
                    int& answer) {

    auto start = steady_clock::now();

    answer = func(numbers);

    auto stop = steady_clock::now();

    return duration_cast<nanoseconds>(
        stop - start
    ).count();
}

int main() {

    // Generate random input
    int n = 500;

    mt19937 rng(random_device{}());
    uniform_int_distribution<int> dist(-100, 100);

    vector<int> numbers(n);

    for (int i = 0; i < n; i++) {
        numbers[i] = dist(rng);
    }

    // Execute all three algorithms
    int ans3, ans2, ans1;

    long long time3 = benchmark(n3, numbers, ans3);
    long long time2 = benchmark(n2, numbers, ans2);
    long long time1 = benchmark(n1, numbers, ans1);

    // Verify correctness
    cout << "\n========== RESULTS ==========\n";

    cout << "Input size: " << n << "\n";
    cout << "Maximum subarray sum: " << ans1 << "\n";

    if (ans1 == ans2 && ans2 == ans3) {
        cout << "Correctness check: match\n";
    }
    else {
        cout << "Correctness check: error\n";
    }

    cout << "\n========== TIMINGS ==========\n";

    cout << left << setw(15) << "Algorithm"
         << right << setw(15) << "Time (ns)"
         << "\n";

    cout << string(30, '-') << "\n";

    cout << left << setw(15) << "O(n^3)"
         << right << setw(15) << time3 << "\n";

    cout << left << setw(15) << "O(n^2)"
         << right << setw(15) << time2 << "\n";

    cout << left << setw(15) << "O(n)"
         << right << setw(15) << time1 << "\n";


    // Visual comparison (logarithmic scale)
    cout << "\n========== VISUAL COMPARISON ==========\n";
    cout << "(Longer bars indicate slower execution)\n\n";

    long long maxTime = max({time1, time2, time3});

    auto displayBar = [&](string name, long long t) {

        int length = 1;

        if (t > 0 && maxTime > 0) {
            length = 1 + 39 * log10(1.0 + 9.0 * t / maxTime);
        }

        cout << left << setw(10) << name << "| ";

        for (int i = 0; i < length; i++) {
            cout << "❚";
        }

        cout << " (" << t << " ns)\n";
    };

    displayBar("O(n^3)", time3);
    displayBar("O(n^2)", time2);
    displayBar("O(n)", time1);

    cout << "\n=======================================\n";

    return 0;
}

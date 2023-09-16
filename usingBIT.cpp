#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class FenwickTree {
public:
    FenwickTree(int size) : tree(size + 1, 0) {}

    void update(int idx, int val) {
        idx++;
        while (idx < tree.size()) {
            tree[idx] += val;
            idx += (idx & -idx);
        }
    }

    int query(int idx) {
        idx++;
        int sum = 0;
        while (idx > 0) {
            sum += tree[idx];
            idx -= (idx & -idx);
        }
        return sum;
    }

private:
    vector<int> tree;
};

int countRangeSum(vector<int>& nums, int lower, int upper) {
    int n = nums.size();
    vector<long long> prefix_sum(n + 1, 0);
    for (int i = 0; i < n; i++) {
        prefix_sum[i + 1] = prefix_sum[i] + nums[i];
    }

    vector<long long> sorted_sum(prefix_sum.begin(), prefix_sum.end());
    sort(sorted_sum.begin(), sorted_sum.end());

    FenwickTree bit(n + 1);
    int count = 0;

    for (int i = 0; i <= n; i++) {
        int left = lower_bound(sorted_sum.begin(), sorted_sum.end(), prefix_sum[i] - upper) - sorted_sum.begin();
        int right = upper_bound(sorted_sum.begin(), sorted_sum.end(), prefix_sum[i] - lower) - sorted_sum.begin();
        count += bit.query(right) - bit.query(left);
        bit.update(lower_bound(sorted_sum.begin(), sorted_sum.end(), prefix_sum[i]) - sorted_sum.begin(), 1);
    }

    return count+1;
}

int main() {
    int n;
    cout << "Enter the number of elements in the array: ";
    cin >> n;

    vector<int> A(n);
    cout << "Enter the elements of the array: ";
    for (int i = 0; i < n; i++) {
        cin >> A[i];
    }

    int lower, upper;
    cout << "Enter the lower bound: ";
    cin >> lower;
    cout << "Enter the upper bound: ";
    cin >> upper;

    int result = countRangeSum(A, lower, upper);
    cout << "Number of range sums within [" << lower << ", " << upper << "]: " << result << endl;

    return 0;
}

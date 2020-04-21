#include <algorithm>
#include <iostream>
#include <tuple>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class fenwick_tree {
private:
    int get_parent(const int index) const {
        return index - (index & -index);
    }

    int get_next(const int index) const {
        return index + (index & -index);
    }

public:
    void update_ft(vector<int>& fenwick_tree, int val, int index) {
        while (index < fenwick_tree.size()) {
            fenwick_tree[index] += val;
            index = get_next(index);
        }
    }

    vector<int> create_empty_tree(size_t len) {
        vector<int> empty_fenwick_tree(len + 1);
        return empty_fenwick_tree;
    }

    int get_sum(const vector<int>& fenwick_tree, int index) {
        int sum = 0;
        while (index > 0) {
            sum += fenwick_tree[index];
            index = get_parent(index);
        }
        return sum;
    }

    // sum [left, right]
    int sum_range(const vector<int>& fenwick_tree, int left, int right) {
        return get_sum(fenwick_tree, right) - get_sum(fenwick_tree, left - 1);
    }
};

// Example of possible usage
int main() {
    int n;
    cin >> n;
    vector<vector<int>> pairs(n);
    vector<int> compress;
    int max_w = 0;
    for (int i = 0; i != n; ++i) {
        int h, w;
        cin >> h >> w;
        if (h > w) swap(h, w);
        compress.push_back(h);
        compress.push_back(w);
        pairs[i] = {h, w};
        max_w = max(max_w, w);
    }
    sort(compress.begin(), compress.end());
    unordered_map<int, int> map;

    compress.erase(unique(compress.begin(), compress.end()), compress.end());
    for (int i = 0; i != compress.size(); ++i) {
        map[compress[i]] = i + 1;
    }

    max_w = map[max_w];
    sort(pairs.begin(), pairs.end(), [](const vector<int>& v1, const vector<int>& v2){
        return tie(v1[0], v1[1]) > tie(v2[0], v2[1]);
    });

    fenwick_tree* ft = new fenwick_tree();
    vector<int> tree = ft->create_empty_tree(max_w);
    int ans = 0;
    unordered_set<int> group;
    for (int i = 0; i != n; ++i) {
        int w_i = map[pairs[i][1]];
        if (ft->sum_range(tree, w_i + 1, max_w) == 0) {
            ++ans;
        }
        group.insert(w_i);
        if ((i < n-1) && (pairs[i][0] != pairs[i+1][0])) {
            for (int prev_w : group) {
                ft->update_ft(tree, 1, prev_w);
                group.erase(prev_w);
            }
        }
    }
    cout << ans << endl;
    return 0;
}

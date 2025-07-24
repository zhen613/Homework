#include <iostream>
#include <vector>
using namespace std;
vector<vector<int>> powerset(vector<int>& s, int index) {
    if (index < 0) {
        vector<vector<int>> result = {{}};
        return result;
    }
    int x = s[index];
    vector<vector<int>> subsets = powerset(s, index - 1);
    vector<vector<int>> newSubsets = subsets;

    for (vector<int>& subset : subsets) {
        subset.push_back(x);
        newSubsets.push_back(subset);
    }
    return newSubsets;
}
int main() {
    vector<int> s = {1, 2, 3};
    vector<vector<int>> result = powerset(s, s.size() - 1);
    for (vector<int>& subset : result) {
        cout << "{";
        for (int i = 0; i < subset.size(); i++) {
            cout << subset[i];
            if (i < subset.size() - 1) cout << ", ";
        }
        cout << "}" << endl;
    }
    return 0;
}

//遞迴
#include iostream
using namespace std;
int Ackerman(int m, int n) {
    if (m == 0) {
        return n + 1;
    } else if (m > 0 && n == 0) {
        return Ackerman(m - 1, 1);
    } else if (m > 0 && n > 0) {
        return Ackerman(m - 1, Ackerman(m, n - 1));
    }
}

int main() {
    int result;
    result = Ackerman(2, 3);
    cout << "Ackerman(2, 3) = " << result << endl;
    return 0;
}
//非遞迴
#include iostream
using namespace std;

int acker(int m, int n) {
    stack<int> s;
    s.push(m);

    while (!s.empty()) {
        m = s.top();
        s.pop();

        if (m == 0) {
            n = n + 1;
        } else if (n == 0) {
            n = 1;
            s.push(m - 1);
        } else {
            s.push(m - 1);
            s.push(m);
            n = n - 1;
        }
    }

    return n;
}

int main() {
    int m, n;
    cout << "m = "; cin >> m;
    cout << "n = "; cin >> n;
    int result = acker(m, n);
    cout << "Acker(" << m << ", " << n << ") = " << result << endl;
    return 0;
}

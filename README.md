# Data-Structure  41143224
# 問題一(阿克曼函數)
# 解題說明
此為阿克曼函數直接依照題目的要求寫出遞迴，假設m=3,n=4即為條件三開始執行一層一層最終m=0 n擔任了執行次數的角色。若不使用遞迴則能使用堆疊只要條件符合就把數值丟進去n並在條件一一成立時值行相對應的動作，並設計n堆疊頂端為
-1並且m堆疊沒有資料便輸出一直在累加的n。
# 程式實作
```
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
}//遞迴
```
<img width="489" height="167" alt="螢幕擷取畫面 2025-07-24 154032" src="https://github.com/user-attachments/assets/78157195-7195-4a20-801b-ecb484694f99" />

```
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
}//非遞迴
```
<img width="586" height="206" alt="image" src="https://github.com/user-attachments/assets/d836e15a-6856-47a4-a46f-826628a9c9ee" />

# 效能分析
空間複雜度:隨著 M,N 增加越來越大<br>
時間複雜度:隨著 M,N 增加越來越大<br>

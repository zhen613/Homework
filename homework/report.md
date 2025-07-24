# 41143224
## 作業一
## 解題說明
此為阿克曼函數直接依照題目的要求寫出遞迴，假設m=3,n=4即為條件三開始執行一層一層最終m=0 n擔任了執行次數的角色。若不使用遞迴則能使用堆疊只要條件符合就把數值丟進去n並在條件一一成立時值行相對應的動作，並設計n堆疊頂端為
-1並且m堆疊沒有資料便輸出一直在累加的n。
## 解題策略
*    使用遞迴函式將問題拆解為更小的子問題：
A(m, n) = n + 1, 當 m = 0 時作為第一種結束條件。
A(m, n) = A(m-1, 1), 當 m > 0 且 n = 0 時作為第二種結束條件。
A(m, n) = A(m-1, A(m, n-1)), 當 m > 0 且 n > 0 時，遞迴拆解為更小的子問題。
*    設定遞迴的結束條件：
當 m = 0 時，返回 n + 1。
當 n = 0 且 m > 0 時，返回 A(m-1, 1)。
這些條件確保遞迴在可控範圍內終止。
*    主程式呼叫遞迴函式，並輸出計算結果：
主函數接收用戶輸入的 m 和 n。
呼叫遞迴函數 A(m, n)，計算結果並輸出。
## 程式實作

此為遞迴:
```cpp
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
<img width="489" height="167" alt="螢幕擷取畫面 2025-07-24 154032" src="https://github.com/user-attachments/assets/78157195-7195-4a20-801b-ecb484694f99" /><br>

此為非遞迴:
```cpp
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

## 效能分析
空間複雜度:隨著 M,N 增加越來越大。<br>
時間複雜度:隨著 M,N 增加越來越大。<br>

## 測試與驗證
| 測試案例 | 輸入參數 $m$  | 輸入參數 $n$ | 預期輸出 | 實際輸出 |
|----------|--------------|----------|----------|----------|
| 測試一   |        $m = 0 $      |  $n = 0$      | 1        | 1        |
| 測試二   |        $m = 1 $     | $n = 1$      | 3        | 3        |
| 測試三   |      $m =2 $        | $n = 2$      | 7        | 7        |
| 測試四   |        $m =3 $      | $n = 3$      | 61       | 61       |
| 測試五   |       $m = 4  $     | $n = 2$     | Overflow | Overflow |
## 結論
*    使用已知值測試，例如 A(1, 2) = 4 和 A(2, 2) = 7，驗證遞迴邏輯正確性。
*    逐步輸入小值（如 m, n ≤ 3），檢查結果並監控是否出現堆棧溢出或超時。
*    對於較大值（如 m = 4, n = 2），測試大數運算庫的支援性。
## 申論及開發報告
*    輸入:M,N。
*    比較情況。
*    情況 1.如果 M=0,則直接回傳 N+1。<br>
情況 2.如果 M 大於 0 且 N=0,則進入遞迴,呼叫阿克曼(M-1,1),回傳結果。<br>
情況 3.如果兩者都大於 0,進入更深層的迴圈,呼叫阿克曼(M-1,A(M,N-1))。
*    極限在 A(4,0),A(4,1)將無法計算。
## 作業二
## 解題說明
只針對題目的3個元素去撰寫，程式偏向暴力破解，但一樣能達成目標，如果要能夠變成隨機應變的程式，則需要換個寫法，利入加入查詢演算法來安排每一個字元的輸出。
## 解題策略
*    遞迴思想：
這段程式碼採用了遞迴來生成幂集。基本思想是對於一個包含 n 個元素的集合，添加第 n 個元素，生成新的子集。
*    程式邏輯分解：
基礎情況（n = 1）：直接輸出空集 {} 和單個元素 {a}, {b}, {c}。<br>
遞迴情況（n = 2 或 n = 3）：先輸出 n-1 層的幂集結果，然後通過 powerset(a, b, c, n-1) 遞迴處理剩餘元素。每次遞迴會生成當前層級的所有子集，並逐步擴展。<br>
## 解題範例
S={'a', 'b', 'c'}，其所有子集合（幂集）為：{}, {a}, {b}, {c}, {a, b}, {a, c}, {b, c}, {a, b, c}。<br>
## 程式實作
```cpp
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
```
## 效能分析
*    時間複雜度:$O(2^n)$。每層子集數量從 1 增長到 $2^n$。每個子集的複製和添加操作是線性時間。
*    空間複雜度:$O(2^n \cdot n)$。最終返回的幂集包含 $2^n$ 個子集，每個子集平均包含約 $n/2$ 個元素（考慮所有組合的平均值）。因此，總儲存空間為 $O(2^n \cdot n)$。
## 測試與驗證
測試輸出<br>
<br>
<img width="358" height="247" alt="螢幕擷取畫面 2025-07-24 181838" src="https://github.com/user-attachments/assets/f85cba8a-4bdc-417a-b7b6-88e46218d8b3" /><br>
## 結論
該程式碼實現了通過遞迴生成集合幂集的功能，時間複雜度為 $O(2^n)$，空間複雜度為 $O(2^n \cdot n)$，其中 $n$ 為集合元素數量，適合用於理解幂集概念，但對於大規模資料可能因指數級複雜度而效率低下。
# 申論及開發報告
*    函數 powerset：
輸入：整數向量 s（集合）和索引 index（當前處理元素的位置）。<br>
邏輯：當 index < 0 時，返回包含空集的向量作為基礎情況；否則，遞迴處理 index - 1，獲取當前子集集合，然後為每個子集添加當前元素 s[index]，生成新子集。<br>
輸出：包含所有子集的二維向量。<br>
*    主函數 main：
初始化範例集合 s = {1, 2, 3}。<br>
呼叫 powerset 並從最後一個元素開始遞迴。<br>
使用巢狀迴圈格式化輸出，每個子集以 {1, 2} 形式顯示。<br>
語言特性：使用 std::vector 確保動態記憶體管理，using namespace std; 簡化命名空間使用。<br>
## 心得報告
*    遞迴算法的應用：理解了遞迴在生成幂集中的作用，通過逐步添加元素從空集構建所有子集，深化了分治思想在組合問題中的實用性。
*    複雜度認識：掌握了時間複雜度 $O(2^n)$ 和空間複雜度 $O(2^n \cdot n)$ 的影響，認識到指數級增長對大規模資料的限制。
*    資料結構運用：熟悉了 vector 在動態儲存子集中的靈活性，特別是二維向量的使用，並學會了格式化輸出子集的技巧。







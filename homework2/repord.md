# 41143224

## 解題說明
實現了多項式的加法、乘法和求值功能。使用 Polynomial 類別，並包含內部的 Term
類別，用以表示多項式的項。可以輸入兩個多項式，然後會計算和、積，和特定數值
下的值，更能計算加法、乘法和求值三個功能的執行時間。
## 解題策略

## 程式實作
```cpp
#include<iostream>
#include<chrono>
using namespace std;

class Polynomial;
class Term {
    friend Polynomial;
    friend ostream& operator<<(ostream& os, const Polynomial& p);
private:
    float coef; // 係數
    int term;   // 次方
};

class Polynomial {
    friend ostream& operator<<(ostream& os, const Polynomial& p);
private:
    Term* termArray;
    int capacity;  // 空間大小
    int terms;     // 非0的項式

public:
    Polynomial(); // 建構子
    float Eval(float f); //求多項式
    void NewTerm(const float newCoef, const int newExp); //結果的導出 新coef 和 exp
    Polynomial Multiply(const Polynomial& poly); // 多項式相乘
    Polynomial Add(const Polynomial& poly);//多項式相加
};

Polynomial::Polynomial() : capacity(2), terms(0) {
    termArray = new Term[capacity];
}

void Polynomial::NewTerm(const float newCoef, const int newExp) {
    
    if (terms == capacity) {
        capacity *= 2;
        Term* temp = new Term[capacity]; // 更換Array空間大小
        copy(termArray, termArray + terms, temp);
        delete[] termArray; // 釋放記憶體空間
        termArray = temp;
    }
    termArray[terms].coef = newCoef;
    termArray[terms++].term = newExp;
}

float Polynomial::Eval(float f) {
    float result = 0;
    for (int i = 0; i < terms; i++) {
        result += termArray[i].coef * pow(f, termArray[i].term);
    }
    return result;
}

ostream& operator<<(ostream& os, const Polynomial& p) {//ostream 及operator 定義輸出給不同的次方係數
    for (int i = 0; i < p.terms; i++) {
        if (p.termArray[i].term == 0) {
            os << p.termArray[i].coef;
            continue;
        }
        if (i == p.terms - 1) {
            os << p.termArray[i].coef << "X^" << p.termArray[i].term;
        }
        else {
            os << p.termArray[i].coef << "X^" << p.termArray[i].term << " + ";
        }
    }
    return os;
}
Polynomial Polynomial::Multiply(const Polynomial& poly) {
    Polynomial result;
    for (int i = 0; i < terms; i++) {
        for (int j = 0; j < poly.terms; j++) {
            //將相同係數相乘
            float newCoef = termArray[i].coef * poly.termArray[j].coef;
            int newExp = termArray[i].term + poly.termArray[j].term;

            //將結果導出
            result.NewTerm(newCoef, newExp);
        }
    }

    return result;
}
Polynomial Polynomial::Add(const Polynomial& poly) {
    Polynomial result;

    for (int i = 0; i < terms; i++) {
        for (int j = 0; j < poly.terms; j++) {
            //將相同的係數相加
            float newCoef = termArray[i].coef + poly.termArray[j].coef;
            int newExp = termArray[i].term + poly.termArray[j].term;

           //將結果導出
            result.NewTerm(newCoef, newExp);
        }
    }

    return result;
}

int main() {
   

    auto start = std::chrono::high_resolution_clock::now();
    Polynomial poly1, poly2;
    int num;
    int n1, n2;
    cout << "poly1幾項?"; cin >> num;
    for (int i = 0; i < num; i++) {
        cout << "係數：";
        cin >> n2;
        for (int j = 0; j < 1; j++) {
            cout << "次方：";
            cin >> n1;
            poly1.NewTerm(n2, n1);
        }
    }

    cout << "poly2幾項?"; cin >> num;
    for (int i = 0; i < num; i++) {
        cout << "係數：";
        cin >> n2;
        for (int j = 0; j < 1; j++) {
            cout << "次方：";
            cin >> n1;
            poly2.NewTerm(n2, n1);
        }
    }
    cout << "多項式1: " << poly1 << endl;
    cout << "多項式2: " << poly2 << endl;

    Polynomial product = poly1.Multiply(poly2);
    cout << "相乘後: " << product << endl;
    Polynomial add = poly1.Add(poly2);
    cout << "相加後：" << add << endl;

    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;

    std::cout << "Elapsed time: " << duration.count() << " seconds" << std::endl;
    return 0;
}
```

## 效能分析
*    時間複雜度：O(1)，僅執行常數時間操作（分配小陣列和設置變數）。
*    空間複雜度為：O(n)，其中 n 是項數。
## 測試與驗證
| 測試案例 | 輸入參數 $１$ |輸入參數 $２$ |預期輸出（＋）|預期輸出（＊） | 實際輸出 |
|----------|--------------|----------|----------|----------|----------|
| 測試一   | 3x² + 2x + 1     | 2x + 3       |3x² + 4x + 4| 6x³ + 13x² + 8x + 3      | １１        |

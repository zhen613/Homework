# 41143224
## 解題說明
實現多項式加法、減法、乘法、除法求值功能。使用
polynomial 類別,此外在加入 linked list 功能實作簡單的連結
串列。可以輸入兩個多項式,計算不同算法下的值,也能計算
出所有功能下的執行時間。
## 解題策略
*    鏈結串列實現：
linked_list 類別實現了一個單向鏈結串列，透過 node<E> 儲存泛型資料 E。<br>
iterator 類別提供遍歷功能，支援 begin(  ) 和 end(  ) 方法。<br>
available_list 類別管理一個可重複使用的節點池，以優化記憶體分配和釋放。<br>
*    多項式類別 (Polynomial)：
多項式以 Term 物件陣列表示，每個 Term 包含係數 (coef) 和指數 (exp)。<br>
支援的操作包括加法 ( + )、減法 ( - )、乘法 ( * )、除法 ( / ) 和在給定 x 值下求值。<br>
輸入 (operator>>) 解析多項式表達式，輸出 (operator<<) 格式化顯示多項式。<br>
## 程式實作
```cpp
#include <iostream>
#include <algorithm>
#include <math.h>
#include <sys/time.h>

template<typename E>
class linked_list;

template<typename E>
class available_list;

template<typename E>
class node;


template<typename E>
class iterator{

    friend linked_list<E>;

public:

    iterator& operator++(){
        pointer = pointer->next;
        return *this;
    };

    iterator& operator++(int dummy){
        pointer = pointer->next;
        return *this;
    };

    node<E>* operator*(){
        return pointer;
    }

    friend bool operator!=(const iterator<E>& lhs, const iterator<E>& rhs){
        return lhs.pointer != rhs.pointer;
    }

    friend bool operator==(const iterator<E>& lhs, const iterator<E>& rhs) {
        return lhs.pointer == rhs.pointer;
    }

private:
    explicit iterator(node<E>* node_ptr)
            : pointer(node_ptr)
    {}

    node<E>* pointer;
};

template<typename E>
class node{

    friend linked_list<E>;
    friend available_list<E>;
    friend iterator<E>;

public:
    explicit node(E data)
            : data(data)
            , next(nullptr)
    {}

    E get_data(){
        return data;
    };

private:
    E data;
    node<E>* next;

    node(){}
};

template<typename E>
class available_list{
public:

    available_list(){}

    node<E>* allocate(){
        if (head->next == nullptr){
            return new node<E>();
        }

        node<E>* current = head;
        while (current->next != nullptr){
            node<E>* next = current->next;
            if (next->next == nullptr){
                node<E>* allocated = next;
                current->next == nullptr;
                return allocated;
            }else {
                current = next;
            }
        }
    }

    void deallocate(node<E>* node_to_deallocated){
        memset(node_to_deallocated, 0, sizeof(node<E>));
        if (head->next == nullptr){
            return head->next = node_to_deallocated;
        }

        node<E>* current = head;
        while (current->next != nullptr){
            node<E>* next = current->next;
            if (next->next == nullptr){
                next->next = node_to_deallocated;
                return;
            }else {
                current = next;
            }
        }
    }

private:
    node<E>* head;
};

template<typename E>
class linked_list{

public:
    linked_list(available_list<E>* available_list)
    : head(nullptr)
    , available_list(available_list)
    { }

    void append(E data){
        node<E>* new_node = available_list->allocate();

        if (head == nullptr){
            head = new_node;
            return;
        }

        node<E>* tail = nullptr;
        for(auto it = begin(); it != end(); it++){
            tail = *it;
        }


        tail->next = new_node;
    }

    void reverse(){
        node<E>* current = head;
        node<E>* prev = nullptr;

        while (current != nullptr){
            auto next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }

        head = prev;
    }

    E remove(int idx){
        if (head == nullptr){
            throw std::exception();
        }

        if (idx == 0){
            E data = head->get_data();
            if (head->next != nullptr){
                auto tmp = head->next;
                available_list->deallocate(head);
                head = tmp;
                return data;
            }else{
                available_list->deallocate(head);
                head = nullptr;
            }
            return data;
        }


        int current_idx = 0;
        for(iterator<E> it = begin(); it != end(); it++, current_idx++) {
            if (current_idx == idx - 1){
                node<E>* prev = *it;
                node<E>* target = prev->next;

                if (target == nullptr){
                    // out of boundary
                    throw std::exception();
                }

                E data = target->get_data();
                prev->next = target->next;
                available_list->deallocate(target);
                return data;
            }
        }

        // out of boundary
        throw std::exception();
    }

    int size(){
        int current_idx = 0;
        for(iterator<E> it = begin(); it != end(); it++, current_idx++) {}
        return current_idx;
    }

    int at(int idx){
        if (idx < 0){
            throw std::exception();
        }

        int current_idx = 0;
        for(iterator<E> it = begin(); it != end(); it++, current_idx++) {
            if (current_idx == idx){
                node<E>* nd = *it;
                return nd->get_data();
            }
        }

        throw std::exception();
    }

    iterator<E> begin(){
        return iterator<E>(head);

    }

    iterator<E> end(){
        return iterator<E>(nullptr);
    }

private:
    node<E>* head;
    available_list<E>* available_list;
};

class Polynomial
{
    friend std::ostream& operator<<(std::ostream& os, const Polynomial &p);
    friend std::istream& operator>>(std::istream& is, Polynomial &p);
    class Term {
        friend Polynomial;
        friend std::ostream& operator<<(std::ostream& os, const Polynomial &p);
    private:
        float coef;
        int exp;
    };
private:
    Term *termArray;
    int capacity;
    int terms;
public:
    Polynomial();
    Polynomial operator+(const Polynomial& poly);
    Polynomial operator-(const Polynomial& poly);
    Polynomial operator*(const Polynomial& poly);
    Polynomial operator/(const Polynomial& poly);
    Polynomial Add(Polynomial poly);
    Polynomial Mult(Polynomial poly);
    Polynomial Sub(Polynomial poly);
    Polynomial Div(Polynomial poly);
    float Evaluate(float f);
    void Setup(int a, int b,float c[],int d[]);
};

Polynomial::Polynomial()
{
    capacity = 0;
    terms = 0;
}
Polynomial Polynomial::Add(Polynomial poly)
{
    Polynomial result;
    int maxDegree = std::max(this->capacity - 1, poly.capacity - 1);
    result.Setup(maxDegree + 1, 0, nullptr, nullptr);

    for (int i = 0; i <= maxDegree; i++)
    {
        result.termArray[i].coef = (i < this->capacity) ? this->termArray[i].coef : 0;
        result.termArray[i].coef += (i < poly.capacity) ? poly.termArray[i].coef : 0;
        result.termArray[i].exp = i;
    }

    return result;
}
Polynomial Polynomial::Mult(Polynomial poly)
{
    Polynomial result;
    int maxCapacity = this->capacity + poly.capacity - 1;
    result.Setup(maxCapacity, 0, nullptr, nullptr);

    for (int i = 0; i < this->capacity; i++)
    {
        for (int j = 0; j < poly.capacity; j++)
        {
            int newExp = this->termArray[i].exp + poly.termArray[j].exp;
            float newCoef = this->termArray[i].coef * poly.termArray[j].coef;
            result.termArray[newExp].coef += newCoef;
            result.termArray[newExp].exp = newExp;
        }
    }

    return result;
}

Polynomial Polynomial::Sub(Polynomial poly)
{
    Polynomial result;
    int maxDegree = std::max(this->capacity - 1, poly.capacity - 1);
    result.Setup(maxDegree + 1, 0, nullptr, nullptr);

    for (int i = 0; i <= maxDegree; i++)
    {
        result.termArray[i].coef = (i < this->capacity) ? this->termArray[i].coef : 0;
        result.termArray[i].coef -= (i < poly.capacity) ? poly.termArray[i].coef : 0;
        result.termArray[i].exp = i;
    }

    return result;
}

Polynomial Polynomial::Div(Polynomial poly)
{
    Polynomial result;
    int maxCapacity = this->capacity - poly.capacity + 1;
    result.Setup(maxCapacity, 0, nullptr, nullptr);

    for (int i = result.capacity ; i >= 0; i--) {
        result.termArray[i].coef =
                this->termArray[i + poly.capacity - 1].coef / poly.termArray[poly.capacity - 1].coef;
        float k = result.termArray[i].coef;
        for (int j = poly.capacity; j >= 0; j--) {
            this->termArray[i+j].coef -= k * poly.termArray[j].coef;
        }
    }

    return result;
}

Polynomial Polynomial::operator+(const Polynomial& poly){
    return this->Add(poly);
}
Polynomial Polynomial::operator-(const Polynomial& poly){
    return this->Sub(poly);
}
Polynomial Polynomial::operator*(const Polynomial& poly){
    return this->Mult(poly);
}
Polynomial Polynomial::operator/(const Polynomial& poly){
    return this->Div(poly);
}

float Polynomial::Evaluate(float x)
{
    float result = 0;

    for (int i = 0; i < this->capacity; i++)
    {
        result += this->termArray[i].coef * pow(x, this->termArray[i].exp);
    }
    return result;
}

void Polynomial::Setup(int a,int b,float c[],int d[]) {
    this->capacity = a + 1;
    this->terms = b;
    this->termArray = new Term[capacity];
    for (int i = 0; i < capacity; i++) {
        termArray[i].coef = 0;
        termArray[i].exp = i;
    }
    for (int i = 0; i < terms; i++) {
        termArray[d[i]].coef = c[i];
        termArray[d[i]].exp = d[i];
    }
    /*
    for (int i = 0; i < capacity; i++) {
        std::cout << termArray[i].coef <<" "<< termArray[i].exp << ' '<< i << std::endl;
    }
    */
}
std::istream& operator>>(std::istream& is, Polynomial &p) {
    char ch; bool negative = false;
    float coef = 0, f_coef[100] = { 0 };
    int max = 0, exp = 0, i_exp[100] = { 0 }, count = 0;

    ch = getchar();
    while (ch != '\n') {
        coef = 0; negative = false;
        while ((ch >= '0' && ch <= '9') || ch == '.' || ch == '+' || ch == '-' || ch == ' ') {
            if (ch == ' ' or ch == '+') {
                ch = getchar();
                continue;
            }
            if (ch == '-') {
                negative = true;
                ch = getchar();
            }
            while (ch != '.' && (ch >= '0' && ch <= '9')) {
                coef = coef * 10 + ch - '0';
                ch = getchar();
            }
            if(ch == '.')ch = getchar();
            int c = 1;
            while ((ch >= '0' && ch <= '9')) {
                coef = coef + pow(0.1, c) * (ch - '0');
                ch = getchar();
                c++;
            }
            if (negative) coef = coef*(-1);
            f_coef[count] = coef;
        }

        if (coef == 0) f_coef[count] = 1;
        if (ch == 'x' || ch == 'X') {
            ch = getchar();
            while (ch == ' ') {
                ch = getchar();
            }
            if (ch == '^') {
                exp = 0;
                while ((ch >= '0' && ch <= '9') || ch == '^' || ch == ' ') {
                    if (ch == '^' || ch == ' ') {
                        ch = getchar();
                        continue;
                    }
                    exp = exp * 10 + ch - '0';
                    ch = getchar();
                }
                i_exp[count] = exp;
                if (max < exp) max = exp;
            } else {
                i_exp[count] = 1;
                if (max < 1) max = 1;
            }
        } else {
            i_exp[count] = 0;
        }
        count++;
    }
    for (int i = 0; i < count; i++) {
        for (int j = i + 1; j < count; j++) {
            if (i_exp[i] < i_exp[j]) {
                std::swap(i_exp[i], i_exp[j]);
                std::swap(f_coef[i], f_coef[j]);
            }
        }
    }
    /*
    for (int i = 0; i < count; i++) {
        std::cout << f_coef[i] << " " << i_exp[i]<<std::endl;
    }
    */
    p.Setup(max, count, f_coef, i_exp);
    return is;
}
std::ostream& operator<<(std::ostream& os, const Polynomial &p) {
    bool f = true;
    for (int i = p.capacity - 1; i > 1; i--) {
        if (p.termArray[i].coef != 0) {
            if (f) std::cout << p.termArray[i].coef << " x ^ " << p.termArray[i].exp;
            else {
                if(p.termArray[i].coef > 0) std::cout << " + " << p.termArray[i].coef << " x ^ " << p.termArray[i].exp;
                else std::cout << " - " << p.termArray[i].coef * (-1) << " x ^ " << p.termArray[i].exp;
            }
            f = false;
        }
    }
    if (p.capacity - 1 > 0) {
        if (p.termArray[1].coef > 0) {
            if (f) std::cout<< p.termArray[1].coef << " x ";
            else std::cout << " + " << p.termArray[1].coef << " x ";
            f = false;
        }
        else if (p.termArray[1].coef < 0) {
            std::cout << " - " << p.termArray[1].coef * (-1) << " x ";
            f = false;
        }
    }
    if (p.capacity - 1 >= 0) {
        if (p.termArray[0].coef > 0) {
            if (f) std::cout << p.termArray[0].coef;
            else std::cout << " + " << p.termArray[0].coef;
            f = false;
        }
        else if (p.termArray[0].coef < 0) {
            std::cout << " - " << p.termArray[0].coef * (-1);
            f = false;
        }
    }
    return os;
}
int main() {
    struct timespec start, end;
    Polynomial a, b;
    float x;
    std::cout << "請輸入A(x)：";
    std::cin >> a;
    std::cout << "請輸入B(x)：";
    std::cin >> b;
    std::cout << "請輸入x的值：";
    std::cin >> x;
    std::cout << a << std::endl;
    std::cout << b << std::endl;
    clock_gettime(CLOCK_MONOTONIC, &start);
    auto add = a + b;
    auto sub = a - b;
    auto mul = a * b;
    auto div = a / b;
    std::cout << "A(x) + B(x) = " << add << std::endl;
    std::cout << "A(x) - B(x) = " << sub << std::endl;
    std::cout << "A(x) * B(x) = " << mul << std::endl;
    std::cout << "A(x) / B(x) = " << div << std::endl;

    std::cout << "A(x) + B(x) = " << add.Evaluate(x) << std::endl;
    std::cout << "A(x) - B(x) = " << sub.Evaluate(x) << std::endl;
    std::cout << "A(x) * B(x) = " << mul.Evaluate(x) << std::endl;
    std::cout << "A(x) / B(x) = " << div.Evaluate(x) << std::endl;
    clock_gettime(CLOCK_MONOTONIC, &end);
    std::cout << "程式完成時間: " <<  (end.tv_sec - start.tv_sec) * 1000 + (end.tv_nsec - start.tv_nsec) / 1000000 << "ms" << std::endl;
    system("pause");
    return 0;
}

```
## 效能分析
*    時間複雜度
鏈結串列操作：O(n)（append, reverse, remove, size, at），O(1)（begin, end）。<br>
記憶體池操作：O(k)（allocate, deallocate）。<br>
加/減：O(max(m, n))。<br>
乘/除：O(m * n)。<br>
求值：O(n)。<br>
*    空間複雜度
鏈結串列：O(n)。<br>
記憶體池：O(k)。<br>
多項式：O(m + n)（主導於多項式陣列和結果儲存）。<br>
## 測試與驗證
| 測試案例         | 輸入                  | 預期輸出      | 實際輸出      | 驗證結果 | 備註                |
|-------------------|-----------------------|---------------|---------------|----------|---------------------|
| 1. 輸入多項式    | "A(x) = 2x<br>B(x) = x" | -             | -             | 通過      | 輸入格式正確        |
| 2. 加法 A(x) + B(x) | "A(x) = 2x<br>B(x) = x" | 3x           | 3x            | 通過      | 2x + x = 3x        |
| 3. 減法 A(x) - B(x) | "A(x) = 2x<br>B(x) = x" | 1x 或 x      | 1x            | 通過      | 2x - x = x         |
| 4. 乘法 A(x) * B(x) | "A(x) = 2x<br>B(x) = x" | 2x^2         | 2x ^ 2        | 通過      | 2x * x = 2x^2      |
| 5. 除法 A(x) / B(x) | "A(x) = 2x<br>B(x) = x" | 2            | 2             | 通過      | 2x / x = 2         |
| 6. 求值 A(x) + B(x) | x = 1                | 3            | 3             | 通過      | 3x 在 x=1 為 3     |
| 7. 求值 A(x) - B(x) | x = 1                | 1            | 1             | 通過      | x 在 x=1 為 1      |
| 8. 求值 A(x) * B(x) | x = 1                | 2            | 2             | 通過      | 2x^2 在 x=1 為 2   |
| 9. 求值 A(x) / B(x) | x = 1                | 2            | 2             | 通過      | 2 在 x=1 為 2      |
## 申論及開發報告
*    鏈結串列管理 (linked_list)：使用自訂節點 (node) 和迭代器 (iterator)，支援動態數據結構操作（如添加、移除、反轉等）。
記憶體池管理 (available_list)：提供節點的分配與釋放，優化記憶體使用。
多項式運算 (Polynomial)：支援多項式的加、減、乘、除操作，以及在指定 x 值下的求值。
輸入輸出處理：透過 operator>> 解析多項式表達式，operator<< 格式化輸出。
*    結構設計
鏈結串列：
採用單向鏈結串列結構，支援泛型 (template<typename E>)。
提供 append、remove、reverse 等操作，時間複雜度為 O(n)。
迭代器實現支援標準遍歷介面 (begin()、end())，時間複雜度為 O(1)。
記憶體池：
available_list 管理可重用節點，旨在減少動態分配開銷。
當前實現存在邏輯錯誤（例如 current->next == nullptr 應為 current->next = nullptr），需修正。
多項式類：
使用 Term 陣列儲存係數和指數，支援動態分配。
運算函數 (Add、Sub、Mult、Div) 實現基本多項式運算，時間複雜度分別為 O(max(m, n))、O(max(m, n))、O(m * n)、O(m * n)。

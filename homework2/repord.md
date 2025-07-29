# 41143224

作業一
## 解題說明
實現了多項式的加法、乘法和求值功能。使用 Polynomial 類別，並包含內部的 Term
類別，用以表示多項式的項。可以輸入兩個多項式，然後會計算和、積，和特定數值
下的值，更能計算加法、乘法和求值三個功能的執行時間。
## 解題策略

##　程式實作
```cpp
Polynomial Polynomial::add(const Polynomial& poly) { //加法
Polynomial result;
int max = this->capacity > poly.capacity ? capacity : poly.capacity;
int min = this->capacity < poly.capacity ? capacity : poly.capacity;
int big = this->capacity > poly.capacity ? 0 : 1;
for (int i = 0; i < min; i++) {
result.termArray[i].coefficient = poly.termArray[i].coefficient + this->termArray[i].coefficient;
result.termArray[i].exponent = i;
}
for (int i = min; i < max; i++) {
if(big == 0) result.termArray[i].coefficient = this->termArray[i].coefficient;
else result.termArray[i].coefficient = poly.termArray[i].coefficient;
result.termArray[i].exponent = i;
}
return result;
}
~多項式乘法程式碼~
Polynomial Polynomial::multiply(const Polynomial& poly) { //乘法
Polynomial result;
int newExponent;
float newCoefficient;
int maxCapacity = (this->capacity * poly.capacity);
for (int i = 0; i < this->capacity; i++) {
for (int j = 0; j < poly.capacity; j++) {
result.termArray[this->termArray[i].exponent + poly.termArray[j].exponent].coefficient +=
this->termArray[i].coefficient * poly.termArray[j].coefficient;
}
}
return result; }
~x 求值~
float Polynomial::evaluate(float x) { //x 求值
float result = 0;
int j = this->capacity - 1;
while(j >= 0) {
result = result + this->termArray[j].coefficient * pow(x, this->termArray[j].exponent);
j--;
}
return result;
}
```

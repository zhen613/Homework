# 41143224
## 解題說明
實現多項式加法、減法、乘法、除法求值功能。使用
polynomial 類別,此外在加入 linked list 功能實作簡單的連結
串列。可以輸入兩個多項式,計算不同算法下的值,也能計算
出所有功能下的執行時間。
## 解題策略

## 程式實作
```cpp

class Term {
friend Polynomial;
friend std::ostream& operator<<(std::ostream& os, const
Polynomial &p);
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
result.termArray[i].coef = (i < this->capacity) ? this-
>termArray[i].coef : 0;
result.termArray[i].coef += (i < poly.capacity) ?
poly.termArray[i].coef : 0;
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
int newExp = this->termArray[i].exp +
poly.termArray[j].exp;
float newCoef = this->termArray[i].coef *
poly.termArray[j].coef;
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
result.termArray[i].coef = (i < this->capacity) ? this-
>termArray[i].coef : 0;
result.termArray[i].coef -= (i < poly.capacity) ?
poly.termArray[i].coef : 0;
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
this->termArray[i + poly.capacity - 1].coef /
poly.termArray[poly.capacity - 1].coef;
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
result += this->termArray[i].coef * pow(x, this-
>termArray[i].exp);
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
std::cout << termArray[i].coef <<" "<< termArray[i].exp << '
'<< i << std::endl;
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
while ((ch >= '0' && ch <= '9') || ch == '.' || ch == '+' || ch
== '-' || ch == ' ') {
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
std::ostream& operator<<(std::ostream& os, const Polynomial
&p) {
bool f = true;
for (int i = p.capacity - 1; i > 1; i--) {
if (p.termArray[i].coef != 0) {
if (f) std::cout << p.termArray[i].coef << " x ^ " <<
p.termArray[i].exp;
else {
if(p.termArray[i].coef > 0) std::cout << " + " <<
p.termArray[i].coef << " x ^ " << p.termArray[i].exp;
else std::cout << " - " << p.termArray[i].coef * (-1) << "
x ^ " << p.termArray[i].exp;
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
std::cout << "請輸入 A(x)：";
std::cin >> a;
std::cout << "請輸入 B(x)：";
std::cin >> b;
std::cout << "請輸入 x 的值：";
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
std::cout << "程式完成時間: " << (end.tv_sec - start.tv_sec) *
1000 + (end.tv_nsec - start.tv_nsec) / 1000000 << "ms" <<
std::endl;
system("pause");
return 0;
}
```


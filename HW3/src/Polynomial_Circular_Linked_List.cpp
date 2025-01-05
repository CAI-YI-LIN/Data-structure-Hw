#include <iostream>
#include <cmath> 
using namespace std;

// 節點結構，用於存儲單項式的係數、指數及鏈接下一個節點的指針
struct Node {
    int coef; // 系數
    int exp;  // 指數
    Node* link; // 指向下一個節點的指針

    // 節點的建構函數，默認係數為0，指數為0，指針為nullptr
    Node(int c = 0, int e = 0, Node* l = nullptr) : coef(c), exp(e), link(l) {}
};

// 多項式類別
class Polynomial {
private:
    Node* head; // 指向多項式頭節點的指針

public:
    Polynomial(); // 默認構造函數，初始化空多項式
    Polynomial(const Polynomial& a); // 拷貝構造函數，進行深拷貝
    ~Polynomial(); // 析構函數，釋放所有動態分配的記憶體
    const Polynomial& operator=(const Polynomial& a); // 賦值運算符，支持多項式的賦值操作

    Polynomial operator+(const Polynomial& b) const; // 多項式加法
    Polynomial operator-(const Polynomial& b) const; // 多項式減法
    Polynomial operator*(const Polynomial& b) const; // 多項式乘法

    float Evaluate(float x) const; // 計算多項式在x處的值

    void InsertTerm(int coef, int exp); // 插入一項到多項式中

    friend std::istream& operator>>(std::istream& is, Polynomial& x); // 支持多項式的輸入
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& x); // 支持多項式的輸出
};

// 默認構造函數：初始化空的多項式，頭節點指向自己形成循環鏈表
Polynomial::Polynomial() {
    head = new Node();
    head->link = head;
}

// 拷貝構造函數：深拷貝另一個多項式
Polynomial::Polynomial(const Polynomial& a) {
    head = new Node();
    head->link = head;
    *this = a; // 使用賦值運算符進行深拷貝
}

// 析構函數：釋放所有節點的記憶體
Polynomial::~Polynomial() {
    Node* current = head->link;
    while (current != head) {
        Node* temp = current;
        current = current->link;
        delete temp; // 釋放節點記憶體
    }
    delete head; // 釋放頭節點
}

// 賦值運算符：支持多項式的賦值操作
const Polynomial& Polynomial::operator=(const Polynomial& a) {
    if (this != &a) { // 避免自賦值
        this->~Polynomial(); // 釋放當前多項式的記憶體
        head = new Node();
        head->link = head;
        Node* current = a.head->link;
        while (current != a.head) {
            InsertTerm(current->coef, current->exp); // 插入節點
            current = current->link;
        }
    }
    return *this;
}

// 插入項到多項式，保持指數遞減順序
void Polynomial::InsertTerm(int coef, int exp) {
    if (coef == 0) return; // 係數為0則不插入
    Node* current = head;
    while (current->link != head && current->link->exp > exp) {
        current = current->link; // 找到適當的位置
    }
    if (current->link != head && current->link->exp == exp) {
        current->link->coef += coef; // 合併同類項
        if (current->link->coef == 0) { // 如果係數變為0則刪除該項
            Node* temp = current->link;
            current->link = temp->link;
            delete temp;
        }
    }
    else {
        Node* newNode = new Node(coef, exp, current->link); // 創建新節點
        current->link = newNode;
    }
}

// 多項式加法
Polynomial Polynomial::operator+(const Polynomial& b) const {
    Polynomial c;
    Node* aCurrent = head->link;
    Node* bCurrent = b.head->link;

    while (aCurrent != head && bCurrent != b.head) {
        if (aCurrent->exp == bCurrent->exp) {
            c.InsertTerm(aCurrent->coef + bCurrent->coef, aCurrent->exp); // 同指數項相加
            aCurrent = aCurrent->link;
            bCurrent = bCurrent->link;
        }
        else if (aCurrent->exp > bCurrent->exp) {
            c.InsertTerm(aCurrent->coef, aCurrent->exp); // 插入較大的指數項
            aCurrent = aCurrent->link;
        }
        else {
            c.InsertTerm(bCurrent->coef, bCurrent->exp);
            bCurrent = bCurrent->link;
        }
    }

    while (aCurrent != head) { // 處理剩餘項
        c.InsertTerm(aCurrent->coef, aCurrent->exp);
        aCurrent = aCurrent->link;
    }

    while (bCurrent != b.head) {
        c.InsertTerm(bCurrent->coef, bCurrent->exp);
        bCurrent = bCurrent->link;
    }

    return c;
}

// 多項式減法
Polynomial Polynomial::operator-(const Polynomial& b) const {
    Polynomial c;
    Node* aCurrent = head->link;
    Node* bCurrent = b.head->link;

    while (aCurrent != head && bCurrent != b.head) {
        if (aCurrent->exp == bCurrent->exp) {
            c.InsertTerm(aCurrent->coef - bCurrent->coef, aCurrent->exp); // 同指數項相減
            aCurrent = aCurrent->link;
            bCurrent = bCurrent->link;
        }
        else if (aCurrent->exp > bCurrent->exp) {
            c.InsertTerm(aCurrent->coef, aCurrent->exp);
            aCurrent = aCurrent->link;
        }
        else {
            c.InsertTerm(-bCurrent->coef, bCurrent->exp);
            bCurrent = bCurrent->link;
        }
    }

    while (aCurrent != head) {
        c.InsertTerm(aCurrent->coef, aCurrent->exp);
        aCurrent = aCurrent->link;
    }

    while (bCurrent != b.head) {
        c.InsertTerm(-bCurrent->coef, bCurrent->exp);
        bCurrent = bCurrent->link;
    }

    return c;
}

// 多項式乘法
Polynomial Polynomial::operator*(const Polynomial& b) const {
    Polynomial c;
    Node* aCurrent = head->link;

    while (aCurrent != head) {
        Node* bCurrent = b.head->link;
        while (bCurrent != b.head) {
            c.InsertTerm(aCurrent->coef * bCurrent->coef, aCurrent->exp + bCurrent->exp); // 係數相乘，指數相加
            bCurrent = bCurrent->link;
        }
        aCurrent = aCurrent->link;
    }

    return c;
}

// 計算多項式的值
float Polynomial::Evaluate(float x) const {
    float result = 0.0;
    Node* current = head->link;
    while (current != head) {
        result += current->coef * std::pow(x, current->exp); // 累加每項的值
        current = current->link;
    }
    return result;
}

// 多項式輸入
std::istream& operator>>(std::istream& is, Polynomial& x) {
    int n; // 多項式項數
    is >> n;
    for (int i = 0; i < n; ++i) {
        int coef, exp;
        is >> coef >> exp;
        x.InsertTerm(coef, exp); // 插入每一項
    }
    return is;
}

// 多項式輸出
std::ostream& operator<<(std::ostream& os, const Polynomial& x) {
    Node* current = x.head->link;
    bool firstTerm = true;
    while (current != x.head) {
        if (!firstTerm && current->coef > 0) {
            os << " + "; // 正數項前加"+"
        }
        else if (current->coef < 0) {
            os << " - "; // 負數項前加"-"
        }
        os << std::abs(current->coef) << "x^" << current->exp; // 輸出係數與指數
        current = current->link;
        firstTerm = false;
    }
    return os;
}
void TestPolynomial(const Polynomial& p1, const Polynomial& p2) {
    // 計算多項式 p1 和 p2 的和、差以及積
    Polynomial sum = p1 + p2;
    Polynomial difference = p1 - p2;
    Polynomial product = p1 * p2;

    // 顯示多項式 p1 和 p2 的具體形式
    std::cout << "P1: " << p1 << std::endl;
    std::cout << "P2: " << p2 << std::endl;

    // 顯示多項式的加法、減法及乘法結果
    std::cout << "P1 + P2: " << sum << std::endl;
    std::cout << "P1 - P2: " << difference << std::endl;
    std::cout << "P1 * P2: " << product << std::endl;
    cout << endl; // 分隔輸出部分

    // 定義一組 x 值，用於評估多項式在不同 x 下的值
    float x_values[] = { -1, 0, 1, 2 };

    // 迴圈遍歷每個 x 值，計算 sum、difference 和 product 在該 x 值處的結果
    for (float x : x_values) {
        std::cout << "P1 + P2(" << x << ") = " << sum.Evaluate(x) << std::endl;
        std::cout << "P1 - P2(" << x << ") = " << difference.Evaluate(x) << std::endl;
        std::cout << "P1 * P2(" << x << ") = " << product.Evaluate(x) << std::endl;
        cout << endl; // 每次計算完後增加一行空白行，便於輸出區分
    }

    // 輸出分隔線，便於測試多項式組之間的區分
    std::cout << "---------------------------------------------------------------" << std::endl;
}


int main() {
    // 測資 1：基本加法與乘法測試
    Polynomial p1_1, p1_2;
    p1_1.InsertTerm(3, 2);
    p1_1.InsertTerm(2, 1);
    p1_1.InsertTerm(1, 0);
    p1_2.InsertTerm(1, 3);
    p1_2.InsertTerm(1, 1);
    p1_2.InsertTerm(5, 0);
    TestPolynomial(p1_1, p1_2);

    // 測資 2：包含零係數的多項式
    Polynomial p2_1, p2_2;
    p2_1.InsertTerm(4, 4);
    p2_1.InsertTerm(0, 3);
    p2_1.InsertTerm(2, 2);
    p2_2.InsertTerm(3, 3);
    p2_2.InsertTerm(0, 2);
    p2_2.InsertTerm(1, 1);
    TestPolynomial(p2_1, p2_2);

    // 測資 3：包含負係數的多項式
    Polynomial p3_1, p3_2;
    p3_1.InsertTerm(-2, 3);
    p3_1.InsertTerm(-4, 2);
    p3_1.InsertTerm(1, 1);
    p3_1.InsertTerm(-5, 0);
    p3_2.InsertTerm(3, 3);
    p3_2.InsertTerm(-1, 1);
    p3_2.InsertTerm(6, 0);
    TestPolynomial(p3_1, p3_2);

    // 測資 4：僅有常數項的多項式
    Polynomial p4_1, p4_2;
    p4_1.InsertTerm(7, 0);
    p4_2.InsertTerm(-3, 0);
    TestPolynomial(p4_1, p4_2);

    // 測資 5：包含相同指數的多項式項
    Polynomial p5_1, p5_2;
    p5_1.InsertTerm(5, 3);
    p5_1.InsertTerm(2, 2);
    p5_1.InsertTerm(3, 3);
    p5_2.InsertTerm(1, 3);
    p5_2.InsertTerm(1, 1);
    p5_2.InsertTerm(4, 3);
    TestPolynomial(p5_1, p5_2);

    return 0;
}
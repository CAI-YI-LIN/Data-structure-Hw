#include<iostream>
#include<cmath>
using namespace std;

// 前置宣告 Polynomial 類別，供 Term 類別使用
class Polynomial;

// 類別 Term 表示多項式中的一個項次
class Term {
private:
	float coef; // 系數
	int exp;    // 指數
public:
	// 獲取系數
	float getCoef() const { return coef; }
	// 獲取指數
	int getExp() const { return exp; }
	// 宣告 Polynomial 為友元類別，允許存取 private 成員
	friend class Polynomial;
};

// 類別 Polynomial 表示多項式
class Polynomial {
public:
	Polynomial();                             // 建構子
	Polynomial(const Polynomial& other);     // 拷貝建構子
	~Polynomial();                           // 解構子
	Polynomial Add(Polynomial b);            // 多項式相加
	Polynomial Mult(Polynomial b);           // 多項式相乘
	Polynomial BubbleSort();                 // 泡沫排序（整理多項式項次）
	Polynomial combine();					// 合併結果多項式中相同指數的項次
	void NewTerm(const float theCoeff, const int theExp); // 新增項次
	float Eval(float x);                     // 計算多項式值
	Polynomial& operator=(const Polynomial& other); // 多載賦值運算子
	friend ostream& operator<<(ostream& os, Polynomial& poly); // 多載輸出運算子
	friend istream& operator>>(istream& is, Polynomial& poly); // 多載輸入運算子

private:
	Term* termArray; // 儲存多項式項次的陣列
	int capacity;    // 陣列容量
	int terms;       // 有效項次數
};

// 預設建構子：初始化多項式
Polynomial::Polynomial() : capacity(1), terms(0) {
	termArray = new Term[capacity]; // 動態分配儲存空間
}

// 拷貝建構子
Polynomial::Polynomial(const Polynomial& other) {
	terms = other.terms;            // 複製有效項次數
	capacity = other.capacity;      // 複製容量
	termArray = new Term[capacity]; // 動態分配新的儲存空間
	for (int i = 0; i < terms; i++) {
		termArray[i] = other.termArray[i]; // 複製每個項次
	}
}

// 解構子：釋放動態分配的儲存空間
Polynomial::~Polynomial() {
	delete[] termArray; // 釋放陣列空間
}


// 新增項次並擴充儲存空間（若已滿）
void Polynomial::NewTerm(const float theCoeff, const int theExp)
{
	if (terms == capacity) // 若儲存空間不足
	{
		capacity *= 2; // 將容量擴充為原來的兩倍
		Term* temp = new Term[capacity]; // 分配新的儲存空間
		copy(termArray, termArray + terms, temp); // 將原本的資料複製到新空間
		delete[] termArray; // 釋放舊的儲存空間
		termArray = temp;   // 指向新的儲存空間
	}
	termArray[terms].coef = theCoeff; // 設定項次的系數
	termArray[terms++].exp = theExp;  // 設定項次的指數並增加項次數
}

// 多項式加法，返回兩個多項式的和
Polynomial Polynomial::Add(Polynomial b)
{
	Polynomial c; // 儲存結果的多項式
	int aPos = 0, bPos = 0; // a 和 b 的目前指標位置
	while ((aPos < terms) && (bPos < b.terms)) // 同時遍歷兩個多項式
	{
		if (termArray[aPos].exp == b.termArray[bPos].exp) // 當指數相等時
		{
			float t = termArray[aPos].coef + b.termArray[bPos].coef; // 系數相加
			if (fabs(t) > 1e-6) // 如果結果非零（處理浮點數誤差）
				c.NewTerm(t, termArray[aPos].exp); // 新增非零項次
			aPos++; bPos++; // 同時移動 a 和 b 的指標
		}
		else if (termArray[aPos].exp < b.termArray[bPos].exp) // b 的項次指數較大
		{
			c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp); // 新增 b 的項次
			bPos++; // 移動 b 的指標
		}
		else // a 的項次指數較大
		{
			c.NewTerm(termArray[aPos].coef, termArray[aPos].exp); // 新增 a 的項次
			aPos++; // 移動 a 的指標
		}
	}
	// 將剩下的項次加入結果
	for (; aPos < terms; aPos++)
		c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
	for (; bPos < b.terms; bPos++)
		c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
	return c; 
}


// 多項式乘法，返回兩個多項式的乘積
Polynomial Polynomial::Mult(Polynomial b)
{
	Polynomial c; // 儲存結果的多項式
	for (int i = 0; i < terms; i++) // 遍歷第一個多項式的每個項次
	{
		for (int j = 0; j < b.terms; j++) // 遍歷第二個多項式的每個項次
		{
			float tempCoef = termArray[i].coef * b.termArray[j].coef; // 系數相乘
			int tempExp = termArray[i].exp + b.termArray[j].exp;     // 指數相加
			c.NewTerm(tempCoef, tempExp); // 將新項次加入結果多項式
		}
	}
	return c; 
}


// 泡沫排序：將多項式按照指數從大到小排序
Polynomial Polynomial::BubbleSort()
{
	bool swapped; // 標記是否進行交換
	for (int i = 0; i < terms - 1; i++)
	{
		swapped = false;
		for (int j = 0; j < terms - i - 1; j++) // 後面的元素已排好序，減少內層迴圈次數
		{
			if (termArray[j].exp < termArray[j + 1].exp) // 指數較小則交換
			{
				Term temp = termArray[j];
				termArray[j] = termArray[j + 1];
				termArray[j + 1] = temp;
				swapped = true; // 標記進行過交換
			}
		}
		if (!swapped) break; // 若未交換，表示已排序完成，提早退出
	}
	return *this;
}


// 合併結果多項式中相同指數的項次
Polynomial Polynomial::combine()
{
	int newTerms = 0; // 記錄合併後的有效項數
	for (int i = 0; i < terms; i++)
	{
		if (termArray[i].coef == 0) continue; // 跳過係數為 0 的項
		for (int j = i + 1; j < terms; j++)
		{
			if (termArray[i].exp == termArray[j].exp) // 合併相同指數的項
			{
				termArray[i].coef += termArray[j].coef; // 合併系數
				termArray[j].coef = 0; // 標記為已合併
			}
		}
		if (termArray[i].coef != 0) {
			termArray[newTerms++] = termArray[i]; // 將有效項次移至前面
		}
	}
	terms = newTerms; // 更新有效項數
	return *this;
}


// 給定變數 x，計算多項式的值
float Polynomial::Eval(float x)
{
	float result = 0; // 儲存最終結果
	for (int i = 0; i < terms; i++) // 遍歷每一項
	{
		result += termArray[i].coef * pow(x, termArray[i].exp); // 計算當前項的值並累加
	}
	return result; 
}

// 重載輸出運算子 <<，以友好的格式輸出多項式
ostream& operator<<(ostream& os, Polynomial& poly)
{
	
	poly.BubbleSort(); // 先對多項式項次按照指數降序排序
	poly.combine();		//合併結果多項式中相同指數的項次
	for (int i = 0; i < poly.terms; i++)
	{
		if (poly.termArray[i].getCoef() == 0) continue; // 略過係數為 0 的項

		// 處理正負號顯示
		if (i > 0 && poly.termArray[i].getCoef() > 0) os << " + ";
		else if (i >= 0 && poly.termArray[i].getCoef() < 0) os << " - ";

		// 輸出係數部分（省略 1 和 -1 的顯示，除非是常數項）
		if (poly.termArray[i].getCoef() != 1 && poly.termArray[i].getCoef() != -1)
			os << abs(poly.termArray[i].getCoef());

		// 輸出 x 和指數部分
		if (poly.termArray[i].getExp() != 0) {
			os << "x";
			if (poly.termArray[i].getExp() != 1) os << "^" << poly.termArray[i].getExp();
		}
		// 若係數為 ±1 且指數為 0，需補充數字 1
		else if (poly.termArray[i].getCoef() == 1 || poly.termArray[i].getCoef() == -1) {
			os << "1";
		}
	}
	return os; 
}

// 重載輸入運算子 >>，從使用者輸入多項式
istream& operator>>(istream& is, Polynomial& poly) {
	cout << "Enter the number of terms in the polynomial: ";
	int n;
	is >> n;

	// 如果項數大於當前容量，重新分配記憶體
	if (n > poly.capacity) {
		delete[] poly.termArray; // 釋放舊的記憶體
		poly.capacity = n;
		poly.termArray = new Term[poly.capacity]; // 分配新的記憶體
	}

	poly.terms = 0; // 重置現有的項數
	cout << "(Input example: 3 2 means 3x^2)\n";
	for (int i = 0; i < n; i++) {
		float coef;
		int exp;
		cout << "Enter the coefficient and exponent for term " << i + 1 << ": ";
		is >> coef >> exp; // 讀取使用者輸入的係數和指數
		poly.NewTerm(coef, exp); // 添加新項
	}
	return is; 
}

// 重載=運算子，實現深拷貝
Polynomial& Polynomial::operator=(const Polynomial& other) {
	if (this != &other) { // 檢查是否為自我賦值
		delete[] termArray; // 釋放當前物件的舊記憶體

		// 複製其他物件的數據
		terms = other.terms;
		capacity = other.capacity;
		termArray = new Term[capacity]; // 分配新記憶體空間

		// 複製數據內容
		for (int i = 0; i < terms; i++) {
			termArray[i] = other.termArray[i];
		}
	}
	return *this; 
}

int main() {
	Polynomial poly1, poly2; // 創建兩個多項式物件

	// 使用 >> 重載輸入多項式
	cout << "Enter the first polynomial\n";
	while (cin >> poly1)  // 持續讀取使用者輸入的多項式
	{	cout << "\nEnter the second polynomial\n";
		cin >> poly2;

		// 使用 << 重載輸出多項式
		cout << endl;
		cout << "P1(x) = " << poly1 << endl; // 輸出第一個多項式
		cout << "P2(x) = " << poly2 << endl; // 輸出第二個多項式

		// 計算多項式加法和乘法
		cout << endl;
		Polynomial sum = poly1.Add(poly2);       // 加法運算
		Polynomial product = poly1.Mult(poly2);  // 乘法運算
		cout << "P1(x) + P2(x) = " << sum << endl;       // 輸出加法結果
		cout << "P1(x) * P2(x) = " << product << endl;   // 輸出乘法結果

		// 測試不同 x 值的多項式計算結果
		cout << endl;
		cout << "Test variables x={ 0, 1, 2, -1 }" << endl;
		float testX[] = { 0, 1, 2, -1 }; // 測試的 x 值集合
		for (float x : testX) {
			// 計算加法和乘法結果對應的多項式值
			cout << "Add" << " " << "P(" << x << ") =  " << sum.Eval(x) << "\t\t";
			cout << "Mult" << " " << "P(" << x << ") =  " << product.Eval(x) << endl;
		}

		// 提示再次輸入第一個多項式
		cout << "\nEnter the first polynomial:\n";
	}
	return 0;
}
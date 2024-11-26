#include<iostream>
#include<cmath>
using namespace std;

// �e�m�ŧi Polynomial ���O�A�� Term ���O�ϥ�
class Polynomial;

// ���O Term ��ܦh���������@�Ӷ���
class Term {
private:
	float coef; // �t��
	int exp;    // ����
public:
	// ����t��
	float getCoef() const { return coef; }
	// �������
	int getExp() const { return exp; }
	// �ŧi Polynomial ���ͤ����O�A���\�s�� private ����
	friend class Polynomial;
};

// ���O Polynomial ��ܦh����
class Polynomial {
public:
	Polynomial();                             // �غc�l
	Polynomial(const Polynomial& other);     // �����غc�l
	~Polynomial();                           // �Ѻc�l
	Polynomial Add(Polynomial b);            // �h�����ۥ[
	Polynomial Mult(Polynomial b);           // �h�����ۭ�
	Polynomial BubbleSort();                 // �w�j�Ƨǡ]��z�h���������^
	Polynomial combine();					// �X�ֵ��G�h�������ۦP���ƪ�����
	void NewTerm(const float theCoeff, const int theExp); // �s�W����
	float Eval(float x);                     // �p��h������
	Polynomial& operator=(const Polynomial& other); // �h����ȹB��l
	friend ostream& operator<<(ostream& os, Polynomial& poly); // �h����X�B��l
	friend istream& operator>>(istream& is, Polynomial& poly); // �h����J�B��l

private:
	Term* termArray; // �x�s�h�����������}�C
	int capacity;    // �}�C�e�q
	int terms;       // ���Ķ�����
};

// �w�]�غc�l�G��l�Ʀh����
Polynomial::Polynomial() : capacity(1), terms(0) {
	termArray = new Term[capacity]; // �ʺA���t�x�s�Ŷ�
}

// �����غc�l
Polynomial::Polynomial(const Polynomial& other) {
	terms = other.terms;            // �ƻs���Ķ�����
	capacity = other.capacity;      // �ƻs�e�q
	termArray = new Term[capacity]; // �ʺA���t�s���x�s�Ŷ�
	for (int i = 0; i < terms; i++) {
		termArray[i] = other.termArray[i]; // �ƻs�C�Ӷ���
	}
}

// �Ѻc�l�G����ʺA���t���x�s�Ŷ�
Polynomial::~Polynomial() {
	delete[] termArray; // ����}�C�Ŷ�
}


// �s�W�������X�R�x�s�Ŷ��]�Y�w���^
void Polynomial::NewTerm(const float theCoeff, const int theExp)
{
	if (terms == capacity) // �Y�x�s�Ŷ�����
	{
		capacity *= 2; // �N�e�q�X�R����Ӫ��⭿
		Term* temp = new Term[capacity]; // ���t�s���x�s�Ŷ�
		copy(termArray, termArray + terms, temp); // �N�쥻����ƽƻs��s�Ŷ�
		delete[] termArray; // �����ª��x�s�Ŷ�
		termArray = temp;   // ���V�s���x�s�Ŷ�
	}
	termArray[terms].coef = theCoeff; // �]�w�������t��
	termArray[terms++].exp = theExp;  // �]�w���������ƨüW�[������
}

// �h�����[�k�A��^��Ӧh�������M
Polynomial Polynomial::Add(Polynomial b)
{
	Polynomial c; // �x�s���G���h����
	int aPos = 0, bPos = 0; // a �M b ���ثe���Ц�m
	while ((aPos < terms) && (bPos < b.terms)) // �P�ɹM����Ӧh����
	{
		if (termArray[aPos].exp == b.termArray[bPos].exp) // ����Ƭ۵���
		{
			float t = termArray[aPos].coef + b.termArray[bPos].coef; // �t�Ƭۥ[
			if (fabs(t) > 1e-6) // �p�G���G�D�s�]�B�z�B�I�ƻ~�t�^
				c.NewTerm(t, termArray[aPos].exp); // �s�W�D�s����
			aPos++; bPos++; // �P�ɲ��� a �M b ������
		}
		else if (termArray[aPos].exp < b.termArray[bPos].exp) // b ���������Ƹ��j
		{
			c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp); // �s�W b ������
			bPos++; // ���� b ������
		}
		else // a ���������Ƹ��j
		{
			c.NewTerm(termArray[aPos].coef, termArray[aPos].exp); // �s�W a ������
			aPos++; // ���� a ������
		}
	}
	// �N�ѤU�������[�J���G
	for (; aPos < terms; aPos++)
		c.NewTerm(termArray[aPos].coef, termArray[aPos].exp);
	for (; bPos < b.terms; bPos++)
		c.NewTerm(b.termArray[bPos].coef, b.termArray[bPos].exp);
	return c; 
}


// �h�������k�A��^��Ӧh���������n
Polynomial Polynomial::Mult(Polynomial b)
{
	Polynomial c; // �x�s���G���h����
	for (int i = 0; i < terms; i++) // �M���Ĥ@�Ӧh�������C�Ӷ���
	{
		for (int j = 0; j < b.terms; j++) // �M���ĤG�Ӧh�������C�Ӷ���
		{
			float tempCoef = termArray[i].coef * b.termArray[j].coef; // �t�Ƭۭ�
			int tempExp = termArray[i].exp + b.termArray[j].exp;     // ���Ƭۥ[
			c.NewTerm(tempCoef, tempExp); // �N�s�����[�J���G�h����
		}
	}
	return c; 
}


// �w�j�ƧǡG�N�h�������ӫ��Ʊq�j��p�Ƨ�
Polynomial Polynomial::BubbleSort()
{
	bool swapped; // �аO�O�_�i��洫
	for (int i = 0; i < terms - 1; i++)
	{
		swapped = false;
		for (int j = 0; j < terms - i - 1; j++) // �᭱�������w�Ʀn�ǡA��֤��h�j�馸��
		{
			if (termArray[j].exp < termArray[j + 1].exp) // ���Ƹ��p�h�洫
			{
				Term temp = termArray[j];
				termArray[j] = termArray[j + 1];
				termArray[j + 1] = temp;
				swapped = true; // �аO�i��L�洫
			}
		}
		if (!swapped) break; // �Y���洫�A��ܤw�Ƨǧ����A�����h�X
	}
	return *this;
}


// �X�ֵ��G�h�������ۦP���ƪ�����
Polynomial Polynomial::combine()
{
	int newTerms = 0; // �O���X�᪺֫���Ķ���
	for (int i = 0; i < terms; i++)
	{
		if (termArray[i].coef == 0) continue; // ���L�Y�Ƭ� 0 ����
		for (int j = i + 1; j < terms; j++)
		{
			if (termArray[i].exp == termArray[j].exp) // �X�֬ۦP���ƪ���
			{
				termArray[i].coef += termArray[j].coef; // �X�֨t��
				termArray[j].coef = 0; // �аO���w�X��
			}
		}
		if (termArray[i].coef != 0) {
			termArray[newTerms++] = termArray[i]; // �N���Ķ������ܫe��
		}
	}
	terms = newTerms; // ��s���Ķ���
	return *this;
}


// ���w�ܼ� x�A�p��h��������
float Polynomial::Eval(float x)
{
	float result = 0; // �x�s�̲׵��G
	for (int i = 0; i < terms; i++) // �M���C�@��
	{
		result += termArray[i].coef * pow(x, termArray[i].exp); // �p���e�����Ȩò֥[
	}
	return result; 
}

// ������X�B��l <<�A�H�ͦn���榡��X�h����
ostream& operator<<(ostream& os, Polynomial& poly)
{
	
	poly.BubbleSort(); // ����h�����������ӫ��ƭ��ǱƧ�
	poly.combine();		//�X�ֵ��G�h�������ۦP���ƪ�����
	for (int i = 0; i < poly.terms; i++)
	{
		if (poly.termArray[i].getCoef() == 0) continue; // ���L�Y�Ƭ� 0 ����

		// �B�z���t�����
		if (i > 0 && poly.termArray[i].getCoef() > 0) os << " + ";
		else if (i >= 0 && poly.termArray[i].getCoef() < 0) os << " - ";

		// ��X�Y�Ƴ����]�ٲ� 1 �M -1 ����ܡA���D�O�`�ƶ��^
		if (poly.termArray[i].getCoef() != 1 && poly.termArray[i].getCoef() != -1)
			os << abs(poly.termArray[i].getCoef());

		// ��X x �M���Ƴ���
		if (poly.termArray[i].getExp() != 0) {
			os << "x";
			if (poly.termArray[i].getExp() != 1) os << "^" << poly.termArray[i].getExp();
		}
		// �Y�Y�Ƭ� ��1 �B���Ƭ� 0�A�ݸɥR�Ʀr 1
		else if (poly.termArray[i].getCoef() == 1 || poly.termArray[i].getCoef() == -1) {
			os << "1";
		}
	}
	return os; 
}

// ������J�B��l >>�A�q�ϥΪ̿�J�h����
istream& operator>>(istream& is, Polynomial& poly) {
	cout << "Enter the number of terms in the polynomial: ";
	int n;
	is >> n;

	// �p�G���Ƥj���e�e�q�A���s���t�O����
	if (n > poly.capacity) {
		delete[] poly.termArray; // �����ª��O����
		poly.capacity = n;
		poly.termArray = new Term[poly.capacity]; // ���t�s���O����
	}

	poly.terms = 0; // ���m�{��������
	cout << "(Input example: 3 2 means 3x^2)\n";
	for (int i = 0; i < n; i++) {
		float coef;
		int exp;
		cout << "Enter the coefficient and exponent for term " << i + 1 << ": ";
		is >> coef >> exp; // Ū���ϥΪ̿�J���Y�ƩM����
		poly.NewTerm(coef, exp); // �K�[�s��
	}
	return is; 
}

// ����=�B��l�A��{�`����
Polynomial& Polynomial::operator=(const Polynomial& other) {
	if (this != &other) { // �ˬd�O�_���ۧڽ��
		delete[] termArray; // �����e�����°O����

		// �ƻs��L���󪺼ƾ�
		terms = other.terms;
		capacity = other.capacity;
		termArray = new Term[capacity]; // ���t�s�O����Ŷ�

		// �ƻs�ƾڤ��e
		for (int i = 0; i < terms; i++) {
			termArray[i] = other.termArray[i];
		}
	}
	return *this; 
}

int main() {
	Polynomial poly1, poly2; // �Ыب�Ӧh��������

	// �ϥ� >> ������J�h����
	cout << "Enter the first polynomial\n";
	while (cin >> poly1)  // ����Ū���ϥΪ̿�J���h����
	{	cout << "\nEnter the second polynomial\n";
		cin >> poly2;

		// �ϥ� << ������X�h����
		cout << endl;
		cout << "P1(x) = " << poly1 << endl; // ��X�Ĥ@�Ӧh����
		cout << "P2(x) = " << poly2 << endl; // ��X�ĤG�Ӧh����

		// �p��h�����[�k�M���k
		cout << endl;
		Polynomial sum = poly1.Add(poly2);       // �[�k�B��
		Polynomial product = poly1.Mult(poly2);  // ���k�B��
		cout << "P1(x) + P2(x) = " << sum << endl;       // ��X�[�k���G
		cout << "P1(x) * P2(x) = " << product << endl;   // ��X���k���G

		// ���դ��P x �Ȫ��h�����p�⵲�G
		cout << endl;
		cout << "Test variables x={ 0, 1, 2, -1 }" << endl;
		float testX[] = { 0, 1, 2, -1 }; // ���ժ� x �ȶ��X
		for (float x : testX) {
			// �p��[�k�M���k���G�������h������
			cout << "Add" << " " << "P(" << x << ") =  " << sum.Eval(x) << "\t\t";
			cout << "Mult" << " " << "P(" << x << ") =  " << product.Eval(x) << endl;
		}

		// ���ܦA����J�Ĥ@�Ӧh����
		cout << "\nEnter the first polynomial:\n";
	}
	return 0;
}
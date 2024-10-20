#include <iostream>
#include <chrono>  // �ޤJ�ɶ����q�����Y�ɮ�
using namespace std;

const int STACK_SIZE = 50000;  // �]�w�@�Ө����j�����|�Ŷ�

// �Ψ�Ӱ}�C�������|�� Ackermann �D���j�禡
int AckermannDoubleStack(int m, int n) {
    // �ϥΨ�Ӱ}�C�Ӽ������|
    int stack_m[STACK_SIZE]; // �s�� m ����
    int stack_n[STACK_SIZE]; // �s�� n ����

    int top = 0;  // ��l�ư��|�������w
    stack_m[top] = m; // �N��l m ���J���|
    stack_n[top] = n; // �N��l n ���J���|

    // ����|�����Ů�
    while (top >= 0) {
        m = stack_m[top]; // ���X���|���� m
        n = stack_n[top]; // ���X���|���� n
        top--; // �X���|

        if (m == 0) {
            if (top >= 0) {
                stack_n[top] = n + 1;  // �� m == 0 �ɡA��s n �� n + 1
            }
            else {
                return n + 1;  // ���|�ŮɡA��^�p�⵲�G
            }
        }
        else if (n == 0) {
            top++; // �i�J�U�@�h���j
            stack_m[top] = m - 1; // �N (m-1) ���J���|
            stack_n[top] = 1;  // �N n �]�� 1
        }
        else {
            top++; // �i�J�U�@�h���j
            stack_m[top] = m - 1; // �N (m-1) ���J���|
            stack_n[top] = -1;  // �аO�ݭn��s�� n
            top++; // �i�J�U�@�h
            stack_m[top] = m; // �N m ���J���|
            stack_n[top] = n - 1; // �N (n-1) ���J���|
        }
    }

    return -1;  // �û������Ө�o�̡A�@���O�I����^��
}

int main()
{
    int m, n;

    // �`��Ū�� m �M n ����
    while (cin >> m >> n)
    {
        // �}�l�p��
        auto start = chrono::high_resolution_clock::now();

      
        int result = AckermannDoubleStack(m, n);

        // ����p��
        auto end = chrono::high_resolution_clock::now();

        // �p�����ɶ�
        chrono::duration<double> duration = end - start;

        // ��X���G�M����ɶ�
        cout << "Ackermann Double Stack: " << result << endl;
        cout << "Execution time: " << duration.count() << " seconds" << endl;
    }

    return 0;
}

/*
�̤j�Ө�����
    ������(3,12)=32765

STACK_SIZE���|�j�p�����i�Ө�����
    ��[50000] --> (3,12) = 32765
*/

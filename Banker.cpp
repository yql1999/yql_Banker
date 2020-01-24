//���м��㷨 
#include "stdafx.h"
#include <iostream>
using namespace std;

#define MAXN 100


int Available[MAXN];	//����Դδ�������Դ��
int Max[MAXN][MAXN];	//ÿ����������������Դ��
int Allocation[MAXN][MAXN];	//ÿ��������ռ�е���Դ��
int Need[MAXN][MAXN];	//ÿ�����̻������Դ��
int Request[MAXN];	//��������ĸ���Դ��
int Finish[MAXN];
int path[MAXN] = { 0 };	//��ȫ����
int PNum, RNum;	//����������Դ��



void input(int PNum, int RNum) {
	int i,j;
    cout << "����ÿ����������������Դ����\n";
    for (i = 0; i < PNum; i++) {
        cout << "P" << i << " ��";
        for (j = 0; j < RNum; j++)
            cin >> Max[i][j];
    }
    cout << "����ÿ��������ռ�е���Դ����\n";
    for (i = 0; i < PNum; i++) {
        cout << "P" << i << " ��";
        for (j = 0; j < RNum; j++) {
            cin >> Allocation[i][j];
			//ÿ�����̻������Դ��Need
            Need[i][j] = Max[i][j] - Allocation[i][j];
            if (Need[i][j] < 0) {
                cout << "����Ľ���P" << i << "��ӵ�еĵ�" << j + 1 << "����Դ������С��0�����������룺\n";
                j--;
                continue;
            }
        }
    }
    cout << "ÿ�����̻������Դ����\n";
    for (i = 0; i < PNum; i++) {
        cout << "P" << i << " ��";
        for (j = 0; j < RNum; j++) {
            cout << " " << Need[i][j];
        }
        cout << endl;
    }
    cout << "����δ�������Դ����\n";
    for (i = 0; i < RNum; i++)
        cin >> Available[i];
}

//�ж��Ƿ���ڰ�ȫ����
int Safe() {
    int i, j, jj, k = 0;
    int Available_copy[MAXN];	//δ�������Դ��
    int Allocation_copy[MAXN][MAXN];	//��ռ�е���Դ��
    int Need_copy[MAXN][MAXN];	//���̻������Դ��
    
    for (i = 0; i < RNum; i++) 
		Available_copy[i] = Available[i];
	for (i = 0; i < PNum; i++) {
        for (j = 0; j < RNum; j++)
            Allocation_copy[i][j] = Allocation[i][j];
    }
    for (i = 0; i < PNum; i++) {
        for (j = 0; j < RNum; j++)
            Need_copy[i][j] = Need[i][j];
    }
    for (i = 0; i < PNum; i++) 
		Finish[i] = 0;
		
	//����ÿ������
    for (i = 0; i < PNum; i++) {
        if (Finish[i] == 1)
            continue;
        else {				
			//ǰ�᣺��Ҫ����Դ<δ�������Դ
            for (j = 0; j < RNum; j++) {
                if (Need_copy[i][j] > Available_copy[j])
                    break;
            }
			//���ҵ�һ�����̵�������Դ��������Ҫ�󣬸���
            if (j == RNum) {
                Finish[i] = 1;
                for (jj = 0; jj < RNum; jj++){
                	Available_copy[jj] += Allocation[i][jj];
                	Allocation_copy[i][jj] = 0;
                	Need_copy[i][jj] = 0;
				}
                
				int ii;    
                cout << "Detail process" << k << ":\n" << "����P" << i << "���󣬸�����Դ�б�";
                cout << "\n�����ѷ��䵽����Դ����\n";
    			for (ii = 0; ii < PNum; ii++) {
        			cout << "P" << ii << " ��";
        			for (jj = 0; jj < RNum; jj++)
            		cout << " " << Allocation_copy[ii][jj];
        			cout << endl;
    			} 
    			cout << "���̻������Դ����\n";
    			for (ii = 0; ii < PNum; ii++) {
        			cout << "P" << ii << " ��";
        			for (jj = 0; jj < RNum; jj++)
            			cout << " " << Need_copy[ii][jj];
        			cout << endl;
    			}
    			cout << "δ�������Դ����";
    			for (jj = 0; jj < RNum; jj++)
        			cout << " " << Available_copy[jj];
    			cout << endl;
    			
                path[k++] = i + 1;	//д�밲ȫ���� 
                i = -1;	//NOTE
            }
            else 
				continue;
        }
        if (k == PNum) {	//���ڰ�ȫ����
            return 1;
        }
    }
    return 0;
}

//�����ȫ����
void outPath() {
    cout << "��ȫ���У�P" << path[0] - 1;
    for (int i = 1; path[i] != 0; i++) {
        cout << "->P" << path[i] - 1;
    }
	//���path��Ϊ�´δ��밲ȫ������׼��
    for (int j = 0; j < PNum; j++) 
		path[j] = 0;
    cout << endl;
}

int requestP() {
    int n,i;
    cout << "����Ҫ������Դ�Ľ��̺ţ�";
    cin >> n;
    cout << "�����������ĸ���Դ����";
    for (i = 0; i < RNum; i++)
        cin >> Request[i];
    for (i = 0; i < RNum; i++) {
        if (Request[i] > Need[n][i]) {
            cout << "Error���������Դ�����ڽ����������Դ����\n";
            return 1;
        }
        if (Request[i] > Available[i]) {
            cout << "������Դ������δ�������Դ����ϵͳ���㹻��Դ������P" << n << "�����ȴ�...\n";
            return 1;
        }
    }
	//����δ���䡢�ѷ���ͻ������Դ��
    for (i = 0; i < RNum; i++) {
        Available[i] -= Request[i];
        Allocation[n][i] += Request[i];
        Need[n][i] -= Request[i];
    }
    if (Safe()) {
        cout << "���ڰ�ȫ���У�ϵͳ���ڰ�ȫ״̬��ͬ���������\n";
		outPath();
    }
	//�������ڰ�ȫ���У���ԭδ���䡢�ѷ���ͻ������Դ��
    else {
        for (i = 0; i < RNum; i++) {
            Available[i] += Request[i];
            Allocation[n][i] -= Request[i];
            Need[n][i] += Request[i];
        }
        cout << "�����ڰ�ȫ���У�ϵͳ���ڲ���ȫ״̬���ܾ�����\n";
    }
    return 0;
}

void print() {
    int i, j;
    
	cout << "\n�����ѷ��䵽����Դ����\n";
    for (i = 0; i < PNum; i++) {
        cout << "P" << i << " ��";
        for (j = 0; j < RNum; j++)
            cout << " " << Allocation[i][j];
        cout << endl;
    } 
    cout << "���̻������Դ����\n";
    for (i = 0; i < PNum; i++) {
        cout << "P" << i << " ��";
        for (j = 0; j < RNum; j++)
            cout << " " << Need[i][j];
        cout << endl;
    }
    cout << "δ�������Դ����";
    for (j = 0; j < RNum; j++)
        cout << " " << Available[j];
    cout << endl;
} 


int main(){
	cout<<"----------���м��㷨----------\n";
    cout << "�����������";
    cin >> PNum;
    cout << "������Դ���ࣺ";
    cin >> RNum;
    input(PNum, RNum);	//��ȡ����
    cout << "RESULT��\n";
    if (Safe()) {
        cout << "���ڰ�ȫ���У�ϵͳ���ڰ�ȫ״̬��\n";
        outPath();
    }
    else {
        cout << "�����ڰ�ȫ���У�ϵͳ���ڲ���ȫ״̬��\n";
        return 0;
    }
    cout << endl;
    while (true) {
        requestP();
        print();
        string s;
        cout << "�Ƿ��ٴ�������䣿������yes��no��\n";
        while (true) {
            cin >> s;
            if (s == "yes" || s == "no")
                break;
            else {
                cout << "�밴Ҫ���������룺\n";
                continue;
            }
        }
        if (s == "yes")
            continue;
        else 
			break;
    }
    return 0;
}

#include <stdio.h>
#include <string.h>

// ������ӹ���GETS��ʵ��
int GETS(char *str) {
    int count = 0;
    char ch;
    while ((ch = getchar()) != '\n') {
        *str++ = ch;
        count++;
    }
    *str = '\0'; // �ַ�����'\0'��β
    return count; // �����ַ�������
}

// ������ӹ���PUTS��ʵ��
int PUTS(const char *str) {
    int count = 0;
    while (*str) {
        putchar(*str++);
        count++;
    }    
    putchar('\n');
    return count; // ����������ַ�����
}

// ������MAIN
int main() {
    char input[30],longestString[30]={0}; // �ַ������飬����Ϊ30�������29���ַ�����'\0'
    int maxLength = 0; // ��¼��ַ����ĳ���

    // ѭ����ȡ�ַ���ֱ���������
    while (1) {
        int length = GETS(input);
        if (length == 0) break; // �������Ϊ���У����˳�ѭ��

        if (length > maxLength) {
            maxLength = length;
            int i=0;
            while(input[i]!='\0'){
            	longestString[i] = input[i];
            	i++;
            }
            longestString[i]='\0';
        }
    }

    // �������ַ���
    PUTS(longestString);

    return 0;
}
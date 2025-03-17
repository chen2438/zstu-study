#include <stdio.h>
#include <string.h>

// 假设的子过程GETS的实现
int GETS(char *str) {
    int count = 0;
    char ch;
    while ((ch = getchar()) != '\n') {
        *str++ = ch;
        count++;
    }
    *str = '\0'; // 字符串以'\0'结尾
    return count; // 返回字符串长度
}

// 假设的子过程PUTS的实现
int PUTS(const char *str) {
    int count = 0;
    while (*str) {
        putchar(*str++);
        count++;
    }    
    putchar('\n');
    return count; // 返回输出的字符个数
}

// 主过程MAIN
int main() {
    char input[30],longestString[30]={0}; // 字符串数组，长度为30以容纳最长29个字符加上'\0'
    int maxLength = 0; // 记录最长字符串的长度

    // 循环读取字符串直到输入空行
    while (1) {
        int length = GETS(input);
        if (length == 0) break; // 如果输入为空行，则退出循环

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

    // 输出最长的字符串
    PUTS(longestString);

    return 0;
}
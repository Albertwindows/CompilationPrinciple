#include <iostream>
#include <ctype.h>
#include <stdio.h>
#include <cstring>
const int keywordSum = 8;
const char * keyword[] = { "if","else","for","while","do","int","read","write" };
char singleword[50] = "+-*(){};,:";
char doubleword[10] = "><=!";
const int MAX_TEXT_LEN = 300;
char Scanin[MAX_TEXT_LEN], Scanout[MAX_TEXT_LEN];
FILE * fin, *fout;
#define DEBUG_LINUX
int TESTscan()
{
    int lines = 1;
    char ch, token[40];
    int es = 0, j, n;
#ifdef DEBUG_WINDOWS
#define DEBUG
    strcpy(Scanin, "C:\\Coding\\CompilationPrinciple\\in.txt");
    strcpy(Scanout, "C:\\Coding\\CompilationPrinciple\\out.txt");
#endif

#ifdef DEBUG_LINUX
#define DEBUG
    strcpy(Scanin, "/home/wz/桌面/projects/CompilationPrinciple/_clion_/in.txt");
    strcpy(Scanout, "./out.txt");
#endif
#ifndef DEBUG
    printf("请输入源程序文件名（包括路径）：");
	scanf("%s", Scanin);
	printf("请输入词法分析输出文件名（包括路径）");
	scanf("%s", Scanout);
#endif // DEBUG

    if ((fin = fopen(Scanin, "r")) == NULL)
    {
        //printf("fopen return NULL, error=%d/n", GetLastError());
        printf("\n打开此法分析输入文件出错\n");
        return 1;
    }
    if ((fout = fopen(Scanout, "w")) == NULL)
    {
        printf("\n创建测法分析输出文件出错！\n");
        return 2;
    }
    ch = getc(fin);
    while (ch != EOF) {
        if (ch=='\n') lines++;
        while (ch == ' ' || ch == '\n' || ch == '\t') {
            ch = getc(fin);
        }
        if (isalpha(ch))
        {
            token[0] = ch; j = 1;
            ch = getc(fin);
            while (isalnum(ch) || ch == '_')
            {
                token[j++] = ch;
                ch = getc(fin);
            }
            token[j] = '\0';
            n = 0;
            while (n < keywordSum && strcmp(token, keyword[n])) n++;
            if (n >= keywordSum) {
                fprintf(fout, "%s\t%s\n", "ID", token);
            }
            else {
                fprintf(fout, "%s\t%s\n", token, token);
            }

        }
        else if (isdigit(ch))
        {
            token[0] = ch;
            j = 1;
            ch = getc(fin);
            while (isdigit(ch))
            {
                token[j++] = ch;
                ch = getc(fin);
            }
            token[j] = '\0';
            fprintf(fout, "%s\t%s\n", "NUM", token);

        }
        else if (strchr(singleword, ch) != NULL) {
            token[0] = ch;
            ch = getc(fin);
            if (ch == '=')
            {
                token[1] = ch; token[2] = '\0';
                ch = getc(fin);

            }
            else
            {
                token[1] = '\0';
            }
            fprintf(fout, "%s\t%s\n", token, token);
        }
        else if (strchr(doubleword, ch) != 0) {
            token[0] = ch;
            ch = getc(fin);
            if (ch == '=')
            {
                token[1] = ch; token[2] = '\0';
                ch = getc(fin);

            }
            else
            {
                token[1] = '\0';
            }
            fprintf(fout, "%s\t%s\n", token, token);
        }
        else if (ch == '/') {
            ch = getc(fin);
            //add new function
            if (ch == '/')
            {
                while((ch = getc(fin)) && ch!='\n' &&ch!=EOF);
            }
            else if (ch == '*')
            {
                char ch1 = getc(fin);
                do {
                    ch = ch1; ch1 = getc(fin);
                } while ((ch != '*' || ch1 != '/') && ch1 != EOF);
                ch = getc(fin);
            }
            else {
                token[0] = '/'; token[1] = '\0';
                fprintf(fout, "%s\t%s\n", token, token);
            }

        }
        else {
            token[0] = ch; token[1] = '\0';
            ch = getc(fin);
            es = 3;
            fprintf(fout, "%s\t%s the number of line is: %d\n", "ERROR", token,lines);
        }

    }
    fclose(fin);
    fclose(fout);
    return es;
}
using namespace std;
int main()
{
    TESTscan();
    return 0;
}
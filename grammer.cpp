#include <stdio.h>
#include <ctype.h>
int test_parse();
int program();
int compound_stat();
int statement();
extern char token[20],token1[40];
extern char Scanout[300];//保存词法分析输出文件名
extern FILE * fp;
int test_parse()
{
    int es = 0;
    if ((fp=fopen(Scanout,"r"))==NULL){
        printf("\n打开%s错误！\n",Scanout);
        es = 10;
    }
    if (es==0) es = program();
    printf("=========语法分析结果！=========");
    switch (es){
        case 0: printf("语法分析成功！\n");
            break;
        case 10:printf("\n打开%s错误！\n",Scanout);
            break;
        case 1:printf("缺少{！\n");
            break;
        case 2:printf("缺少}！\n");
            break;
        case 3:printf("缺少标示符!\n");
            break;
        case 4:printf("缺少分号！\n");
            break;
        case 5:printf("缺少(!\n");
            break;
        case 6:printf("缺少)!\n");
            break;
        case 7:printf("缺少操作数！\n");
            break;
    }
    fclose(fp);
    return (es);
}
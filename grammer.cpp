#include <stdio.h>
#include <ctype.h>
#include <conio.h>
int TESTparse();
int program();
int compound_stat();
int statement();
int expreesion_stat();
int expreesion();
int bool_expr();
int additive_expr();
int term();
int factor();
int if_stat();
int while_stat();
int for_stat();
int read_stat();
int write_stat();
int declaration_stat();
int declaration_list();
int statement_list();
int compound_stat();
char token[20],token1[40];
extern char Scanout[300];//保存词法分析输出文件名
FILE * fp;
int TESTparse()
{
    int es = 0;
    if ((fp=fopen(Scanout,"r")==NULL)){
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
        case 2:printf("缺少{！\n");
    }
    fclose(fp);
    return (es);
}
//<程序>::={<声明序列><语句序列>}
//<program>::={<declaration_list><statement_list>};
int program(){
    int es = 0;
    //different
    fscanf(fp,"%s %s\n",token,token1);
    printf("%s %s\n",token,token1);
    if (strcmp(token,"{"))
    {
        es = 1;
        return (es);
    }
    //different
    fscanf(fp,"%s %s",token,token1);
    printf("%s %s\n",token,token1);
    es = declaration_list();
    if (es>0) return (es);
    if (strcmp(token,"}")){
        return es = 2;
    }
    return es ;
}

int statement()
{
    int es = 0;
    if (es == 0 && strcmp(token,"if")==0) es = if_stat();
    if (es == 0 && strcmp(token,"while")==0) es = while_stat();
    if (es == 0 && strcmp(token,"for")==0) es = for_stat();
    if (es == 0 && strcmp(token,"read")==0) es = read_stat();
    if (es == 0 && strcmp(token,"write")==0) es = write_stat();
    if (es == 0 && strcmp(token,"{")==0) es = compound_stat();
    if (es == 0 && strcmp(token,"ID")==0 || strcmp(token,"NUM")==0||strcmp(token,"{")==0)
        es = expreesion_stat();
    return es;
}
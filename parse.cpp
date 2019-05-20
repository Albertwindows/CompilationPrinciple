#include "parse.h"
#include <iostream>
using namespace std;
extern char token[20], token1[40];
extern char Scanin[300], Scanout[300];
extern FILE *fin, *fout,*fp;
extern const char * keyword[];
extern const char *singleword;
extern const char *doubleword;
extern const int MAX_TEXT_LEN;
int TESTparse()
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
//<程序>::={<声明序列><语句序列>}
//<program>::={<declaration_list><statement_list>};
int program(){
    int es = 0;
    //different
    fscanf(fp,"%s %s\n",token,token1);
    cout<<"===========program()========="<<endl;
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
    es = statement_list();
    if (es>0) return (es);

    if (strcmp(token,"}")){
        es = 2;
        return es;
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
    if (es == 0 && (strcmp(token,"ID")==0 || strcmp(token,"NUM")==0||strcmp(token,"{")==0))
        es = expression_stat();
    return es;
}

int expression_stat()
{
    int es = 0;
    if (strcmp(token, ";") == 0){
        fscanf(fp, "%s %s\n", token,token1);
        printf("%s %s\n",token,token1);
        return(es);
    }
    es = expression();
    if (es > 0) return(es);
    if (es == 0 && strcmp(token, ";") == 0)
    {
        fscanf(fp, "%s %s\n", token,token1);
        printf("%s %s\n", token, token1);
        return(es);
    }
    else
    {
        es = 4;
        return(es);
    }
}


int expression()
{
    int es = 0, fileadd;
    char token2[20], token3[40];
    if (strcmp(token, "ID") == 0)
    {
        fileadd = ftell(fp);
        fscanf(fp,"%s %s\n",token2,token3);
        printf("%s %s\n",token2,token3);
        if (strcmp(token2, "=") == 0){
            fscanf(fp, "%s %s\n", token, token1);
            printf("%s %s\n",token,token1);
            es = bool_expr();
            if (es > 0) return(es);
        }
        else
        {
            fseek(fp, fileadd, 0);
            printf("%s %s\n",token,token1);
            es = bool_expr();
            if (es > 0) return(es);
        }
    }
    else es = bool_expr();
    return(es);
}


int bool_expr()
{
    int es = 0;
    es = additive_expr();
    if (es > 0)return(es);
    if (strcmp(token, ">") == 0 || strcmp(token, ">=") == 0 || strcmp(token, "<") == 0 || strcmp(token, "<=") == 0 || strcmp(token, "==") == 0 || strcmp(token, "<") == 0)
    {
        fscanf(fp, "%s %s\n", token, token1);
        printf("%s %s\n", token, token1);
        es = additive_expr();
        if (es > 0) return(es);
    }
    return(es);
}


int additive_expr()
{
    int es = 0;
    es = term();
    while (strcmp(token, "+") == 0 || strcmp(token, "-") == 0)
    {
        fscanf(fp, "%s %s\n", token, token1);
        printf("%s %s\n", token, token1);
        es = term();
        if (es > 0) return(es);
    }
    return(es);
}


int if_stat(){
    int es=0;
    fscanf(fp,"%s %s\n",token,token1);
    printf("%s %s\n",token,token1);
    if(strcmp(token,"("))    return(es=5);
    fscanf(fp, "%s %s\n", token,token1);
    printf("%s %s\n",token,token1);
    es=expression();
    if(es>0) return(es);
    if(strcmp(token,")"))    return(es=6);
    fscanf(fp,"%s %s\n",token,token1);
    printf("%s %s\n",token,token1);
    es=statement();
    if(es>0) return(es);
    if(strcmp(token,"else")==0)
    {
        fscanf(fp,"%s %s\n",token,token1);
        printf("%s %s\n",token,token1);
        es=statement();
        if(es>0) return(es);
    }
    return(es);
}


int while_stat()
{
    int es=0;
    fscanf(fp,"%s %s\n",token,token1);
    printf("%s %s\n",token,token1);
    if(strcmp(token,"("))    return(es=5);
    fscanf(fp,"%s %s\n",token,token1);
    printf("%s %s\n",token,token1);
    es=expression();
    if(es>0) return(es);
    if(strcmp(token,")"))    return(es=6);
    fscanf(fp,"%s %s\n",token,token1);
    printf("%s %s\n",token,token1);
    es=statement();
    return(es);
}


int term()
{

    int es=0;
    es=factor();
    if(es>0) return(es);
    while(strcmp(token,"*")==0||strcmp(token,"/")==0)
    {
        fscanf(fp,"%s %s\n",token,token1);
        printf("%s %s\n",token,token1);
        es=factor();
        if(es>0) return(es);
    }
    return(es);
}

int factor()
{
    int es=0;
    if(strcmp(token,"(")==0)
    {
        fscanf(fp,"%s %s\n",token,token1);
        printf("%s %s\n",token,token1);
        es=expression();
        if(es>0) return(es);
        if(strcmp(token,")")) return(es=6);
        fscanf(fp,"%s %s\n",token,token1);
        printf("%s %s\n",token,token1);
    }
    else
    {
        if(strcmp(token,"ID")==0||strcmp(token,"NUM")==0)
        {
            fscanf(fp,"%s %s\n",token,token1);
            printf("%s %s\n",token,token1);
            return(es);
        }else
        {
            es=7;
            return(es);
        }
    }
    return(es);
}


int for_stat()
{
    int es = 0;
    fscanf(fp, "%s %s\n", token, token1);
    printf("%s %s\n", token, token1);

    if (strcmp(token, "(")) return (es = 5);
    fscanf(fp, "%s %s\n", token, token1);
    printf("%s %s\n", token, token1);
    es = expression();
    if (es > 0) return(es);

    if (strcmp(token, ";")) return (es = 4);
    fscanf(fp, "%s %s\n", token, token1);
    printf("%s %s\n", token, token1);
    es = expression();
    if (es > 0) return(es);

    if (strcmp(token, ";")) return (es = 4);
    fscanf(fp, "%s %s\n", token, token1);
    printf("%s %s\n", token, token1);
    es = expression();
    if (es > 0) return(es);

    if (strcmp(token, ")")) return (es = 6);
    fscanf(fp, "%s %s\n", token, token1);
    printf("%s %s\n", token, token1);
    es = statement();
    return(es);
}


int write_stat()
{
    int es = 0;
    fscanf(fp, "%s %s\n", token, token1);
    printf("%s %s\n", token, token1);
    es = expression();
    if (es > 0) return(es);
    if (strcmp(token, ";"))  return(es = 4);
    fscanf(fp, "%s %s\n", token, token1);
    printf("%s %s\n", token, token1);
    return(es);
}

int read_stat()
{
    int es = 0;
    fscanf(fp, "%s %s\n", token, token1);
    printf("%s %s\n", token, token1);
    if (strcmp(token, "ID"))  return(es = 3);
    fscanf(fp, "%s %s\n", token, token1);
    printf("%s %s\n", token, token1);
    if (strcmp(token, ";"))  return(es = 4);
    fscanf(fp, "%s %s\n", token, token1);
    printf("%s %s\n", token, token1);
    return(es);
}


int declaration_stat()
{
    int es = 0;
    fscanf(fp, "%s %s\n", token, token1);
    printf("%s %s\n", token, token1);
    if (strcmp(token, "ID"))  return(es = 3);
    fscanf(fp, "%s %s\n", token, token1);
    printf("%s %s\n", token, token1);
    if (strcmp(token, ";"))  return(es = 4);
    fscanf(fp, "%s %s\n", token, token1);
    printf("%s %s\n", token, token1);
    return (es);
}


//<声明序列>::=<声明序列><声明语句>|<声明语句>
//<declaration_list>::=
//<declaration_list><declaraction_stat>|ε
//改成<declaration_list>::={<declaration_stat>}
int declaration_list()
{
    int es = 0;
    while (strcmp(token, "int") == 0)
    {
        es = declaration_stat();
        if (es > 0) return(es);
    }
    return(es);
}

//<语句序列>::=<语句序列><语句>|ε
//<statement_list>::=<statement><statement>|ε
//改成<statement_list>::={<statement>}
int statement_list()
{
    int es = 0;
    while (strcmp(token, "}"))
    {
        es = statement();
        if (es > 0) return(es);
    }
    return(es);
}

//<复合语句>::={<语句序列>}
//<compound>::={<statement_list>}
int compound_stat()
{
    int es = 0;
    fscanf(fp, "%s %s\n", token, token1);
    printf("%s %s\n", token, token1);
    es = statement_list();
    return(es);
}


int maina()
{
    int es = 0;
    es = TESTscan();
    if (es > 0) printf("语法分析有错，编译停止！");
    else printf("语法分析成功！\n");
    if (es == 0)
    {
        es = TESTparse();
        if (es == 0) printf("语法分析成功！\n");
        else printf("语法分析错误！\n");
    }
    return 0;
}


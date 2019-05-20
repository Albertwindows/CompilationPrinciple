//
// Created by Albert on 2019/5/7.
//

#ifndef _CLION__PARSE_H
#define _CLION__PARSE_H

#include<stdio.h>
#include<ctype.h>
#include<string.h>

int TESTparse();
int program();
int statement();

int expression_stat();
int expression();
int bool_expr();
int additive_expr();


int term();
int factor();
int if_stat();
int while_stat();

int for_stat();
int write_stat();
int read_stat();
int declaration();


int declaration_list();
int statement_list();
int compound_stat();
int TESTscan();


#endif //_CLION__PARSE_H

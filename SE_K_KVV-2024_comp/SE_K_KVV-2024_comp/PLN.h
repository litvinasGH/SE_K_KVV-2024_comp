#pragma once
#include <iostream>
#include <locale>
#include <stack>
#include <set>
#include <vector>
#include <map>
#include "LT.h"  // ������� ������
#include "IT.h"  // ������� ���������������

#define EXP1 28 // ������� ������� ���������
#define EXP2 50 // ������� ������� ���������
#define EXP3 66 // ������� �������� ���������
// � �.�.

/// <summary>���������� �������� ������</summary>
///<param name="lextable_pos">������� ��������� � lextable</param>
///<param name="lextable">������� ������</param>
/// <param name="idtable">������� ���������������</param>
/// <returns>���������� ����������</returns>
bool PolishNotation( // ���������� �������� ������ � ������� ������
    int lextable_pos,
    LT::LexTable& lextable, 
    IT::IdTable& idtable     
);

// PolishNotation() == true  ���������� �������� ������ ��������� �������
// PolishNotation() == false ���������� �������� ������ �� ���������


#pragma once
#include <iostream>
#include <locale>
#include <stack>
#include <set>
#include <vector>
#include <map>
#include "LT.h"  // таблица лексем
#include "IT.h"  // таблица идентификаторов

#define EXP1 28 // позиция первого выражения
#define EXP2 50 // позиция второго выражения
#define EXP3 66 // позиция третьего выражения
// и т.д.

/// <summary>построение польской записи</summary>
///<param name="lextable_pos">позиция выражения в lextable</param>
///<param name="lextable">таблица лексем</param>
/// <param name="idtable">таблица идентификаторов</param>
/// <returns>Успешность построения</returns>
bool PolishNotation( // построение польской записи в таблице лексем
    int lextable_pos,
    LT::LexTable& lextable, 
    IT::IdTable& idtable     
);

// PolishNotation() == true  построение польской записи выполнено успешно
// PolishNotation() == false построение польской записи не выполнено


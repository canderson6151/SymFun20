
//
// Author: Chris Anderson  
// (C) UCLA 2012 
//

/*
#############################################################################
#
# Copyright 1996-2019 Chris Anderson
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the Lesser GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# For a copy of the GNU General Public License see
# <http://www.gnu.org/licenses/>.
#
#############################################################################
*/
#include <cstring>
#include <cmath>

#include "SCC_OperatorLib.h"
using namespace std;

#ifndef REAL_OPERATOR_LIB_
#define REAL_OPERATOR_LIB_

namespace SCC
{
class  RealOperatorLib : public SCC::OperatorLib
{

public :

	RealOperatorLib()
	{
	    const char* LibSymbols [] =
	    {"+", "-", "+", "-", "*", "/","^","sin", "cos",
	    "tan","asin","acos","atan","atan2",
	    "sinh","cosh","tanh",
	    "ceil","exp","abs","floor","fmod","log","log10","sqrt","pow"};

	     Symbols = new const char*[operatorCount];
	     for(int i = 0; i <  operatorCount; ++i)
	     {
	    	 Symbols[i] = LibSymbols[i];
	     }

	     int PriorityValues [] =
	     {3,3,5,5,4,4,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

	     Priority = new int[operatorCount];
	     for(int i = 0; i <  operatorCount; ++i)
	     {
	    	 Priority[i] = PriorityValues [i];
	     }

	     int  ArgCountValues[] =
	     {1,1,2,2,2,2,2,1,1,1,1,1,1,2,1,1,1,1,1,1,1,2,1,1,1,2};
	     ArgCount = new int[operatorCount];

	     for(int i = 0; i <  operatorCount; ++i)
	     {
	    	 ArgCount[i] = ArgCountValues[i];
	     }


	     void* FunctionArrayValues [] =
	     {
	     (void*)SCC::RealOperatorLib::Plus,
	     (void*)SCC::RealOperatorLib::Minus,
	     (void*)SCC::RealOperatorLib::Add,
	     (void*)SCC::RealOperatorLib::Subtract,
	     (void*)SCC::RealOperatorLib::Times,          // 5 //
	     (void*)SCC::RealOperatorLib::Divide,
	     (void*)SCC::RealOperatorLib::Exponentiate,
	     (void*)SCC::RealOperatorLib::Sin,
	     (void*)SCC::RealOperatorLib::Cos,
	     (void*)SCC::RealOperatorLib::Tan,            // 10 //
	     (void*)SCC::RealOperatorLib::Asin,
	     (void*)SCC::RealOperatorLib::Acos,
	     (void*)SCC::RealOperatorLib::Atan,
	     (void*)SCC::RealOperatorLib::Atan2,           //14//
	     (void*)SCC::RealOperatorLib::Sinh,
	     (void*)SCC::RealOperatorLib::Cosh,
	     (void*)SCC::RealOperatorLib::Tanh,
	     (void*)SCC::RealOperatorLib::Ceil,
	     (void*)SCC::RealOperatorLib::Exp,
	     (void*)SCC::RealOperatorLib::Abs,           // 20 //
	     (void*)SCC::RealOperatorLib::Floor,
	     (void*)SCC::RealOperatorLib::Fmod,
	     (void*)SCC::RealOperatorLib::Log,
	     (void*)SCC::RealOperatorLib::Log10,           // 24 //
	     (void*)SCC::RealOperatorLib::Sqrt,            // 25 //
	     (void*)SCC::RealOperatorLib::Pow
	     };

	     FunctionArray = new void*[operatorCount];
	     for(int i = 0; i <  operatorCount; ++i)
	     {
	    	 FunctionArray[i] = FunctionArrayValues[i];
	     }
	}

	~RealOperatorLib()
	{
		delete [] Symbols;
		delete [] Priority;
		delete [] ArgCount;
		delete [] FunctionArray;
	}


    int getOperatorIndex(const char* Sym) const
    {
        int ireturn = -1;
        int i;
    	for(i=0; i< operatorCount; i++)
        {
    	if(strcmp(Sym,Symbols[i]) == 0) ireturn = i;
        }
        return ireturn;
    }

    int getUnaryOperatorIndex(const char* Sym) const
    {
        int ireturn = -1;
    	if(strcmp(Sym,"+") == 0) ireturn = 0;
        if(strcmp(Sym,"-") == 0) ireturn = 1;
        return ireturn;
    }

    int getBinaryOperatorIndex(const char* Sym) const
    {
        int ireturn = -1;
    	if(strcmp(Sym,"+") == 0) ireturn = 2;
        if(strcmp(Sym,"-") == 0) ireturn = 3;
        return ireturn;
    }

    int getOperatorPriority(int index) const
    {
     	return Priority[index];
    }

    int getOperatorArgCount(int index) const
    {
     	return ArgCount[index];
    }

    int getOperatorCount() const
    {
     	return operatorCount;
    }

    const char* getOperatorSymbol(int index) const
    {
     	return Symbols[index];
    }
//
//  Unary Operators
//
    static void Plus(double** const argPtr)
    {	*argPtr[1] =  +(*argPtr[0]);  }

    static void Minus(double** const argPtr)
    {	*argPtr[1] =  -(*argPtr[0]);  }

    static void Add(double**  const argPtr)
    { 	*argPtr[2] =  (*argPtr[0])+(*argPtr[1]); }

    static void Subtract(double** const argPtr)
    { 	*argPtr[2] =  (*argPtr[0])-(*argPtr[1]); }

    static void Times(double** const argPtr)
    {	*argPtr[2] = (*argPtr[0])*(*argPtr[1]); }

    static void Divide(double** const argPtr)
    {	*argPtr[2] =  (*argPtr[0])/(*argPtr[1]); }

    static void Exponentiate(double** argPtr)
    {	*argPtr[2] =  pow(*argPtr[0],*argPtr[1]); }

    static void Sin(double** argPtr)
    { 	*argPtr[1] = sin(*argPtr[0]); }

    static void Cos(double** argPtr)
    {	*argPtr[1] = cos(*argPtr[0]); }

    static void Tan(double** argPtr)
    {	*argPtr[1] = tan(*argPtr[0]); }

    static void Asin(double** argPtr)
    {	*argPtr[1] = asin(*argPtr[0]); }

    static void Acos(double** argPtr)
    {	*argPtr[1] = acos(*argPtr[0]); }

    static void Atan(double** argPtr)
    {  *argPtr[1] = atan(*argPtr[0]); }

    static void Atan2(double** argPtr)
    { *argPtr[2] = atan2(*argPtr[0],*argPtr[1]);}

    static void Sinh(double** argPtr)
    {	*argPtr[1] = sinh(*argPtr[0]); }

    static void Cosh(double** argPtr)
    {	*argPtr[1] = cosh(*argPtr[0]); }

    static void Tanh(double** argPtr)
    {	*argPtr[1] = tanh(*argPtr[0]); }

    static void Ceil(double** argPtr)
    {	*argPtr[1] = ceil(*argPtr[0]); }

    static void Exp(double** argPtr)
    {	*argPtr[1] = exp(*argPtr[0]); }

    static void Abs(double** argPtr)
    {	*argPtr[1] = fabs(*argPtr[0]); }

    static void Floor(double** argPtr)
    {	*argPtr[1] = floor(*argPtr[0]); }

    static void Fmod(double** argPtr)
    { *argPtr[2] = fmod(*argPtr[0],*argPtr[1]);}

    static void Log(double** argPtr)
    {	*argPtr[1] = log(*argPtr[0]); }

    static void Log10(double** argPtr)
    {	*argPtr[1] = log10(*argPtr[0]); }

    static void Sqrt(double** argPtr)
    {	*argPtr[1] = sqrt(*argPtr[0]); }

    static void Pow(double** argPtr)
    { *argPtr[2] = pow(*argPtr[0],*argPtr[1]);}



    constexpr static int  operatorCount = 26;

    void**  FunctionArray;
    const char** Symbols;
    int*         Priority;
    int*         ArgCount;
};
}
#endif


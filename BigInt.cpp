#include <iostream>
#include <string>
#include<vector>
#include "BigInt.h"


std::vector<unsigned int> add(std::vector<unsigned int> lhs, std::vector<unsigned int> rhs) {
    int length = max(lhs.size(), rhs.size());
    int carry = 0;
    int sumOfCol;
    std::vector<unsigned int> result;

    while (lhs.size() < length) 
      {lhs.insert(lhs.begin(),0);}
    while (rhs.size() < length) 
      {rhs.insert(rhs.begin(),0);}
    
    for (int i = length-1; i >= 0; i--) 
    {
      sumOfCol = lhs[i] + rhs[i] + carry;
      carry = sumOfCol/10000;
      result.push_back(sumOfCol % 10000);
    }
    
    if (carry!=0)
    {
      result.push_back(carry);
    }
    return result;
}

std::vector<unsigned int> subtract(std::vector<unsigned int> lhs, std::vector<unsigned int> rhs) {
    int length = max(lhs.size(), rhs.size());
    int diff;
    std::vector<unsigned int> result;

    while (lhs.size() < length) 
      {lhs.insert(lhs.begin(),0);}
    while (rhs.size() < length) 
      {rhs.insert(rhs.begin(),0);}

    for (int i = length-1; i >= 0; i--) 
    {
        diff = lhs[i] - rhs[i];
        if (diff >= 0)
            {result.push_back(diff);}
        else {
            int j = i - 1;
            while (j >= 0) 
            {
                lhs[j] = (lhs[j] - 1);
                if (lhs[j] != 9999) 
                    break;
                else 
                    j--;
            }
            result.push_back(diff+10000);
        }
      
    }
    return result;
}


std::vector<unsigned int> multiply(std::vector<unsigned int> num1, std::vector<unsigned int> num2) 
{ 
    int len1 = num1.size(); 
    int len2 = num2.size(); 
    if (len1 == 0 || len2 == 0) 
      {return {0};}
    std::vector<unsigned int> result(len1 + len2, 0);  
    int i_n1 = 0;  
    int i_n2 = 0;  
    
    for (int i = len1-1; i >= 0; i--) 
    { 
        int carry = 0; 
        int n1 = num1[i]; 
        i_n2 = 0;             
        for (int j = len2-1; j >= 0; j--) 
        { 
            int n2 = num2[j]; 

            int sum = n1*n2 + result[i_n1 + i_n2] + carry; 
            carry = sum/10000;
            result[i_n1 + i_n2] = sum % 10000; 
  
            i_n2++; 
        } 
        if (carry > 0) 
            result[i_n1 + i_n2] += carry; 
        i_n1++; 
    } 
    int i = result.size() - 1; 
    while (i>=0 && result[i] == 0) 
      {i--;} 
    if (i == -1) 
      {return {0};}  
    return result;
} 


    void bigInteger::toInteger()
    {
        if(representation[0]=='-' || signOfInteger==1)
        {
            signOfInteger=1;
            representation = representation.substr(1,representation.size()-1);
        }
        else
        {
            signOfInteger=0;
        }
        int i=representation.size()-1;
        int number=0;
        std::string r;
        for(i=representation.size()-1;i>=0;i-=4)
        {
            if(i<=3)
            {
                r = representation.substr(0, i+1);
                v.insert(v.begin(),stoi(r));
            }
            else
            {
                r = representation.substr(i-3, 4);
                v.insert(v.begin(),stoi(r));
            }
            
        }
    }
    void bigInteger::toString()
        {
            std::string res="";
            int i;
            for(i=this->v.size()-1;i>=0;i--)
                {
                    int r = this->v[i];
                    if(r < 10 )
                        {res.append("0");}
                    if(r < 100 )
                        {res.append("0");}
                    if(r < 1000 )
                        {res.append("0");}
                    res.append(std::to_string(r));
                }
                this->representation=res;
        }
    void bigInteger::displayNumber()
    {
        if(this->signOfInteger)
        {
            std::cout<<"-";
        }
        std::cout<<this->representation;
    }

 bigInteger multiplyBigInteger( bigInteger a, bigInteger b)
 {
     bigInteger c;
     c.v = multiply(a.v,b.v);
     c.signOfInteger = (a.signOfInteger+b.signOfInteger) % 2;
     c.toString();
     return c;
 }
 bigInteger addBigInteger( bigInteger a, bigInteger b)
 {
     int length = max(a.representation.size(), b.representation.size());
     while (a.representation.size() < length) 
      {a.representation.insert(0,"0");}
    while (b.representation.size() < length) 
      {b.representation.insert(0,"0");}
     bigInteger c;
     if(a.signOfInteger == b.signOfInteger)
     {
         c.v = add(a.v,b.v);
         c.signOfInteger=a.signOfInteger;
     }
     else{
                 if(a.representation.compare(b.representation)<0)
                 {
                     c.v = subtract(b.v,a.v);
                     c.signOfInteger=b.signOfInteger;
                 }
                 else {
                    if(a.representation.compare(b.representation)>0)
                     {
                         c.v = subtract(a.v,b.v);
                         c.signOfInteger=a.signOfInteger;
                     }
                     else
                     {
                            c.v={0};
                            c.signOfInteger=0;
                     }
                 }
        }
        c.toString();
        return c;
 }
 bigInteger subtractBigInteger( bigInteger a, bigInteger b)
 {
    int length = max(a.representation.size(), b.representation.size());
     while (a.representation.size() < length) 
      {a.representation.insert(0,"0");}
    while (b.representation.size() < length) 
      {b.representation.insert(0,"0");}
     bigInteger c;
     if(a.signOfInteger != b.signOfInteger)
     {
         c.v = add(a.v,b.v);
         c.signOfInteger=a.signOfInteger;
     }
     else{
                 if(a.representation.compare(b.representation)<0)
                 {
                     c.v = subtract(b.v,a.v);
                     c.signOfInteger = (1+b.signOfInteger) % 2;
                 }
                 else {
                    if(a.representation.compare(b.representation)>0)
                     {
                         c.v = subtract(a.v,b.v);
                         c.signOfInteger = a.signOfInteger;
                     }
                     else
                     {
                            c.v={0};
                            c.signOfInteger=0;
                     }
                 }
        }
        c.toString();
        return c;
 }
 bigInteger modulo(bigInteger a, bigInteger b)
 {
    if(a.representation.compare(b.representation)<0)
    {
            return a;
    }
    while(a.representation.compare(b.representation) > 0)
    {
        a = subtractBigInteger(b, a);
    }
    return a;
 }
int main() 
{
    using namespace std;
    bigInteger r1,r2,r3,r4;
    cin>>r1.representation>>r2.representation;
    r1.toInteger();
    r2.toInteger();
    r3 = addBigInteger(r1,r2);
    r3.toInteger();
    cout<<"Addition of the numbers :";
    r3.displayNumber();
    r3 = multiplyBigInteger(r1,r2);
    r3.toInteger();
    cout<<endl;
    cout<<"Multiplication of the numbers :";
    r3.displayNumber();
    r4 = subtractBigInteger(r1,r2);
    r4.toInteger();
    cout<<endl;
    cout<<"Subtraction of the numbers :";
    r4.displayNumber();
    return 0;
}

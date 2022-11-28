#ifndef _mstest
#define _mstest

#define setup() std::cout << "\n\n" << __FUNCTION_NAME__ << "\n\n"

#include "my_string.h"

#include <iostream>
#include <string>

using namespace std;
using mstring = my_string<char>;

void TEST1()    // https://boycoding.tistory.com/178
{
    setup();
    mstring myName("Alex");
    std::cout << "My name is: " << myName;
}

void TEST2()    // https://boycoding.tistory.com/178
{
    setup();
    std::cout << "Enter your full name: ";
    mstring name;
    std::cin >> name; // this won't work as expected since std::cin breaks on whitespace

    std::cout << "Enter your age: ";
    mstring age;
    std::cin >> age;

    std::cout << "Your name is " << name << " and your age is " << age;
}

void TEST3()    // https://boycoding.tistory.com/178
{
    setup();
    
    mstring a("45");
    mstring b("11");

    std::cout << a + b << "\n"; // a and b will be appended, not added
    a += " volts";
    std::cout << a;
}

void TEST4()
{
    setup();
    
    mstring myName("Alex");
    std::cout << myName << " has " << myName.length() << " characters\n";
}

void TEST5()    // https://blockdmask.tistory.com/338
{
    setup();
    
    mstring str1 = "BlockDMask";
    mstring str2("BlogBlogBlogBlog");
    mstring str3(str1);
 
    //mstring을 생성하는 다양한 방법.
    std::cout << "==> onstructor" << std::endl;
    std::cout << "str1 = \"BlockDMask\" \n : " << str1 << std::endl << std::endl;
    std::cout << "str2(\"BlogBlogBlogBlog\") \n : " << str2 << std::endl << std::endl;
    std::cout << "str3(str1) \n : " << str3 << std::endl << std::endl;
 
    //push_back, pop_back
    std::cout << std::endl;
    std::cout << "==> mstring front, back example." << std::endl;
    str1.push_back('1');
    std::cout << "str1.push_back('1') : " << str1 << std::endl;
    str1.push_back('2');
    std::cout << "str1.push_back('2') : " << str1 << std::endl;
    str1.pop_back();
    std::cout << "str1.pop_back() :  " << str1 << std::endl;
    str1.pop_back();
    std::cout << "str1.pop_back() :  " << str1 << std::endl;
    str1.pop_back();
    std::cout << "str1.pop_back() :  " << str1 << std::endl;
 
    //operator+ stirng 덧셈.
    std::cout << std::endl;
    std::cout << "==> str1 += str2" << std::endl;
    str1 += str2;
    std::cout << str1 << std::endl;
           
    std::cout << std::endl;
}

void TEST6()    // https://blockdmask.tistory.com/338
{
    setup();
    
    mstring str2 = "BlogBlogBlogBlog";
 
    cout << "==> str2 original" << endl;
    cout << "str2 : " << str2 << endl;
    cout << "str2.size() : " << str2.size() << endl;
    cout << "str2.length() : " << str2.length() << endl;
    cout << "str2.capacity() : " << str2.capacity() << endl;
    
    cout << endl;
    str2.resize(4);
    cout << "==> str2.resize(4)" << endl;
    cout << "str2 : " << str2 << endl;
    cout << "str2.size() : " << str2.size() << endl;
    cout << "str2.length() : " << str2.length() << endl;
    cout << "str2.capacity() : " << str2.capacity() << endl;
 
    cout << endl;
    str2.shrink_to_fit();
    cout << "==> str2.shrink_to_fit()" << endl;
    cout << "str2 : " << str2 << endl;
    cout << "str2.size() : " << str2.size() << endl;
    cout << "str2.length() : " << str2.length() << endl;
    cout << "str2.capacity() : " << str2.capacity() << endl;
 
    cout << endl;
    str2.clear();
    cout << "==> str2.clear()" << endl;
    cout << "str2 : " << str2 << endl;
    cout << "str2.size() : " << str2.size() << endl;
    cout << "str2.length() : " << str2.length() << endl;
    cout << "str2.capacity() : " << str2.capacity() << endl;
 
    cout << endl;
}

void TEST7()    // https://blockdmask.tistory.com/338
{
    mstring str1 = "BlockDMask";
    mstring str2 = "BlogBlogBlogBlog";
 
    cout << "str1 : " << str1 << endl;
    cout << "str2 : " << str2 << endl;
    cout << endl;
    
    //string substr example.
    cout << "str1.substr(5) : " << str1.substr(5) << endl;
    cout << "str1.substr(5,1) : " << str1.substr(5,1) << endl;
    
    //string replace example.
    cout << "str1.replace(5, 2, str2) : " << str1.replace(5, 2, str2) << endl;
 
    //string swap example.
    cout << endl;
    mstring str3 = "C++ example";
    cout << "str2 : " << str2 << endl;
    cout << "str3 : " << str3 << endl;
 
    cout << endl;
    cout << "swap(str2, str3)" << endl;
    cout << "str2 : " << str2 << endl;
    cout << "str3 : " << str3 << endl;
 
    cout << endl;
}

void TEST8()    // https://blockdmask.tistory.com/338
{
    string str1 = "BlockDMask";
    string str2 = "BlogBlogBlogBlog";
 
    cout << "str1 : " << str1 << endl;
    cout << "str2 : " << str2 << endl;
    cout << endl;
 
    //find
    cout << "==> string find example." << endl;
    cout << "str1.find(\"DM\") : " << str1.find("DM") << endl;
    cout << "str2.find(\"Blog\") : " << str2.find("Blog") << endl;
    cout << "str2.find(\"Blog\", 5) : " << str2.find("Blog", 5) << endl;
 
    //operator[], at
    cout << endl;
    cout << "==> string operator[], at() example." << endl;
    cout << "str1[0] : " << str1[0] << endl;
    cout << "str1[3] : " << str1[3] << endl;
    cout << "str1[str1.size()-1] : " << str1[str1.size() - 1] << endl;
    cout << endl;
    cout << "str1.at(0) : " << str1.at(0) << endl;
    cout << "str1.at(3) : " << str1.at(3) << endl;
    cout << "str1.at(str1.size()-1) : " << str1.at(str1.size() - 1) << endl;
 
    //front, back
    cout << endl;
    cout << "==> string front, back example." << endl;
    cout << "str1[0] : " << str1[0] << endl;
    cout << "str1.at(0) : " << str1.at(0) << endl;
    cout << "str1.front() : " << str1.front() << endl;
    cout << endl;
    cout << "str1[str1.size()-1] : " << str1[str1.size() - 1] << endl;
    cout << "str1.at(str1.size()-1) : " << str1.at(str1.size() - 1) << endl;
    cout << "str1.back() : " << str1.back() << endl;
 
    cout << endl;
}

//-------------------- SangHoon Test -------------------------------

void TEST9( )       // https://coding-factory.tistory.com/703
{
    setup( );

    mstring str = "Hello World"; //문자열 선언

    cout << str.at( 4 ) << endl; //at(index): 문자열 index 위치의 문자를 반환
    cout << str[ 4 ] << endl; //문자열[index]: 배열처럼 index의 위치의 문자를 반환
    cout << str.front( ) << endl; //문자열 맨 앞의 문자를 반환
    cout << str.back( ) << endl; //문자열 맨 끝의 문자를 반환
}

void TEST10( )       // https://coding-factory.tistory.com/703
{
    setup( );

    mstring str = "Hello World"; //문자열 선언

    cout << str.length( ) << endl; //문자열의 길이를 반환
    cout << str.size( ) << endl; //문자열이 사용하고 있는 Size를 반환
    cout << str.capacity( ) << endl; //문자열에 할당된 메모리 크기 반환
}

void TEST11( )      // https://rebro.kr/53
{
    setup( );

    mstring str1 = "abcdef";
    mstring str2 = "bbbbbb";
    mstring str3 = "aaaa";
    mstring str4 = "abcdef";
    cout << ( str1 < str2 ) << ' ' << ( str1 < str3 ) << ' ' << ( str1 == str4 ) << endl;
    //1 : true , 0 : false

    str1 += "A";
    cout << str1 << '\n';
    str1 = str1 + str2;
    cout << str1 << '\n';
}

void TEST12( )      // https://rebro.kr/53
{
    setup( );

    mstring str = "apple";
    mstring str2 = "banana";
    str.append( str2 );            cout << str << '\n';
    str.append( str2, 1, 3 );      cout << str << '\n';
    str.append( 3, 'k' );          cout << str << '\n';
    str.clear( );                 cout << str << '\n';
    str.assign( "apple" );         cout << str << '\n';
    str.insert( 2, str2 );         cout << str << '\n';
    str.replace( 3, 3, "ttt" );    cout << str << '\n';
    str.erase( 0, 2 );             cout << str << '\n';
    str.erase( );                 cout << str << '\n';
    str.push_back( 'a' );          cout << str << '\n';
    str.push_back( 'b' );          cout << str << '\n';
    str.pop_back( );              cout << str << '\n';
}

#endif
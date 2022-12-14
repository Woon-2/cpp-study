#ifndef _dog
#define _dog

#include <iostream>

class Dog
{
public:
    Dog() noexcept : id{++numid} { std::cout << "Dog 생성\n"; }
    ~Dog() { std::cout << "Dog 소멸\n"; }
    Dog(const Dog& o) noexcept : id{o.id} { std::cout << "Dog 복사 생성\n"; }
    Dog(Dog&& o) noexcept : id{o.id} { std::cout << "Dog 이동 생성\n"; o.id = 0; }
    Dog& operator=(const Dog& o) noexcept
    {
        if (this != &o)
        {
            id = o.id;
            std::cout << "Dog 복사 할당\n";
        }
        
        return *this;
    }
    Dog& operator=(Dog&& o) noexcept
    {
        if (this != &o)
        {
            id = o.id;
            o.id = 0;
            std::cout << "Dog 이동 할당\n";
        }
        
        return *this;
    }
    void growl() const noexcept { std::cout << "으르렁\n"; }
    void bark() const noexcept { std::cout << "왈왈\n"; }
    const int getid() const noexcept { return id; }

private:
    static int numid;
    int id;

};

const bool operator<(const Dog& lhs, const Dog& rhs) noexcept;
const bool operator>(const Dog& lhs, const Dog& rhs) noexcept;
const bool operator<=(const Dog& lhs, const Dog& rhs) noexcept;
const bool operator>=(const Dog& lhs, const Dog& rhs) noexcept;
const bool operator==(const Dog& lhs, const Dog& rhs) noexcept;
const bool operator!=(const Dog& lhs, const Dog& rhs) noexcept;

#endif
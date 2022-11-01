#ifndef _my_string
#define _my_string

#include <cstring>

class my_string
{
public:
	const char& at(const size_t n) const;
	const char& front() const;
	const char* c_str() const;
	const char* data() const;
	bool empty() const;
	int size() const;
	int length() const;
	void reserve(const size_t n);
	size_t capacity();
	void shrink_to_fit();
	void resize(const size_t n);
	void clear();
	void insert(const size_t n, const char* other);
	void erase(const size_t n, const size_t m);
	void push_back(const char c);
	void pop_back();
	void append(const char c);
	int compare(const char* other) const;
	void replace(const char* A, const char* B);
	const my_string& substr(const size_t n, const size_t m);
	int find(const char* str) const;

private:
	size_t	byteObtained;
	char*	myString;
	int		m_length;
};
#endif

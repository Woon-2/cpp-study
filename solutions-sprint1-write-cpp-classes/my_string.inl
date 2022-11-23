#include "my_string.h"

template <class CharT>
constexpr
my_string<CharT>::
my_string() noexcept
    : sz{ std::size_t{ 0 } }, cap{ std::size_t{ 0 } },
      dat{ _construct<CharT>(_safe_cap(), CharT{}) }
{
    
}

template <class CharT>
my_string<CharT>::
my_string(std::size_t count, CharT ch)
    : sz{ count }, cap{ closest_bin(sz) },
      dat{ _construct<CharT>(_safe_cap(), CharT{}) }
{
    std::fill_n(this->data(), this->size(), ch);
}

template <class CharT>
my_string<CharT>::
my_string(const my_string& other, std::size_t pos,
          std::size_t count)
    : sz{ std::min(count, other.size() -
                   _check_i_is_in_size(pos, other,
                                       "pos > other.size()")) },
      cap{ closest_bin(sz) },
      dat{ _construct<CharT>(_safe_cap(), CharT{}) }
{
    std::copy(other.data() + pos,
              other.data() + pos + this->size(),
              this->data());
}

template <class CharT>
my_string<CharT>::
my_string(const CharT* str, std::size_t count)
    : sz{ count }, cap{ closest_bin(sz) },
      dat{ _construct<CharT>(_safe_cap(), CharT{}) }
{
    std::copy(str, str + this->size(), this->data());
}

template <class CharT>
my_string<CharT>::
my_string(const CharT* str)
    : my_string(str, _strlen(str))
{

}

template <class CharT>
my_string<CharT>::
my_string(const my_string& other)
    : my_string(other, std::size_t{ 0 }, npos)
{

}

template <class CharT>
my_string<CharT>::my_string(my_string&& other)
    : my_string()
{
    this->swap(other);
}

template <class CharT>
my_string<CharT>::~my_string()
{
    _destroy(data());
}

template <class CharT>
my_string<CharT>&
my_string<CharT>::
operator=(const my_string& other)
{
    return this->assign(other);
}

template <class CharT>
my_string<CharT>&
my_string<CharT>::
operator=(my_string&& other) noexcept
{
    return this->assign(std::move(other));
}

template <class CharT>
my_string<CharT>&
my_string<CharT>::
operator=(const CharT* str)
{
    return this->assign(str);
}

template <class CharT>
my_string<CharT>&
my_string<CharT>::
operator=(CharT ch)
{
    return this->assign(&ch, 1);
}

template <class CharT>
my_string<CharT>&
my_string<CharT>::
assign(std::size_t count, CharT ch)
{
    return this->replace(std::size_t{ 0 }, this->size(),
                         count, ch);
}

template <class CharT>
my_string<CharT>&
my_string<CharT>::
assign(const my_string& str, std::size_t pos,
       std::size_t count)
{
    return this->replace(std::size_t{ 0 }, this->size(), str,
                         _check_i_is_in_size(pos, str,
                                             "pos > str.size()"),
                         count);
}

template <class CharT>
my_string<CharT>&
my_string<CharT>::
assign(my_string&& str) noexcept
{
    this->swap(str);
    
    return *this;
}

template <class CharT>
my_string<CharT>&
my_string<CharT>::
assign(const CharT* str, std::size_t count)
{
    return this->replace(std::size_t{ 0 }, this->size(),
                         str, count);
}

template <class CharT>
my_string<CharT>&
my_string<CharT>::
assign(const CharT* str)
{
    return this->assign(str, _strlen(str));
}

template <class CharT>
constexpr
CharT&
my_string<CharT>::
at(std::size_t pos)
{
    return const_cast<CharT&>(
        static_cast<const my_string&>(*this).at(pos));
}

template <class CharT>
constexpr
const CharT&
my_string<CharT>::
at(std::size_t pos) const
{
    return (*this)[
        debug_check_out_of_range(pos, std::size_t{ 0 },
                                 this->size() - 1,
                                 "pos >= size()")];
}

template <class CharT>
constexpr
CharT&
my_string<CharT>::
operator[](std::size_t index)
{
    // The behavior is undefined if index > size() : cppreference
    return const_cast<CharT&>(
        static_cast<const my_string&>(*this)[index]);
}

template <class CharT>
constexpr
const CharT&
my_string<CharT>::
operator[](std::size_t index) const
{
    return this->data()[index];
}

template <class CharT>
constexpr
CharT&
my_string<CharT>::
front()
{
    return const_cast<CharT&>(
        static_cast<const my_string&>(*this).front());
}

template <class CharT>
constexpr
const CharT&
my_string<CharT>::
front() const
{
    return (*this)[std::size_t{ 0 }];
}

template <class CharT>
constexpr
CharT&
my_string<CharT>::
back()
{
    return const_cast<CharT&>(
        static_cast<const my_string&>(*this).back());
}

template <class CharT>
constexpr
const CharT&
my_string<CharT>::
back() const
{
    // The behavior is undefined if empty() == true.
    // : cppreference
    return (*this)[this->size() - 1];
}

template <class CharT>
constexpr
CharT*
my_string<CharT>::
data() noexcept
{
    return const_cast<CharT*>(
        static_cast<const my_string&>(*this).data() );
}

template <class CharT>
constexpr
const CharT*
my_string<CharT>::
data() const noexcept
{
    return this->dat;
}

template <class CharT>
constexpr
const CharT*
my_string<CharT>::
c_str() const noexcept
{
    return this->data();
}

template <class CharT>
constexpr
bool
my_string<CharT>::
empty() const noexcept
{
    return this->size() == std::size_t{ 0 };
}

template <class CharT>
constexpr
std::size_t
my_string<CharT>::
size() const noexcept
{
    return this->sz;
}

template <class CharT>
constexpr
std::size_t
my_string<CharT>::
length() const noexcept
{
    return this->size();
}

template <class CharT>
constexpr
std::size_t
my_string<CharT>::
capacity() const noexcept
{
    return this->cap;
}

template <class CharT>
void
my_string<CharT>::
reserve(std::size_t new_cap)
{
    if (this->capacity() < new_cap)
        my_string{ new_cap, *this }.swap(*this);
}

template <class CharT>
void
my_string<CharT>::
shrink_to_fit()
{
    my_string{ this->size(), *this }.swap(*this);
}

template <class CharT>
void
my_string<CharT>::
clear() noexcept
{
    this->_set_sz(std::size_t{ 0 });
}

template <class CharT>
my_string<CharT>&
my_string<CharT>::
insert(std::size_t index, std::size_t count, CharT ch)
{
    return this->replace(_check_i_is_in_size(index, *this,
                                             "index > size()"),
                         std::size_t{ 0 }, ch, count);
}
    
template <class CharT>
my_string<CharT>&
my_string<CharT>::
insert(std::size_t index, const CharT* str)
{
    return this->insert(index, str, _strlen(str));
}   

template <class CharT>
my_string<CharT>&
my_string<CharT>::
insert(std::size_t index, const CharT* str, std::size_t count)
{
    return this->replace(_check_i_is_in_size(index, *this,
                                             "index > size()"),
                         std::size_t{ 0 }, str, count);
}   

template <class CharT>
my_string<CharT>&
my_string<CharT>::
insert(std::size_t index, const my_string& str)
{
    return this->insert(index, str, std::size_t{ 0 });
}

template <class CharT>
my_string<CharT>&
my_string<CharT>::
insert(std::size_t index, const my_string& str,
       std::size_t index_str, std::size_t count)
{
    return this->insert(_check_i_is_in_size(index_str, str,
                                            "index_str > str.size()"),
                        str.data() + index_str,
                        std::min(count, str.size() - index_str));
}

template <class CharT>
my_string<CharT>&
my_string<CharT>::
replace(std::size_t pos, std::size_t count, const my_string& str)
{
    return this->replace(pos, count, str, std::size_t{ 0 });
}

template <class CharT>
my_string<CharT>&
my_string<CharT>::
replace(std::size_t pos, std::size_t count, const my_string& str,
        std::size_t pos_str, std::size_t count_str)
{
    // if count_str == npos or if would extend past str.size(),
    // [pos_str, str.size()) is used to replace.
    return this->replace(pos, count, str.data() + pos_str,
                         std::min(count_str, str.size() -
                                  _check_i_is_in_size(pos_str,
                                                      str,
                                                      "pos_str > str.size()")));
}

template <class CharT>
my_string<CharT>&
my_string<CharT>::
replace(std::size_t pos, std::size_t count, const CharT* str,
        std::size_t count_str)
{
    this->_mutate(_check_i_is_in_size(pos, *this,
                                      "pos > size()"),
                  count, str, count_str);
    
    return *this;
}

template <class CharT>
my_string<CharT>&
my_string<CharT>::
replace(std::size_t pos, std::size_t count, const CharT* str)
{
    return this->replace(pos, count, str, _strlen(str));
}

template <class CharT>
my_string<CharT>&
my_string<CharT>::
replace(std::size_t pos, std::size_t count,
        std::size_t count_ch, CharT ch)
{
    this->_mutate(_check_i_is_in_size(pos, *this, "pos > size()"),
                  count, ch, count_ch);
    
    return *this;
}

template <class CharT>
void
my_string<CharT>::
push_back(CharT ch)
{
    this->_mutate(this->size(), std::size_t{ 0 },
                  ch, std::size_t{ 1 });
}

template <class CharT>
void
my_string<CharT>::
pop_back()
{
    this->_mutate(this->size() - 1, std::size_t{ 1 },
                  nullptr, std::size_t{ 0 });
}

template <class CharT>
my_string<CharT>&
my_string<CharT>::
append(std::size_t count, CharT ch)
{
    return this->insert(this->size(), count, ch);
}   

template <class CharT>
my_string<CharT>&
my_string<CharT>::
append(const my_string& str)
{
    return this->append(str, std::size_t{ 0 });
}   

template <class CharT>
my_string<CharT>&
my_string<CharT>::
append(const my_string& str, std::size_t pos,
       std::size_t count)
{
    return this->append(str.data() +
                        _check_i_is_in_size(pos, str,
                                            "pos > str.size()"),
                        std::min(count, str.size() - pos));
}   

template <class CharT>
my_string<CharT>&
my_string<CharT>::
append(const CharT* str)
{
    return this->append(str, _strlen(str));
}   

template <class CharT>
my_string<CharT>&
my_string<CharT>::
append(const CharT* str, std::size_t count)
{
    return this->insert(this->size(), str, count);
}

template <class CharT>
my_string<CharT>&
my_string<CharT>::
operator+=(const my_string& str)
{
    return this->append(str);
}

template <class CharT>
my_string<CharT>&
my_string<CharT>::
operator+=(CharT ch)
{
    return this->push_back(ch);
}

template <class CharT>
my_string<CharT>&
my_string<CharT>::
operator+=(const CharT* str)
{
    return this->append(str);
}

template <class CharT>
my_string<CharT>&
my_string<CharT>::
erase(std::size_t index, std::size_t count)
{
    this->_mutate(_check_i_is_in_size(index, *this,
                                      "index > size()"),
                  std::min(count, this->size() - index),
                  nullptr, std::size_t{ 0 });
    
    return *this;
}

template <class CharT>
constexpr
int
my_string<CharT>::
compare(const my_string& str) const noexcept
{
    return this->compare(std::size_t{ 0 }, this->size(), str);
}

template <class CharT>
constexpr
int
my_string<CharT>::
compare(std::size_t pos, std::size_t count,
        const my_string& str) const
{
    return this->compare(pos, count, str, std::size_t{ 0 });
}

template <class CharT>
constexpr
int
my_string<CharT>::
compare(std::size_t pos1, std::size_t count1,
        const my_string& str, std::size_t pos2,
        std::size_t count2) const
{
    return this->compare(_check_i_is_in_size(pos1, *this,
                                             "pos1 > size()"),
                         count1, str.data() +
                         _check_i_is_in_size(pos2, str,
                                             "pos2 > str.size()"),
                         count2);
}

template <class CharT>
constexpr
int
my_string<CharT>::
compare(const CharT* str) const
{
    return this->compare(std::size_t{ 0 }, this->size(),
                         str);
}

template <class CharT>
constexpr
int
my_string<CharT>::
compare(std::size_t pos, std::size_t count,
        const CharT* str) const
{
    return this->compare(std::size_t{ 0 }, count, str,
                         _strlen(str));
}

template <class CharT>
constexpr
int
my_string<CharT>::
compare(std::size_t pos, std::size_t count1,
        const CharT* str, std::size_t count2) const
{
    auto my_len = std::min(count1, this->size() -
                           _check_i_is_in_size(pos, *this,
                                               "pos > size()"));
    
    // Firstly, compare characters in common range
    int ret = _strncmp(this->data() + pos, str,
                       std::min(my_len, count2));
    
    if (!ret && my_len)
        // Secondly, compare lengths
        ret = my_len - count2;
        
    return ret;
}

template <class CharT>
constexpr
my_string<CharT>
my_string<CharT>::
substr(std::size_t pos, std::size_t count) const
{
    return my_string{*this,
                    _check_i_is_in_size(pos, *this, "pos > size()"),
                    count};
}

template <class CharT>
void
my_string<CharT>::
resize(std::size_t n)
{
    if (this->capacity() < n) this->reserve(n);
    
    _set_sz(n);
}

template <class CharT>
void
my_string<CharT>::
resize(std::size_t n, CharT ch)
{
    if (this->capacity() < n)
    {
        auto old_size = this->size();
        this->reserve(n);
        
        std::fill_n(this->data() + old_size,
                    this->size() - old_size, ch);
    }
    
    _set_sz(n);
}

template <class CharT>
void
my_string<CharT>::
swap(my_string& rhs) noexcept
{
    std::swap(this->sz, rhs.sz);
    std::swap(this->cap, rhs.cap);
    std::swap(this->dat, rhs.dat);
}

template <class CharT>
constexpr
std::size_t
my_string<CharT>::
find(const my_string& str, std::size_t pos) const noexcept
{
    return this->find(str.data(), pos, str.size());
}

template <class CharT>
constexpr
std::size_t
my_string<CharT>::
find(const CharT* str, std::size_t pos) const
{
    return this->find(str, pos, _strlen(str));
}

template <class CharT>
constexpr
std::size_t
my_string<CharT>::
find(const CharT* str, std::size_t pos,
     std::size_t count) const
{
    std::size_t ret =
        std::search(this->data() + std::min(this->size(), pos),
                    this->data() + this->size(), str, str + count)
        - this->data();
    
    if (ret == this->size()) ret = npos;
    
    return ret;
}

template <class CharT>
constexpr
std::size_t
my_string<CharT>::
find(CharT ch, std::size_t pos) const noexcept
{
    std::size_t ret =
        std::find(this->data() + std::min(this->size(), pos),
                  this->data() + this->size(), ch)
        - this->data();
        
    if (ret == this->size()) ret = npos;
    
    return ret;
}

template <class CharT>
my_string<CharT>::
my_string(std::size_t required_cap, const my_string& other)
    : sz{ std::min(other.sz, required_cap) },
      cap{ required_cap }, dat{ _construct<CharT>(_safe_cap(), CharT{}) }
{
    std::copy(other.data(), other.data() + this->size(),
              this->data());
}

template <class CharT>
std::size_t
my_string<CharT>::
_safe_cap() noexcept
{
    return capacity() + 1;
}

template <class CharT>
void
my_string<CharT>::
_set_sz(std::size_t n) noexcept
{
    this->sz = n;
    (*this)[n] = CharT{};
}

/**
 * data in range [this->data() + pos, this->data() + pos + len1]
 * is replaced with [str, str + len2].
 * exception unchecked.
*/
template <class CharT>
void
my_string<CharT>::
_mutate(std::size_t pos, std::size_t len1,
        const CharT* str, std::size_t len2)
{
    const std::size_t how_much = this->size() - pos - len1;
    const std::size_t new_sz = this->size() + len2 - len1;
    
    if (new_sz > this->capacity())
    {
        my_string tmp{ closest_bin(new_sz), *this };
        
        if (pos)
            std::copy(this->data(), this->data() + pos,
                      tmp.data());
        if (str && len2)
            std::copy(str, str + len2, tmp.data() + pos);
        if (how_much)
            std::copy(this->data() + pos + len1,
                      this->data() + this->size(),
                      tmp.data() + pos + len2);
            
        this->swap(tmp);
    }
    else
    {
        if (how_much)
            std::move(this->data() + pos + len1,
                      this->data() + this->size(),
                      this->data() + pos + len2);
        if (str && len2)
            std::copy(str, str + len2, this->data() + pos);
    }
    
    this->_set_sz(new_sz);
}

/**
 * data in range [this->data() + pos, this->data() + pos + len]
 * is replaced with ch of count.
 * exception unchecked.
*/
template <class CharT>
void
my_string<CharT>::
_mutate(std::size_t pos, std::size_t len, CharT ch,
        std::size_t count)
{
    const std::size_t how_much = this->size() - pos - len;
    const std::size_t new_sz = this->size() + count - len;
    
    if (new_sz > this->capacity())
    {
        my_string tmp{ count, ch };
        
        if (pos)
            std::copy(this->data(), this->data() + pos,
                      tmp.data());
        if (count)
            std::fill_n(tmp.data() + pos, count, ch);
        if (how_much)
            std::copy(this->data() + pos + len,
                      this->data() + this->size(),
                      tmp.data() + pos + count);
            
        this->swap(tmp);
    }
    else
    {
        if (count)
            std::fill_n(this->data() + pos, count, ch);
        if (how_much)
            std::move(this->data() + pos + len,
                      this->data() + this->size(),
                      this->data() + pos + count);
    }
    
    this->_set_sz(new_sz);
}

template <class CharT>
constexpr
my_string<CharT>
operator+(const my_string<CharT>& lhs,
          const my_string<CharT>& rhs)
{
    return __str_concat(lhs.data(), lhs.size(), rhs.data(), rhs.size());
}

template <class CharT>
constexpr
my_string<CharT>
operator+(const my_string<CharT>& lhs, const CharT* rhs)
{
    return __str_concat(lhs.data(), lhs.size(), rhs, _strlen(rhs));
}

template <class CharT>
constexpr
my_string<CharT>
operator+(const CharT* lhs, const my_string<CharT>& rhs)
{
    return __str_concat(lhs, _strlen(lhs), rhs.data(), rhs.size());
}

template <class CharT>
constexpr
my_string<CharT>
operator+(const my_string<CharT>& lhs, CharT rhs)
{
    return __str_concat(lhs.data(), lhs.size(), &rhs, std::size_t{ 1 });
}

template <class CharT>
constexpr
my_string<CharT>
operator+(CharT lhs, const my_string<CharT>& rhs)
{
    return __str_concat(&lhs, std::size_t{ 1 }, rhs.data(), rhs.size());
}

template <class CharT>
constexpr
my_string<CharT>
operator+(my_string<CharT>&& lhs, my_string<CharT>&& rhs)
{
    return std::move(lhs.append(rhs));
}

template <class CharT>
constexpr
my_string<CharT>
operator+(my_string<CharT>&& lhs, const my_string<CharT>& rhs)
{
    return std::move(lhs.append(rhs));
}

template <class CharT>
constexpr
my_string<CharT>
operator+(const my_string<CharT>& lhs, my_string<CharT>&& rhs)
{
    return std::move(rhs.insert(std::size_t{ 0 }, lhs));
}

template <class CharT>
constexpr
my_string<CharT>
operator+(my_string<CharT>&& lhs, const CharT* rhs)
{
    return std::move(lhs.append(rhs));
}

template <class CharT>
constexpr
my_string<CharT>
operator+(const CharT* lhs, my_string<CharT>&& rhs)
{
    return std::move(rhs.insert(std::size_t{ 0 }, lhs));
}

template <class CharT>
constexpr
my_string<CharT>
operator+(my_string<CharT>&& lhs, CharT rhs)
{
    return std::move(lhs.append(std::size_t{ 1 }, rhs));
}

template <class CharT>
constexpr
my_string<CharT>
operator+(CharT lhs, my_string<CharT>&& rhs)
{
    return std::move(rhs.insert(std::size_t{ 0 }, std::size_t{ 1 }, lhs));
}

template <class CharT>
constexpr
bool
operator==(const my_string<CharT>& lhs,
           const my_string<CharT>& rhs) noexcept
{
    return lhs.size() == rhs.size()
        && !_strncmp(lhs.data(), rhs.data(), lhs.size());
}

template <class CharT>
constexpr
bool
operator==(const CharT* lhs, const my_string<CharT>& rhs)
{
    return _strcmp(lhs, rhs.data());
}

template <class CharT>
constexpr
bool
operator==(const my_string<CharT>& lhs, const CharT* rhs)
{
    return rhs == lhs;
}

template <class CharT>
constexpr
bool
operator!=(const my_string<CharT>& lhs,
           const my_string<CharT>& rhs) noexcept
{
    return !(lhs == rhs);
}

template <class CharT>
constexpr
bool
operator!=(const CharT* lhs, const my_string<CharT>& rhs)
{
    return !(lhs == rhs);
}

template <class CharT>
constexpr
bool
operator!=(const my_string<CharT>& lhs, const CharT* rhs)
{
    return !(lhs == rhs);
}

template <class CharT>
constexpr
bool
operator<(const my_string<CharT>& lhs,
          const my_string<CharT>& rhs) noexcept
{
    return lhs.compare(rhs) < 0;
}

template <class CharT>
constexpr
bool
operator<(const CharT* lhs, const my_string<CharT>& rhs)
{
    return rhs.compare(lhs) > 0;
}

template <class CharT>
constexpr
bool
operator<(const my_string<CharT>& lhs, const CharT* rhs)
{
    return lhs.compare(rhs) < 0;
}

template <class CharT>
constexpr
bool
operator>(const my_string<CharT>& lhs,
          const my_string<CharT>& rhs) noexcept
{
    return rhs < lhs;
}

template <class CharT>
constexpr
bool
operator>(const CharT* lhs,
          const my_string<CharT>& rhs)
{
    return rhs < lhs;
}

template <class CharT>
constexpr
bool
operator>(const my_string<CharT>& lhs, const CharT* rhs)
{
    return rhs < lhs;
}

template <class CharT>
constexpr
bool
operator<=(const my_string<CharT>& lhs,
           const my_string<CharT>& rhs) noexcept
{
    return !(rhs < lhs);
}

template <class CharT>
constexpr
bool
operator<=(const CharT* lhs, const my_string<CharT>& rhs)
{
    return !(rhs < lhs);
}

template <class CharT>
constexpr
bool
operator<=(const my_string<CharT>& lhs, const CharT* rhs)
{
    return !(rhs < lhs);
}

template <class CharT>
constexpr
bool
operator>=(const my_string<CharT>& lhs,
           const my_string<CharT>& rhs) noexcept
{
    return !(lhs < rhs);
}

template <class CharT>
constexpr
bool
operator>=(const CharT* lhs, const my_string<CharT>& rhs)
{
    return !(lhs < rhs);
}

template <class CharT>
constexpr
bool
operator>=(const my_string<CharT>& lhs, const CharT* rhs)
{
    return !(lhs < rhs);
}

template<class CharT, class Traits>
std::basic_ostream<CharT, Traits>&
operator<<(std::basic_ostream<CharT, Traits>& os,
           const my_string<CharT>& str)
{
    return os.write(reinterpret_cast<const char*>(str.data()), str.size());
}

template<class CharT, class Traits>
std::basic_istream<CharT, Traits>&
operator>>(std::basic_istream<CharT, Traits>& is,
           my_string<CharT>& str)
{
    static constexpr std::size_t str_max_size = 1'000'000'000;
    
    using istream_type = std::basic_istream<CharT, Traits>;
    using string_type = my_string<CharT>;
    using ios_base = typename istream_type::ios_base;
    using int_type = typename istream_type::int_type;
    using ctype = std::ctype<CharT>;
    using ctype_base = typename ctype::ctype_base;

    std::size_t extracted = 0;
    
    typename ios_base::iostate err = ios_base::goodbit;
    typename istream_type::sentry cerb(is, false);
    
    if (cerb)
	{
	    try
	    {
	        // Avoid reallocation for common case.
	        str.clear();
	        CharT buf[128];
	        std::size_t len = 0;	      
	        const std::streamsize width = is.width();
	        const std::size_t n = width > 0 ? width : str_max_size;
	        
	        const ctype& ct = std::use_facet<ctype>(is.getloc());
	        const int_type eof = Traits::eof();
	        int_type c = is.rdbuf()->sgetc();
	        
	        while (extracted < n
		           && !Traits::eq_int_type(c, eof)
		           && !ct.is(ctype_base::space,
				   Traits::to_char_type(c)))
			{
			    if (len == sizeof(buf) / sizeof(CharT))
			    {
			        str.append(buf, sizeof(buf) / sizeof(CharT));
			        len = 0;
			    }
				       
				buf[len++] = Traits::to_char_type(c);
				++extracted;
				c = is.rdbuf()->snextc();
			}
			
			str.append(buf, len);
			
			if (extracted < n && Traits::eq_int_type(c, eof))
			    err |= ios_base::eofbit;
			    
			is.width(0);
	    }
	    catch(...)
	    {
	        is.setstate(ios_base::badbit);
	    }
	}
    
    if (!extracted)
        err |= ios_base::failbit;
    if (err)
        is.setstate(err);
    
    return is;
}

template <class CharT>
constexpr
std::size_t
_strlen(const CharT* str)
{
    std::size_t ret{ 0 };
    for (; *str != CharT{} ; ++ret, ++str)
        ;
    return ret;
}

template <class CharT>
constexpr
int
_strcmp(const CharT* lhs, const CharT* rhs)
{
    for(; *lhs && *lhs == *rhs; ++lhs, ++rhs)
        ;
        
    return *reinterpret_cast<const unsigned*>(lhs)
        - *reinterpret_cast<const unsigned*>(rhs);
}

template <class CharT>
constexpr
int
_strncmp(const CharT* lhs, const CharT* rhs, std::size_t n)
{
    for(; n && *lhs && *lhs == *rhs; --n, ++lhs, ++rhs)
        ;
        
    return *reinterpret_cast<const unsigned*>(lhs)
        - *reinterpret_cast<const unsigned*>(rhs);
}

template <class CharT>
my_string<CharT>
__str_concat(const CharT* lhs, std::size_t len1,
             const CharT* rhs, std::size_t len2)
{
    my_string<CharT> ret;
    ret.reserve(len1 + len2);
    ret.append(lhs, len1);
    ret.append(rhs, len2);
    
    return ret;
}

template <class T, class ... Args>
T*
_construct(std::size_t num_of_obj, Args&& ... args)
{
    return new T[num_of_obj]{ std::forward<Args>(args)... };
}

template <class T>
void
_destroy(T* ptr)
{
    delete[] ptr;
}

constexpr
std::size_t
closest_bin(std::size_t n) noexcept
{
    std::size_t ret{ n };
    
    if (n >= 2u)
    {
        --n;
        ret = 2u;
        
        while(n >>= 1u)
            ret <<= 1u;
    }
    
    return ret;
}
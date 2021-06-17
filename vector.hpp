#ifndef vector_h
#define vector_h

#include <iostream>
#include <algorithm>        
#include <memory>

using namespace std;
using std::size_t;

template <class T>
class Vector{
public:                
    // MEMBER TYPES
    typedef T value_type;
    typedef std::allocator<T> allocator_type;
    typedef size_t size_type;
    typedef T* iterator;
    typedef const T* const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
    typedef value_type& reference;
    typedef const value_type& const_reference;

    // MEMBER FUNCTIONS
    Vector() { create(); }
    explicit Vector(size_type n, const T &val = T{}) { create(n, val); }
    Vector(std::initializer_list<T> array);
    Vector(const Vector& v) { create(v.begin(), v.end()); }
    ~Vector() { uncreate(); }
    Vector& operator=(const Vector&);
    void assign( size_type count, const T& value);
    allocator_type get_allocator() const {return alloc; };

    // ELEMENT ACCESS
    reference at(size_type i);
    const_reference at(size_type i) const;
    T& operator[](size_type i) { return data[i]; }          // --
    const T& operator[](size_type i) const { return data[i]; }
    reference front() { return *data; }
    const_reference front() const {return *data; }
    reference back() { return *(avail-1); }
    const_reference back() const { return *(avail-1); }

    // ITERATORS
    iterator begin() noexcept {return data; }
    const_iterator begin() const noexcept { return data; }
    iterator end() noexcept { return avail; }
    const_iterator end() const noexcept { return avail; }
    reverse_iterator rbegin() noexcept { return reverse_iterator(avail); }
    const_reverse_iterator rbegin() const noexcept { return reverse_iterator(avail); };
    reverse_iterator rend() noexcept { return reverse_iterator(data); }
    const_reverse_iterator rend() const noexcept { return reverse_iterator(data); };

    // CAPACITY
    bool empty() const { return (begin() == end()); }
    size_type size() const { return avail - data; }
    // size_type max_size()
    void reserve(size_type new_cap);
    size_type capacity() const { return limit - data; }
    void shrink_to_fit();

    // MODIFIERS
    void clear();
    iterator insert(const_iterator pos, const T& value);
    iterator insert(const_iterator pos, size_type count, const T& value); // -
    iterator erase(iterator pos);
    iterator erase(iterator first, iterator last);
    void push_back(const T& val);
    void pop_back();
    void resize(size_type count);
    void resize(size_type count, const value_type& value);
    void swap(Vector<T>& other) noexcept;

    //non-member func
    // OPERATORS
    bool operator==(const Vector<T>& other) const;
    bool operator!=(const Vector<T>& other) const;
    bool operator<(const Vector<T>& other) const;
    bool operator>(const Vector<T>& other) const;
    bool operator>=(const Vector<T>& other) const;
    bool operator<=(const Vector<T>& other) const;


private:
    iterator data;      // first element in vec
    iterator avail;     // first element after last element in vec
    iterator limit;     // capacity

    allocator_type alloc; // atminties valdymui

    void create();
    void create(size_t, const T&);
    void create(const_iterator, const_iterator);
    void uncreate();
    // funkcijos push_backui \/
    void growTwice();
    void unchecked_append(const T&);

};


// Creating empty vec
template <class T>
void Vector<T>::create() {
    data = avail = limit = nullptr;
}

// creating Vector from array
template <class T>
Vector<T>::Vector(std::initializer_list<T> array){
    data = alloc.allocate(array.size());
    limit = avail = std::uninitialized_copy(array.begin(), array.end(), data);
}

// creating vec from val
template <class T>
void Vector<T>::create(size_type a, const T& val) {
    data = alloc.allocate(a);
    limit = avail = data + a;
    std::uninitialized_fill(data, limit, val);
}

template <class T>
void Vector<T>::create(const_iterator i, const_iterator k) {
    data = alloc.allocate(k-i);
    limit = avail = std::uninitialized_copy(i, k, data); 
}

// del Vector ir atminties perskirstymas

template <class T>
void Vector<T>::uncreate() {
    if(data){
        iterator it = avail;
        while(it != data){
            alloc.destroy(--it);
        }
        alloc.deallocate(data, limit - data);
    } 
    data = limit = avail = nullptr;
}

// assignment operator
template <class T>
Vector<T>& Vector<T>::operator=(const Vector& a) {
    if(&a != this) {
        uncreate();
        create(a.begin(), a.end());
    }
    return *this;
}

// element access funcs

template <class T>
typename Vector<T>::reference Vector<T>::at(size_type i) {
    if (i >= 0 && size() > i)
        return data[i];

    else throw std::out_of_range {"Vector::at"};
}

template <class T>
typename Vector<T>::const_reference Vector<T>::at(size_type i) const{
    if (i >= 0 && size() > i)
        return data[i];

    else throw std::out_of_range {"Vector::at"};
}

// capacity
// reserve
template <class T>
void Vector<T>::reserve(size_type new_cap){
    if(new_cap > capacity()){
        iterator new_data = alloc.allocate(new_cap);
        iterator new_avail = std::uninitialized_copy(data, avail, new_data);
        uncreate();
        data = new_data;
        avail = new_avail;
        limit = data + new_cap;
    }
}

// shrink_to_fit
template <class T>
void Vector<T>::shrink_to_fit() {
    if(avail != limit){
    alloc.deallocate(avail, limit - avail);
    limit = avail;
    }
}

// assign
template <class T>
void Vector<T>::assign(size_type count, const T& val) {
    if(count < 1)
        throw std::invalid_argument{ "Vector::assign" };

    if(count > capacity()) {
        uncreate();
        create(count, val);
    }
    else{
        iterator it = avail;
        while(it != data){
            alloc.destroy(--it);        //del all elements
        }
        avail = data + count;
        std::uninitialized_fill(data, avail, val);
    }
}

// clear
template <class T>
void Vector<T>::clear() {
    iterator it = avail;
    while (it != data)
        alloc.destroy(--it);
    avail = data;
}

// erase

template <class T>
typename Vector<T>::iterator Vector<T>::erase(iterator p){
    if(p >= avail || p < data){
        throw std::out_of_range{"vector::erase"};
    }
    for(iterator i = p; i < avail - 1; i++){
        *i = *(i+1);        // i kaire
    }
    --avail;
    return p;
}

template <class T>
typename Vector<T>::iterator Vector<T>::erase(iterator f, iterator l){
    if(f > l)
        throw std::invalid_argument{"vector::erase"};
    if(data > f || l > avail)
        throw std::out_of_range{"vector::erase"};
    for(iterator i = f; i < avail - 1; i++){
        *i = *(i+(l - f));
    }
    avail = avail - (l - f);
    return l;
}



//insert
template <class T>
typename Vector<T>::iterator Vector<T>::insert(const_iterator p, const T& val){
    if (p >= avail || p < data)
        throw std::out_of_range{ "Vector::insert" };
    int p_int = 0;
    for (iterator i = data; i < p; i++)
        p_int ++;

    size_type new_sz = size() + 1;
    iterator new_data = alloc.allocate(new_sz);
    iterator new_avail = std::uninitialized_copy(data, avail + 1, new_data);

    new_data[p_int] = val;
    int after_p = p_int + 1;
    int new_last = size() + 1;

    for (int i = after_p; i < new_last; i++)
        new_data[i] = data[i - 1];
    
    uncreate();
    data = new_data;
    avail = new_avail;
    limit = data + new_sz;

    return data + p_int;
}

template <class T>
typename Vector<T>::iterator Vector<T>::insert(const_iterator p, size_type count, const T& val){
    if(data < p || p >= avail || count < 1)
        throw std::out_of_range{"Vector::insert"};
    avail = avail + count;
    int p_int = 0;
    int i = 0;

    for(iterator i = data; i < p; i++)
        p_int ++;
    size_type new_sz = size() + count;
    iterator new_data = alloc.allocate(new_sz);
    iterator new_avail = std::uninitialized_copy(data, avail, new_data);
    
    for (i = 0; i < p_int; i++)
        new_data[i] = data[i];

    for (i = p_int; i <= p_int + count; i++)
        new_data[i] = val;

    int after_insert = p_int + count;
    int new_last = size() + count;
    for (i = after_insert; i < new_last; i++) {
        new_data[i] = data[i - count];
    }
    uncreate();
    data = new_data;
    avail = new_avail;
    limit = data + new_sz;

    return data + p_int;
}


// ----
template <class T>
void Vector<T>::growTwice(){
    size_type new_sz = std::max((limit - data) * 2, ptrdiff_t(1));
    reserve(new_sz);
}

template <class T>
void Vector<T>::unchecked_append(const T& val) {
    alloc.construct(avail++, val);
}
// ----

// push_back
template <class T>
void Vector<T>::push_back(const T& val){
    if(avail == limit)
        growTwice();
    unchecked_append(val);
        
}

// pop_back
template <class T>
void Vector<T>::pop_back(){
    iterator it = avail;
    alloc.destroy(--it);
    avail--;
}

// resize
template <class T>
void Vector<T>::resize(size_type count) {
    if (count > size() || count < 0)
        throw std::invalid_argument{ "Vector::resize" };
    while(begin() + count != avail)
        alloc.destroy(--avail); 
}

template <class T>
void Vector<T>::resize(size_type count, const value_type& val) {
    if(count < 0)
        throw std::invalid_argument{"Vector::resize"};
    if(count < size())
        resize(count);
    else{
        if(avail == limit)
            reserve(size() + (count - size()));
            std::uninitialized_fill(avail, limit, val);
            avail = limit;
    }
}

//swap
template <class T>
void Vector<T>::swap(Vector<T>& other) noexcept{
    iterator tt = data;
    data = other.data;
    other.data = tt;

    tt = avail;
    avail = other.avail;
    other.avail = tt;

    tt = limit;
    limit = other.limit;
    other.limit = tt;
}


// -- operatoriai -------

template <class T>
bool Vector<T>::operator==(const Vector<T>& other) const{
    if(size() == other.size()){
        for(int i = 0; i < size(); i++)
            if(at(i) != other.at(i))
                return false;
        return true;
    }
    else return false;
}

template <class T>
bool Vector<T>::operator!=(const Vector<T>& other) const{
    return other == *this ? false : true;
}

template <class T>
bool Vector<T>::operator<(const Vector<T>& other) const{
    size_type size2;
    if (size() < other.size())
        size2 = size();
    else size2 = other.size();

    for(size_type i; i < size2; i++)
        if(at(i) != other[i])
            return at(i) < other[i];

    return size() < other.size();
}

template <class T>
bool Vector<T>::operator>(const Vector<T>& other) const{
    size_type size2;
    if (size() < other.size())
        size2 = size();
    else size2 = other.size();

    for(size_type i; i < size2; i++)
        if(at(i) != other[i])
            return at(i) > other[i];

    return size() > other.size();
}

template <class T>
bool Vector<T>::operator<=(const Vector<T>& other) const{
    return other > *this ? false : true;
}

template <class T>
bool Vector<T>::operator>=(const Vector<T>& other) const{
    return other < *this ? false : true;
}


#endif
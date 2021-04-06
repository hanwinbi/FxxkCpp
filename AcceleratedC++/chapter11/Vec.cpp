#include <memory>

template <class T> class Vec
{
public:
    typedef T* iterator;
    typedef const T* const_iterator;
    typedef size_t size_type;
    typedef T value_type;
    typedef std::ptrdiff_t difference_type;
    typedef T& reference;
    typedef const T& const_reference;

    Vec(){ create();} //构造函数
    explicit Vec(std::size_t n, const T& val=T()){ create(n, val);}

    size_type size() const {return avail-data;}

    T& operator[](size_type i){return data[i];}
    const T& operator[](size_type i){return data[i];}

    iterator begin(){return data;}
    const_iterator begin() const{ return data;}

    iterator end(){return avail;}
    const_iterator end() const{return avail;}

    void push_back(const T& val){
        if(avail == limit) grow();
        unchecked_append(val);
    }

    Vec(const_iterator Vec& v){return create(v.begin(), v.end())}

    Vec& operator=(const Vec&);

    ~Vec(){ uncreate(); }

    size_type size
private:
    iterator data; //Vec中的首元素
    iterator limit; //Vec中的末元素
    iterator avail;

    allocator<T> alloc;

    void create();
    void create(size_type, const T&);
    void create(const_iterator, const_iterator);

    void uncreate();

    void grow();
    void unchecked_append(const T&);
}; // 模版类后需要加;

template <class T> Vec<T>& Vec<T>::operator=(const Vec& rhs){
    if(&rhs != this){
        uncreate();
        create(rhs.begin(), rhs.end());
    }
    return *this;
} // 模版函数后面不用;

template <class T> void Vec<T>::create(){
    data = avail = limit = 0;
}

template <class T> void Vec<T>::create(size_type n, const T& val){
    data = alloc.allocate(n);
    limit=avail=data+n;
    uninitialized_fill(data, limit, val);
}

template <class T> void Vec<T>::create(const_iterator i, const_iterator j){
    data = alloc.allocate(j-i);
    limit=avail=uninitialized_copy(i, j, data);
}

template <class T> void Vec<T>::uncreate(){
    if(data){
        iterator it=avail;
        while(it!=data){
            alloc.destroy(--it);
        }
        alloc.deallocate(data, limit-data);
    }
    data=limit=avail=0;
}

template <class T> void Vec<T>::grow(){
    size_type new_size=max(2*(limit-data), ptrdiff_t(1));

    iterator new_data=alloc.allocate(new_size);
    iterator new_avail=uninitialized_copy(data, avail, new_data);

    uncreate();

    data=new_data;
    avail=new_avail;
    limit=data+new_size;
}

template <class T> void Vec<T>::unchecked_append(const T& val){
    alloc.construct(avail++, val);
}

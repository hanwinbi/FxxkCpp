class U_ptr{
    friend class HasSmartPtr;
    int *ip;
    int use;
    U_ptr(int *p):ip(p),use(1){}
    ~U_ptr(){ delete ip; }
};

class HasSmartPtr{
private:
    U_ptr *ptr;
    int val;
public:
    HasSmartPtr(int *p, int i):ptr(new U_ptr(p)), val(i){}
    HasSmartPtr(const HasSmartPtr &orig):ptr(orig.ptr),val(orig.val){ ++ptr->use;}
    HasSmartPtr& operator=(const HasSmartPtr&);
    ~HasSmartPtr(){ if(--ptr->use==0) delete ptr;}

    int *get_ptr(){return ptr->ip;}
    int get_int(){ return val;}
    void set_ptr(int *p){ ptr->ip = p;}
    void set_int(int i){val = i;}
    int get_ptr_val() const {return *ptr->ip;}
    void set_ptr_val(int i) const {*ptr->ip = i;}
};

HasSmartPtr& HasSmartPtr::operator=(const HasSmartPtr & rhs){
    ++rhs.ptr->use;
    if(--ptr->use==0){
        delete ptr;
    }
    ptr = rhs.ptr;
    val = rhs.val;
    return *this;
}

class HasPtr
{
private:
    int *ptr;
    int val;
public:
    HasPtr(int *p, int i):ptr(p),val(i){};

    int *get_ptr() const{return ptr;}
    int get_int() const{return val;}

    void set_ptr(int *p){ptr = p;}
    void set_int(int i){val = i;}

    int get_ptr_val() const { return *ptr;}
    void set_ptr_val(int i) const { *ptr = i;}
};


int main(){
    int obj = 0;
    HasPtr ptr1(&obj, 42);
    HasPtr ptr2(ptr1);
}

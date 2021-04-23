template <class Type> class Queue{
public:
    Queue();
    Type &front();
    const Type &front() const;
    void push(const Type &);
    void pop();
    bool empty() const;
private:
 
};
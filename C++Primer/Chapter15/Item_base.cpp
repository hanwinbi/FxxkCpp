#include <iostream>

using namespace std;

class Item_base
{
private:
    std::string isbn;
public:
    Item_base(const std::string &book="", double sales_price=0.0): isbn(book), price(sales_price){}
    std::string book() const{ return isbn;}
    virtual double net_price(std::size_t n) const{ return n * price;}
    virtual ~Item_base(){}
protected:
    double price; 
};

class Disc_item: public Item_base{
protected:
    std::size_t quantity;
    double discount;
public:
    Disc_item(const std::string &book="", double sales_price=0.0, 
                std::size_t qty=0, double disc_rate=0.0): Item_base(book,sales_price), quantity(qty),discount(disc_rate){}
};

class Bulk_item: public Disc_item
{
public:
    Bulk_item(const std::string &book="", double sales_price=0.0, 
                std::size_t qty=0, double disc_rate=0.0): Disc_item(book,sales_price, qty, disc_rate){}
    // double net_price(std::size_t cnt) const;
};

void print_total(ostream &os, const Item_base& item, size_t n){
    os << "ISBN: " << item.book() << "\tnumber sold: " << n << "\ttotal price: " << item.net_price(n) << endl; 
}

int main(){
    Item_base base("123456", 10.0);
    Bulk_item derived("978-7-115-14554-3", 99, 5, .19);
    
    print_total(cout, base, 10);
    print_total(cout, derived, 10);

    cout << derived.book();
}

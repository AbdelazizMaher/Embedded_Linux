#include <iostream>
#include <string>

enum OrderStatus
{
    CREATE,
    SHIPPING,
    DELIVERED,
    PAID
};

std::string OrderStatusToString(OrderStatus status) {
    switch (status) {
        case CREATE:
            return "CREATE";
        case SHIPPING:
            return "SHIPPING";
        case DELIVERED:
            return "DELIVERED";
        case PAID:
            return "PAID";
    }
    return "UNKNOWN";
}

class Order
{
private:
    std::string date;
    OrderStatus state;
public:
    Order(std::string Given_date)
        : date {Given_date} {
    }
    OrderStatus getOrderStatus() { return state; }
    void setOrderStatus(OrderStatus Given_state) { state = Given_state; }
    void Display()
    {
        std::cout << "\n================ Order ================" << std::endl;
        std::cout << "date: " << date << std::endl;
        std::cout << "state: " << OrderStatusToString(state) << std::endl;
        std::cout << "=========================================\n" << std::endl;
    }

};

class Customer
{
private:
     std::string name , deliveryAdress ,contact;
     bool active;
     Order *orders[10];
     int ordersCount = 0;
public:
    Customer(std::string Given_name ,std::string Given_deliveryAdress ,std::string Given_contact ,bool ISactive )
        : name{Given_name} , deliveryAdress{Given_deliveryAdress} , contact{Given_contact} , active{ISactive} {
    }
    void putOrder(std::string CustomerOrder_date)
    {
        orders[ordersCount] = new Order{CustomerOrder_date};
        orders[ordersCount]->setOrderStatus(CREATE);
        ordersCount++;
    }
    int getOrdersCount() const { return ordersCount; }
    Order *getOrder(int OrderNum)
    {
        return orders[OrderNum - 1];
    }
    void Display()
    {
        std::cout << "\n================ Customer ================" << std::endl;
        std::cout << "name: " << name << std::endl;
        std::cout << "deliveryAdress: " << deliveryAdress << std::endl;
        std::cout << "contact: " << contact << std::endl;
        std::cout << "active: " << std::boolalpha << active << std::endl;
        std::cout << "============================================\n" << std::endl;
    }
    ~Customer()
    {
        for( int i = 0 ; i < ordersCount ; i++)
            delete orders[i];
    }
};

class Item
{
private:
    float weight;
    std::string description;
    double price;
public:
    Item(float Given_weight ,std::string Given_description ,double Given_price)
        : weight {Given_weight} , description{Given_description} , price{Given_price} {
    }
    double getPriceForQuantity(int Given_qty) { return (price * Given_qty);}
    float getWeight() { return weight; }
    void Display()
    {
        std::cout << "\n================ Item ================" << std::endl;
        std::cout << "weight: " << weight << std::endl;
        std::cout << "description: " << description << std::endl;
        std::cout << "price: " << price << std::endl;
        std::cout << "========================================\n" << std::endl;
    }
};

class OrderDetail
{
private:
    int qty;
    std::string taxStatus;
    Item *itemDetails;
public:
    OrderDetail(int Given_qty , std::string Given_taxStatus)
        : qty{Given_qty} , taxStatus{Given_taxStatus} {
    }
    void addItem(float Given_Itemweight ,std::string Given_Itemdescription ,double Given_Itemprice)
    {
        itemDetails = new Item{Given_Itemweight,Given_Itemdescription,Given_Itemprice};
    }
    Item *getItem() { return itemDetails; }
    double calculateSubTotal(){ return itemDetails->getPriceForQuantity(qty); }
    double calculateWeight() { return (itemDetails->getWeight() * qty); }
    int getQTY() { return qty; }
    void Display()
    {
        std::cout << "\n================ OrderDetail ================" << std::endl;
        std::cout << "qty: " << qty << std::endl;
        std::cout << "taxStatus: " << taxStatus << std::endl;
        std::cout << "===============================================\n" << std::endl;
    }
    ~OrderDetail()
    {
        delete itemDetails;
    }
};

class Payment
{
private:
    float amount;
public:
    Payment(float Given_amount)
        : amount {Given_amount} {
    }
};

class Credit : public Payment
{
private:
    std::string number ,type ,expireDate;
public:
    Credit(float Given_amount, const std::string Given_number, const std::string Given_type, const std::string Given_expireDate)
        : Payment(Given_amount), number(Given_number), type(Given_type), expireDate(Given_expireDate) {
    }
};

class Cash : public Payment
{
private:
    float cashTendered;
public:
    Cash(float Given_amount, float Given_cashTendered)
        : Payment(Given_amount), cashTendered{Given_cashTendered} {
    }
};

class Check : public Payment
{
private:
    std::string name ,bankID;
public:
    Check(float Given_amount, std::string Given_name,std::string Given_bankID)
        : Payment(Given_amount), name{Given_name} , bankID{Given_bankID} {
    }
    void authorized() { std::cout << "Processing check payment..." << std::endl; }
};

class WireTransfer : public Payment
{
private:
    std::string bankID ,bankName;
public:
    WireTransfer(float Given_amount, std::string Given_bankID,std::string Given_bankName)
        : Payment(Given_amount), bankID{Given_bankID} , bankName{Given_bankName} {
    }
};

int main()
{
    OrderDetail firstOrderDetail{3, "Taxable"};
    firstOrderDetail.addItem(2.5, "Widget",10.0);

    Customer Abdelaziz("AbdelazizMaher", "El-syouf,Alexandria", "01062894289", true);
    Abdelaziz.putOrder("29FEB2024");

    Abdelaziz.Display();
    Abdelaziz.getOrder(Abdelaziz.getOrdersCount())->Display();
    firstOrderDetail.Display();
    firstOrderDetail.getItem()->Display();

    Credit creditCardPayment(100.0, "1234567890123456", "Visa", "12/25");
    return 0;
}

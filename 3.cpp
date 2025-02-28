#include<iostream>
#include<vector>
#include<algorithm>

#define CALLRATE 0.10

enum CustomerType
{
    PREPAID,
    POSTPAID
};
typedef CustomerType customer_t;
class ICustomer
{
    public:
     virtual void makeCall(int) = 0;
     virtual void credit(double) = 0;
     virtual double balance() const = 0;
};
class Customer : public ICustomer
{
    customer_t m_type;
    std::string m_id;
    std::string m_name;
    double m_balance;
    public:
        Customer(customer_t,std::string,std::string,double);
        customer_t type() const;
        std::string id() const;
        std::string name() const;
        double balance() const ;
        void display() const {
            std::cout << m_type << ", " << m_id << ", " << m_name << ", " << m_balance << "\n";
        }
        void setbalance(double);
};
class PrepaidCustomer : public Customer
{
    public:
        PrepaidCustomer(std::string,std::string, double);
        void makeCall(int) override; // reduces the m_balance using number of minutes passed as input i.e input*CALLRATE
        void credit(double) override;// adds the input passed to m_balance

};

class PostpaidCustomer : public Customer
{
    public:
        PostpaidCustomer(std::string,std::string,double);
        void makeCall(int) override;// adds the m_balance using number of minutes passed as input i.e input*CALLRATE
        void credit(double) override;// negates  the input passed to m_balance
};

class MobileBilling
{
    std::vector<ICustomer*> m_customers;
    public:
        MobileBilling() = default;
        void addCustomer(customer_t,std::string,std::string,double);
        void displayCustomers();
        bool isCustomerFound(std::string);
        ICustomer* findCustomerById(std::string);
};

Customer::Customer(customer_t type, std::string id, std::string name, double balance)
    : m_type(type), m_id(id), m_name(name), m_balance(balance) {}

customer_t Customer::type() const { return m_type; }

std::string Customer::name() const { return m_name; }
std::string Customer::id() const { return m_id; }
double Customer::balance() const { return m_balance; }



void Customer::setbalance(double balance) { m_balance = balance; }


PrepaidCustomer::PrepaidCustomer(std::string id, std::string name, double balance)
    : Customer(PREPAID, id, name, balance) {}

void PrepaidCustomer::makeCall(int minutes) {
    setbalance(balance() - minutes * CALLRATE);
}

void PrepaidCustomer::credit(double amount) {
    setbalance(balance() + amount);
}


PostpaidCustomer::PostpaidCustomer(std::string id, std::string name, double balance)
    : Customer(POSTPAID, id, name, balance) {}

void PostpaidCustomer::makeCall(int minutes) {
    setbalance(balance() + minutes * CALLRATE);
}

void PostpaidCustomer::credit(double amount) {
    setbalance(balance() - amount);
}

void MobileBilling::addCustomer(customer_t type, std::string id, std::string name, double balance) {
    if (type == PREPAID) {
        m_customers.push_back(new PrepaidCustomer(id, name, balance));
    } else {
        m_customers.push_back(new PostpaidCustomer(id, name, balance));
    }
}

void MobileBilling::displayCustomers() {
    for (const auto& customer : m_customers) {
        dynamic_cast<Customer*>(customer)->display();
    }
}

bool MobileBilling::isCustomerFound(std::string id) {
    for (const auto& customer : m_customers) {
        if (dynamic_cast<Customer*>(customer)->id() == id) {
            return true;
        }
    }
    return false;
}

ICustomer* MobileBilling::findCustomerById(std::string id) {
    for (const auto& customer : m_customers) {
        if (dynamic_cast<Customer*>(customer)->id() == id) {
            return customer;
        }
    }
    return nullptr;
}
int main()
{
    int t,no;
    std::string i,n;
    double b;
    MobileBilling database1;
    std::cin >> no;
    for(int j=0;j<no;j++)
    {
        std::cin >> t >> i >> n >> b;
        database1.addCustomer((customer_t)t,i,n,b);
    }
    database1.displayCustomers();
    std::cin >> i;
    std::cout << database1.isCustomerFound(i) << '\n';

    std::cin >> i >> no >> b;
    auto icust = database1.findCustomerById(i);
    Customer* ccust = dynamic_cast<Customer*>(icust);
    ccust->makeCall(no);
    ccust->credit(b);
    ccust->display();
}

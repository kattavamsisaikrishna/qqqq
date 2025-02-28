#include<iostream>
#include<string>
#include<algorithm>
#include<vector>

class Contact
{
    std::string m_name;
    std::string m_phoneNumber;
    int m_code;
    public:
        Contact();
        Contact(std::string,std::string,int);
        Contact(const Contact &);
        std::string name() const;
        std::string number() const;

        int code() const;
        void display() const
        {
            std::cout << m_name << ", " << m_code  << ", " << m_phoneNumber << std::endl;
        }

        bool operator<(const Contact&);
};
class PhoneBook
{
    std::vector<Contact> m_contacts;
    public:
    void addContact(std::string,std::string,int);
    void removeContactByNumber(std::string);
    void displayAllContacts();
    Contact* findContactByNumber(std::string);
    void sortByCodeByCode();

};
Contact::Contact() = default;
Contact::Contact(std::string n,std::string p,int c) : m_name(n),m_phoneNumber(p),m_code(c){}
Contact::Contact(const Contact &other) = default;
std::string Contact::name() const{
    return m_name;
}
std::string Contact::number() const{
    return m_phoneNumber;
}
int Contact::code() const
{
    return m_code;
}
bool Contact::operator<(const Contact &other)
{
    if(m_code < other.m_code)
    {
        return true;
    }
    else
    {
        return false;
    }
}
void PhoneBook::addContact(std::string n,std::string p,int c)
{
    Contact obj(n,p,c);
    m_contacts.push_back(obj);
}
void PhoneBook::removeContactByNumber(std::string p)
{
    int index = -1;
    for(int i=0;i<m_contacts.size();i++ )
    {
        if(m_contacts[i].number() == p)
        {
            index = i;
        }
    }
    m_contacts.erase(m_contacts.begin()+index);
}
void PhoneBook::displayAllContacts()
{
    for (Contact i : m_contacts)
    {
         i.display();
    }
}
Contact* PhoneBook::findContactByNumber(std::string number)
{
    for ( auto& contact : m_contacts) {
        if (contact.number() == number) {
            return &contact;
        }
    }
    return nullptr;
}
void PhoneBook::sortByCodeByCode()
{
    std::sort(m_contacts.begin(), m_contacts.end(), [](const Contact& a, const Contact& b) {
        return a.code() < b.code(); 
    });
}


int main()
{
    std::string name, number;
    int code,iter;
    PhoneBook pb1;

    std::cin >> iter;
    for(int i=0;i<iter ; i++)
    {
        std::cin >> name >> number >> code;
        pb1.addContact(name, number, code);
    }

    pb1.displayAllContacts();

    std::cin >> number;

    pb1.removeContactByNumber(number);
    pb1.displayAllContacts();

    std::cin >> number;
    Contact* pbptr1 = pb1.findContactByNumber(number);
    pbptr1->display();

    pb1.sortByCodeByCode();
    pb1.displayAllContacts();
    return 0;
}
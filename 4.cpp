#include<iostream>
#include<string>
#include<algorithm>
#include<vector>

class Employee
{
    std::string m_id;
    std::string m_name;
    double m_salary;
    int m_exp;
    public:
    Employee();
    Employee(std::string,std::string,double,int);
    Employee(const Employee&);
    std::string id() const;
    std::string name() const;
    double salary() const;
    int exp() const;
    void display() const
    {
        std::cout << m_id << ", " << m_name << ", " << m_salary << ", " << m_exp << "\n";
    }
    bool operator<(const Employee&);
};






Employee::Employee() = default;
Employee::Employee(std::string a,std::string b,double c, int d):m_id(a),m_name(b),m_salary(c),m_exp(d) {}
Employee::Employee(const Employee& other) = default;
std::string Employee::id() const{ return m_id;}
std::string Employee::name() const{ return m_name;}
double Employee::salary() const {return m_salary;}
int Employee::exp() const { return m_exp;}
bool Employee::operator<(const Employee& other)
{
    if(m_salary < other.m_salary)
    {
        return true;
    }
    return false;
}





class EmployeeData
{
    std::vector<Employee> m_employees;
    public:
        void addEmployee(std::string, std::string,double, int );
        void removeEmployee(std::string);
        void displayAll();
        Employee *findEmployeeByName(std::string);
        double findAverageExperience();
        void sortBySalary();
};








void EmployeeData::addEmployee(std::string a, std::string b, double c, int d)
{
    Employee obj(a,b,c,d);
    m_employees.push_back(obj);
}
void EmployeeData::removeEmployee(std::string id)
{
    int index = -1;
    for(int i=0;i<m_employees.size();i++)
    {
        if(m_employees[i].id() == id)
        {
            index = i;
        }
    }
    m_employees.erase(m_employees.begin()+index);
}
void EmployeeData::displayAll()
{
    for(Employee i : m_employees)
    {
        i.display();
    }
}
Employee* EmployeeData::findEmployeeByName(std::string name)
{
    for ( auto& employee : m_employees) {
        if (employee.name() == name) {
            return &employee;
        }
    }
    return nullptr;
}
double EmployeeData::findAverageExperience()
{
    double sum = 0;
    for(auto employee : m_employees)
    {
        sum += employee.exp();
    }
    return sum/m_employees.size();
}
void EmployeeData::sortBySalary()
{
    std::sort(m_employees.begin(), m_employees.end(), [](const Employee& a, const Employee& b) {
        return a.salary() < b.salary(); 
    });
}



int main()
{
    return 0;
}
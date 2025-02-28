#include<iostream>
#include<vector>
#include<algorithm>
class box 
{
    public:
    int len,ht,bdt,wt,m_volume;
    public:
        box(int len,int ht,int bdt,int wt):len(len),ht(ht),bdt(bdt),wt(wt) {
            m_volume = len * ht* bdt;
        }

        friend std::ostream& operator<<(std::ostream& out, const box&);
};
std::ostream& operator<<(std::ostream& out, box& ref)
{
    out << ref.len << " " << ref.ht << " " << ref.bdt << " " << ref.wt << " " << ref. m_volume;
    return out;
}
int user_function(const std::vector<box>& input, std::vector<box>& result, int threshold_volume) {
    for (const auto& box : input) {
        if (box.m_volume < threshold_volume) {
            result.push_back(box);
        }
    }
    std::sort(result.begin(), result.end(), [](const box& a, const box& b) {
        return a.wt < b.wt;  // Compare weights to sort in ascending order
    });
    return result.size();
}
int main()
{
    int N = 0, len = 0, ht = 0, bdt = 0, wt = 0, val = 0;
    std::cin >> N;
    std::vector<box> vect1;
    std::vector<box> vect2;

    for(int i=0;i<N;i++)
    {
        std::cin >> len >> ht >> bdt >> wt;
        vect1.emplace_back(len,ht,bdt,wt);
    }
    std::cin >> val;
    std::cout << user_function(vect1,vect2,val) << std::endl;

    for(int index = 0; index < vect2.size(); index++)
    {
        std::cout << vect2[index] << std::endl;
    }
    return 0;
}

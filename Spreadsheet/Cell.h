
#include <iostream>
#include <vector>
#include <string>

std::ostream& operator<<(std::ostream& out, const std::vector<int>& ob);

class Cell
{
private:
    std::string val;
public:
    Cell();
    Cell(const Cell& rhv);
    Cell(Cell&& rhv);
    Cell(int val);
    Cell(double val);
    Cell(char val);
    Cell(bool val);
    Cell(std::string val);
    Cell(const std::vector<int>& val);

    const Cell& operator=(const Cell& rhv);  
    const Cell& operator=(Cell&& rhv);  
    const Cell& operator=(int rhv);  
    const Cell& operator=(double rhv);  
    const Cell& operator=(char rhv);  
    const Cell& operator=(bool rhv);  
    const Cell& operator=(std::string rhv);  
    const Cell& operator=(const std::vector<int>& rhv);

    operator int();  
    operator double();  
    operator char();  
    operator bool();  
    operator std::string();  
    operator std::vector<int>();  

    // Getter and Setter for val
    std::string getValue() const { return val; }
    void setValue(const std::string& newVal) { val = newVal; }
};

bool operator==(const Cell& lhv, const Cell& rhv);
bool operator!=(const Cell& lhv, const Cell& rhv);

std::ostream& operator<<(std::ostream& out, const Cell& ob);
std::istream& operator>>(std::istream& in, Cell& ob);


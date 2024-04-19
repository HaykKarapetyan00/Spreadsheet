#include "cell.h"

#include <iostream>
#include <sstream>

Cell::Cell() : val("") {}
Cell::Cell(const Cell& rhv) : val(rhv.val) {}
Cell::Cell(Cell&& rhv) : val(std::move(rhv.val)) {}
Cell::Cell(int val) : val(std::to_string(val)) {}
Cell::Cell(double val) : val(std::to_string(val)) {}
Cell::Cell(char val) : val(std::string(1, val)) {}
Cell::Cell(bool val) : val(val ? "true" : "false") {}
Cell::Cell(std::string val) : val(val) {}
Cell::Cell(const std::vector<int>& val) {
    std::stringstream ss;
    for (int num : val) {
        ss << num << ' ';
    }
    this->val = ss.str();
}

const Cell& Cell::operator=(const Cell& rhv) {
    if (this != &rhv) {
        val = rhv.val;
    }
    return *this;
}

const Cell& Cell::operator=(Cell&& rhv) {
    if (this != &rhv) {
        val = std::move(rhv.val);
    }
    return *this;
}

const Cell& Cell::operator=(int rhv) {
    val = std::to_string(rhv);
    return *this;
}

const Cell& Cell::operator=(double rhv) {
    val = std::to_string(rhv);
    return *this;
}

const Cell& Cell::operator=(char rhv) {
    val = std::string(1, rhv);
    return *this;
}

const Cell& Cell::operator=(bool rhv) {
    val = rhv ? "true" : "false";
    return *this;
}

const Cell& Cell::operator=(std::string rhv) {
    val = rhv;
    return *this;
}

const Cell& Cell::operator=(const std::vector<int>& rhv) {
    std::stringstream ss;
    for (int num : rhv) {
        ss << num << ' ';
    }
    val = ss.str();
    return *this;
}

Cell::operator int() {
    return std::stoi(val);
}

Cell::operator double() {
    return std::stod(val);
}

Cell::operator char() {
    return val.empty() ? '\0' : val[0];
}

Cell::operator bool() {
    return val == "true";
}

Cell::operator std::string() {
    return val;
}

Cell::operator std::vector<int>() {
    std::vector<int> result;
    std::stringstream ss(val);
    int num;
    while (ss >> num) {
        result.push_back(num);
    }
    return result;
}

bool operator==(const Cell& lhv, const Cell& rhv) {
    return lhv.getValue() == rhv.getValue();
}

bool operator!=(const Cell& lhv, const Cell& rhv) {
    return !(lhv == rhv);
}

std::ostream& operator<<(std::ostream& out, const std::vector<int>& ob) {
    for (int num : ob) {
        out << num << ' ';
    }
    return out;
}

std::istream& operator>>(std::istream& in, Cell& ob) {
    std::string s;
    in >> s;
    ob = Cell(s);
    return in;
}
std::ostream& operator<<(std::ostream& out, const Cell& ob) {
    out << ob.getValue();
    return out;
}
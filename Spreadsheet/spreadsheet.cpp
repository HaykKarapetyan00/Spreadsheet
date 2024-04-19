#include "SpreadSheet.h"
#include <algorithm>

SpreadSheet::SpreadSheet() : SpreadSheet(2, 2) {}

SpreadSheet::SpreadSheet(size_t size) : SpreadSheet(size, size) {}

SpreadSheet::SpreadSheet(size_t row, size_t col) : m_row(row), m_col(col) {
    m_board = new Cell*[m_row];
    for (size_t i = 0; i < m_row; ++i) {
        m_board[i] = new Cell[m_col];
        for (size_t j = 0; j < m_col; ++j) {
            m_board[i][j] = Cell();
        }
    }
}

SpreadSheet::SpreadSheet(const SpreadSheet& rhv) : SpreadSheet(rhv.m_row, rhv.m_col) {
    for (size_t i = 0; i < m_row; ++i) {
        for (size_t j = 0; j < m_col; ++j) {
            m_board[i][j] = rhv.m_board[i][j];
        }
    }
}

SpreadSheet::SpreadSheet(SpreadSheet&& rhv) noexcept : m_board(rhv.m_board), m_row(rhv.m_row), m_col(rhv.m_col) {
    rhv.m_board = nullptr;
    rhv.m_col = 0;
    rhv.m_row = 0;
}

const SpreadSheet& SpreadSheet::operator=(const SpreadSheet& rhv) {
    if (this != &rhv) {
        clear();
        m_col = rhv.m_col;
        m_row = rhv.m_row;
        m_board = new Cell*[m_row];
        for (size_t i = 0; i < m_row; ++i) {
            m_board[i] = new Cell[m_col];
            for (size_t j = 0; j < m_col; ++j) {
                m_board[i][j] = rhv.m_board[i][j];
            }
        }
    }
    return *this;
}

const SpreadSheet& SpreadSheet::operator=(SpreadSheet&& rhv) noexcept {
    if (this != &rhv) {
        clear();
        m_board = rhv.m_board;
        m_row = rhv.m_row;
        m_col = rhv.m_col;
        rhv.m_board = nullptr;
        rhv.m_col = 0;
        rhv.m_row = 0;
    }
    return *this;
}

SpreadSheet::~SpreadSheet() {
    clear();
}

void SpreadSheet::resizeRow(size_t size) {
    Cell** tmp = new Cell*[size];
    for (size_t i = 0; i < size; ++i) {
        tmp[i] = new Cell[m_col];
        for (size_t j = 0; j < m_col; ++j) {
            if (i < m_row){
                tmp[i][j] = m_board[i][j];
            }
            else{
                tmp[i][j] = "";
            }
        }
    }
    clear();
    for (size_t i = 0; i < size; i++){
        for (size_t j = 0; j < m_col; j++){
            m_board[i][j] = tmp[i][j];
        }
    }
    m_row = size;
}

void SpreadSheet::resizeCol(size_t size) {
    Cell** tmp = new Cell*[m_row];
    for (size_t i = 0; i < m_row; ++i) {
        tmp[i] = new Cell[size];
        for (size_t j = 0; j < size; ++j) {
            if (j < m_col){
                tmp[i][j] = m_board[i][j];
            }
            else{
                tmp[i][j] = "";
            }
        }
    }
    clear();
    m_board = tmp;
    m_col = size;
}

void SpreadSheet::resize(size_t s1, size_t s2) {
    Cell** tmp = new Cell*[s1];
    for (size_t i = 0; i < s1; ++i) {
        tmp[i] = new Cell[s2];
        for (size_t j = 0; j < s2; ++j) {
            tmp[i][j] = (i < m_row && j < m_col) ? m_board[i][j] : Cell();
        }
    }
    clear();
    m_board = tmp;
    m_row = s1;
    m_col = s2;
}

void SpreadSheet::clear() noexcept {
    if (m_board) {
        for (size_t i = 0; i < m_row; ++i) {
            delete[] m_board[i];
        }
        delete[] m_board;
        m_board = nullptr;
        m_row = 0;
        m_col = 0;
    }
}

size_t SpreadSheet::col() const {
    return m_col;
}

size_t SpreadSheet::row() const {
    return m_row;
}

Cell& SpreadSheet::operator[](std::initializer_list<int> index) {
    auto it = index.begin();
    if (*it >= 0 && *it < static_cast<int>(m_row) && *(it + 1) >= 0 && *(it + 1) < static_cast<int>(m_col)) {
        return m_board[*it][*(it + 1)];
    }
    throw std::out_of_range("");
}

const Cell** SpreadSheet::getVal() const {
    return const_cast<const Cell**>(m_board);
}

bool operator==(const SpreadSheet& lhs, const SpreadSheet& rhs) {
    if (lhs.row() != rhs.row() || lhs.col() != rhs.col()) {
        return false;
    }
    const Cell** val1 = lhs.getVal();
    const Cell** val2 = rhs.getVal();
    size_t row = lhs.row();
    size_t col = lhs.col();
    for (size_t i = 0; i < row; ++i) {
        for (size_t j = 0; j < col; ++j) {
            if (val1[i][j] != val2[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool operator!=(const SpreadSheet& lhs, const SpreadSheet& rhs) {
    return !(lhs == rhs);
}

SpreadSheet SpreadSheet::slice(std::initializer_list<size_t> rows, std::initializer_list<size_t> cols) {
    SpreadSheet obj(*this);
    obj.removeRows(rows);
    obj.removeCols(cols);
    return obj;
}

SpreadSheet::Column SpreadSheet::operator[](size_t pos) {
    return Column(m_board[pos]);
}

const SpreadSheet::Column SpreadSheet::operator[](size_t pos) const {
    return Column(m_board[pos]);
}

SpreadSheet::Column::Column(Cell* col) : col(col) {}

Cell& SpreadSheet::Column::operator[](size_t pos) {
    return col[pos];
}

const Cell& SpreadSheet::Column::operator[](size_t pos) const {
    return col[pos];
}

std::ostream& operator<<(std::ostream& out, const SpreadSheet& ob) {
    int width = 8;
    double width_table = ob.col() * 9.1;
    int h_line = 1;
    for (size_t i = 0; i < ob.row(); ++i)
    {
        for(size_t k = 0; k < width_table; ++k)
        {
            out << std::setw(1) << "-";
        }
        out << "\n";
        for(size_t j = 0; j < ob.col(); ++j)
       	{
            out << std::setw(h_line) << "|" << std::setw(width) << std::left << ob[i][j];
        }
        out << std::setw(h_line) << "|";
        out << "\n";
    }
    for(size_t k = 0; k < width_table; ++k)
    {
        out << std::setw(1) << "-";
    }
    out << "\n";
    return out;
}

int SpreadSheet::max_length() const {
    int max = 0;
    for (size_t i = 0; i < m_row; ++i) {
        for (size_t j = 0; j < m_col; ++j) {
            std::string str = m_board[i][j];
            max = std::max(max, static_cast<int>(str.length()));
        }
    }
    return max;
}

void SpreadSheet::mirrorH() {
    for (size_t i = 0; i < m_row; ++i) {
        for (size_t j = 0; j < m_col / 2; ++j) {
            std::swap(m_board[i][j], m_board[i][m_col - j - 1]);
        }
    }
}

void SpreadSheet::mirrorV() {
    for (size_t i = 0; i < m_row / 2; ++i) {
        for (size_t j = 0; j < m_col; ++j) {
            std::swap(m_board[i][j], m_board[m_row - i - 1][j]);
        }
    }
}

void SpreadSheet::mirrorD() {
    for (size_t i = 0; i < m_row; ++i) {
        for (size_t j = i + 1; j < m_col; ++j) {
            std::swap(m_board[i][j], m_board[j][i]);
        }
    }
}

void SpreadSheet::removeRows(std::initializer_list<size_t> rows) {
    std::vector<size_t> rowsToRemove(rows);
    std::sort(rowsToRemove.begin(), rowsToRemove.end(), std::greater<size_t>());

    for (size_t row : rowsToRemove) {
        if (row < m_row) {
            delete[] m_board[row]; 
            for (size_t i = row; i < m_row - 1; ++i) {
                m_board[i] = m_board[i + 1];
            }
            --m_row;
        }
    }
}

void SpreadSheet::removeCols(std::initializer_list<size_t> cols) {
    std::vector<size_t> colsToRemove(cols);
    std::sort(colsToRemove.begin(), colsToRemove.end(), std::greater<size_t>());

    for (size_t col : colsToRemove) {
        if (col < m_col) {
            for (size_t i = 0; i < m_row; ++i) {
                for (size_t j = col; j < m_col - 1; ++j) {
                    m_board[i][j] = m_board[i][j + 1];
                }
            }
            --m_col;
        }
    }
}

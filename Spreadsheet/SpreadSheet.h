#include "Cell.h"
#include <iostream>
#include <vector>
#include <string>
#include <initializer_list>
#include <iomanip>

class Proxy 
{
public:
    explicit Proxy(Cell* ptr);

public:    
    Cell& operator[] (size_t index);
    const Cell& operator[] (size_t index) const;

private:
    Cell* m_ptr;
};

class SpreadSheet
{
private:
    void rotate_left();	
    void rotate_right();
    Cell** m_board;
    size_t m_row;
    size_t m_col;
private:
	class Column;
public:
	SpreadSheet();
	SpreadSheet(const SpreadSheet& rhv);
	SpreadSheet(SpreadSheet&& rhv) noexcept;
	SpreadSheet(size_t row, size_t col);
	explicit SpreadSheet(size_t size);
	~SpreadSheet();
public:
	const SpreadSheet& operator=(const SpreadSheet& rhv);
	const SpreadSheet& operator=(SpreadSheet&& rhv) noexcept;
public:
	Cell& operator[](std::initializer_list<int> index);
	Column operator[](size_t pos);
    const Column operator[](size_t pos) const;
public:
	void resizeRow(size_t size);
	void resizeCol(size_t size);
	void resize(size_t s1, size_t s2);
    size_t row() const;
	size_t col() const;
	void rotate(size_t count);
	void mirrorH();
	void mirrorV();
	void mirrorD();
	void mirrorSD();
	void clear() noexcept;
	void removeRow(size_t row);
    void removeRows(std::initializer_list<size_t> rows);
    void removeCol(size_t col);
    void removeCols(std::initializer_list<size_t> cols);
    SpreadSheet slice(std::initializer_list<size_t> rows, std::initializer_list<size_t> cols); 
	const Cell** getVal() const;
    int max_length() const;
};

class SpreadSheet::Column 
{
    private:
        Cell* col;
    public:
        explicit Column(Cell* col);
    public:
        Column() = delete;
        Column(const Column&) = delete;
        Column(Column&&) = delete;

        const Column& operator=(const Column&) = delete;
        const Column& operator=(Column&&) = delete;
    public:
        Cell& operator[](size_t pos);
        const Cell& operator[](size_t pos) const;
};

bool operator==(const SpreadSheet& lhs, const SpreadSheet& rhs);
bool operator!=(const SpreadSheet& lhs, const SpreadSheet& rhs);

std::ostream& operator<<(std::ostream& out, const SpreadSheet& ob);

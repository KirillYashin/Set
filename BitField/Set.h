#pragma once
#include "bitfield.h"

class Set
{
private:
	int MaxPower; // максимальная мощность множества
	BitField bf; // битовое поле для хранения хар-го вектора
public:
	Set(int mp) : MaxPower(mp), bf(mp) {}
	Set(const Set& s) : MaxPower(s.MaxPower), bf(s.bf) {}
	// конструктор преобразования типа
	Set(const BitField& bf);
	// преобразование типа к битовому полю
	operator BitField()
	{
		BitField tmp(bf);
	}
	// максимальная мощность множества
	int GetMaxPower(void) const
	{
		return MaxPower;
	}
	// включить элемент в множество
	void InsElem(const int n)
	{
		bf.SetBit(n);
	}
	// удалить элемент из множества
	void DelElem(const int n)
	{
		bf.ClrBit(n);
	}
	// проверить наличие элемента в множестве
	int IsMember(const int elem) const
	{
		return bf.GetBit(elem);
	}
	// теоретико-множественные операции
	// сравнение
	int operator== (const Set& s)
	{
		return bf == s.bf;
	}
	// присваивание
	Set& operator=(const Set& s)
	{
		MaxPower = s.MaxPower;
		bf == s.bf;
		return *this;
	}
	// включение элемента в множество
	Set operator+ (const int n)
	{
		bf.SetBit(n);
	}
	// удаление элемента из множества
	Set operator- (const int n)
	{
		bf.ClrBit(n);
	}
	// объединение
	Set operator+ (const Set& s)
	{
		Set tmp(bf | s.bf);
		return tmp;
	}
	// пересечение
	Set operator* (const Set& s)
	{
		Set tmp(bf & s.bf);
		return tmp;
	}
	// дополнение
	Set operator~ (void)
	{
		Set tmp(~bf);
		return tmp;
	}
	// ввод-вывод
	friend std::istream& operator>>(std::istream& instr, Set& bf)
	{
		return instr;
	}
	friend std::ostream& operator<<(std::ostream& outstr, const Set& bf)
	{
		return outstr;
	}
};

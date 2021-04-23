#pragma once
#include "bitfield.h"

class Set
{
private:
	int MaxPower; // ������������ �������� ���������
	BitField bf; // ������� ���� ��� �������� ���-�� �������
public:
	Set(int mp) : MaxPower(mp), bf(mp) {}
	Set(const Set& s) : MaxPower(s.MaxPower), bf(s.bf) {}
	// ����������� �������������� ����
	Set(const BitField& bf);
	// �������������� ���� � �������� ����
	operator BitField()
	{
		BitField tmp(bf);
	}
	// ������������ �������� ���������
	int GetMaxPower(void) const
	{
		return MaxPower;
	}
	// �������� ������� � ���������
	void InsElem(const int n)
	{
		bf.SetBit(n);
	}
	// ������� ������� �� ���������
	void DelElem(const int n)
	{
		bf.ClrBit(n);
	}
	// ��������� ������� �������� � ���������
	int IsMember(const int elem) const
	{
		return bf.GetBit(elem);
	}
	// ���������-������������� ��������
	// ���������
	int operator== (const Set& s)
	{
		return bf == s.bf;
	}
	// ������������
	Set& operator=(const Set& s)
	{
		MaxPower = s.MaxPower;
		bf == s.bf;
		return *this;
	}
	// ��������� �������� � ���������
	Set operator+ (const int n)
	{
		bf.SetBit(n);
	}
	// �������� �������� �� ���������
	Set operator- (const int n)
	{
		bf.ClrBit(n);
	}
	// �����������
	Set operator+ (const Set& s)
	{
		Set tmp(bf | s.bf);
		return tmp;
	}
	// �����������
	Set operator* (const Set& s)
	{
		Set tmp(bf & s.bf);
		return tmp;
	}
	// ����������
	Set operator~ (void)
	{
		Set tmp(~bf);
		return tmp;
	}
	// ����-�����
	friend std::istream& operator>>(std::istream& instr, Set& bf)
	{
		return instr;
	}
	friend std::ostream& operator<<(std::ostream& outstr, const Set& bf)
	{
		return outstr;
	}
};

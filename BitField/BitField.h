#pragma once
#include <iostream>
#include <string>
#include <stdio.h>
#include <Exception.h>

typedef unsigned int TELEM;

class BitField
{
private:
	int BitLen; // длина битового пол€ - макс. к-во битов
	TELEM* pMem; // пам€ть дл€ представлени€ битового пол€ (16 бит)
	int MemLen; // к-во эл-тов ћем дл€ представлени€ бит.пол€
	// методы реализации
	// индекс в pћем дл€ бита n
	int GetMemIndex(const int n) const
	{
		return n >> 4;//—двиг вправо на 4 бита
	}
	// битова€ маска дл€ бита n
	TELEM GetMemMask(const int n) const
	{
		return 1 << (n & 15);//—двиг влево
	}
public:
	BitField(int len) : BitLen(len), MemLen((len + 15) >> 4)
	{
		pMem = new TELEM[MemLen];
		if (pMem != nullptr)
		{
			for (int i = 0; i < MemLen; ++i)
			{
				pMem[i] = 0;
			}
		}
	}

	BitField(const BitField& bf) : BitLen(bf.BitLen), MemLen(bf.MemLen)
	{
		pMem = new TELEM[MemLen];
		if (pMem != nullptr)
		{
			for (int i = 0; i < MemLen; ++i)
			{
				pMem[i] = bf.pMem[i];
			}
		}
	}

	~BitField()
	{
		delete pMem;
	}

	// получить длину (к-во битов)
	int GetLength(void) const
	{
		return BitLen;
	}

	// установить бит
	void SetBit(const int n)
	{
		if (!((n > -1) && (n < BitLen)))
			throw Exception("Wrong index");
		else
			pMem[GetMemIndex(n)] |= GetMemMask(n);
	}

	// очистить бит
	void ClrBit(const int n)
	{
		if (!((n > -1) && (n < BitLen)))
			throw Exception("Wrong index");
		else
			pMem[GetMemIndex(n)] &= ~GetMemMask(n);//ƒополнение до единицы(~)(мен€ем 0 на 1 и 1 на 0), 
	}

	// получить значение бита
	int GetBit(const int n) const
	{
		if (!((n > -1) && (n < BitLen)))
			throw Exception("Wrong index");
		else
			return pMem[GetMemIndex(n)] & GetMemMask(n);
	}

	// сравнение
	int operator==(const BitField& bf)
	{
		if (BitLen != bf.BitLen)
			return 0;
		else
		{
			for (int i = 0; i < MemLen, pMem != nullptr; ++i)
			{
				if (pMem[i] != bf.pMem[i]) { return 0; }
			}
		}
		return 1;
	}

	// присваивание
	BitField& operator=(const BitField& bf)
	{
		if (MemLen != bf.MemLen)
		{
			MemLen = bf.MemLen;
			if (pMem != nullptr)
			{
				delete pMem;
			}
			pMem = new TELEM[MemLen];
		}
		for (int i = 0; i < MemLen, pMem != nullptr; i++) {
			pMem[i] = bf.pMem[i];
		}
		return *this;
	}

	// операци€ "или"
	BitField operator|(const BitField& bf)
	{
		int tempLen;
		if (BitLen < bf.BitLen)
			tempLen = bf.BitLen;
		else
			tempLen = BitLen;
		BitField tempBit(tempLen);
		for (int i = 0; i < MemLen; i++)
		{
			tempBit.pMem[i] = pMem[i];
		}
		for (int i = 0; i < bf.MemLen; i++)
		{
			tempBit.pMem[i] |= bf.pMem[i];
		}
		return tempBit;
	}

	// операци€ "и"
	BitField operator&(const BitField& bf)
	{
		int tempLen;
		if (BitLen < bf.BitLen)
			tempLen = bf.BitLen;
		else 
			tempLen = BitLen;
		BitField tempBit(tempLen);
		for (int i = 0; i < MemLen; i++)
		{
			tempBit.pMem[i] = pMem[i];
		}
		for (int i = 0; i < bf.MemLen; i++)
		{
			tempBit.pMem[i] &= bf.pMem[i];
		}
		return tempBit;
	}

	// отрицание
	BitField operator~(void)
	{
		int tempLen = BitLen;
		BitField tempBit(tempLen);
		for (int i = 0; i < MemLen; i++)
		{
			tempBit.pMem[i] = ~pMem[i];
		}
		return tempBit;
	}

	// ввод-вывод
	friend std::istream& operator>>(std::istream& istr, BitField& bf)
	{
		int i = 0; char ch;
		do {
			istr >> ch;
		} while (ch != ' ');
		while (1) {
			istr >> ch;
			if (ch == '0') 
				bf.ClrBit(i++);
			else if (ch == '1')
				bf.SetBit(i++);
			else
				break;
		}
		return istr;
	}

	friend std::ostream& operator<<(std::ostream& outstr, const BitField& bf)
	{
		for (int i(0); i < bf.MemLen, bf.pMem != nullptr; i++)
		{
			std::cout << bf.pMem[i] << " ";
		}
		std::cout << std::endl;
		return outstr;
	}
};


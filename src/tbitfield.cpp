// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int _BitLen=1)
{
		BitLen = _BitLen;
		MemLen = (BitLen / 32) + 1;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
		{
			pMem[i] = 0;
		}
}

TBitField::TBitField(const TBitField &b) // конструктор копирования
{
		BitLen = b.BitLen;
		MemLen = b.MemLen;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
		{
			pMem[i] = b.pMem[i];
		}
}

TBitField::~TBitField()
{
	delete[]pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	return n / 32;
}

TELEM TBitField::GetMemMask(const int bit) const // битовая маска для бита n
{
	int p = bit % 32;
	  return 1 << p;
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int b) // установить бит
{
	 int pos;
	  pos = GetMemIndex(b);
	  TELEM mask;
	  mask = GetMemMask(b);
	  pMem[pos] |= mask;
}

void TBitField::ClrBit(const int b) // очистить бит
{
	  int pos;
	  pos = GetMemIndex(b);
	  TELEM mask;
	  mask = GetMemMask(b);
	  mask = ~mask;
	  pMem[pos] &= mask;
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	  int pos = GetMemIndex(b);
	  TELEM mask = GetMemMask(b);
	  int res;
	  res = pMem[pos] & mask;
	  return res;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if(this!= &bf)
	{
		if(MemLen != bf.MemLen)
		{
			MemLen = bf.MemLen;
			delete []pMem;
			pMem = new TELEM [MemLen];
		}
		for (int i=0; i < MemLen; i++)
		{
			pMem[i]=bf.pMem[i];
		}
	}
	BitLen = bf.BitLen;
	return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
  if (BitLen != bf.BitLen) return 0;
	  else
		{
			for (int i = 0; i < MemLen - 1; i++)
			{
				if (pMem[i] != bf.pMem[i]) return 0;
			}
			for (int i = (MemLen - 1) * 32; i < BitLen; i++)
			{
				if (GetBit(i) != bf.GetBit(i)) return 0;
			}
			return 1;
		 }
}

bool TBitField::operator!=(const TBitField &bf) const // сравнение
{
  if(*this == bf) return false;
	  else return true;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	 int maxBitLen = bf.BitLen;
	 if (BitLen>bf.BitLen)
	 {
		 maxBitLen = BitLen;
	 }
	  TBitField res(BitLen);
	  if (BitLen < bf.BitLen)
	  {
		  for (int i = 0; i < MemLen - 1; i++)
		  {
			  res.pMem[i] = pMem[i];
		  }
		  for (int i= (MemLen-1)*32; i<BitLen;i++)
		  {
			  if(GetBit(i))
			  {
				  res.SetBit(i);
			  }
		  }
		  for(int i=0;i<res.MemLen;i++)
		  {
			  res.pMem[i]=res.pMem[i] & bf.pMem[i];
		  }
	  }
	  else
	  {
		  for(int i=0;i<bf.MemLen;i++)
		  {
			  res.pMem[i]=bf.pMem[i];
		  }
		  for(int i= (bf.MemLen-1)*32; i<bf.BitLen;i++)
		  {
			  if(bf.GetBit(i))
			  {
				  res.SetBit(i);
			  }
		  }
		  for(int i=0;i<res.MemLen;i++)
		  {
			  res.pMem[i] = res.pMem[i] & pMem[i];
		  }
	  }
	  return res;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int maxBitLen = bf.BitLen;
	 if (BitLen>bf.BitLen)
	 {
		 maxBitLen = BitLen;
	 }
	  TBitField res(BitLen);
	  if (BitLen < bf.BitLen)
	  {
		  for (int i = 0; i < MemLen - 1; i++)
		  {
			  res.pMem[i] = pMem[i];
		  }
		  for (int i= (MemLen-1)*32; i<BitLen;i++)
		  {
			  if(GetBit(i))
			  {
				  res.SetBit(i);
			  }
		  }
		  for(int i=0;i<res.MemLen;i++)
		  {
			  res.pMem[i]=res.pMem[i] & bf.pMem[i];
		  }
	  }
	  else
	  {
		  for(int i=0;i<bf.MemLen;i++)
		  {
			  res.pMem[i]=bf.pMem[i];
		  }
		  for(int i= (bf.MemLen-1)*32; i<bf.BitLen;i++)
		  {
			  if(bf.GetBit(i))
			  {
				  res.SetBit(i);
			  }
		  }
		  for(int i=0;i<res.MemLen;i++)
		  {
			  res.pMem[i] = res.pMem[i] & pMem[i];
		  }
	  }
	  return res;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField res(*this);
	for(int i=0; i<MemLen; i++)
	{
		res.pMem[i] = ~pMem[i];
	}
	return res;
}

// ввод/вывод

istream &operator>>(istream &is, TBitField &bf) // ввод
{
	char c;
	int i=0;
	do
	{
		is>>c;
		if (c == '0') bf.ClrBit(i);
		if (c == '1') bf.SetBit(i);
		i++;
	} 
		while ((c == '0') || (c == '1'));
		return is;
}

ostream &operator<<(ostream &os, const TBitField &bf) // вывод
{
	for(int i=0; i<bf.BitLen; i++)
	{
		os<<bf.GetBit(i);
	}
	return os;
}

// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.h - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#ifndef __BITFIELD_H__
#define __BITFIELD_H__

#include <iostream>

using namespace std;

typedef unsigned int TELEM;

class TBitField
{
private:
  int  BitLen; // длина битового поля - макс. к-во битов
  TELEM *pMem; // память для представления битового поля
  int  MemLen; // к-во эл-тов Мем для представления бит.поля

  // методы реализации
  int   GetMemIndex(const int n) const
  {
	  return n / 32;
  }
  ; // индекс в pМем для бита n       (#О2)
  TELEM GetMemMask(const int bit) const
  {
	  int p = bit % 32;
	  return 1 << p;
  }
  ; // битовая маска для бита n       (#О3)
public:
	TBitField(int _BitLen = 1)
	{
		BitLen = _BitLen;
		MemLen = (BitLen / 32) + 1;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
		{
			pMem[i] = 0;
		}
	}
	               //                                   (#О1)
	TBitField(const TBitField &b)
	{
		BitLen = b.BitLen;
		MemLen = b.MemLen;
		pMem = new TELEM[MemLen];
		for (int i = 0; i < MemLen; i++)
		{
			pMem[i] = b.pMem[i];
		}
	}   //                                   (#П1)
  ~TBitField()
  {
	  delete[]pMem;
  }
	  ;                      //                                    (#С)

  // доступ к битам
  int GetLength(void) const
  {

  };      // получить длину (к-во битов)           (#О)
  void SetBit(const int b)// установить бит                       (#О4)
  {
	  int pos;
	  pos = GetMemIndex(b);
	  TELEM mask;
	  mask = GetMemMask(b);
	  pMem[pos] |= mask;

  }       
  void ClrBit(const int b)// очистить бит                         (#П2)
  {
	  int pos;
	  pos = GetMemIndex(b);
	  TELEM mask;
	  mask = GetMemMask(b);
	  mask = ~mask;
	  pMem[pos] &= mask;
  }
		
      
  int  GetBit(const int b) const // получить значение бита               (#Л1
  {
	  int pos = GetMemIndex(b);
	  TELEM mask = GetMemMask(b);
	  int res;
	  res = pMem[pos] & mask;
	  return res;
  }
 

  // битовые операции
  int operator==(const TBitField &bf) const; // сравнение                 (#О5)
  int operator!=(const TBitField &bf) const; // сравнение
  TBitField& operator=(const TBitField &bf); // присваивание              (#П3)
  TBitField  operator|(const TBitField &b)// операция "или"            (#О6)
  {
	  TBitField res(BitLen);
	  for (int i = 0; i < MemLen; i++)
	  {
		  res.pMem[i] = pMem[i] | b.pMem[i];
		  return res;
	  }
  }
  TBitField  operator&(const TBitField &bf)
  {

  }
  // операция "и"              (#Л2)
  TBitField  operator~(void);                // отрицание                  (#С)

  friend istream &operator>>(istream &istr, TBitField &bf);       //      (#О7)
  friend ostream &operator<<(ostream &ostr, const TBitField &bf); //      (#П4)
};
// Структура хранения битового поля
//   бит.поле - набор битов с номерами от 0 до BitLen
//   массив pМем рассматривается как последовательность MemLen элементов
//   биты в эл-тах pМем нумеруются справа налево (от младших к старшим)
// О8 Л2 П4 С2

#endif

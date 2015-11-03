#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// ������ �������
template <class ValType>
class TVector {
protected:
	ValType *pVector;
	int Size;       // ������ �������
	int StartIndex; // ������ ������� �������� �������
public:
	TVector(int s = 10, int si = 0);
	TVector(const TVector &v);                // ����������� �����������
	virtual ~TVector();
	int GetSize() const { return Size; } // ������ �������
	int GetStartIndex() const { return StartIndex; } // ������ ������� ��������
	ValType& operator[](int pos) const;             // ������
	bool operator==(const TVector &v) const;  // ���������
	bool operator!=(const TVector &v) const;  // ���������
	TVector& operator=(const TVector &v);     // ������������

	// ��������� ��������
	TVector  operator+(const ValType &val);   // ��������� ������
	TVector  operator-(const ValType &val);   // ������� ������
	TVector  operator*(const ValType &val);   // �������� �� ������

	// ��������� ��������
	TVector  operator+(const TVector &v);     // ��������
	TVector  operator-(const TVector &v);     // ���������
	ValType  operator*(const TVector &v);     // ��������� ������������

	// ����-�����
	template <class ValType>
	friend istream& operator>>(istream &in, TVector &v) 
	{
		for (int i = 0; i < v.Size; i++)
			in >> v.pVector[i];
		return in;
	}
	template <class ValType>
	friend ostream& operator<<(ostream &out, const TVector &v) 
	{
		for (int i = 0; i < v.Size + v.StartIndex; i++)
			out << v[i] << ' ';
		return out;
	}
};

template <class ValType>
TVector<ValType>::TVector(int s, int si = 0) 
{
	if (s > MAX_VECTOR_SIZE) 
		throw invalid_argument("CONSTRUCTOR: MAX_VECTOR_SIZE < SIZE");
	
	if (s < 0) 
		throw invalid_argument("CONSTRUCTOR: SIZE < 0");
	
	if (si < 0) 
		throw invalid_argument("CONSTRUCTOR: START INDEX < 0");

	if (!(si < s)) 
		throw invalid_argument("CONSTRUCTOR: START INDEX >= SIZE");
	
	pVector = new ValType[s];
	Size = s;
	StartIndex = si;

	for (int i = 0; i < Size; i++) 
		pVector[i] = ValType();
	
} /*-------------------------------------------------------------------------*/

template <class ValType> //����������� �����������
TVector<ValType>::TVector(const TVector<ValType> &v) 
{
	Size = v.Size;
	StartIndex = v.StartIndex;
	pVector = new ValType[Size];

	for (int i = 0; i < StartIndex; i++) 
		pVector[i] = ValType();

	for (int i = StartIndex; i < Size; i++) 
		pVector[i] = v.pVector[i];
} /*-------------------------------------------------------------------------*/

template <class ValType>
TVector<ValType>::~TVector() 
{
	delete[] pVector;
} /*-------------------------------------------------------------------------*/

template <class ValType> // ������
ValType& TVector<ValType>::operator[](int pos) const 
{
	if (pos < 0) 
		throw invalid_argument("[] ARGUMENT < 0");
	
	if (!(pos < Size)) 
		throw invalid_argument("[] ARGUMENT > SIZE");
/*	
	if (pos < StartIndex) 
		throw invalid_argument("[] ARGUMENT < START INDEX");*/
	
	return pVector[pos];
} /*-------------------------------------------------------------------------*/


template <class ValType> // ���������
bool TVector<ValType>::operator==(const TVector &v) const 
{
	if (Size != v.GetSize()) 
	{
		return false;
	}
	if (StartIndex != v.GetStartIndex())
	{
		return false;
	}

	for (int i = StartIndex; i < Size; i++) 
	{
		if (pVector[i] != v.pVector[i]) 
		{
			return false;
		}
	}
	return true;
} /*-------------------------------------------------------------------------*/

template <class ValType> // ���������
bool TVector<ValType>::operator!=(const TVector &v) const 
{
	return !(*this == v);
} /*-------------------------------------------------------------------------*/

template <class ValType> // ������������
TVector<ValType>& TVector<ValType>::operator=(const TVector &v) 
{
	if (this != &v) 
	{
		if (Size != v.GetSize())
		{
			delete[]pVector;
			pVector = new ValType[v.Size];
		}
		Size = v.GetSize();
		StartIndex = v.GetStartIndex();
		for (int i = StartIndex; i < Size; i++) 
		{
			pVector[i] = v.pVector[i];
		}
	}
	return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // ��������� ������
TVector<ValType> TVector<ValType>::operator+(const ValType &val) 
{
	for (int i = StartIndex; i < Size; i++) 
		pVector[i] = pVector[i] + val;
	
	return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // ������� ������
TVector<ValType> TVector<ValType>::operator-(const ValType &val) 
{
	for (int i = StartIndex; i < Size; i++) 
		pVector[i] = pVector[i] - val;
	
	return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // �������� �� ������
TVector<ValType> TVector<ValType>::operator*(const ValType &val) 
{
	for (int i = StartIndex; i < Size; i++) 
		pVector[i] = pVector[i] * val;
	
	return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // ��������
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType> &v) 
{
	if ((GetSize() != v.GetSize()) || (GetStartIndex() != v.GetStartIndex())) 
		throw invalid_argument("ADDITION OF VECTORS OF DIFFERENT LENGTH");

	TVector<ValType> result(GetSize(), GetStartIndex());

	for (int i = StartIndex; i < Size; i++) 
		result[i] = pVector[i] + v.pVector[i];
	
	return result;
} /*-------------------------------------------------------------------------*/

template <class ValType> // ���������
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType> &v) 
{
	if ((GetSize() != v.GetSize()) || (GetStartIndex() != v.GetStartIndex())) 
		throw invalid_argument("SUBTRACTION OF VECTORS OF DIFFERENT LENGTH");

	TVector<ValType> result(GetSize(), GetStartIndex());

	for (int i = StartIndex; i < Size; i++)
		result[i] = pVector[i] - v.pVector[i];
	
	return result;
} /*-------------------------------------------------------------------------*/

template <class ValType> // ��������� ������������
ValType TVector<ValType>::operator*(const TVector<ValType> &v) 
{
	if ((GetSize() != v.GetSize()) || (GetStartIndex() != v.GetStartIndex())) 
		throw invalid_argument("MULTIPLICATION OF VECTORS OF DIFFERENT LENGTH");

	ValType result = 0;
	
	for (int i = StartIndex; i < Size; i++) 
		result = result + pVector[i] * v.pVector[i];
		
	return result;
} /*-------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/
/*---------------------------------------------------------------------------*/

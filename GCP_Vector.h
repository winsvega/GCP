#ifndef GCP_VectorH
#define GCP_VectorH

namespace gcp
{
	template< class T>
	class GCP_Vector
	{
	protected:
		T* _mElems;
		unsigned int _mSize;
		unsigned int _iSize;
		int _startsize;
		int _mulsize;
		void initValues()
		{
			_startsize = 4;
			_mulsize = 2;
			_mSize = _startsize;
			_iSize = 0;
			_mElems = new T[_mSize];
		}
		void resize(int newSize){
			T* newElems = new T[newSize];

			for (unsigned int i = 0; i < _iSize; i++)
				newElems[i] = _mElems[i];

			_mSize = newSize;
			delete[]_mElems;
			_mElems = newElems;
		}

		void quickSort(GCP_Vector<T> *a, int l, int r)
		{
			if (a->size() < 2)
				return;

			T x = a->at(l + (r - l) / 2); //(l+r)/2,
			int i = l;
			int j = r;

			while (i <= j)
			{
				while (a->compareAltB(a->at(i), x)) i++;    //a(i) < x
				while (a->compareAgtB(a->at(j), x)) j--;    //a(j) > x
				if (i <= j)
				{
					a->swap(i, j);
					i++;
					j--;
				}
			}
			if (i < r)
				quickSort(a, i, r);

			if (l < j)
				quickSort(a, l, j);
		}
	public:
		GCP_Vector()		{
			initValues();
		}
		GCP_Vector (GCP_Vector const &rhs)
		{
			initValues();
			clear();
			int size = rhs.size();
			for (int i = 0; i < size; i++)
				push_back(rhs.at(i));
		}
		~GCP_Vector()	{
			delete[]_mElems;
		}

		void push_back(T element)		{
			//cause SP to trouble if copying instance is another vector!!!
			_mElems[_iSize] = element;
			_iSize++;
			if (_iSize >= _mSize)
				resize(_mSize*_mulsize);
		}

		void slectDistinct()
		{
			int k = 0;
			int *toDelete = new int[_iSize];
			for (unsigned int i = 0; i < _iSize; i++)
			{
				for (unsigned int j = i + 1; j < _iSize; j++)
				{
					if (_mElems[j] == _mElems[i])
					{
						toDelete[k] = j;
						k++;
					}
				}
			}

			//!REV
			for (unsigned int i = 0; i < k; i++)
			{
				erase(toDelete[i]);
				for (unsigned int j = i + 1; j < k; j++)
				{
					if (toDelete[j] > toDelete[i])
						toDelete[j]--;
				}
			}

			delete toDelete;
		}

		void qsort()
		{
			quickSort(this, 0, size() - 1);
		}

		bool compareAltB(T a, T b)
		{
			if (a < b)
				return true;
			return false;
		}

		bool compareAgtB(T a, T b)
		{
			if (a > b)
				return true;
			return false;
		}

		T pop_back(){
			_iSize--;
			return _mElems[_iSize];
		}

		T pop_first(){

			T value = _mElems[0];
			for (unsigned int i = 0; i < _iSize - 1; i++)
				_mElems[i] = _mElems[i + 1];

			_iSize--;

			return value;

		}

		bool has_value(T val)
		{
			for (unsigned int i = 0; i < _iSize; i++)
				if (_mElems[i] == val)
					return true;
			return false;
		}

		void erase(unsigned int _index)		{
			if (_index >= _iSize)
				return;

			//memory loss?  do like resize operation
			//for (unsigned int i = _index; i < _iSize - 1; i++)
			//	_mElems[i] = _mElems[i + 1];

			T* newElems = new T[_mSize];
			for (unsigned int i = 0; i < _index; i++)
				newElems[i] = _mElems[i];

			for (unsigned int i = _index+1; i < _iSize; i++)
				newElems[i-1] = _mElems[i];

			delete[]_mElems;
			_mElems = newElems;

			_iSize--;
		}

		unsigned int size() const
		{
			return _iSize;
		}

		void clear()
		{
			_iSize = 0;
			_mSize = _startsize;
			delete[]_mElems;
			_mElems = new T[_mSize];
		}

		T& at(unsigned int x) const
		{
			if (x >= _iSize)
			{
				//assert(!"Value out of range!");
				x = _iSize - 1;
			}
			return (_mElems[x]);
		}

		T& operator[](unsigned int x){
			if (x >= _iSize)
			{
				//assert(!"Value out of range!");
				x = _iSize-1;
			}
			return (_mElems[x]);
		}

		GCP_Vector& operator=(GCP_Vector const &rhs)
		{
			if (this != &rhs)
			{
				clear();
				for (int i = 0; i < rhs.size(); i++)
				{
					push_back(rhs.at(i));
				}
			}
			return *this;
		}

		void eat(GCP_Vector *rhs)
		{
			clear();
			int size = rhs->size();
			for (int i = 0; i < size; i++)
			{
				push_back(rhs->pop_first());
			}
		}

		void swap(unsigned int i, unsigned int j)
		{
			if (i >= _iSize || j >= _iSize)
				return;

			T x = _mElems[i];
			_mElems[i] = _mElems[j];
			_mElems[j] = x;

		}
	};

	typedef GCP_Vector<int> GCP_VectorInt;
	typedef GCP_Vector<double> GCP_VectorDouble;
}

#endif

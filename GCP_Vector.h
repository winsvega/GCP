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
			T x = a->at(l + (r - l) / 2);
			//запись эквивалентна (l+r)/2,
			//но не вызввает переполнения на больших данных
			int i = l;
			int j = r;
			//код в while обычно выносят в процедуру particle
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
			_startsize = 4;
			_mulsize = 2;
			_mSize = _startsize;
			_iSize = 0;
			_mElems = new T[_mSize];
		}
		~GCP_Vector()	{
			delete[]_mElems;
		}

		void push_back(T element)		{
			_mElems[_iSize] = element;
			_iSize++;
			if (_iSize >= _mSize)
				resize(_mSize*_mulsize);
		}

		void sort()
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

		void erase(unsigned int x)		{
			if (x >= _iSize)
				return;


			for (unsigned int i = x; i < _iSize - 1; i++)
				_mElems[i] = _mElems[i + 1];

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

		T &at(unsigned int x) const
		{
			if (x >= _iSize)
			{
				//assert(!"Value out of range!");
				x = _iSize - 1;
			}
			return (_mElems[x]);
		}

		GCP_Vector &operator=(const GCP_Vector &rhs)
		{
			//! NOT WORKING
			clear();
			for (int i = 0; i < rhs.size(); i++)
			{
				push_back(rhs.at(i));
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

		T &operator[](unsigned int x){
			if (x >= _iSize)
				x = _iSize;
			return (_mElems[x]);
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
}

#endif

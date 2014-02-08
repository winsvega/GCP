#ifndef GCP_VectorH
#define GCP_VectorH

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
		 
			for(unsigned int i=0;i<_iSize;i++)
				newElems[i] = _mElems[i];
		 
			_mSize = newSize;			
			delete []_mElems; 
			_mElems = newElems;			
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
			delete  []_mElems; 
		}

		void push_back(T element)		{
			_mElems[_iSize] = element;
			_iSize++;
			if(_iSize>=_mSize)
				resize(_mSize*_mulsize);
		}

		T pop_back(){
			_iSize--;
			return _mElems[_iSize];
		}

		T pop_first(){

			T value = _mElems[0];
			for(unsigned int i=0; i<_iSize-1; i++)
				_mElems[i]=_mElems[i+1];

			_iSize--;

			return value;

		}

		bool has_value(T val)
		{
			for(unsigned int i=0; i<_iSize; i++)
				if(_mElems[i] == val)
					return true;
			return false;
		}
		void erase(unsigned int x)		{
			if(x >= _iSize)
				return;

			
			for(unsigned int i=x; i<_iSize-1; i++)
				_mElems[i]=_mElems[i+1];

			_iSize--;	
		}

		unsigned int size()
		{
			return _iSize;
		}

		void clear()
		{
			_iSize = 0;
			_mSize = _startsize;
			delete []_mElems;
			_mElems = new T[_mSize];	
		}

		T &at(unsigned int x)		{
			if(x >= _iSize)
				x = _iSize;
			return (_mElems[x]);
		}

		GCP_Vector &operator=(GCP_Vector rhs)
		{
			//! NOT WORKING
			clear();			
			for(int i=0; i<rhs.size(); i++)
			{
				push_back(rhs.at(i));
			}
			return *this;
		}

		void eat (GCP_Vector *rhs)
		{
			clear();		
			int size = rhs->size();
			for(int i=0; i<size; i++)
			{
				push_back(rhs->pop_first());
			}
		}



		T &operator[](unsigned int x){
			if(x >= _iSize)
				x = _iSize;
			return (_mElems[x]);
		} 
		void swap (unsigned int i, unsigned int j)
		{
			if(i >= _iSize || j >= _iSize)
			return;	

			T x = _mElems[i];
			_mElems[i] = _mElems[j];
			_mElems[j] = x;

		}
};




#endif
#ifndef GCP_SPointerH
#define GCP_SPointerH

namespace gcp
{
   template <class T>
   class GCP_SPointer;
   class GCP_SPointerBase
   {
   private:
      int  _nRef;
      bool _isEmpty;
      void AddRef() 	{ _nRef++; }
      int DelRef()	{ _nRef--;		return _nRef; }
   public:
      GCP_SPointerBase() : _nRef(0), _isEmpty(false){}
      template <class T>
      friend class GCP_SPointer;
   };

   template <class T>
   class GCP_SPointer
   {
   private:
      T* _pointee;
      void release(){
         if (_pointee != NULL)			{
            assert(_pointee->_nRef > 0);
            if (_pointee->DelRef() == 0)				{
               delete _pointee;
               _pointee = NULL;
            }
         }
      }

   public:
      explicit GCP_SPointer() : _pointee(NULL){}
      GCP_SPointer(int n) : _pointee(NULL){}
      explicit GCP_SPointer(T* pointee) : _pointee(pointee)
      {
         if (pointee != NULL)
         {
            if (!(_pointee->_isEmpty))
               _pointee->AddRef();
            else
               _pointee = NULL;
         }
      };
      GCP_SPointer(GCP_SPointer const& pnt) : _pointee(NULL) {
         release();
         _pointee = pnt.getPointer();
         if (_pointee != NULL)
         {
            if (!(_pointee->_isEmpty))
               _pointee->AddRef();
            else
               _pointee = NULL;
         }
      }

      T* getPointer() const  { return _pointee; }	//Опасно отдавать указатель наружу!


      GCP_SPointer& operator=(GCP_SPointer const &rhs)			//Присваиваем один указатель другому
      {
         if (_pointee != rhs.getPointer())		//Разные указатели. Отпускаем наш указатель. Новому добавляем ссылку.
         {
            release();
            _pointee = rhs.getPointer();
            _pointee->AddRef();
         }
         return *this;
      }

      GCP_SPointer&  operator=(const int rhs)		{ _pointee = NULL;	return *this; }

      ~GCP_SPointer(){ release(); };

      ///
      void setEmpty(bool empty)
      {
         //Застваить все окружение и все смартпоинтеры думать, что класс удален (потом пожно отключить)
         if (_pointee != NULL)
         {
            if (_pointee->_nRef > 0)
               _pointee->_isEmpty = empty;
         }
      }

      ///
      int getRefCount() const
      {
         if (_pointee)
            return _pointee->_nRef;
         return -1;
      }

      ///
      bool isEmpty()
      {
         if (_pointee != NULL)
            return  _pointee->_isEmpty;

         return true;
      }


      T& operator*() const	{ return *_pointee; }//оператор *		
      T* operator->() const	{ return _pointee; }//оператор ->
      operator T* ()	{ return _pointee; }//приведение к типу T*
	  //operator GCP_SPointer<T>() { return GCP_SPointer<T>(this); }

      /*template <class D>
      operator GCP_SPointer<D> ()
      {
      GCP_SPointer<D> sliced = GCP_SPointer<D>(static_cast<D>_pointee);
      return sliced;
      }*/

      //оператор взятия адреса
      //T** operator& () {	return &_pointee;	}

      //операторы сравнения
      bool operator!() const { return _pointee == 0; }
      //inline friend bool operator != (const GCP_SPointer& lhs, const GCP_SPointer& rhs) { return lhs.pointee_ != rhs.pointee_;}
      //inline friend bool operator != (const GCP_SPointer& lhs, int rhs) { return lhs.pointee_ != rhs;}
      inline friend bool operator == (const GCP_SPointer& lhs, const GCP_SPointer& rhs) { return lhs._pointee == rhs._pointee; }
      //inline friend bool operator == (const SmartPtr& lhs, const T* rhs) { return lhs.pointee_ == rhs;}
      //inline friend bool operator == (const T* lhs, const SmartPtr* rhs) { return lhs == rhs.pointee_;}
      //inline friend bool operator != (const SmartPtr& lhs, const T* rhs) { return lhs.pointee_ != rhs;}
      //inline friend bool operator != (const T* lhs, const SmartPtr& rhs) { return lhs != rhs.pointee_;}
   };
}
#endif


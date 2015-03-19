#ifndef GCP_DelegateH
#define GCP_DelegateH
/////////////////////////////////
//http://habrahabr.ru/post/78299/
/////////////////////////////////
#include <assert.h>
namespace gcp
{
	//////////////////////////////////////////////////////////////////
	//  Контейнер для хранения до 2-х аргументов.
	//////////////////////////////////////////////////////////////////
	struct NIL {};
	class IArguments { public: virtual ~IArguments() {} };
	template< class T1 = NIL, class T2 = NIL>
	class Arguments : public IArguments
	{
		public: Arguments() {}
		public: Arguments(T1 i_arg1) :
				arg1(i_arg1) {}
		public: Arguments(T1 i_arg1, T2 i_arg2) :
				arg1(i_arg1), arg2(i_arg2) {}
		public: T1 arg1; T2 arg2;
	};
	//////////////////////////////////////////////////////////////////
	//  Контейнер для хранения указателя на метод.
	//////////////////////////////////////////////////////////////////
	class IContainer {
	public:
		virtual void* Call(void* arg){ return (void*)0; };
		virtual ~IContainer(){};
	};

	template< class T, class M>
	class Container : public IContainer {};
	//////////////////////////////////////////////////////////////////
	//  Специализация для метода c входным аргументом void*
	//////////////////////////////////////////////////////////////////
	template< class T>
	class Container< T, void (T::*)(void*) > : public IContainer
	{
		typedef void (T::*M)(void*);
		public: Container(T* c, M m) : m_class(c), m_method(m) {}
		private: T* m_class; M m_method;
		public:
		void* Call(void* i_arg1)
		{
			(m_class->*m_method)(i_arg1);
			return (void*)0;
		}
		//~Container(){delete m_class;}
	};
	//////////////////////////////////////////////////////////////////
	//  Специализация для метода c входным аргументом void* и выходным аргументом void*
	//////////////////////////////////////////////////////////////////
	template< class T>
	class Container< T, void* (T::*)(void*) > : public IContainer
	{
		typedef void* (T::*M)(void*);
		public: Container(T* c, M m) : m_class(c), m_method(m) {}
		private: T* m_class; M m_method;
		public:
		void* Call(void* i_arg1)
		{
			return (m_class->*m_method)(i_arg1);
		}
		//~Container(){delete m_class;}
	};
}
#endif

#pragma once
#include "stdafx.h"

template<class TYPE>
class List
{
private:
	template<class T>
	class Element
	{
	private:
		Element<T>* _pNext;
		Element<T>* _pPrevious;
		T* _Object;

	public:
		Element();
		~Element();

		void setNext(Element<T>* pn);
		Element<T>* getNext();

		void setPrevious(Element<T>* pp);
		Element<T>* getPrevious();

		void setObject(T* obj);
		T* getObject();


	};

	template<class T>
	inline Element<T>::Element()
	{
		pNext = NULL;
		pPrevious = NULL;
	}

	template<class T>
	inline Element<T>::~Element()
	{
		pNext = NULL;
		pPrevious = NULL;
	}

	template<class T>
	inline void Element<T>::setNext(Element<T>* pn)
	{
		_pNext = pn;
	}

	template<class T>
	inline Element<T>* Element<T>::getNext()
	{
		return _pNext;
	}

	template<class T>
	inline void Element<T>::setPrevious(Element<T>* pp)
	{
		_pPrevious = pp;
	}

	template<class T>
	inline Element<T>* Element<T>::getPrevious()
	{
		return _pPrevious;
	}

	template<class T>
	inline void setObject(T* obj)
	{
		_Object = obj;
	}

	template<class T>
	inline T* getObject()
	{
		return _Object;
	}



	Element<TYPE>* pFirst;
	Element<TYPE>* pCurrent;


public:
	List();
	~List();

	void initialize();
	bool includeElement(Element<TYPE>* pElement);
	bool includeObject(TYPE* pObj);

};

template<class TYPE>
inline List<TYPE>::List()
{
	initialize();
}

template<class TYPE>
inline List<TYPE>::~List()
{
	//Código que desaloca os elementos
}

template<class TYPE>
inline void List<TYPE>::initialize()
{
	pFirst = NULL;
	pCurrent = NULL;
}

template<class TYPE>
inline bool List<TYPE>::includeElement(Element<TYPE>* pElement)
{
	if (pElement != NULL)
	{
		if (pFirst == NULL)
		{
			pFirst = pElement;
			pCurrent = pFirst;
		}
		else
		{
			pElement->setPrevious(pCurrent);
			pElement->setNext(NULL);
			pCurrent->setNext(pElement);
			pCurrent = pCurrent->getNext();
		}
		return true;
	}
	else
	{
		return false;
	}
}

template<class TYPE>
inline bool List<TYPE>::includeObject(TYPE* pObj)
{
	if (pObj != NULL)
	{
		Element<TYPE>* pElement;
		pElement = new Element<TYPE>();
		pElement->setObject(pObj);
		includeElement(pElement);
		return true;
	}
	else
	{
		return false;
	}
}


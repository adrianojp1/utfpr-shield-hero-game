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
		Element()
		{
			_pNext = NULL;
			_pPrevious = NULL;
		}

		~Element()
		{
			_pNext = NULL;
			_pPrevious = NULL;
		}

		void setpNext(Element<T>* pn)
		{
			_pNext = pn;
		}

		Element<T>* getpNext()
		{
			return _pNext;
		}


		void setpPrevious(Element<T>* pp)
		{
			_pPrevious = pp;
		}

		Element<T>* getpPrevious()
		{
			return _pPrevious;
		}

		void setObject(T* obj)
		{
			_Object = obj;
		}

		T* getObject()
		{
			return _Object;
		}


	};

// List private
private:
	Element<TYPE>* _pFirst;
	Element<TYPE>* _pCurrent;


public:
	// Iterator //
	class iterator
	{
	public:
		friend class List<TYPE>;
		typedef TYPE& reference;
		typedef Element<TYPE>* pointer;

		iterator() : _elem(NULL)
		{
		}
		iterator(pointer ptr) : _elem(ptr)
		{
		}
		reference operator*()
		{
			return (_elem->getObject());
		}
		reference operator->()
		{
			return (*(*this));
		}

		// iterator++;
		iterator& operator++()
		{
			if (_elem)
			{
				_elem = _elem->getpNext();
			}
			return (*this);
		}

		iterator operator++ (int)
		{
			iterator it = *this;
			++(*this);
			return it;
		}

		iterator& operator--()
		{
			if (_elem)
			{
				_elem = _elem->getpPrevious();
			}
			return (*this);
		}

		iterator operator--(int)
		{
			iterator it = *this;
			--(*this);
			return it;
		}

		bool operator != (const iterator& iterator) const
		{
			return (_elem != iterator._elem);
		}

		bool operator == (const iterator& iterator) const
		{
			return (_elem == iterator._elem);
		}

	private:
		pointer _elem;
	};

//List public
public:
	List()
	{
		initialize();
	}

	~List()
	{
		clear();
	}


	void initialize()
	{
		_pFirst = NULL;
		_pCurrent = NULL;
	}

	void clear()
	{
		Element<TYPE>* paux1;
		Element<TYPE>* paux2;

		paux1 = _pFirst;
		paux2 = paux1;

		while (paux1 != NULL)
		{
			paux2 = paux1->getpNext();
			delete (paux1);
			paux1 = paux2;
		}
		_pFirst = NULL;
		_pCurrent = NULL;
	}


	bool includeElement(Element<TYPE>* pElement)
	{
		if (pElement != NULL)
		{
			if (_pFirst == NULL)
			{
				_pFirst = pElement;
				_pFirst->setpPrevious(NULL);
				_pFirst->setpNext(NULL);
				_pCurrent = _pFirst;
			}
			else
			{
				pElement->setpPrevious(_pCurrent);
				pElement->setpNext(NULL);
				_pCurrent->setpNext(pElement);
				_pCurrent = _pCurrent->getpNext();
			}
			return true;
		}
		else
		{
			return false;
		}
	}

	bool includeObject(TYPE* pObj)
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


	Element<TYPE>* getpFirst()
	{
		return _pFirst;
	}

	Element<TYPE>* getpCurrent()
	{
		return _pCurrent;
	}
};


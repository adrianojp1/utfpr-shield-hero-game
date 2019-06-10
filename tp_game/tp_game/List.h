#pragma once

template<class T>
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



	Element<T>* pFirst;
	Element<T>* pCurrent;


public:
	List();
	~List();

	void initialize();
	bool includeElement(Element<T>* pElement);
	bool includeObject(T* pObj);

};

template<class T>
inline List<T>::List()
{
	initialize();
}

template<class T>
inline List<T>::~List()
{
	//Código que desaloca os elementos
}

template<class T>
inline void List<T>::initialize()
{
	pFirst = NULL;
	pCurrent = NULL;
}

template<class T>
inline bool List<T>::includeElement(Element<T>* pElement)
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

template<class T>
inline bool List<T>::includeObject(T* pObj)
{
	if (pObj != NULL)
	{
		Element<T>* pElement;
		pElement = new Element<T>();
		pElement->setObject(pObj);
		includeElement(pElement);
		return true;
	}
	else
	{
		return false;
	}
}


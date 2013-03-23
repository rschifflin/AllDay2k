//Custom heap for Ricochet Robots solver
#include <iostream>
#include <exception>
#include <stdint.h>

class OpenSetException: public std::exception
{
	const char* errString;
	public:
		OpenSetException(const char* msg): errString(msg){}
		const char* what() const throw() { return errString; }
};
	
namespace RicochetRobots
{
	template <class T, class Cmp>
	OpenSet<T, Cmp>::OpenSet()
	{
		m_end = 0;
		m_size = 1024;
		m_isFull = false;
		
		try
		{
			m_list = new T[m_size];
		}
		catch (std::bad_alloc& e)
		{
				std::cerr << "Error: " << e.what() << "\nOpen Set could not allocate initial " << m_size << "-element array.";
				std::terminate(); //Cannot size the array
		}
	}
	//Non-pointer instances of T
	template <class T, class Cmp>
	void OpenSet<T, Cmp>::m_delete()
	{
		//If m_delete is called, it means that m_end - 1u is guarenteed to be inside m_list's array bounds.
		
		//Move last element to root, discard root
		m_list[0] = m_list[m_end - 1u];
		m_end -= 1u;
		
		//Define variables:
		//
		//	i = index of current value;
		//	li = 2*i + 1 = index of current value's left child
		//	ri = 2*i + 2 = index of current value's right child
		//	swap = min(i, li, ri)
		//
		unsigned int i = 0;
		unsigned int li = 1;
		unsigned int ri = 2;
		unsigned int swap = 0;
		
		//While the heap property is not satisfied...
		while (true)
		{
			i = swap;
			li = i*2 + 1;
			ri = i*2 + 2;
			
			if (li < m_end && Cmp()(m_list[li], m_list[swap]) )
				swap = li;
			
			if (ri < m_end && Cmp()(m_list[ri], m_list[swap]) )
				swap = ri;
				
			if (i != swap)
			{
				T tmp = m_list[i];
				m_list[i] = m_list[swap];
				m_list[swap] = tmp;
			}
			else
				break;
		}
	}
	
	template <class T, class Cmp>
	void OpenSet<T, Cmp>::m_insert(T insValue)
	{
		//If m_insert is called, m_end is guarenteed to be within m_list's array bounds
		
		//Add to the end and sift up
		m_list[m_end] = insValue;
		m_end += 1;
		
		unsigned int i = m_end - 1u;
		unsigned int p = (i - 1u) / 2; //p = parent index of list[i]
		
		while (true)
		{
			if (i > 0 && Cmp()(m_list[i], m_list[p]) )
			{
				T tmp = m_list[p];
				m_list[p] = m_list[i];
				m_list[i] = tmp;
				i = p;
				p = (i - 1u) / 2;
			}
			else
				break;
		}
	}

	template <class T, class Cmp>
	OpenSet<T, Cmp>::~OpenSet()
	{
		delete[] m_list;
		m_list = NULL;
	}
	
	template <class T, class Cmp>
	void OpenSet<T, Cmp>::push(T pushValue)
	{
		
		if (!m_isFull)
		{	
			if (m_end == 0 && m_size > 0)
			{
				m_list[0] = pushValue;
				m_end = 1;
			}
			else if (m_end >= m_size) //Expand the array
			{
				try
				{
					if (2*m_size + 1 + m_size > MEM_LIMIT) //Memory needed to allocate and swap arrays versus memory limit
						throw OpenSetException("Memory limit reached!");
					T* newList = new T[2*m_size + 1];
					std::copy(&m_list[0], &m_list[m_end - 1u], &newList[0]);
					delete[] m_list;
					m_list = newList;
					m_size *= 2;
					m_size += 1;
					m_insert(pushValue);				
				}
				catch (std::bad_alloc& e)
				{
					m_isFull = true;
				}
				catch (OpenSetException& e)
				{
					m_isFull = true;					
				}
			}
			else
			{
				m_insert(pushValue);
			}
		}
		

	}
	
	template <class T, class Cmp>
	void OpenSet<T, Cmp>::pop()
	{
		if (m_end > 0)
		{
			m_delete();
			m_isFull = false;
		}
	}
	
	template <class T, class Cmp>
	T OpenSet<T, Cmp>::peek()
	{
		if (m_end > 0)
				return m_list[0];
		else
		{
				std::cerr << "Error: Tried to peek an empty heap\n";
				std::terminate();
		}
		
	}
	
	template <class T, class Cmp>
	void OpenSet<T, Cmp>::clear() //Frees memory and resets size
	{
		m_end = 0;
		m_size = 1024;
		delete[] m_list;
		try
		{
			m_list = new T[m_size];
		}
		catch (std::bad_alloc& e)
		{
				std::cerr << "Error: " << e.what() << "\nOpen Set could not allocate initial " << m_size << "-element array.";
				std::terminate(); //Cannot size the array
		}
		m_isFull = false;
	}
	
	///////////////////////////////////////////////////
	//Template Specialiation: Pointer
	///////////////////////////////////////////////////
	
	
	template <class T, class Cmp>
	OpenSet<T*, Cmp>::OpenSet()
	{
		m_end = 0;
		m_size = 1024;
		m_isFull = false;
		
		try
		{
			m_list = new T*[m_size];
		}
		catch (std::bad_alloc& e)
		{
				std::cerr << "Error: " << e.what() << "\nOpen Set could not allocate initial " << m_size << "-element array.";
				std::terminate(); //Cannot size the array
		}
	}
	
	template <class T, class Cmp>
	void OpenSet<T*, Cmp>::m_delete()
	{
		//If m_delete is called, it means that m_end - 1u is guarenteed to be inside m_list's array bounds.
		
		//Move last element to root, discard root
		m_list[0] = m_list[m_end - 1u];
		m_end -= 1u;
		
		//Define variables:
		//
		//	i = index of current value;
		//	li = 2*i + 1 = index of current value's left child
		//	ri = 2*i + 2 = index of current value's right child
		//	swap = min(i, li, ri)
		//
		unsigned int i = 0;
		unsigned int li = 1;
		unsigned int ri = 2;
		unsigned int swap = 0;
		
		//While the heap property is not satisfied...
		while (true)
		{
			i = swap;
			li = i*2 + 1;
			ri = i*2 + 2;
			
			if (li < m_end && Cmp()(m_list[li], m_list[swap]) )
				swap = li;
			
			if (ri < m_end && Cmp()(m_list[ri], m_list[swap]) )
				swap = ri;
				
			if (i != swap)
			{
				T* tmp = m_list[i];
				m_list[i] = m_list[swap];
				m_list[swap] = tmp;
			}
			else
				break;
		}
	}
	
	template <class T, class Cmp>
	void OpenSet<T*, Cmp>::m_insert(T* insValue)
	{
		//If m_insert is called, m_end is guarenteed to be within m_list's array bounds
		
		//Add to the end and sift up
		m_list[m_end] = insValue;
		m_end += 1;
		
		unsigned int i = m_end - 1u;
		unsigned int p = (i - 1u) / 2; //p = parent index of list[i]
		
		while (true)
		{
			if (i > 0 && Cmp()(m_list[i], m_list[p]) )
			{
				T* tmp = m_list[p];
				m_list[p] = m_list[i];
				m_list[i] = tmp;
				i = p;
				p = (i - 1u) / 2;
			}
			else
				break;
		}
	}
	
	template <class T, class Cmp>
	OpenSet<T*, Cmp>::~OpenSet()
	{
		//Default behaviour on destructor is to clear WITHOUT freeing
		delete[] m_list;
		m_list = NULL;
	}
	
	template <class T, class Cmp>
	void OpenSet<T*, Cmp>::push(T* pushValue)
	{
		
		if (!m_isFull)
		{	
			if (m_end == 0 && m_size > 0)
			{
				m_list[0] = pushValue;
				m_end = 1;
			}
			else if (m_end >= m_size) //Expand the array
			{
				try
				{
					if (2*m_size + 1 + m_size > MEM_LIMIT) //Memory needed to allocate and swap arrays versus memory limit
						throw OpenSetException("Memory limit reached!");
					T** newList = new T*[2*m_size + 1];
					std::copy(&m_list[0], &m_list[m_end], &newList[0]);
					delete[] m_list;
					m_list = newList;
					m_size *= 2;
					m_size += 1;
					m_insert(pushValue);				
				}
				catch (std::bad_alloc& e)
				{
					m_isFull = true;
				}
				catch (OpenSetException& e)
				{
					m_isFull = true;					
				}
			}
			else
			{
				m_insert(pushValue);
			}
		}
		

	}
	
	template <class T, class Cmp>
	void OpenSet<T*, Cmp>::pop()
	{
		if (m_end > 0)
		{
			m_delete();
			m_isFull = false;
		}
	}
	
	template <class T, class Cmp>
	T* OpenSet<T*, Cmp>::peek()
	{
		if (m_end > 0)
				return m_list[0];
		else
		{
				std::cerr << "Error: Tried to peek an empty heap\n";
				std::terminate();
		}
		
	}
	
	template <class T, class Cmp>
	void OpenSet<T*, Cmp>::clearNoFree() //Clears memory and resets size
	{
		m_end = 0;
		m_size = 1024;
		delete[] m_list;
		try
		{
			m_list = new T*[m_size];
		}
		catch (std::bad_alloc& e)
		{
				std::cerr << "Error: " << e.what() << "\nOpen Set could not allocate initial " << m_size << "-element array.";
				std::terminate(); //Cannot size the array
		}
		m_isFull = false;
	}
	
	template <class T, class Cmp>
	void OpenSet<T*, Cmp>::clearAndFree() //Clears memory, deleting their pointers, and resets size
	{
		for (int i = 0; i < m_end; i++)
		{
			delete m_list[i];
			m_list[i] = NULL;
		}
		
		m_end = 0;
		m_size = 1024;
		
		delete[] m_list;
		
		try
		{
			m_list = new T*[m_size];
		}
		catch (std::bad_alloc& e)
		{
				std::cerr << "Error: " << e.what() << "\nOpen Set could not allocate initial " << m_size << "-element array.";
				std::terminate(); //Cannot size the array
		}
		m_isFull = false;
	}	

} //End Namespace Ricochet Robots

//Custom heap for Ricochet Robots solver
//Designed to pop top values and to erase itself + free memory

#ifndef RS_OPENSET
#define RS_OPENSET

#include <stdint.h>
#include <functional>

namespace RicochetRobots
{
	template <class T, class Cmp = std::less<T> > //Takes a type and a strict weak ordering functor
	class OpenSet
	{
		T* m_list; //Array will serve as our binary tree
		unsigned int m_end; //Array index of the next free spot in our binary tree
		unsigned int m_size; //Size of the array- how many nodes it contains

		bool m_isFull; //Is true when we fail to expand the open set any further

		void m_delete(); //Swap first element with last element of the array, then sift it down until it satisfies heap
		void m_insert(T insValue); //Add ins to the next available index of the array, then sift it up until it satisfies heap
	
	public:
		static const uint32_t MEM_LIMIT = ((0u - 1u)/2u);
	
		OpenSet();
		~OpenSet();
		
		bool isFull() const {return m_isFull;}
		bool isEmpty() const {return (m_end == 0);}

		void push(T);
		void pop();
		T    peek();
		void clear();

	};
	
	//Template specialization: T* pointers
	template <class T, class Cmp> //Takes a type and a strict weak ordering functor
	class OpenSet<T*, Cmp>
	{
		T** m_list; //Array will serve as our binary tree
		unsigned int m_end; //Array index of the next free spot in our binary tree
		unsigned int m_size; //Size of the array- how many nodes it contains

		bool m_isFull; //Is true when we fail to expand the open set any further

		void m_delete(); //Swap first element with last element of the array, then sift it down until it satisfies heap
		void m_insert(T* insValue); //Add ins to the next available index of the array, then sift it up until it satisfies heap
	
	public:
		static const uint32_t MEM_LIMIT = ((0u - 1u)/2u);
	
		OpenSet();
		~OpenSet();
		
		bool isFull() const {return m_isFull;}
		bool isEmpty() const {return (m_end == 0);}

		void push(T*);
		void pop();
		T*   peek();
		void clearNoFree(); //Simply clears memory without freeing
		void clearAndFree(); //Deletes pointers stored in memory and clears memory

	};
}

#include "OpenSet.cpp"
#endif //RS_OPENSET

#pragma once

#include <stddef.h>

#include <std.hpp>
#include <kernel/cpu.hpp>

namespace std {
	template<class T> 
	class vector {

		size_t _capacity;
		size_t _size;
		T* buffer;

	public:
		class iterator
		{
			// Thanks to @jeetsukumaran for this!
			public:
				typedef iterator self_type;
				typedef T value_type;
				typedef T& reference;
				typedef T* pointer;
				typedef int difference_type;
				iterator(pointer ptr) : ptr_(ptr) { }
				self_type operator++() { self_type i = *this; ptr_++; return i; }
				self_type operator++(int junk) { ptr_++; return *this; }
				reference operator*() { return *ptr_; }
				pointer operator->() { return ptr_; }
				bool operator==(const self_type& rhs) { return ptr_ == rhs.ptr_; }
				bool operator!=(const self_type& rhs) { return ptr_ != rhs.ptr_; }
			private:
				pointer ptr_;
		};

		//typedef T* iterator; // used as vector::iterator

		// Constructors
		vector();
	   // vector(size_t size);
		vector(const vector<T>& vec);
		~vector();

		// Methods, needs to provide a lot more for STL compatibility... TODO!
		void clear();
		void resize(size_t size);
		void reserve(size_t capacity);
		void push_back(T value);
		void pop_back();
		void remove(T& value);

		size_t capacity() const;
		size_t size() const;

		iterator begin() { return iterator( buffer ); }
		iterator end() { return iterator( buffer + _size ); }

		T& operator[](size_t index);
		vector<T>& operator=(const vector<T>& v);

		friend bool operator==(const vector<T>& v1, const vector<T>& v2) {
			return v1 == v2;
		}
	};
}


namespace std {

	template<class T>
	vector<T>::vector() : _capacity(0), _size(0) { bcprintf("creating\n"); }

	template<class T>
	vector<T>::vector(const vector<T>& vec) : _capacity(vec._capacity), _size(vec._size), buffer(new T[_capacity]) { 
		for(size_t i = 0; i < _size; i++) {
			buffer[i] = vec.buffer[i];
		}
	}

	template<class T>
	vector<T>::~vector() { }

	template<class T> 
	void vector<T>::push_back(T value) {
		bcprintf("push_back\n");
		if(_size >= _capacity) {
			reserve(_capacity*1.5+1); // 1.5 is a bit less than the golden ratio, perfect for our memory allocation uses
		}

		buffer[_size] = value;
		_size++;
	}
	
	template<class T>
	void vector<T>::pop_back() {
		(reinterpret_cast<T*>(buffer)[_size-1]).~T();
		--_size;
	}

	template<class T>
	void vector<T>::reserve(size_t capacity) {
		T* buffer_new = new T[capacity];
		 _capacity = capacity;

		for(size_t i = 0; i < _size; i++) {
			buffer_new[i] = buffer[i];
		}

		//delete[] buffer;
		buffer = buffer_new;
	}


	template<class T>
	vector<T>& vector<T>::operator= (const vector<T>& v) {
		delete[] buffer;
		_size = v._size;

		_capacity = v._capacity;
		buffer = new T [_capacity];
		for (unsigned int i = 0; i < _size; i++)
			buffer[i] = v.buffer[i];
		return *this;
	}

	template<class T>
	T& vector<T>::operator[](size_t index) {
		return buffer[index];
	}

	template<class T>
	size_t vector<T>::capacity() const {
		return _capacity;   
	};

	template<class T>
	size_t vector<T>::size() const {
		return _size;   
	};

	template<class T>
	void vector<T>::clear() {
		_size = 0;
		_capacity = 0;
		buffer = NULL;
	}
}
#pragma once

template<typename T>
class Container
{
private:
	//Variables
	unsigned capacity;
	unsigned nrOfElements;
	T** internal_arr;

	//Private functions
	void initialize_internal_array(const unsigned from_index);

	void expand(const unsigned multiple = 2);

	void free_memory();

public:
	//Constructors/Destructors
	Container(const unsigned initial_cap = 1);

	Container(const Container& obj);

	~Container();

	//Operators
	void operator = (const Container& obj);

	T& operator [](const int index);

	//Accessors
	const unsigned& size() const;
	
	const unsigned& max_size() const;

	//Modifiers

	//Functions
	void push(const T& obj);
	void pop_back();
	void pop_front();
	void remove_ordered(const unsigned& index);
	void remove_unordered(const unsigned& index);
};

//Definitions ======================================================
//Private functions

template<typename T>
void Container<T>::initialize_internal_array(const unsigned from_index)
{
	for (size_t i = from_index; i < this->capacity; i++)
	{
		this->internal_arr[i] = nullptr;
	}
}

template<typename T>
void Container<T>::expand(const unsigned multiple)
{
	//Increase max capacity
	this->capacity *= multiple;

	//Create temp holder array with NEW capacity
	T** temp = new T*[this->capacity];

	//Copuy over data from old array to temporary array
	for (size_t i = 0; i < this->nrOfElements; i++)
	{
		temp[i] = this->internal_arr[i];
	}

	//Delete old pointers to data
	delete[] this->internal_arr;

	//Assign real member array pointer to temporary data
	this->internal_arr = temp;

	//Initialize everything FROM the last valid element to the end of array (empty pointers)
	this->initialize_internal_array(this->nrOfElements);

	//temp pointer is automatically removed by c++
}

template<typename T>
void Container<T>::free_memory()
{
	//Remove the data
	for (size_t i = 0; i < this->capacity; i++)
	{
		delete this->internal_arr[i];
	}

	//Remove the pointer array
	delete[] this->internal_arr;

	this->internal_arr = nullptr;
}

//Constructors / Destructors
template<typename T>
Container<T>::Container(const unsigned initial_cap)
{
	this->capacity = initial_cap;
	this->nrOfElements = 0;

	this->internal_arr = new T*[this->capacity];

	this->initialize_internal_array(0);
}

template<typename T>
Container<T>::Container(const Container& obj)
{
	this->capacity = obj.capacity;
	this->nrOfElements = obj.nrOfElements;

	this->internal_arr = new T*[this->capacity];

	for (size_t i = 0; i < this->nrOfElements; i++)
	{
		this->internal_arr[i] = new T(*obj.internal_arr[i]);
	}

	this->initialize_internal_array(this->nrOfElements);
}

template<typename T>
Container<T>::~Container()
{
	this->free_memory();
}

//Operators
template<typename T>
void Container<T>::operator = (const Container& obj)
{
	this->free_memory();

	this->capacity = obj.capacity;
	this->nrOfElements = obj.nrOfElements;

	this->internal_arr = new T*[this->capacity];

	for (size_t i = 0; i < this->nrOfElements; i++)
	{
		this->internal_arr[i] = new T(*obj.internal_arr[i]);
	}

	this->initialize_internal_array(this->nrOfElements);
}

template<typename T>
T& Container<T>::operator [](const int index)
{
	if (index < 0 || index >= this->nrOfElements) //Error
	{
		std::cout << "CONTAINER::OPERATOR[]::INDEX_OUT_OF_BOUNDS" << "\n";
		throw("CONTAINER::OUT_OF_BOUNDS");
	}

	return *this->internal_arr[index];

}

//Accessors
template<typename T>
const unsigned & Container<T>::size() const
{
	return this->nrOfElements;
}

template<typename T>
const unsigned & Container<T>::max_size() const
{
	return this->capacity;
}

//Modifiers

//Functions
template<typename T>
inline void Container<T>::push(const T & obj)
{
	if (this->nrOfElements >= this->capacity)
		this->expand();

	this->internal_arr[this->nrOfElements++] = new T(obj);
}

template<typename T>
inline void Container<T>::pop_back()
{
	if (this->nrOfElements <= 0)
	{
		std::cout << "CONTAINER::POP_BACK::NO_ELEMENTS_TO_REMOVE";
		throw("CONTAINER::POP_BACK::NO_ELEMENTS_TO_REMOVE");
	}

	delete this->internal_arr[--this->nrOfElements];
	this->internal_arr[this->nrOfElements] = nullptr;
}

template<typename T>
inline void Container<T>::pop_front()
{

}

template<typename T>
inline void Container<T>::remove_ordered(const unsigned & index)
{

}

template<typename T>
inline void Container<T>::remove_unordered(const unsigned & index)
{
	if (index < 0 || index >= this->nrOfElements)
	{
		std::cout << "CONTAINER::REMOVE_UNORDERED::INDEX_OUT_OF_BOUNDS" << "\n";
		throw("CONTAINER::REMOVE_UNORDERED::INDEX_OUT_OF_BOUNDS");
	}

	delete this->internal_arr[index];
	this->internal_arr[index] = this->internal_arr[this->nrOfElements-1];
	this->internal_arr[--this->nrOfElements] = nullptr;
}

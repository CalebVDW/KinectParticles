#pragma once

//An array that resizes itself when an item is removed by moving the last element to the opened space
//I don't know what to call this data structure so I am going with particle list

template <typename T>
class ParticleArray {
public:
	ParticleArray(int size);

	//Non const interface
	void RemoveElementUnchecked(int index);
	void RemoveElement(int index);
	void RemoveElements(bool (*test)(const T&));
	void Push(T element);
	void Append(T* data, int length);
	T& operator[](std::size_t idx) { return head[idx]; }

	//Const interface
	int Size() const;
	int Capacity() const;
	T GetElement(int index) const;

private:
	T* head;
	int maxSize;
	int currentSize;
};

//Create the particle array and allocate memory for the given number of elements
template <typename T>
ParticleArray<T>::ParticleArray(int maxSize)
	:maxSize{ maxSize }, currentSize{ 0 }
{
	head = new T[maxSize];
}

//Remove a single element without validating index for efficiency 
template <typename T>
void ParticleArray<T>::RemoveElementUnchecked(int index)
{
	--currentSize;
	if (currentSize > 0)
		head[index] = head[currentSize];
}

//Remove a single element and check the index passed in for validity
template <typename T>
void ParticleArray<T>::RemoveElement(int index)
{
	if (index > 0 && index < currentSize)
		RemoveElementUnchecked(index);
}

//Remove all elements that return false when passed to the test function
template <typename T>
void ParticleArray<T>::RemoveElements(bool(*test)(const T&))
{
	for (int i = 0; i < currentSize; ++i)
	{
		if (!test(head[i]))
			RemoveElement(i);
	}
}

//Add an element to the end of the array
template <typename T>
void ParticleArray<T>::Push(T element)
{
	if (currentSize < maxSize)
		head[currentSize++] = element;
}

//Add multiple elements to the end of the array
template <typename T>
void ParticleArray<T>::Append(T* data, int length)
{
	if (currentSize + length > maxSize)
		return;
	memcpy(head + currentSize, data, length * sizeof(T));
}

//Get the element at an index. No index validating is done here 
template <typename T>
T ParticleArray<T>::GetElement(int index) const
{
	return head[index];
}

//Get the number of elements currently stored in the array
template <typename T>
int ParticleArray<T>::Size() const
{
	return currentSize;
}

//Get the max number of elements this array can hold
template <typename T>
int ParticleArray<T>::Capacity() const
{
	return maxSize;
}
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
	void Push(T element);
	void Append(T* data, int length);

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
ParticleArray::ParticleArray(int index)
{
	head = new T[index];
}

//Remove a single element without validating index for efficiency 
template <typename T>
void ParticleArray::RemoveElementUnchecked(int index)
{
	delete head[index];
	--currentSize;
	if (currentSize > 0)
		data[index] = data[currentSize];
}

//Remove a single element and check the index passed in for validity
template <typename T>
void ParticleArray::RemoveElement(int index)
{
	if (index > 0 && index < currentSize)
		RemoveElementUnchecked(index);
}

//Add an element to the end of the array
template <typename T>
void ParticleArray::Push(T elemment)
{
	if (currentSize < maxSize)
		data[currentSize] = element;
	++currentSize;
}

//Add multiple elements to the end of the array
template <typename T>
void ParticleArray::Append(T* data, int length)
{
	if (currentSize + length > maxSize)
		return;
	memcpy(head + currentSize, data, length * sizeof(T));
}

//Get the element at an index. No index validating is done here 
template <typename T>
T ParticleArray::GetElement(int index) const
{
	return head[index];
}

//Get the number of elements currently stored in the array
template <typename T>
int ParticleArray::Size() const
{
	return currentSize();
}

//Get the max number of elements this array can hold
template <typename T>
int ParticleArray::Capacity() const
{
	return maxSize;
}
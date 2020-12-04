#pragma once
#include <vector>

template<typename T>
class CircularBuffer {
private:
	T* arr;
	size_t maxSize;
	int headIndex = 0;
	int elementsCount = 0;

	T & getElementAt(int index) {
		return arr[(headIndex + index) % maxSize];
	}

	const T & getElementAt(int index) const {
		return arr[(headIndex + index) % maxSize];
	}

public:
	CircularBuffer(size_t maxSize) {
		this->maxSize = maxSize;
		arr = new T[maxSize];
	}

	~CircularBuffer() {
		delete[] arr;
	}

	T & operator[](int index) {
		return getElementAt(index);
	}

	const T & operator[](int index) const {
		return getElementAt(index);
	}

	int getSize() const {
		return elementsCount;
	}

	int getMaxSize() const {
		return maxSize;
	}

	void clear() {
		headIndex = 0;
		elementsCount = 0;
	}

	void push_back(T value) {
		int index = (headIndex + elementsCount) % maxSize;
		arr[index] = value;
		if (elementsCount == maxSize)
			headIndex = headIndex == maxSize - 1 ? 0 : headIndex + 1;
		else
			elementsCount++;
	}

	std::vector<T> asVectorCopy() const {
		std::vector<T> result;
		result.reserve(getSize());
		for (int i = 0; i < elementsCount; i++)
			result.push_back(getElementAt(i));
		return result;
	}
};
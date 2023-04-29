#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

template<typename T>
class Double_List
{
public:
	Double_List();
	~Double_List();
	int GetSize();
	int& count(const int index);
	T& operator[](const int index);
	void push_front(const T data);
	void push_back(const T data);
	void insert(const T data, const int index);
	void pop_front();
	void pop_back();
	void remove_at(const int index);
	void clear();
	void bubble_sort();
	void info();
	void sum();
	void print();
private:
	template<typename T>
	class Node
	{
	public:
		T data;
		Node<T>* pNext;
		Node<T>* pPrev;
		int count = 0;
		Node(T data = T(), Node<T>* pNext = nullptr, Node<T>* pPrev = nullptr)
		{
			this->data = data;
			this->pNext = pNext;
			this->pPrev = pPrev;
			if (data == 0)
			{
				count++;
			}
			while (abs(data) > 0)
			{
				count++;
				data /= 10;
			}
		}
	};
	Node<T>* head;
	Node<T>* tail;
	int size;
};

int main()
{
	setlocale(LC_ALL, "ru");
	fstream file;
	file.open("lab_17.txt", fstream::in);
	if (!file.is_open())
	{
		cout << "Файл lab_17.txt не открылся...\n";
	}
	else
	{
		Double_List<int> lst;
		int data;
		while (!file.eof())
		{
			if (file >> data)
			{
				lst.push_back(data);
			}
		}
		cout << "Исходный список:\n";
		lst.print();
		lst.bubble_sort();
		cout << "\nОтсортированный список:\n";
		lst.print();
		lst.info();
		lst.sum();
	}
	file.close();
	return 0;
}

template<typename T>
Double_List<T>::Double_List()
{
	size = 0;
	head = nullptr;
	tail = nullptr;
}

template<typename T>
Double_List<T>::~Double_List()
{
	clear();
}

template<typename T>
int Double_List<T>::GetSize()
{
	return size;
}

template<typename T>
void Double_List<T>::push_front(const T data)
{
	if ((head == nullptr) && (tail == nullptr))
	{
		head = tail = new Node<T>(data);
	}
	else
	{
		head = head->pPrev = new Node<T>(data, head, nullptr);
	}
	size++;
}

template<typename T>
void Double_List<T>::push_back(const T data)
{
	if ((head == nullptr) && (tail == nullptr))
	{
		head = tail = new Node<T>(data);
	}
	else
	{
		tail = tail->pNext = new Node<T>(data, nullptr, tail);
	}
	size++;
}

template<typename T>
void Double_List<T>::insert(const T data, const int index)
{
	if (index == 0)
	{
		push_front(data);
	}
	else if (index < (size / 2))
	{
		Node<T>* previous = head;
		for (int i = 0; i < index - 1; i++)
		{
			previous = previous->pNext;
		}
		previous->pNext = previous->pNext->pPrev = new Node<T>(data, previous->pNext, previous);
		size++;
	}
	else
	{
		Node<T>* previous = tail;
		for (int i = size - 1; i > index - 1; i--)
		{
			previous = previous->pPrev;
		}
		previous->pNext = previous->pNext->pPrev = new Node<T>(data, previous->pNext, previous);
		size++;
	}
}

template<typename T>
void Double_List<T>::pop_front()
{
	if ((head == nullptr) && (tail == nullptr))
	{
		return;
	}
	else
	{
		if (head == tail)
		{
			delete head;
			head = tail = nullptr;
		}
		else
		{
			if (head != nullptr)
			{
				head = head->pNext;
				delete head->pPrev;
				head->pPrev = nullptr;
			}
		}
		size--;
	}
}

template<typename T>
void Double_List<T>::pop_back()
{
	if ((head == nullptr) && (tail == nullptr))
	{
		return;
	}
	else
	{
		if (head == tail)
		{
			delete head;
			head = tail = nullptr;
		}
		else
		{
			tail = tail->pPrev;
			delete tail->pNext;
			tail->pNext = nullptr;
		}
		size--;
	}
}

template<typename T>
void Double_List<T>::remove_at(const int index)
{
	if (index == 0)
	{
		pop_front();
	}
	else if (index == size - 1)
	{
		pop_back();
	}
	else if (index < (size / 2))
	{
		Node<T>* previous = head;
		for (int i = 0; i < index - 1; i++)
		{
			previous = previous->pNext;
		}
		Node<T>* to_delete = previous->pNext;
		previous->pNext = to_delete->pNext;
		to_delete->pNext->pPrev = to_delete->pPrev;
		delete to_delete;
		size--;
	}
	else
	{
		Node<T>* previous = tail;
		for (int i = size - 1; i > index - 1; i--)
		{
			previous = previous->pPrev;
		}
		Node<T>* to_delete = previous->pNext;
		previous->pNext = to_delete->pNext;
		to_delete->pNext->pPrev = to_delete->pPrev;
		delete to_delete;
		size--;
	}
}

template<typename T>
void Double_List<T>::clear()
{
	while (size)
	{
		pop_front();
	}
}

template<typename T>
T& Double_List<T>::operator[](const int index)
{
	int counter = 0;
	if (index < (size / 2))
	{
		Node<T>* current = head;
		while (current != nullptr)
		{
			if (counter == index)
			{
				return current->data;
			}
			current = current->pNext;
			counter++;
		}
	}
	else
	{
		counter = size - 1;
		Node<T>* current = tail;
		while (current != nullptr)
		{
			if (counter == index)
			{
				return current->data;
			}
			current = current->pPrev;
			counter--;
		}
	}
}

template<typename T>
int& Double_List<T>::count(const int index)
{
	int counter = 0;
	if (index < (size / 2))
	{
		Node<T>* current = head;
		while (current != nullptr)
		{
			if (counter == index)
			{
				return current->count;
			}
			current = current->pNext;
			counter++;
		}
	}
	else
	{
		counter = size - 1;
		Node<T>* current = tail;
		while (current != nullptr)
		{
			if (counter == index)
			{
				return current->count;
			}
			current = current->pPrev;
			counter--;
		}
	}
}

template<typename T>
void Double_List<T>::bubble_sort()
{
	int temp = 0;
	int number = 0;
	for (int i = 0; i < size; i++)
	{
		for (int j = (size - 1); j >= (i + 1); j--)
		{
			if (this->count(j) < this->count(j - 1))
			{
				temp = this->operator[](j);
				this->operator[](j) = this->operator[](j - 1);
				this->operator[](j - 1) = temp;
				number = this->count(j);
				this->count(j) = this->count(j - 1);
				this->count(j - 1) = number;
			}
		}
	}
}

template<typename T>
void Double_List<T>::info()
{
	int counter = 0;
	for (int i = 0; i < size; i++)
	{
		if (this->count(i) < 4)
		{
			counter++;
		}
	}
	if (!counter)
	{
		cout << "\nНет чисел, у которых меньше 4 цифр\n";
	}
	else
	{
		cout << "\nКоличество чисел, у которых меньше 4 цифр: " << counter << endl;
	}
}

template<typename T>
void Double_List<T>::sum()
{
	int sum = 0;
	for (int i = 0; i < size; i++)
	{
		if (this->count(i) == 2)
		{
			sum += this->operator[](i);
		}
	}
	cout << "Сумма двузначных чисел: " << sum << endl;
}

template<typename T>
void Double_List<T>::print()
{
	for (int i = 0; i < size; i++)
	{
		cout << this->operator[](i) << "(" << this->count(i) << ") ";
	}
}

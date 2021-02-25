#pragma once
#include <iostream>
using namespace std;

template <typename T>
class DList
{
public:
	DList() = default;
	void pushFront(const T& data);
	void pushBack(const T& data);
	void pushFrontByData(const T& foundData, const T& data);
	void pushBackByData(const T& foundData, const T& data);
	void popByData(const T& data);
	void popFront();
	void popBack();
	bool isEmpty() const;
	void reverse();
	void clear();
	DList& operator + (const DList& data1);
	DList& operator * (const DList& data1);
	size_t getSize() const;
	size_t searchAndChangeData(const T& searchData, const T& changeData);
	void printR() const;
	void printL() const;
private:
	struct Node
	{
		T data;
		Node* next = nullptr, * prev = nullptr;
		Node(const T& data = T(), Node* prev = nullptr, Node* next = nullptr)
			:data(data), next(next), prev(prev)
		{}
	};
	Node* head = nullptr, * tail = nullptr;
	size_t size = 0;
	auto findNode(const T& data);
	bool helpCheck(const vector<T>& v, const T& data)
	{
		for (size_t i = 0; i < v.size(); i++)
		{
			if (v[i] == data)
				return false;
		}
		return true;
	}


};
template<typename T>
inline void DList<T>::pushFront(const T& data)
{
	Node* temp = new Node(data, nullptr, head);
	if (isEmpty()) 	tail = temp; //first
	else
	{
		head->prev = temp;
	}
	head = temp;
	++size;
}

template<typename T>
inline void DList<T>::pushBack(const T& data)
{
	Node* temp = new Node(data, tail, nullptr);
	if (isEmpty())
	{
		head = temp;
	}
	else
	{
		tail->next = temp;
	}
	tail = temp;
	++size;
}

template<typename T>
inline void DList<T>::pushFrontByData(const T& findData, const T& data)
{
	Node* find = findNode(findData);
	if (find == nullptr)
	{
		cout << "No such element!" << endl;
		return;
	}
	else {
		Node* temp = new Node(data, nullptr, find);
		if (find == head)
		{
			head = temp;
			temp->next->prev = temp;
		}
		else
		{
			temp->prev = find->prev;
			find->prev->next = temp;
			find->prev = temp;
		}
		++size;
	}
}

template<typename T>
inline void DList<T>::pushBackByData(const T& foundData, const T& data)
{
	Node* find = findNode(foundData);
	if (find == nullptr)
	{
		cout << "No element like this!" << endl;
		return;
	}
	else {
		Node* temp = new Node(data, find, nullptr);
		if (find == tail)
		{
			find->next = temp;
			tail = temp;
		}
		else
		{
			temp->next = find->next;
			find->next->prev = temp;
			find->next = temp;
		}
		++size;
	}
}

template<typename T>
inline void DList<T>::popByData(const T& data)
{
	Node* find = findNode(data);
	if (find != nullptr) {
		while (find != nullptr) {
			Node* temp = find->next;
			if (find->next != nullptr && find->prev != nullptr)
			{
				temp->prev = find->prev;
				find->prev->next = find->next;
				delete find;
			}
			else if (find->prev == nullptr)
			{
				temp->prev = nullptr;
				delete find;
				head = temp;
			}
			else if (find->next == nullptr)
			{
				find->prev->next = nullptr;
				tail = find->prev;
				delete find;
			}
			--size;
			find = findNode(data);
		}
	}
}

template<typename T>
inline void DList<T>::popFront()
{
	if (isEmpty())
		return;
	else if (size == 1)
	{
		delete head;
		head = nullptr;
		tail = nullptr;
	}
	else
	{
		auto temp = head;
		head = head->next;
		head->prev = nullptr;
		delete temp;
	}
	--size;
}

template<typename T>
inline void DList<T>::popBack()
{
	if (isEmpty())
		return;
	else if (size == 1)
	{
		delete head;
		head = nullptr;
		tail = nullptr;
	}
	else
	{
		auto temp = tail;
		tail = tail->prev;
		tail->next = nullptr;
		delete temp;
	}
	--size;
}

template<typename T>
inline bool DList<T>::isEmpty() const
{
	return head == nullptr;
}

template<typename T>
inline size_t DList<T>::getSize() const
{
	return size;
}

template<typename T>
inline size_t DList<T>::searchAndChangeData(const T& searchData, const T& changeData)
{
	size_t countChanges = 0;
	Node* temp = head;
	while (temp != nullptr)
	{
		if (temp->data == searchData) {
			temp->data = changeData;
			++countChanges;
		}
		temp = temp->next;
	}
	return countChanges;
}

template<typename T>
inline void DList<T>::reverse()
{
	Node* temp = head;
	Node* help = nullptr;
	while (temp != nullptr) {
		temp->prev = temp->next;
		temp->next = help;
		if (temp == tail)
			break;
		help = temp->prev->prev;
		temp = temp->prev;
	}
	help = tail;
	tail = head;
	head = help;
}

template<typename T>
inline void DList<T>::clear()
{
	while (!isEmpty())
		popBack();
	size = 0;
}

template<typename T>
inline void DList<T>::printL() const
{
	Node* temp = head;
	cout << "List directly: " << endl;
	while (temp != nullptr) {
		cout << temp->data << " ";
		temp = temp->next;
	}
	cout << endl;
}

template<typename T>
inline void DList<T>::printR() const
{
	Node* temp = tail;
	cout << "List reversed: " << endl;
	while (temp != nullptr) {
		cout << temp->data << " ";
		temp = temp->prev;
	}
	cout << endl;
}

template<typename T>
inline DList<T>& DList<T>::operator+(const DList& data1)
{
	DList l;
	Node* temp = head;
	while (temp != nullptr) {
		l.pushBack(temp->data);
		temp = temp->next;
	}
	temp = data1.head;
	while (temp != nullptr) {
		l.pushBack(temp->data);
		temp = temp->next;
	}
	return l;
}

template<typename T>
inline DList<T>& DList<T>::operator*(const DList& data1)
{
	vector<T> check;
	DList l;
	Node* temp = head;
	while (temp != nullptr) {
		Node* sTemp = data1.head;
		while (sTemp != nullptr) {
			if (temp->data == sTemp->data && helpCheck(check, temp->data))
			{
				l.pushBack(temp->data);
				check.push_back(temp->data);
			}
			sTemp = sTemp->next;
		}
		temp = temp->next;
	}
	return l;
}

template<typename T>
inline auto DList<T>::findNode(const T& data)
{
	Node* res = head;
	while (res != nullptr && res->data != data)
		res = res->next;
	return res;
}
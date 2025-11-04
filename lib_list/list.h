#ifndef LIB_LIST_H_
#define LIB_LIST_H_

template <class T>
struct Node
{
	T value;
	Node<T>* next;
    Node<T>* prev;
	Node(T value_= T(), Node<T>* next_ = nullptr,Node<T>* prev_ = nullptr);

};

template <class T>
Node<T>::Node(T value_, Node<T>* next_,Node<T>* prev_) : value(value_), next(next_),prev(prev_) {}

template <class T>
class List {
protected:
	Node<T>* _head; 
	Node<T>* _tail;
	int _count;
public:
	List();
	List(const List& other);
	virtual ~List();

	inline int size() const;
	inline Node<T>* head() const;
	inline Node<T>* tail() const;

	inline bool is_empty() const;

	virtual void push_front(const T& val) noexcept;
	virtual void push_back(const T& val) noexcept;
	virtual void insert(int pos,const T&val);
	virtual void insert(Node<T>* node, const T& val);

	virtual void pop_front();
	virtual void pop_back();
	virtual void erase(int pos);
	virtual void erase(Node<T>* node);

	Node<T>* find(const T& val) const;

	class Iterator {
		Node<T>* current;
	public:
		Iterator() :current(nullptr){}
		Iterator(Node<T>* pos):current(pos){}
		Iterator(const Iterator& other): current(other.current){}

		Iterator& operator=(const Iterator& other) {
			if (this != &other) {
				current = other.current;
			}
			return *this;
		}
		T& operator*() {
			return current->value;
		}
		bool operator !=(const Iterator& other) {
			return current != other.current;
		}
		Iterator operator++(int) {
			Iterator tmp = *this;
			current = current->next;
			return tmp;
		}
		Iterator& operator++() {
			current = current->next;
			return *this;
		}

	};

	Iterator begin() { return Iterator(_head); }
	Iterator end() { return Iterator(nullptr); }

};

template <class T>
List<T>::List():_head(nullptr),_tail(nullptr),_count(0){}

template <class T>
List<T>::List(const List& other) : _head(nullptr), _tail(nullptr), _count(0) {
	_head = new Node<T>(*other._head);
	Node<T>* tmpNode = _head;
	Node<T>* tmpNode1 = _head->next;
	while (tmpNode1 != nullptr) {
		tmpNode->next = new Node<T>(tmpNode1->value);
		tmpNode = tmpNode->next;
		tmpNode1 = tmpNode1->next;
	}
	_tail = tmpNode;
	_count = other.size();
}

template <class T>
List<T>::~List() {
	while (_head!=nullptr) {
		Node<T>* temp = _head;
		_head = _head->next;
		delete temp;
	}
}

template <class T>
inline int List<T>::size() const {
	return _count;
}

template <class T>
inline Node<T>* List<T>::head() const {
	return _head;
}

template <class T>
inline Node<T>* List<T>::tail() const {
	return _tail;
}

template <class T>
inline bool List<T>::is_empty() const {
	return _count == 0;
}

template <class T>
void List<T>::push_front(const T& val) noexcept {
	Node<T>* node = new Node<T>(val,_head);
	if (is_empty())
		_tail = node;
	_head = node;
	_count++;
}


template <class T>
void List<T>::push_back(const T& val) noexcept {
	Node<T>* node = new Node<T>(val);
	if (is_empty()) {
		_head = node;
		_tail = node;
		_count++;
		return;
	}
	_tail->next = node;
	_tail = node;
	_count++;
}

template <class T>
void List<T>::insert(Node<T>* node, const T& val) {
	if (node == nullptr)
		throw std::logic_error("List is empty");
	Node<T>* new_node = new Node<T>(val,node->next);
	node->next = new_node;
	if (_tail == node)
		_tail = new_node;
	_count++;
}

template <class T>
void List<T>::insert(int pos, const T& val) {
	if (pos < 0 || pos > _count)  
		throw std::logic_error("the position is not on the list");
	if (pos == 0) 
		push_front(val);

	else if (pos == _count)  
		push_back(val);
	else {
		Node<T>* cur = _head;
		int cur_pos = 0;
		while (cur_pos < pos - 1) {  
			cur_pos++;
			cur = cur->next;
		}
		insert(cur, val);  
	}
}

template <class T>
void List<T>::pop_front() {
	if (is_empty()) 
		throw std::logic_error("List is empty ");
	Node<T>* temp = _head;
	_head = _head->next;

	if (_head == nullptr) 
		_tail = nullptr; 
	delete temp;
	_count--;
}

template <class T>
void List<T>::pop_back() {
	if (is_empty()) {
		throw std::logic_error("List is empty");
	}
	if (_head == _tail) {
		delete _head;
		_head = nullptr;
		_tail = nullptr;
	}
	else {
		Node<T>* cur = _head;
		while (cur->next != _tail) {
			cur = cur->next;
		}
		delete _tail;
		_tail = cur;
		_tail->next = nullptr;
	}
	_count--;
}

template <class T>
void List<T>::erase(Node<T>* node) {
	if (node == nullptr) {
		throw std::logic_error("Node indicates nullptr");
	}

	if (node == _head) {
		pop_front();
		return;
	}

	if (node == _tail) {
		pop_back();
		return;
	}

	Node<T>* prev = _head;
	while (prev != nullptr && prev->next != node) {
		prev = prev->next;
	}

	if (prev == nullptr) {
		throw std::logic_error("Node not found in the list");
	}

	prev->next = node->next;
	delete node;
	_count--;
}

template <class T>
void List<T>::erase(int pos) {
	if (pos < 0 || pos >= _count) 
		throw std::logic_error("The position is not in the list");

	if (pos == 0) 
		pop_front();

	else if (pos == _count - 1) 
		pop_back();
	
	else {
		Node<T>* cur = _head;
		int cur_pos = 0;

		while (cur_pos < pos) {
			cur_pos++;
			cur = cur->next;
		}
		erase(cur);
	}
}

template <class T>
Node<T>* List<T>::find(const T& val) const {
	Node<T>* cur = _head;

	while (cur != nullptr) {
		if (cur->value == val)
			return cur;
		cur = cur->next;
	}
	throw std::logic_error("Value not found in the list");
}

#endif
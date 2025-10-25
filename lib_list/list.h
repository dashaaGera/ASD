#ifndef LIB_LIST_H_
#define LIB_LIST_H_

template <class T>
struct Node
{
	T value;
	Node<T>* next;
	Node(T value_=0, Node<T>* next_ = nullptr);

};

template <class T>
Node<T>::Node(T value_, Node<T>* next_) : value(value_), next(next_) {}

template <class T>
class List {
	Node<T>* _head; 
	Node<T>* _tail;
	int _count;
public:
	List();
	List(const List& other);
	~List();

	inline int size() const;
	inline Node<T>* head() const;
	inline Node<T>* tail() const;

	inline bool is_empty() const;

	void push_front(const T& val) noexcept;
	void push_back(const T& val) noexcept;
	void insert(int pos,const T&val);
	void insert(Node<T>* node, const T& val);

	void pop_front();
	void pop_back();
	void erase(int pos);
	void erase(Node<T>* node);

	Node<T>* find(const T& val);

};

template <class T>
List<T>::List():_head(nullptr),_tail(nullptr),_count(0){}

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


#endif

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

#endif

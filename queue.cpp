#include <iostream>
#include <queue>
#include <exception>

/* This file includes an implementation of queue data structure as a circular queue using an array.
This implementation is by no means comprehensive and meant for education purposes.
It lacks the capabilities of a standard optimized queue but still has the basic functionalities.
It is meant to show the underlying strcuture of queue data structure.
*/

class QueueEmptyException : public std::exception
{
private:
    const char *_msg = "Queue is empty";

public:
    QueueEmptyException() : std::exception() {}
    virtual const char *what() const noexcept
    {
        return _msg;
    }
};

class QueueFullException : public std::exception
{
private:
    const char *_msg = "Queue is full";

public:
    QueueFullException() : std::exception() {}
    virtual const char *what() const noexcept
    {
        return _msg;
    }
};

/**
 * @brief A data structure that FIFO behaviour
 *
 * @tparam T
 */
template <typename T>
class Queue
{
public:
    Queue();
    ~Queue();
    Queue(const Queue &obj);
    void enqueue(T val);
    void dequeue();
    T front();
    T back();
    int size();
    bool empty();
    Queue &operator=(const Queue &obj);

private:
    int capacity = 100;
    T *_q;
    int _front;
    size_t _back;
    size_t _size;
};

/**
 * @brief Construct a new Queue< T>:: Queue object
 *
 * @tparam T
 */
template <typename T>
Queue<T>::Queue()
{
    _front = -1;
    _back = -1;
    _size = 0;
    _q = new T[capacity];
}

/**
 * @brief Destroy the Queue< T>:: Queue object
 *
 * @tparam T
 */
template <typename T>
Queue<T>::~Queue()
{
    delete _q;
}

/**
 * @brief Construct a copy of a Queue< T>:: Queue object
 *
 * @tparam T
 * @param obj
 */
template <typename T>
Queue<T>::Queue(const Queue &obj)
{
    this->_q = new T[obj.capacity];
    this->capacity = obj.capacity;
    this->_front = obj._front;
    this->_back = obj._back;
    this->_size = obj._size;
    for (size_t i = 0; i < this->capacity; i++)
    {
        this->_q[i] = obj._q[i];
    }
}

/**
 * @brief assinment overload
 *
 * @tparam T
 * @param obj
 * @return Queue<T>&
 */
template <typename T>
Queue<T> &Queue<T>::operator=(const Queue &obj)
{
    if (this != &obj)
    {
        if (this->capacity < obj.capacity)
        {
            T new_array = new T[obj.capacity];
            delete this->_q;
            this->_q = new_array;
            this->capacity = obj.capacity;
        }
        this->_front = obj._front;
        this->_back = obj._back;
        for (size_t i = 0; i < obj.size(); i++)
        {
            this->_q = obj._q[i];
        }
    }
    return *this;
}

/**
 * @brief Returns the size of the queue
 *
 * @tparam T
 * @return int
 */
template <typename T>
int Queue<T>::size()
{
    return _size;
}

/**
 * @brief Return true if the queue is empty, otherwise return false
 *
 * @tparam T
 * @return true
 * @return false
 */
template <typename T>
bool Queue<T>::empty()
{
    return size() == 0;
}

/**
 * @brief A typical queue operation to add an element to the back of the queue
 *
 * @tparam T
 * @param val Value to be added
 */
template <typename T>
void Queue<T>::enqueue(T val)
{
    if (empty())
    {
        _back = _back + 1;
        _front = _front + 1;
        _q[_back] = val;
        _size++;
    }
    else if (size() != capacity)
    {
        _back = (_back + 1) % capacity;
        _q[_back] = val;
        _size++;
    }
    else
    {
        throw QueueFullException();
    }
}

/**
 * @brief A typical queue operation to remove an element from the front of the queue
 *
 * @tparam T
 */
template <typename T>
void Queue<T>::dequeue()
{
    if (empty())
    {
        throw QueueEmptyException();
    }
    else
    {
        _front = (_front + 1) % capacity;
        _size--;
        if (empty())
        {
            _front = -1;
            _back = -1;
        }
    }
}

/**
 * @brief Returns the element at the front of the queue
 *
 * @tparam T
 * @return T
 */
template <typename T>
T Queue<T>::front()
{
    if (empty())
        throw QueueEmptyException();
    return _q[_front];
}

/**
 * @brief Returns the element at the back of the queue
 *
 * @tparam T
 * @return T
 */
template <typename T>
T Queue<T>::back()
{
    if (empty())
        throw QueueEmptyException();
    return _q[_back];
}

int main()
{
    Queue<int> q;
    q.enqueue(5);
    q.enqueue(9);
    q.enqueue(8);
    q.enqueue(3);

    q.dequeue();
    q.dequeue();
    q.dequeue();
    q.dequeue();
    std::cout << "Size : " << q.size() << std::endl;

    q.enqueue(5);

    std::cout << "Front of the queue : " << q.front() << std::endl;
    std::cout << "Back of the queue : " << q.back() << std::endl;
    std::cout << "Size : " << q.size() << std::endl;

    if (q.empty())
        std::cout << "Queu is emtpy" << std::endl;

    Queue<int> q2(q);

    std::cout << q2.front() << std::endl;

    Queue<int> q3 = q;

    std::cout << q3.back() << std::endl;

    return 0;
}
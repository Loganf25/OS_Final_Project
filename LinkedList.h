#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <string>
#include <sstream>

/*
TODO:
Logan Flora
Linked List Lab 
Implement the following methods:

insert()
push_back()
push_front()
pop_back()
pop_front()

See the method definitions for more details.
*/

template <typename T>
class LinkedList
{
private:
    struct Node
    {
        T data;
        Node *next;
        Node(const T &value) : data(value), next(nullptr) {}
    };

    Node *head;
    Node *tail;
    int count;

public:
    /**
     * @brief Default constructor for LinkedList class.
     */
    LinkedList()
    {
        head = nullptr;
        tail = nullptr;
        count = 0;
    }

    /**
     * @brief Copy constructor for LinkedList class.
     * @param other The LinkedList object to be copied.
     */
    LinkedList(const LinkedList &other)
    {
        head = nullptr;
        tail = nullptr;
        count = 0;
        Node *current = other.head;
        while (current != nullptr)
        {
            push_back(current->data);
            current = current->next;
        }
    }

    /**
     * @brief Destructor for LinkedList class.
     * Deletes all nodes in the linked list.
     */
    ~LinkedList()
    {
        clear();
    }

    /**
     * @brief Clears the linked list by deleting all nodes.
     */
    void clear()
    {
        while (head != nullptr)
        {
            Node *temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        count = 0;
    }

    /**
     * @brief Checks if the linked list is empty.
     * @return True if the linked list is empty, false otherwise.
     */
    bool empty() const
    {
        return count == 0;
    }

    /**
     * @brief Returns the size of the linked list.
     * @return The number of elements in the linked list.
     */
    int size() const
    {
        return count;
    }

    //Adds a new node to the back of a list
    void push_back(const T &value)
    {
        // Create a new node
        Node* newNode = new Node(value); 
        // If the list is empty, set the head to the new node
        if (empty())
        {
            head = newNode;
            tail = newNode;
        }
        // Otherwise, set the tail's next to the new node
        else 
        {
            tail->next = newNode;
            // Set the tail to the new node
            tail = newNode;
        }
        // Increment the count
        count++; 
    }

//Puts a new node at the front of a list
    void push_front(const T &value)
    {
        // Create a new node
        Node* newNode = new Node(value);
        // If the list is empty, set the tail to the new node
        if (empty())
            tail = newNode;
        // Set the new node's next to the head
        newNode->next = head; 
        // Set the head to the new node
        head = newNode; 
        // Increment the count
        count++; 
    }

    //This one puts a new node is a specified index area of a list 
    void insert(int index, const T &value)
    {
        // If the index is out of range, throw an exception
        if (index < 0 || index >= count)
            throw std::out_of_range("Index out of range");
        // Create a new node
        Node* toInsert = new Node(value); 
        // If the index is 0, set the new node's next to the head
        if (index == 0)
        {
            toInsert->next = head;
        }
        // Set the head to the itterating node
        Node* newNode = head; 
        // Otherwise, iterate through the list to the index - 1 node
        for (int i = 0; i < index - 1; i++)
        {
           newNode = newNode->next;   
        }
        // Set the new node's next to the index node's next
        toInsert->next = newNode->next; 
        // Set the index node's next to the new node
        newNode->next = toInsert;
        // If the index is the last node, set the tail to the new node
        if (index == count - 1)
        {
            tail = toInsert;
        }
        // Increment the count
        count++; 
    }

    //Removes the back elements of a linked list 
    void pop_back()
    {
        // if the list is empty, throw an exception
        if (empty())
        {
            throw std::out_of_range("LinkedList is empty");
        }
        // If the head is the tail, delete the head
        if (head == tail)
        {
            delete head;
            head = nullptr;
            tail = nullptr;
        }
        // Otherwise, iterate through the list to the node before the tail
        else 
        {
            Node* temp = head;
            for (int i = 0; i < count - 2; i++)
            {
                temp = temp->next;
            }
            // Delete the tail
            delete tail;
            // Set the tail to the node before the tail
            tail = temp;
            // Set the tail's next to nullptr
            tail->next = nullptr;
        }
        // Decrement the count
        count--; 
    }

    //Removes the first element of a linked list 
    void pop_front()
    {
        // if the list is empty, throw an exception
        if (empty())
        {
            throw std::out_of_range("LinkedList is empty");
        }
        // Set the head to the next node
        Node* Todelete = head;
        head = head->next; 
        // Delete the old head
        delete Todelete; 
        // Decrement the count
        count--; 
    }

    /**
     * @brief Removes the element at the specified index from the linked list.
     * @param index The index of the element to be removed.
     * @throws std::out_of_range if the index is out of range.
     */
    void erase(int index)
    {
        if (index < 0 || index >= count)
        {
            throw std::out_of_range("Index out of range");
        }
        if (index == 0)
        {
            Node *temp = head;
            head = head->next;
            delete temp;
        }
        else
        {
            Node *temp = head;
            for (int i = 0; i < index - 1; i++)
            {
                temp = temp->next;
            }
            Node *nodeToDelete = temp->next;
            temp->next = nodeToDelete->next;
            delete nodeToDelete;
            if (index == count - 1)
            {
                tail = temp;
            }
        }
        count--;
    }

    /**
     * @brief Returns the value of the first element in the linked list.
     * @return The value of the first element.
     * @throws std::out_of_range if the linked list is empty.
     */
    T front() const
    {
        if (empty())
        {
            throw std::out_of_range("LinkedList is empty");
        }
        return head->data;
    }

    /**
     * @brief Returns the value of the last element in the linked list.
     * @return The value of the last element.
     * @throws std::out_of_range if the linked list is empty.
     */
    T back() const
    {
        if (empty())
        {
            throw std::out_of_range("LinkedList is empty");
        }
        return tail->data;
    }

    /**
     * @brief Returns the elements of the linked list as a string.
     */

    std::string toString() const
    {
        std::string result = "";
        Node *temp = head;
        bool first = true;
        while (temp != nullptr)
        {
            std::stringstream ss;
            ss << temp->data;
            if (!first)
            {
                result.append(" ");
            }
            else
            {
                first = false;
            }
            result.append(ss.str());
            temp = temp->next;
        }
        return result;
    }

    /**
     * @brief Prints the elements of the linked list.
     */
    void print() const
    {
        std::cout << toString() << std::endl;
    }

    /**
     * @brief Overloads the assignment operator to copy the contents of another LinkedList.
     * @param other The LinkedList to be copied.
     * @return A reference to the copied LinkedList.
     */
    LinkedList<T> &operator=(const LinkedList<T> &other)
    {
        if (this != &other)
        {
            clear();
            Node *temp = other.head;
            while (temp != nullptr)
            {
                push_back(temp->data);
                temp = temp->next;
            }
        }
        return *this;
    }

    /**
     * @brief Overloads the << operator to print the elements of the linked list.
     * @param os The output stream.
     * @param list The linked list to be printed.
     * @return The output stream.
     */
    friend std::ostream &operator<<(std::ostream &os,
                                    const LinkedList<T> &list)
    {
        os << list.toString();
        return os;
    }
};

#endif // LINKEDLIST_H

template <class T>
struct Node
{
    T data;
    Node* next;
};

template <class T>
class single_linked_list 
{
public:    
    Node<T> * m_head = nullptr;
    
public:
    single_linked_list() {}
    single_linked_list(const single_linked_list& other) = delete;

    void insert_item(Node<T>* previousNode, Node<T>* newNode) 
    {
        if (previousNode == nullptr) 
        {
            // Is the first node
            if (m_head != nullptr) 
            {
                // The list has more elements
                newNode->next = m_head;
            }
            else 
            {
                newNode->next = nullptr;
            }
            m_head = newNode;
        }
        else 
        {
            if (previousNode->next == nullptr) 
            {
                // Is the last node
                previousNode->next = newNode;
                newNode->next = nullptr;
            }
            else 
            {
                // Is a middle node
                newNode->next = previousNode->next;
                previousNode->next = newNode;
            }
        }
    }
    void remove_item(Node<T>* previousNode, Node<T>* deleteNode) 
    {
        if (previousNode == nullptr) 
        {
            // Is the first node
            if (deleteNode->next == nullptr) 
            {
                // List only has one element
                m_head = nullptr;
            }
            else 
            {
                // List has more elements
                m_head = deleteNode->next;
            }
        }
        else 
        {
            previousNode->next = deleteNode->next;
        }
    }
};

template <class T, class _Alloc = allocator<T>>
class single_linked_container : single_linked_list<T>
{
    typedef typename _Alloc::template rebind<Node<T>>::other NodeAllocator;

    NodeAllocator m_node_allocator = NodeAllocator();

    size_t m_items = 0x0;

public:
    single_linked_container() {};
    single_linked_container(const single_linked_container& other) = delete;

    ~single_linked_container() {};

    size_t size()
    {
        return m_items;
    }

    bool empty()
    {
        return m_items == 0;
    }

    void insert(const T& item)
    {
        //Use defined allocator
        Node<T>* new_node = (Node<T>*)m_node_allocator.allocate(1);

        new_node->data = item;

        //Insert always in head
        insert_item(nullptr, new_node);

        m_items++;
    }

    T& operator[](const size_t Pos)
    {
        Node<T>* next = m_head;

        //-1 because items pos counted form 0
        size_t counter = m_items - Pos - 1;

        while(counter--)
        {
            next = next->next;
        }

        return next->data;
    }
};
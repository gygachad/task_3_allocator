template <class T>
struct Node
{
    T data;
    Node* next;
};

template <class T>
struct single_linked_list 
{    
    Node<T> * m_head = nullptr;

    single_linked_list() {}
    single_linked_list(const single_linked_list& other) 
    {
        UNUSED(other);
    };

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
class single_linked_container
{
    using NodeAllocator = typename std::allocator_traits<_Alloc>::template rebind_alloc<Node<T>>;

    NodeAllocator m_node_allocator = NodeAllocator();
    
    single_linked_list<T> m_item_list;

public:
    size_t m_items = 0x0;

    single_linked_container() {};

    single_linked_container(const single_linked_container& other)
    {
        Node<T>* copied_node = other.m_item_list.m_head;
        Node<T>* prev_node = nullptr;

        for (m_items = 0; m_items != other.m_items; m_items++)
        {
            //Use defined allocator
            Node<T>* new_node = (Node<T>*)m_node_allocator.allocate(1);
            
            new_node->data = T(copied_node->data);

            //Insert to list tail
            m_item_list.insert_item(prev_node, new_node);

            copied_node = copied_node->next;
            prev_node = new_node;
        }
    }

    ~single_linked_container() 
    {
        Node<T>* delete_node = nullptr;
        Node<T>* next_node = m_item_list.m_head;

        while (m_items)
        {
            //Always delete from head
            m_item_list.remove_item(nullptr, next_node);

            delete_node = next_node;
            next_node = next_node->next;

            delete_node->data.~T();

            m_node_allocator.deallocate(delete_node, 1);

            m_items--;
        }
    }

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

        new_node->data = T(item);

        //Insert always in head
        m_item_list.insert_item(nullptr, new_node);

        m_items++;
    }

    T& operator[](const size_t Pos)
    {
        Node<T>* next = m_item_list.m_head;

        //-1 because items pos counted form 0
        size_t counter = m_items - Pos - 1;

        while(counter--)
        {
            next = next->next;
        }

        return next->data;
    }
};
//-------------------------------------------------
List* create_list()
{
    List* top = new List;
    top -> size_n = 0;
    if (top == NULL)
    {
        return NULL;
    }
    top -> head = top -> tail = NULL;
    return top;
}
//--------------------------------------------------
Node* create_node(List* elem, int data)
{
    if (elem == NULL)
    {
        printf("The list has lost his owner\n");
        return NULL;
    }
    Node* n = new Node;
    if (n == NULL)
    {
        return NULL;
    }
    n -> data = data;
    n -> next = NULL;
    n -> prev = NULL;
    (elem -> size_n)++;
    return n;
}
//------------------------------------------------
void push_in_front(List* elem, Node* n3)
{
    if (elem == NULL)
    {
        printf("The list has lost his owner\n");
        return;
    }
    if (elem -> head == NULL)
    {
        elem -> head = n3;
        elem -> tail = n3;
    }
    else
    {
        n3 -> next = elem -> head;
        elem -> head -> prev = n3;
        elem -> head = n3;
    }
}
//-------------------------------------------------
void push_in_back(List* elem, Node* n1)
{
    if (elem == NULL)
    {
        printf("The list has lost his owner\n");
        return;
    }
    if (elem -> tail == NULL)
    {
        elem -> tail = n1;
        elem -> head = n1;
    }
    else
    {
        elem -> tail -> next = n1;
        n1 -> prev = elem -> tail ;
        elem -> tail = n1;
    }
}
//-----------------------------------------------------------
void print_list(List* elem)
{
    if (elem == NULL)
    {
        printf("The list has lost his owner\n");
        return;
    }
    if (elem -> head != NULL)
    {
        Node* n3 = elem -> head;

        while(n3 != NULL)
        {
            if (n3 -> next == NULL)
            {
                printf("%d\n", n3 -> data);
                n3 = n3 -> next; break;
            }
            printf("%d  ", n3 -> data);
            n3 = n3 -> next;
        }

    }
    else
    {
        printf("Error in printf Node\n");
        return;

    }
}
//-----------------------------------------------------
int insert_after(Node* after, int data, List* elem)
{
    if (elem == NULL)
    {
        printf("The list has lost his owner\n");
        return ERROR_IN_LIST;
    }
    Node* n2 = new Node;
    if (n2 == NULL)
    {
        return ERROR_IN_NODE;
    }
    if (after == NULL)
    {
        printf("No such a node");
        return ERROR_NO_SUCH_NODE;
    }
    if (after -> next == NULL)
    {
        printf("Please, use another one function_1\n");
        return ERROR_ANOTHER_FUNCT;
    }
    n2 -> data = data;
    n2 -> next = after -> next;
    n2 -> prev = after;
    after -> next = n2;
    (n2 -> next) -> prev = n2;
    (elem -> size_n)++;
}
//--------------------------------------------------------------
int delete_node(Node* cur, List* elem)
{
    if (elem == NULL)
    {
        printf("The list has lost his owner\n");
        return ERROR_IN_LIST;
    }
    if (cur == NULL)
    {
        printf("No such a node");
        return ERROR_NO_SUCH_NODE;
    }
    if (cur -> next == NULL || cur -> prev == NULL)
    {
        printf("Please, use another one function_2\n");
        return ERROR_ANOTHER_FUNCT;
    }
    (cur -> next) -> prev = cur -> prev;
    (cur -> prev) -> next = cur -> next;
    (elem -> size_n)--;
    delete cur;
}
//----------------------------------------------------------------------
void delete_list(List* elem)
{
    if (elem == NULL)
    {
        printf("I won't be able to delete this list");
        return;
    }
    Node* n = elem -> head;
    while (n != NULL)
    {
        if (n -> next == NULL)
        {
            delete n;
            return;
        }
        elem -> head = n -> next;
        n -> next = NULL;
        delete n;
        n = elem -> head;
    }
}
//--------------------------------------------------------------------------
Node* search_by_data(int inf, List* elem)
{
    if (elem == NULL)
    {
        printf("The list has lost his owner\n");
        return NULL;
    }
    Node* n = elem -> head;
    while (n != NULL)
    {
        if (n -> data == inf)
        {
             return n;
        }
        n = n -> next;
    }
    return NULL;
}
//--------------------------------------------------------------------------



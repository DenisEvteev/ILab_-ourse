#include "consts_struct_prototips.h"
int main()
{
    List* top = create_list();
    Node* n1 = create_node(top, 9);
    Node* n2 = create_node(top, 5);
    Node* n3 = create_node(top, 4);
    Node* n4 = create_node(top, 665);
    Node* n5 = create_node(top, 774);
    push_in_back(top, n1);
    push_in_back(top, n2);
    push_in_front(top, n3);
    push_in_front(top, n4);
    push_in_back(top, n5);
    insert_after(n4, 50, top);
    print_list(top);
    delete_node(n1, top);
    delete_node(n2, top);
    print_list(top);
    search_by_data(665, top);
    delete top;
    delete n1;
    delete n2;
    delete n3;
    delete n4;
    delete n5;
    return 0;
}

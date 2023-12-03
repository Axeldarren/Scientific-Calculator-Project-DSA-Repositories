#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>

using namespace std;

class Node
{
public:
    string data;   
    Node* next;

private:
    void push(Node** headRef, string inputEquation);
    void deleteHistory(Node** headRef, string key);
    void printHistory(Node* head);
};

// Function to insert a new node at the beginning of the linked list
void push(Node** headRef, string inputEquation)
{
    Node* newNode = new Node();
    newNode->data = inputEquation;
    newNode->next = (*headRef); 
    (*headRef) = newNode;
}
 
// Function to print the history of equations in the linked list 
void printHistory(Node* headRef)
{
    Node* current = headRef;
    int index = 0;
    
    cout << "History (latest to oldest):\n";
    
    while (current != NULL)
    {
        
		cout << index << ") " << current->data <<"\n";
        current = current->next;
        index++;
    }
 }

// Function to delete a node from the linked list by index (currently incorrect)
void deleteNode(Node** headRef, int index)
{
 
    if (*headRef == NULL) 
    {
        cout << "History is empty...";
        return;
    }
 
    Node* current = *headRef;
 
    if (index == 0) 
    {
        *headRef = current->next;
 
        free(current);
        return;
    }
 
    for (int i = 0; current != NULL && i < index - 2; i++)
        current = current->next;
 
    if (current == NULL || current->next == NULL)
        return;

    Node* next = current->next->next;
 
    free(current->next);

    current->next = next;
}
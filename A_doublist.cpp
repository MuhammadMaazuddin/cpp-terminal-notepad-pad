#include <iostream>
#include <fstream>
using namespace std;
struct Node
{
    char letter;
    Node *front;
    Node *back;
    Node *above;
    Node *below;
};
class LinkedList
{
    private:
        Node *head;
        int row;
        int col;
        int PreCol;
        Node *ROW;
        Node *currentCOL;
        Node *NewROW;
    public:
        LinkedList(){head = NULL;row = 0;col=0;}
        void insert(char letter);
        Node* node(char letter);
        void display();
        void edit(int Row,int Col,char letter);
        void save();

};

void LinkedList::save()
{
    ofstream file("save.txt");
    Node *row = head;
    Node *col ;


    while(row->below != NULL)
    {
        col = row;
        while(col->front != NULL)
        {
            if(col->letter!= '~')
            {
                file<<col->letter;
            }
            col = col->front;
            
        }
         if(col->letter!= '~')
            {
                file<<col->letter;
            }
         
        row = row->below;
    }
    col = row;
     while(col->front != NULL)
    {
         if(col->letter!= '~')
            {
                file<<col->letter;
            }
        col = col->front;
    }
     if(col->letter!= '~')
            {
                file<<col->letter;
            }
 

file.close();

}

void LinkedList::edit(int Row,int Col,char letter)
{
    int num1=0,num2=0;
    Node *row = head;
    Node *col ;

    if(row->front == NULL){row->letter = letter;}
    while(row->below != NULL)
    {
        num2 = 0;
        col = row;
        while(col->front != NULL)
        {
            col = col->front;
            num2++;
            if(num1 == Row && num2 == Col)
            {
                col->letter = letter;
                break;
            }
        }
        if(num1 == Row && num2 == Col)
        {
            col->letter = letter;
            break;
        }
        row = row->below;
        num1++;
    }
    col = row;
    num2=0;
     while(col->front != NULL)
    {
        col = col->front;
        num2++;
         if(num1 == Row && num2 == Col)
        {
            col->letter = letter;
            break;
        }
    }
        if(num1 == Row && num2 == Col)
        {
            col->letter = letter;
        }

    
}
Node* LinkedList::node(char letter)
{
    Node* node = new Node;
    node->letter = letter;
    node->back = NULL;
    node->below = NULL;
    node->front = NULL;
    node->above = NULL;
    return node;
}


void LinkedList::insert(char letter) 
{
    if (head == NULL) 
    {
        head = node(letter);
        ROW = head;
        PreCol = col;
        currentCOL = head;
        col++;
    } 
    else 
    {
        if(row == 0 && col > 0)
        {
            Node *temp = head;
            Node *temp1 = currentCOL;
            currentCOL->front = node(letter);
            currentCOL = currentCOL->front;
            currentCOL->back = temp1;
            col++;
            if(letter == '\n')
            {
                PreCol = col;
                row++;
                col=0;
            }

        }
        else if(row > 0)
        {
            Node *newNode = new Node;
            newNode = node(letter);
            if(col == 0)
            {
                NewROW = newNode;
                newNode->above = ROW;
                currentCOL = NewROW;
                ROW->below = newNode;
                col++;
            }
            else if (col > 0)
            {
                int num = 0;
                Node *temp1 = ROW;
                Node *temp2 = currentCOL;
                currentCOL->front = newNode;
                currentCOL = currentCOL->front;
                currentCOL->back = temp2;
                   
              
               

                if(col<PreCol)
                {
                    while(temp1 != NULL)
                    {
                        temp1 = temp1->front;
                        num++;
                        if(num == col)
                        {
                            break;
                        }
                    }
                    currentCOL->above = temp1;
                    temp1->below = currentCOL;
                }
                
                col++;
            }
            if(newNode->letter == '\n')
            {
                PreCol = col;
                ROW = NewROW;
                col=0;
                row++;
            }
            
            

        }


       
    }
}



void LinkedList::display()
{
    Node *row = head;
    Node *col ;


    while(row->below != NULL)
    {
        col = row;
        while(col->front != NULL)
        {
            cout<<col->letter;
            col = col->front;
        }
        cout<<col->letter;
        row = row->below;
    }
    col = row;
     while(col->front != NULL)
    {
        cout<<col->letter;
        col = col->front;
    }
    cout<<col->letter;






    // Node* temp4 = head->front->below->back->front->front->front->above->front->below->front->front;
    // cout<<temp4->letter;
    // cout<<endl;
}

// int main()
// {
//     string array[5];
//     array[0] = "AG nJme is maaz.\n";
//     array[1] = "BH namK is sammar and topper.\n";
//     array[2] = "CI name is zohaib and.\n";
//     array[3] = "DJ name is safwan bhai.\n";
//     array[4] = "EK name is soban programer.\n";
//     LinkedList L1;
//     int num1=0;
//     for(int i=0;i<5;i++)
//     {   num1 = 0;
//         for(int j=0;array[i][j] != '\n';j++)
//         {
//             L1.insert(array[i][j]);
//             num1++;
//         }
//         L1.insert(array[i][num1]);
//     }    
//     L1.display();
//     L1.edit(3,15,'~');
//     L1.display();
//     L1.save();
// }
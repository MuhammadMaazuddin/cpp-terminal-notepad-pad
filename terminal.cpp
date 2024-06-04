#include <ncurses.h>
#include <vector>
#include"A_doublist.cpp"
#include<iostream>
#include<fstream>
using namespace std;
void dict()
{
    vector<string> dictionary;
int num = 0;
               ifstream file("dictionary.txt"); 

            if (file.is_open())
            {
                string line;

                while (getline(file, line))
                {
                    dictionary[num] = line;
                    num++;
                }
                file.close();
            }
}
void notePad() 
{
    LinkedList L1;
    char alpha;
    initscr();
    raw();
    curs_set(1); 
    int width = COLS;
    int height = LINES;

    int leftWidth = width * 0.75; 
    int rightWidth = width * 0.25; 

    WINDOW *leftWin = newwin(height, leftWidth, 0, 0);
    WINDOW *rightWin = newwin(height, rightWidth, 0, leftWidth);

    box(leftWin, 0, 0); 
    box(rightWin, 0, 0); 
    int y = 1, x = 1;

    wrefresh(leftWin);
    wrefresh(rightWin);
    wmove(leftWin, y, x);
    keypad(leftWin, TRUE); 

    int ch;
    while (1) 
    {

        ch = wgetch(leftWin); 
        char letter = static_cast<char>(ch);
        if (ch == KEY_DOWN){y++;} 
        else if (ch == KEY_UP && y>1){y--;} 
        else if (ch == KEY_LEFT && x>1){x--;} 
        else if (ch == KEY_RIGHT && x<57){x++;} 
        else if (ch == KEY_RIGHT && x==57 ){y++;x=1;} 
        else if (ch == 10){L1.insert(letter);y++;x = 1;} 
        else if (ch == 27) {break;}
        else if (ch == 19){L1.save();break;} 
        else if (x==57 ){L1.insert(letter);y++;x = 1;}
        else if (ch == 127 || ch == KEY_BACKSPACE) 
        {
            if (x > 0)
            {
               L1.edit(y-1,x-1,'~');
               mvwaddch(leftWin,y, x, ' ');
               if(x>1){x--;}
            }
            
        }
        else if(ch == 18)
        {
               ifstream file("save.txt"); 

            if (file.is_open())
            {
                string line;
                int row = 0; 
                y=0;
                while (getline(file, line))
                {
                    x=0;
                    line += '\n';
                    for(int i=0;line[i]!='\n';i++)
                    {
                        L1.insert(line[i]);x++;
                    }
                    L1.insert('\n');
                    mvwprintw(leftWin, row, 1, "%s",line.c_str());
                    row++; 
                    y++;
                }
                y--;
                wrefresh(leftWin);
                file.close();
            }
            
        }
        else
        {
           
           L1.insert(letter);
           x++;
        }
      
        box(leftWin, 0, 0);
        box(rightWin,0,0);
       

        wrefresh(leftWin);
        wrefresh(rightWin);
        wmove(leftWin, y, x);

    }

    endwin(); 
    L1.display();

}
int main() 
{
    notePad();
   

    return 0;
}

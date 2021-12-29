#include <ncurses.h>
#include <random>

int main(int argc, char** argv)
{
    unsigned int row=1, column=5, num=1;
    initscr();
    noecho();
    cbreak();
    
    // whole random thing - for random color
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 6);


    if(!has_colors)
    {
        printw("Your terminal does NOT support colors!");
        getch();
        return -1;   
    }
    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    init_pair(4, COLOR_MAGENTA, COLOR_BLACK);
    init_pair(5, COLOR_CYAN, COLOR_BLACK);
    init_pair(6, COLOR_WHITE, COLOR_BLACK);
    init_pair(9, COLOR_RED, COLOR_BLACK);
    
    if(can_change_color())
    {
        init_color(COLOR_RED, 1000,590,500); // kinda brown
    }

    WINDOW* win = newwin(14,13,0,0);
    refresh();
    box(win, 0, 0);
    // wborder(win,'*','*','*','*','*','*','*', '*');
    wrefresh(win);
    
    // star at the bottom of tree
    move(1,6);
    attron(COLOR_PAIR(1));
    attron(A_BLINK);
    printw("@");
    attroff(A_BLINK);
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(2));
    for(int i = 1; i<=9; ++i)  // rows
    {
        if(i == 3+1)
        {
            num = 3;
            column+=2;    
        }
        if(i == 6+1)
        {
            num = 5;
            column+=2;
        }
        move(row+1, column);
        for(int j = 0; j<num; ++j)  // 
        {
            if(j==0)
            {
                attron(A_BLINK);
                attron(COLOR_PAIR(dis(gen)));
                printw(".");
                attroff(A_BLINK);
                attroff(COLOR_PAIR(dis(gen)));
            }
            attron(COLOR_PAIR(2));
            printw("*");
            attroff(COLOR_PAIR(2));
            if(j==num-1)
            {
                attron(A_BLINK);
                attron(COLOR_PAIR(dis(gen)));
                printw(".");
                attroff(A_BLINK);
                attroff(COLOR_PAIR(dis(gen)));
            }
        }

        num+=2;
        column--;
        row++;
    }

    // the trunk
    attron(COLOR_PAIR(9));
    // mvwprintw(win, 11, 5, "#");
    // mvwprintw(win, 12, 5, "#");
    move(11, 6);
    printw("#");
    move(12, 6);
    printw("#");
    attroff(COLOR_PAIR(9));
    refresh();
    wrefresh(win);
    
    getch();
    getch();
    endwin();
    return 0;
}
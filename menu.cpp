


class menu{
public:
  menu(int row, int col){

    help = newwin((row-10), (col/2)-1, 5, ((col/2)+1));
    getmaxyx(help, hrow, hcol);
    refresh();

    box(help, 0,0);
    wrefresh(help);
    refresh();
  }


private:
  int y, x, hrow, hcol;
  WINDOW * help;

};

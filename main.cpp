#include <ncurses.h>
#include <menu.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <dirent.h>
#include <string.h>
#include <linux/limits.h>
#include <iostream>
#include "contenido.cpp"
#include "menu.cpp"
#include "ventana_display.cpp"


#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))
using namespace std;

//Inicia main

int main(int argc, char const *argv[]) {
  chdir("/home");

  int row=0, col=0, c;
  contenido dcont;
  char *abspath=NULL, *prevpath=NULL, *curitemname=NULL, *prueba=NULL, *newpath=NULL;
  getcwd(abspath, FILENAME_MAX);

  initscr();
  keypad(stdscr, TRUE);
  cbreak();
  getmaxyx(stdscr, row, col);
  refresh();



  menu* menu_principal = new menu(row, col);
  refresh();

  ventana_display* vdisplay = new ventana_display(row, col, abspath);
  refresh();
  //mvprintw(0, 0, "Use <SPACE> to select or unselect an item.");
  //mvprintw(1, 0, "<ENTER> to see presently selected items(F2 to Exit)");

  //cout << vdisplay->getDcontPosfinal();


	while((c = wgetch(vdisplay->getDisplay())) != KEY_F(2)){
           switch(c){

           case KEY_DOWN:
				        menu_driver(vdisplay->getMDisplay(), REQ_DOWN_ITEM);
				            break;

			     case KEY_UP:
				       menu_driver(vdisplay->getMDisplay(), REQ_UP_ITEM);
				           break;

           case KEY_NPAGE:
				      menu_driver(vdisplay->getMDisplay(), REQ_SCR_DPAGE);
				          break;

			     case KEY_PPAGE:
				       menu_driver(vdisplay->getMDisplay(), REQ_SCR_UPAGE);
				          break;
           case 10:
               getcwd(prevpath, FILENAME_MAX);
               mvwprintw(stdscr, 0,0, prevpath);
               mvwprintw(stdscr, 0,0, "Antes");
               curitemname=strdup(item_name(current_item(vdisplay->getMDisplay())));
               mvprintw(1,0, "Después");
               mvprintw(1,0, curitemname);


               newpath= vdisplay -> actualizar_display(prevpath, curitemname);
               mvprintw(2, 0,  newpath);
               vdisplay->nuevo_menu(newpath);
               refresh();
               getcwd(prueba, FILENAME_MAX);
               //printf ("\n %s",prueba);
               //cout << vdisplay->getDcontPosfinal() << "\n";
               cout << vdisplay-> getOpciones();




		}
                wrefresh(vdisplay->getDisplay());
	}

	/* Unpost and free all the memory taken up */
        unpost_menu(vdisplay->getMDisplay());
        free_menu(vdisplay->getMDisplay());
        for(int i = 0; i < vdisplay->getOpciones(); ++i){
                free_item(*(vdisplay->getItemsMenu()));
        }

  //cout << row;
  //cout << menu_principal->prueba1();
  //cout << menu_principal->prueba2();



  endwin();
  delete menu_principal;
  return 0;
}

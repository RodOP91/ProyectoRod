

class ventana_display{
  public:
    ventana_display(int row, int col,  char *abspath){
       this->leer_directorio(abspath);

       mvprintw(0,0, "");
       this->items_menu = this->crear_items(this->dcont, this->opciones);
       //mvprintw(1,0, "items creados ");
       menu_display= new_menu((ITEM **) items_menu);

       display = newwin((row-10), (col/2), 5, 0);
       keypad(this->display, TRUE);
       getmaxyx(this->display, drow, dcol);
       wrefresh(this->display);
       //mvprintw(2, 0, "displa creado ");

       set_menu_win(this->menu_display, this->display);
       set_menu_sub(this->menu_display, derwin(this->display, drow-1, dcol-1, 1, 1));
       set_menu_format(this->menu_display, 5, 1);

       box(display, 0, 0);

       post_menu(this->menu_display);
       refresh();
       wrefresh(this->display);

     }

     void nuevo_menu(char *newpath){
       this->leer_directorio(newpath);


       this->items_menu = this->crear_items(this->dcont, this->opciones);


       menu_display= new_menu((ITEM **) items_menu);

       set_menu_win(menu_display, display);
       set_menu_sub(menu_display, derwin(display, drow-1, dcol-1 -1, 1, 1));
       set_menu_format(menu_display, 5, 1);

       box(display, 0, 0);

       post_menu(this->menu_display);
       wrefresh(display);
     }

    char *actualizar_display(char *prevpath, char *curitemname){
      //recibe nuevo **items y lo actualiza en el menu
      char *newpath;
      this -> prevpath = prevpath;
      if(this -> dcont.getNombre(curitemname, this -> opciones) == curitemname && this -> dcont.getEsdir(curitemname, this ->opciones) == true){

            unpost_menu(this->getMDisplay());
            free_menu(this->getMDisplay());
            for(int i = 0; i < this->getOpciones(); ++i){
                  free_item(*(this->getItemsMenu()));
          }

            newpath = this -> dcont.getPath(curitemname, this -> opciones);
            this-> dcont.eliminarlista(this->opciones);
            return(newpath);


      }


    }

    void display_inicial(){
      /*recibe el contenido de /home y lo pone en el menu*/
      chdir("/home");
    }

    int leer_directorio(char *abspath){
      chdir(abspath);
      DIR *dir;
      struct dirent *sd;
      struct stat buf;
      char currentpath[FILENAME_MAX];

      /*Abre directorio, si es NULL regresa error*/
      if((dir = opendir(".")) == NULL){
        return errno;
      }

      /*Si el directorio actual es NULL regresa error*/
      if(getcwd(currentpath, FILENAME_MAX) == NULL){
        return errno;
      }

      /*Mientras que el stream del directorio no tenga datos nulos continúa*/
      while ((sd= readdir(dir)) != NULL){

        /*Si el nombre del archivo en el stream es '.' (cwd) o '..' (directorio padre), no hacer nada*/
        if(strcmp(sd -> d_name,".")==0 /*|| strcmp(sd -> d_name,"..") ==0*/){
            continue;
        }

        /*Gets cwd, then adds /filename to it and sends it to a linked list 'dcont'. Resets currentpath to cwd
        afterwards.*/
        getcwd(currentpath, FILENAME_MAX);
        strcat(currentpath, "/");
        strcat(currentpath, sd->d_name);

        char *path = (currentpath);
        bool es_dir;

        if(stat(currentpath, &buf) == -1){
          cout << currentpath << "\n";
          perror("hey");
          return errno;
        }
        getcwd(currentpath, FILENAME_MAX);

        //Prints Files and Directories. If Directory prints "it's directory", else prints "file info".
        if (S_ISDIR(buf.st_mode)) {
          es_dir = true;
          this-> dcont.crearnodo(path, sd->d_name, es_dir);
        }else{
          es_dir=false;
          this -> dcont.crearnodo(path, sd->d_name, es_dir);
        }
        this -> opciones++;
        //cout <<"Su tamaño es: " << (int)buf.st_size << "\n";


      }


      closedir(dir);

    }

    ITEM ** crear_items(contenido dcont, int opciones){
        this->items_menu = (ITEM **)calloc((this -> dcont.getPosicionfinal())+2, sizeof(ITEM *));

        for (int x = 0; x <= dcont.getPosicionfinal(); x++){
          this->items_menu[x] = new_item(this -> dcont.getNombrex(x, opciones), this -> dcont.getNombrex(x, opciones));
        }
        this->items_menu[(this -> dcont.getPosicionfinal())+1] = (ITEM *)NULL;
        return(this -> items_menu);
    }

    WINDOW * getDisplay(){
      return this -> display;
    }

    MENU * getMDisplay(){
      return this -> menu_display;
    }

    int getOpciones(){
      return this -> opciones;
    }

    ITEM ** getItemsMenu(){
      return this -> items_menu;
    }

    int getDcontPosfinal(){
      return this->dcont.getPosicionfinal();
    }
private:
  int drow, dcol,opciones;
  char *prevpath=NULL;
  contenido dcont;
  WINDOW * display;
  MENU * menu_display;
  ITEM **items_menu;
};

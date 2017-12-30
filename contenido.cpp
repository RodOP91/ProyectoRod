//Definicion de estructura nodo
using namespace std;
struct nodo{
  int pos=0;
  bool es_dir=false;
  char *nombre=NULL;
  char *path=NULL;
  struct nodo *next;
};

//Termina definición de nodo

//Clase contenido: Lista ligada que contiene iformación acerca del stream de directorio abierto en cuestión. Guarda el path
//absoluto, la posición en la que se guardó e incluye los métodos para su impresión en la pantalla.

class contenido{

  private:

    nodo *root=NULL, *cola=NULL;

  public:

    contenido(){
      root= NULL;
      cola= NULL;
    }
    void crearnodo(char *path, char *nombre, bool es_dir){

      nodo *temp = new nodo;
      temp -> path = path;
      temp -> nombre = nombre;
      temp -> es_dir = es_dir;
      temp -> next = NULL;

      if (root==NULL) {

        temp -> pos=0;
        root= temp;
        cola= temp;
        temp=NULL;

      }else{

        temp -> pos= cola -> pos +1 ;
        cola -> next = temp;
        cola = temp;

      }

    }

    void mostrardircont(){
      nodo *temp = new nodo;
      temp = root;

      while (temp->next != NULL) {

        cout << "Su posición: "<< temp -> pos << "\n";
        cout << temp -> path << "\t\n";
        temp= temp->next;

      }

    }

    char *getNombre(char *curitemname, int opciones){
      nodo *temp = new nodo;
      temp= root;
      for(int i=0; i < opciones; i++) {
        if(curitemname == temp -> nombre){
          return(temp -> nombre);
        }
        temp= temp->next;
      }
    }

    char *getNombrex(int x, int opciones){
      nodo *temp = new nodo;
      temp= root;
      for(int i=0; i < opciones; i++) {
        if(x == temp -> pos){
          return(temp -> nombre);
        }
        temp= temp->next;
      }
    }

    int getPosicionfinal(){
      return this->cola->pos;
    }

    char *getPath(char *curitemname, int opciones){
      nodo *temp = new nodo;
      temp=root;
      for(int i=0; i < opciones ; i++){
        if(curitemname == temp -> nombre){
          return(temp -> path);
        }
        temp = temp -> next;
      }
    }

    bool getEsdir(char *curitemname, int opciones){
      nodo *temp = new nodo;
      temp=root;
      for(int i=0; i < opciones ; i++){
        if(curitemname == temp -> nombre){
          return(temp -> es_dir);
        }
        temp = temp -> next;
      }
    }

    void eliminarlista(int opciones){

      nodo *actual=new nodo;
      nodo *previo=new nodo;
      actual=root;
      for(int x=0; x< opciones; x++){
        while(actual->next!=NULL)
        {
          previo=actual;
          actual=actual->next;
        }

          previo->next=NULL;
          cola=previo;
          delete actual;
      }
    }


};

//Termina clase contenido

# Proyectorod
EL proyecto usa tres clases:
1.menu --> Crea una ventana "help" donde se pondrá información al usuario. Simplemente es un "anuncio"
2.contenido --> Crea listas ligadas para guardar el nombre, path, posicion y es_dir(true/false) de un archivo leído por readdir().
3.ventana_display --> Crea una ventana "display" que se encargará de crear/destruir menús conforme vaya navegando el usuario. Además aquí están todas las funciones para abrir, leer, guardar y cambiar directorios.

Main se comunica principalmente con ventana_display. Por el momento crea y muestra los contenidos del directorio inicial (/home) pero al momento de querer cambiar de directorio simplemente no funciona como debería. Presiento que tiene algo que ver a partir del "case: 10" del main y la función actualizar_display() que manda a llamar. 

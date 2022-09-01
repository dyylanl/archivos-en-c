//(2) Escriba una aplicación básica con interfaz gráfica. El programa debe desplegar una ventana con un botón “Cerrar” (que haga terminar ordenadamente la aplicación). Comente/Explique el programa.

#include <gtkmm-3.0/gtkmm.h>
#include <iostream>

class Ventana : public Gtk::Window { //Creo una clase que hereda de GtkWindow
    private:
        Gtk::Window *pWindow; //Declaro la ventana
        Gtk::Button *pButton; //Declaro el boton
    public:
        Ventana() {
            pWindows = new Gtk::Window(); //Creo una ventana
            pButton = new Gtk::Button(); //Creo un boton
            pButton -> set_label("salir"); //Label del boton "salir"
            pWindow -> add(*pButton); //Agrego a la ventana el boton
            pButton -> signal_clicked.connect(sigc::memfunc(*this, &Ventana::evento)); //Evento del clic del boton
            pWindow -> show_all(); //Dibujar todo
        }
        Gtk::Window* getWindow() {return this -> pWindow;} //Es para que el lanzador pueda mostrar la ventana.
    private:
        void evento(){
            Gtk::Aplication::close(); //El evento cierra la aplicacion
        }
};

int main() {
    auto app = Gtk::Aplication::create(); //Instancia la aplicacion
    Ventana win; //Instancio ventana
    app->run(*win.getWindow()); //Corro aplicacion que lanza la ventana
    return 0;
}

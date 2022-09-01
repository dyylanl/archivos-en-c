/*
 * Escriba una rutina que le de formato al contenido de un edit. El formato
 * deseado consiste en pasar a mayúscula la primer letra de cada palabra y
 * dejar el resto de los caracteres en minúscula.
 */

#include <gtkmm.h>
#define ERROR "***ERR***"
#define SEPARADOR_DECIMAL "."

void Formatear(Gtk::Entry* entry) {
    Glib::ustring texto = entry->get_text();
    if (Glib::Ascii::strtod(texto) != 0) {//Texto es un número
        int posPunto = texto.find(SEPARADOR_DECIMAL);
        texto = texto.substr(0, posPunto+3);
    } else  //No es número
        texto = ERROR;
    entry->set_text(texto);
}

// Todo lo que va de acá para abajo no está pedido en el ejercicio, es sólo para ver si funciona la función
class BotonFormatear : public Gtk::Button {
	public:
		BotonFormatear(Gtk::Entry* entry) : Gtk::Button("Formatear") {
			this->entry = entry;	
		}
	private:
		Gtk::Entry* entry;
		void on_clicked() { 
		    Formatear(entry);
		}
};

int main(int argc, char* argv[]) {
	Gtk::Main kit(argc, argv);
	Gtk::Entry entry;
	BotonFormatear boton(&entry);
	Gtk::VBox vbox;
	vbox.add(entry);
	vbox.add(boton);
	Gtk::Window v;
	v.add(vbox);
	v.show_all();
	Gtk::Main::run(v);
	return 0;
}	

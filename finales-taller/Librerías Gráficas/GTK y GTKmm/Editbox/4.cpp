/*
 * Escriba una rutina que le de formato al contenido de un edit. El formato
 * deseado consiste en pasar a mayúscula la primer letra de cada palabra y
 * dejar el resto de los caracteres en minúscula.
 */

#include <gtkmm.h>
#define ESPACIO " "

void formatearPalabraDelTexto(Glib::ustring &texto, int inicioPalabra, int finPalabra) {
    Glib::ustring palabra = texto.substr(inicioPalabra, finPalabra);
    palabra = palabra.lowercase();
    palabra.replace(0,1, palabra.substr(0,1).uppercase());
    texto.replace(inicioPalabra, finPalabra, palabra);
}

void Formatear(Gtk::Entry* entry) {
    Glib::ustring texto = entry->get_text();
    int inicioPalabra = 0;
    int sigEspacio = -1;
    while(texto.find(ESPACIO, sigEspacio+1) != std::string::npos) {
        sigEspacio = texto.find(ESPACIO, sigEspacio+1);
        formatearPalabraDelTexto(texto, inicioPalabra, sigEspacio-inicioPalabra);
        inicioPalabra = sigEspacio+1;
    }
    //Formateo del último espacio encontrado hasta el final del texto
    formatearPalabraDelTexto(texto, inicioPalabra, texto.size()-inicioPalabra);
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

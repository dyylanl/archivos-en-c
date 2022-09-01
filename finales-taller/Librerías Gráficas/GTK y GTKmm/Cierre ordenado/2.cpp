/*
 * Escriba la función MAYUSCULA que tome el contenido de un Edit de una ventana
 * (recibido como parámetro) y lo escriba en el mismo control poniéndo en mayúscula.
 */

#include <gtkmm.h>

void Mayuscula(Gtk::Entry* entry) {
	Glib::ustring texto = entry->get_text();
	entry->set_text(texto.uppercase());
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
			Mayuscula(entry);
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

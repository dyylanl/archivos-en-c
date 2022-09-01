/*
 * Escriba la función MAYUSCULA que tome el contenido de un Edit de una ventana
 * (recibido como parámetro) y lo escriba en el mismo control poniéndo en mayúscula.
 */

#include <gtkmm.h>
#include <gtkmm/application.h>

// Todo lo que va de acá para abajo no está pedido en el ejercicio, es sólo para ver si funciona la función
class BotonFormatear : public Gtk::Button {
	public:
		BotonFormatear(char* label) : Gtk::Button(label) {
		}
	private:
		void on_clicked() { 
		    //Gtk::Main::signal_quit();
		    Gtk::Aplication::close();
		    //Mayuscula(entry);
		}
};

int main(int argc, char* argv[]) {
	Gtk::Main kit(argc, argv);
    Gtk::Window v;
	char label[] = "Cerrar Ventana";
	BotonFormatear boton(label);
	v.add(boton);
	v.show_all();
	Gtk::Main::run(v);
	return 0;
}	

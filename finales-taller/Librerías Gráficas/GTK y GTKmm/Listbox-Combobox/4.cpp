/*
 * Escriba el trozo de código necesario para cargar un Combobox/Listbox de una ventana
 * con 20 strings del tipo “Opción xx”, siendo x un entero entre 1 y 20.
 */


#include <gtkmm.h>
//#include <sstream>
#include <string>

int main(int argc, char* argv[]) {
	Gtk::Main kit(argc, argv);	
	Gtk::ComboBoxText combo;
	
	Glib::ustring str = "Opcion ";
	//std::stringstream sstream;
	for (int i = 1; i <= 20; ++i) {
		//sstream << i;
		//combo.append_text(str + sstream.str());
		//sstream.str("");
	    std::string stri = std::to_string(i);
	    combo.append_text(str + stri);
	}
	
	Gtk::Window v;
	v.add(combo);
	v.show_all();
	Gtk::Main::run(v);
	return 0;
}	

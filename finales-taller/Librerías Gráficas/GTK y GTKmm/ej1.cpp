/*
Ej1:
Implemente una rutina (en Windows o Linux) que dibuje un óvalo que ocupe toda la ventana.

*/

//#include <gtkmm/drawingarea.h>
//#include <gtkmm/application.h>
//#include <gtkmm/window.h>
#include <gtkmm.h>

#include <cmath>
#define ANCHO_LINEA 0.05

class Ovalo : public Gtk::DrawingArea {
	protected:
        //const Cairo::RefPtr<Cairo::Context>& cr
		//virtual bool on_draw(const Cairo::RefPtr<Cairo::Context> &cr) {
        bool on_expose_event(GdkEventExpose* ev) {
            Glib::RefPtr< Gdk::Window > window = get_window();
            if (window) {
                Cairo::RefPtr< Cairo::Context > ctx = window->create_cairo_context();
                Gtk::Allocation alloc = get_allocation();
                int ancho = alloc.get_width();
                int alto = alloc.get_height();
                int x = ancho / 2;
                int y = alto / 2;
                int w = ancho * 2 / 4.0;
                int h = alto / 2.0;
                ctx->save();

                ctx->translate(x, y);
                ctx->scale(w, h);
                ctx->arc(0, 0, 1.0, 0, 2 * M_PI);
                ctx->set_source_rgba(0, 0, 1.0, 0);
                ctx->fill_preserve();
                ctx->restore();  // back to opaque black
                ctx->stroke();
                return true;
                //}
            }
        }
};

int main(int argc, char* argv[]) {
    Gtk::Main kit(argc, argv);
    Ovalo unDibujo;
    Gtk::Window unaVentana;
    unaVentana.add(unDibujo);
    unaVentana.show_all();
    Gtk::Main::run(unaVentana);
    return 0;

    /*Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.gtkmm.example");
    Gtk::Window win;
	win.set_title("DrawingArea");
	Ovalo area;
	win.add(area);
	area.show();
    return app->run(win);*/
}

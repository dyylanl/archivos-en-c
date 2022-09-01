//Escriba una rutina (para ambiente gráfico Windows o Linux) que muestre la figura.

#include <gtkmm.h>
#include <vector>

class Dibujo : public Gtk::DrawingArea {
    private:
        bool on_expose_event(GdkEventExpose* ev) {
            Glib::RefPtr< Gdk::Window > window = get_window();
            if (window) {
                Cairo::RefPtr< Cairo::Context > ctx = window->create_cairo_context();
                Gtk::Allocation alloc = get_allocation();
                ctx->scale(alloc.get_width(), alloc.get_height());

                ctx->move_to(0,0);
                ctx->line_to(1,1);
                ctx->move_to(0,1);
                ctx->line_to(1,0);
                ctx->set_source_rgb(0,0,0);
                ctx->set_line_width(0.02);
                std::vector< double > vLine(2);
                vLine[0] = 0.04;
                vLine[1] = 0.01;
                ctx->set_dash(vLine,0.02);
                ctx->stroke();
            }
        }
};
int main(int argc, char* argv[]) {
    Gtk::Main kit(argc, argv);  
    Dibujo unDibujo;
    Gtk::Window unaVentana;
    unaVentana.add(unDibujo);
    unaVentana.show_all();
    Gtk::Main::run(unaVentana);
    return 0;
}   

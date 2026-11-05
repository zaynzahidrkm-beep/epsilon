#include <ion.h>
#include <kandinsky.h>
#include <cmath>
#include <cstdio>

// Couleurs (RGB565)
KDColor col_bg = KDColor::RGB888(240, 240, 240);
KDColor col_bar = KDColor::RGB888(30, 144, 255); // Bleu
KDColor col_text = KDColor::RGB888(20, 20, 20);
KDColor col_white = KDColor::RGB888(255, 255, 255);

void draw_header(const char* title) {
    kd_rect_fill(KDRect(0, 0, 320, 30), col_bar);
    kd_draw_string(title, KDPoint(10, 7), 0, col_bar, col_white);
}

void afficher_menu_principal() {
    kd_rect_fill(KDRect(0, 30, 320, 192), col_bg);
    draw_header("Physique Term - Pesanteur");
    
    kd_draw_string("1. Rappels & Cours (2eme Loi Newton)", KDPoint(10, 50), 0, col_bg, col_text);
    kd_draw_string("2. Calculateur (Fleche & Portee)", KDPoint(10, 90), 0, col_bg, col_text);
    kd_draw_string("3. Equation de Trajectoire z(x)", KDPoint(10, 130), 0, col_bg, col_text);
    kd_draw_string("EXE: Choisir   |   BACK: Quitter", KDPoint(10, 190), 0, col_bg, KDColor::RGB888(100, 100, 100));
}

void ecran_cours() {
    kd_rect_fill(KDRect(0, 30, 320, 192), col_bg);
    draw_header("Rappels de Cours");
    
    kd_draw_string("1. Systeme: {Projectile}, Referentiel: Terrestre", KDPoint(10, 45), 0, col_bg, col_text);
    kd_draw_string("2. Bilan des forces: Poids P = m.g (sec. P)", KDPoint(10, 70), 0, col_bg, col_text);
    kd_draw_string("3. 2e Loi de Newton: a(t) = g", KDPoint(10, 95), 0, col_bg, col_text);
    kd_draw_string("4. Vitesse: vx(t)=v0.cos(a), vz(t)=-g.t+v0.sin(a)", KDPoint(10, 120), 0, col_bg, col_text);
    kd_draw_string("5. Position: x(t)=v0.cos(a).t", KDPoint(10, 145), 0, col_bg, col_text);
    kd_draw_string("   z(t)=-0.5.g.t^2 + v0.sin(a).t + z0", KDPoint(10, 165), 0, col_bg, col_text);
    
    kd_draw_string("Appuyer sur Back pour retourner", KDPoint(10, 195), 0, col_bg, KDColor::RGB888(120, 120, 120));
    
    while (true) {
        Ion::Keyboard::state key = Ion::Keyboard::scan();
        if (key.keyDown(Ion::Keyboard::Key::Back)) return;
    }
}

void ecran_calculateur() {
    kd_rect_fill(KDRect(0, 30, 320, 192), col_bg);
    draw_header("Resultats Type (Exemple v0=15, a=45°)");
    
    double v0 = 15.0;
    double alpha_deg = 45.0;
    double g = 9.81;
    double alpha = alpha_deg * M_PI / 180.0;
    double z0 = 0.0;
    
    double vz0 = v0 * sin(alpha);
    double vx0 = v0 * cos(alpha);
    
    double t_max = vz0 / g;
    double z_max = -0.5 * g * t_max * t_max + vz0 * t_max + z0;
    double x_max = vx0 * t_max;
    
    double delta = vz0 * vz0 + 2 * g * z0;
    double t_vol = (vz0 + sqrt(delta)) / g;
    double x_p = vx0 * t_vol;
    
    char buf[64];
    snprintf(buf, sizeof(buf), "V0: %.1f m/s | Angle: %.1f deg", v0, alpha_deg);
    kd_draw_string(buf, KDPoint(10, 45), 0, col_bg, col_text);
    
    snprintf(buf, sizeof(buf), "Temps au sommet: %.2f s", t_max);
    kd_draw_string(buf, KDPoint(10, 80), 0, col_bg, col_text);
    
    snprintf(buf, sizeof(buf), "Fleche max (Hmax): %.2f m", z_max);
    kd_draw_string(buf, KDPoint(10, 110), 0, col_bg, col_text);
    
    snprintf(buf, sizeof(buf), "Portee (sol z=0): %.2f m", x_p);
    kd_draw_string(buf, KDPoint(10, 140), 0, col_bg, col_text);
    
    kd_draw_string("Appuyer sur Back pour retourner", KDPoint(10, 195), 0, col_bg, KDColor::RGB888(120, 120, 120));
    
    while (true) {
        Ion::Keyboard::state key = Ion::Keyboard::scan();
        if (key.keyDown(Ion::Keyboard::Key::Back)) return;
    }
}

void ecran_trajectoire() {
    kd_rect_fill(KDRect(0, 30, 320, 192), col_bg);
    draw_header("Equation de Trajectoire");
    
    kd_draw_string("Formule generale :", KDPoint(10, 50), 0, col_bg, col_text);
    kd_draw_string("z(x) = -g / (2*v0^2*cos^2(a)) * x^2", KDPoint(10, 80), 0, col_bg, col_text);
    kd_draw_string("       + tan(a) * x + z0", KDPoint(10, 105), 0, col_bg, col_text);
    
    kd_draw_string("Cette parabole decrit exactement", KDPoint(10, 140), 0, col_bg, col_text);
    kd_draw_string("la trajectoire du projectile dans le plan.", KDPoint(10, 165), 0, col_bg, col_text);
    
    kd_draw_string("Appuyer sur Back pour retourner", KDPoint(10, 195), 0, col_bg, KDColor::RGB888(120, 120, 120));
    
    while (true) {
        Ion::Keyboard::state key = Ion::Keyboard::scan();
        if (key.keyDown(Ion::Keyboard::Key::Back)) return;
    }
}

extern "C" void main() {
    while (true) {
        afficher_menu_principal();
        
        while (true) {
            Ion::Keyboard::state key = Ion::Keyboard::scan();
            if (key.keyDown(Ion::Keyboard::Key::One) || key.keyDown(Ion::Keyboard::Key::EXE)) {
                ecran_cours();
                break;
            }
            if (key.keyDown(Ion::Keyboard::Key::Two)) {
                ecran_calculateur();
                break;
            }
            if (key.keyDown(Ion::Keyboard::Key::Three)) {
                ecran_trajectoire();
                break;
            }
            if (key.keyDown(Ion::Keyboard::Key::Back)) {
                return;
            }
        }
    }
}



   

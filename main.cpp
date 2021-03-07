///////////////////////////////////////////////////////////////////////////////
// Imagina
// ----------------------------------------------------------------------------
// IN - Synth�se d'images - Mod�lisation g�om�trique
// Auteur : Gilles Gesqui�re
// ----------------------------------------------------------------------------
// Base du TP 1
// programme permettant de cr�er des formes de bases.
// La forme repr�sent�e ici est un polygone blanc dessin� sur un fond rouge
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "vec.h"


/* Dans les salles de TP, vous avez g�n�ralement acc�s aux glut dans C:\Dev. Si ce n'est pas le cas, t�l�chargez les .h .lib ...
Vous pouvez ensuite y faire r�f�rence en sp�cifiant le chemin dans visual. Vous utiliserez alors #include <glut.h>.
Si vous mettez glut dans le r�pertoire courant, on aura alors #include "glut.h"
*/

#include <GL/glut.h>
#include <vector>

using namespace std;
using namespace Angel;
// D�finition de la taille de la fen�tre
#define WIDTH  720

#define HEIGHT 720

// D�finition de la couleur de la fen�tre
#define RED   1
#define GREEN 0
#define BLUE  0
#define ALPHA 1


// Touche echap (Esc) permet de sortir du programme
#define KEY_ESC 27

#define Z_TOUCH 122
#define S_TOUCH 115
#define Q_TOUCH 113
#define D_TOUCH 100

#define O_TOUCH 111
#define L_TOUCH 108
#define K_TOUCH 107
#define M_TOUCH 109

typedef struct {
    double x;
    double y;
    double z;
} Point;


// Ent�tes de fonctions
void init_scene();

void render_scene();

GLvoid initGL();

GLvoid window_display();

GLvoid window_reshape(GLsizei width, GLsizei height);

GLvoid window_key(unsigned char key, int x, int y);

float x_key_P0 = 0;
float y_key_P0 = 0;

float x_key_P1 = 0;
float y_key_P1 = 0;

int main(int argc, char **argv) {
    // initialisation  des param�tres de GLUT en fonction
    // des arguments sur la ligne de commande
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA);
    // d�finition et cr�ation de la fen�tre graphique, ainsi que son titre
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("Premier exemple : carré");

    // initialisation de OpenGL et de la sc�ne
    initGL();
    init_scene();



    // choix des proc�dures de callback pour
    // le trac� graphique
    glutDisplayFunc(&window_display);
    // le redimensionnement de la fen�tre
    glutReshapeFunc(&window_reshape);
    // la gestion des �v�nements clavier
    glutKeyboardFunc(&window_key);

    // la boucle prinicipale de gestion des �v�nements utilisateur
    glutMainLoop();

    return 1;
}

// initialisation du fond de la fen�tre graphique : noir opaque
GLvoid initGL() {
    glClearColor(RED, GREEN, BLUE, ALPHA);
}

// Initialisation de la scene. Peut servir � stocker des variables de votre programme
// � initialiser
void init_scene() {
}

// fonction de call-back pour l�affichage dans la fen�tre

GLvoid window_display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // C'est l'endroit o� l'on peut dessiner. On peut aussi faire appel
    // � une fonction (render_scene() ici) qui contient les informations
    // que l'on veut dessiner
    render_scene();

    // trace la sc�ne grapnique qui vient juste d'�tre d�finie
    glFlush();
}

// fonction de call-back pour le redimensionnement de la fen�tre

GLvoid window_reshape(GLsizei width, GLsizei height) {
    glViewport(0, 0, width, height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    // ici, vous verrez pendant le cours sur les projections qu'en modifiant les valeurs, il est
    // possible de changer la taille de l'objet dans la fen�tre. Augmentez ces valeurs si l'objet est
    // de trop grosse taille par rapport � la fen�tre.
    glOrtho(-2.0, 2.0, -2.0, 2.0, -2.0, 2.0);

    // toutes les transformations suivantes s�appliquent au mod�le de vue
    glMatrixMode(GL_MODELVIEW);
}

// fonction de call-back pour la gestion des �v�nements clavier

GLvoid window_key(unsigned char key, int x, int y) {
    switch (key) {
        case KEY_ESC:
            exit(1);

        case Z_TOUCH:
            y_key_P0 += 0.1;
            break;

        case S_TOUCH:
            y_key_P0 -= 0.1;
            break;

        case Q_TOUCH:
            x_key_P0 -= 0.1;
            break;

        case D_TOUCH:
            x_key_P0 += 0.1;
            break;

        case O_TOUCH:
            y_key_P1 += 0.1;
            break;

        case L_TOUCH:
            y_key_P1 -= 0.1;
            break;

        case K_TOUCH:
            x_key_P1 -= 0.1;
            break;

        case M_TOUCH:
            x_key_P1 += 0.1;
            break;


        default:
            printf("La touche %d n�est pas active.\n", key);
            break;
    }
    glutPostRedisplay();
}

/**
 * Tracer une courbe à l'aide d'un ensemble de point
 * @param points Ensemble de points
 */
void draw_curve(const vector<vec3> &points) {
    glBegin(GL_LINE_STRIP);
    for (size_t i = 0; i < points.size(); ++i) {
        double x = points[i].x;
        double y = points[i].y;
        double z = points[i].z;
        glVertex3f(x, y, z);
    }
    glEnd();
}

#define F1(U) (2 * pow(U, 3) - 3 * pow(U, 2) + 1)
#define F2(U) (-2 * pow(U, 3) + 3 * pow(U, 2))
#define F3(U) (pow(U, 3) - 2 * pow(U, 2) + U)
#define F4(U) (pow(U, 3) - pow(U, 2))

/**
 *
 * @param P0 Point P0
 * @param P1 Point P1
 * @param V0 Point V0
 * @param V1 Point V1
 * @nbu: precision
 * @return: liste de point
 */
vector<vec3> hermite_cubic_curve(vec3 P0, vec3 P1, vec3 V0, vec3 V1, long nb_u) {

    vector<vec3> points(nb_u);

    for (int i = 0; i < nb_u; ++i) {
        float u = (float) i / (float) (nb_u - 1);
        points.push_back(vec3(F1(u) * vec3{P0} + F2(u) * vec3{P1} + F3(u) * V0 + F4(u) * V1));

    }

    return points;
}
/**
 * Permet de calculer la factorielle de k
 * @param k Nombre à factorialisé
 * @return résulta de fact(k)
 */
double fact(double k) {
    return k == 0 ? 1 : k * fact(k - 1);
}

/**
 * @param n taille de TabControlPoint
 * @param i pointeur dans TabControlPoint
 * @return p3
**/
double bernstein(double n, double i, double u) {
    return fact(n) / (fact(i) * fact(n - i)) * pow(u, i) * pow(1 - u, n - i);
}

/**
 @param TabControlPoint: liste de point
 @param nbu: precision
 @return return: liste de point
 **/
vector<vec3> BezierCurveByBernstein(vector<vec3> TabControlPoint, long nbU) {
    vector<vec3> points;

    for (long i = 0; i <= nbU; ++i) {

        double u = 1 / (double) (nbU - 1) * i;

        vec3 point(0, 0, 0);

        for (size_t j = 0; j < TabControlPoint.size(); ++j) {
            double b = bernstein(TabControlPoint.size() - 1, j, u);
            point += b * vec3(TabControlPoint[j]);

        }

        points.emplace_back(point);
    }

    return points;
}

/**
 * TabControlPoint: liste de point
 * @param n taille de TabControlPoint
 * @param i pointeur dans TabControlPoint
 * @param i pointeur dans TabControlPoint
 * @return: p3
 **/
vec3 Casteljau(vector<vec3> TabControlPoint, double n, double i, double u) {
    if (n == 0)
        return TabControlPoint[i];

    vec3 p1 = Casteljau(TabControlPoint, n - 1, i, u);
    vec3 p2 = Casteljau(TabControlPoint, n - 1, i + 1, u);

        vector<vec3> p1_p2 = { p1,p2};
        glColor3f(0, 1, 0);
        draw_curve(p1_p2);

    vec3 p3 = ((1 - u) * p1) + (u * p2);

    return p3;
}

/**
 * TabControlPoint: liste de point
 * nbu: precision
 * return: liste de point
 **/
vector<vec3> BezierCurveByCasteljau(const vector<vec3>& TabControlPoint, long nbU) {

    vector<vec3> points;

    for (long i = 0; i <= nbU; ++i) {

        double u = 1 / (double) (nbU - 1) * i;

        vec3 p3 = Casteljau(TabControlPoint, TabControlPoint.size() -1  , 0, u);

        points.push_back(p3);
    }

    return points;
}


//////////////////////////////////////////////////////////////////////////////////////////
// Fonction que vous allez modifier afin de dessiner
/////////////////////////////////////////////////////////////////////////////////////////
void render_scene() {
//D�finition de la couleur
    glColor3f(1.0, 1.0, 1.0);

    /**
     * ----------------------------------------------------Exercice 1 ----------------------------------------------------
     */


    //Trace la suite de point
    vec3 p0 = {0,0,0};
    vec3 p1 = {2,0,0};
    vec3 v1 = {1,1,0};
    vec3 v2 = {1,-1,0};

    //Trace une courbe en suivant l'algorithme de Hermite
    vector<vec3> courbe_hermite = hermite_cubic_curve(p0, p1, v1, v2, 100);
    draw_curve(courbe_hermite);

    /**
    * ----------------------------------------------------Exercice 2 ----------------------------------------------------
    */

//    // Même figure que l'exercice 1 mais avec en plus la possibilité de controle le premier et le dernier point de la courbe avec respectivement
//    // les touches ZQSD pour P1 et OKLM pour P2
//
//    vector<vec3> points = {
//            vec3(0 + x_key_P0, 0 + y_key_P0, 0),
//            vec3{2, 0, 0},
//            vec3{1, 1, 0},
//            vec3{1 + x_key_P1, -1 + y_key_P1, 0},
//    };
//    glColor3f(0, 1, 0);
//    draw_curve(points);
//
//    //Trace une courbe en suivant l'algorithme de Bernstein
//    vector<vec3> courbe_bezier= BezierCurveByBernstein(points,100);
//    glColor3f(0, 0, 1);
//    draw_curve(courbe_bezier);


    /**
   * ----------------------------------------------------Exercice 3 ----------------------------------------------------
   */

//    // Trace une courbe, de même que pour l'exercice 2, cette courbe permet sa modification dynamique du premier et
//    // dernier point avec les touches ZQSD pour P1 et OKLM pour P2
//    vector<vec3> points = {
//            vec3(-2 + x_key_P0,1.0 + y_key_P0,0.0) ,
//            vec3{-1, 2, 0},
//            vec3{0, 0.5, 0},
//            vec3{0.5, -2, 0},
//            vec3{2 + x_key_P1, 0.5f + y_key_P1 , 0}
//    };
//
//    //Trace une courbe en suivant l'algorithme de CastelJau
//    vector<vec3> courbe_castelJau = BezierCurveByCasteljau(points, 20);
//    draw_curve(courbe_castelJau);


}
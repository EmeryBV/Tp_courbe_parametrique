/**
 * @author Emery bourget Vecchio alia EmeryBv (github)
 */

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
    glutCreateWindow("Surface paramétrique");

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
    glClearColor(0.2, 0.2, 0.2,0);
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
    glOrtho(-3.0, 3.0, -3.0, 3.0, -3.0, 3.0);

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
/**
 * Trace une surface cylindrique
 * @param courbe Courbe  Courbe obtenue à partir de l'algorithme de CastelJau
 * @param directrice Vecteur de directeur
 * @param nbU Precision de  U
 * @return Une liste de liste de point
 */
vector<vector<vec3>> surface_cylindrique(vector<vec3> courbe, vec3 directrice, long nbU) {
vector<vector<vec3>> all_courbe;
    for (long i = 0; i <= nbU; ++i){
        vector<vec3> courbeV;
        double v = i / ((double)nbU-1);
        for (size_t j = 0; j < courbe.size(); ++j){
            vec3 point = courbe[j] + (1 - v) * directrice;
            courbeV.push_back(point);
        }
        all_courbe.push_back(courbeV);
    }
    return all_courbe;
}

/**
 * Trace une surface reglee
 * @param courbe Courbe  Courbe obtenue à partir de l'algorithme de CastelJau
 * @param directrice Vecteur de directeur
 * @param nbU Precision de  U
 * @return Une liste de liste de point
 */
vector<vector<vec3>>  surface_reglee(vector<vec3> courbe1, vector<vec3> courbe2, long nbU) {
    vector<vector<vec3>> all_courbe;
    for (long i = 0; i <= nbU; ++i){
        double v = i / ((double)nbU-1);
        vector<vec3> courbeV;
        for (size_t j = 0; j < courbe1.size(); ++j){
            vec3 point = vec3((1 - v) * vec3(courbe1[j]) + v * vec3(courbe2[j]));
            courbeV.push_back(point);
        }


//        draw_curve(courbeV);
        all_courbe.push_back(courbeV);

    }

    return all_courbe;
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

        double u = i / (double) (nbU - 1);

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
 * Trace une surface à l'aide du polynôme de Bernstein
 * @param GrilleControlPoint Liste de courbe
 * @param nbU Précision de U
 * @param nbV Précision de V
 * @return Une liste de courbe representant une surface
 */
vector<vector<vec3> > surface_bernstein(vector<vector<vec3> >& GrilleControlPoint, long nbU, long nbV) {

    vector<vector<vec3>> all_courbe;

    vector<vector<vec3>> control_u;

    glColor3f(1, 0, 0);


    for (int i = 0; i < GrilleControlPoint.size(); ++i) {
        control_u.push_back(BezierCurveByBernstein(GrilleControlPoint[i], nbU));
    }

    vector<vector<vec3> > control_v;

    for (int y = 0; y <= nbU; ++y){

        control_v.push_back(vector<vec3>());

        for (int i = 0; i < control_u.size(); ++i)
            control_v[y].push_back(control_u[i][y]);

        all_courbe.push_back(BezierCurveByBernstein(control_v[y], nbV));
    }

    return all_courbe;
}



/**
 * Permet d'afficher les courbes perpendiculaire par rapport à chacune des courbes du paramètre surface afin de representer une grille
 * @param surface liste de courbe formant une surface
 * @return liste de courbe
 */
 vector<vector<vector<vec3>>> surface_grid(vector<vector<vec3>> &surface) {
    vector<vector<vector<vec3>>> all_courbe;
    if (surface.empty())
        return all_courbe;

    for (int i = 0; i < surface.size(); ++i) {
        draw_curve(surface[i]);
    }

    vector<vector<vec3> > listVec3;

    for (int i = 0; i < surface[0].size(); ++i) {
        listVec3.push_back(vector<vec3>());
        for (size_t v = 0; v < surface.size(); ++v) {
            listVec3[i].push_back(surface[v][i]);
        }
        all_courbe.push_back(listVec3);
    }
     return all_courbe;
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

        double u = i / (double) (nbU - 1);

        vec3 p3 = Casteljau(TabControlPoint, TabControlPoint.size() -1  , 0, u);

        points.push_back(p3);
    }

    return points;
}

void render_scene() {
//D�finition de la couleur
    glColor3f(1.0, 1.0, 1.0);

    vector<vec3> points1 = {
            vec3(-2 + x_key_P0,1.0 + y_key_P0,0.0) ,
            vec3{-1, 2, 0},
            vec3{0, 0.5, 0},
            vec3{0.5, -2, 0},
            vec3{2 + x_key_P1, 0.5f + y_key_P1 , 0}
    };


    vector<vec3> points2 = {
            vec3(-1 + x_key_P0,0.0 + y_key_P0,0.0) ,
            vec3{-2, 1, 0},
            vec3{-1, -0.5, 0},
            vec3{-0.5, -3, 0},
            vec3{1 + x_key_P1, -0.5f + y_key_P1 , 0}
    };

    vector<vec3> points3 = {
            vec3(-2 + x_key_P0,-1 + y_key_P0,0.0) ,
            vec3{-3, 0, 0},
            vec3{-2, -1.5, 0},
            vec3{-1.5, -4, 0},
            vec3{0 + x_key_P1, -1.5f + y_key_P1 , 0}
    };

    vector<vec3> points4 = {
            vec3(2 + x_key_P0,3 + y_key_P0,0.0) ,
            vec3{1, 4, 0},
            vec3{2, 2.5, 0},
            vec3{2.5, 0, 0},
            vec3{4 + x_key_P1, 2.5f + y_key_P1 , 0}
    };

    //nombre de courbe dans la surface
    int precision = 20;
    //Trace une courbe en suivant l'algorithme de CastelJau sur la liste de vec3 point1
    vector<vec3> courbe_castelJau = BezierCurveByCasteljau(points1, precision);


    /**
     * ----------------------------------------------------Exercice 1 ----------------------------------------------------
     */

    //Vecteur directeur
    vec3 directrice = {-1,1};

    //Calcule la surface Cylindrique
    vector<vector<vec3>> surface_cylindrique_all = surface_cylindrique(courbe_castelJau, directrice, precision);
    //Affiche les courbes iso-paramétriques de la surface cylindrique
    for (int i = 0; i < surface_cylindrique_all.size() ; ++i) {
        glColor3f(0, 1, 0);
        draw_curve(surface_cylindrique_all[i]);
    }

    //Affiche la grille relative à la surface cylindrique
    vector<vector<vector<vec3>>> grid =  surface_grid(surface_cylindrique_all);
    for (int i = 0; i < grid.size() ; ++i) {
        for (int j = 0; j <grid[i].size() ; ++j) {
            if (j==0){ glColor3f(0,0 , 1); }
            else if (j==grid[i].size()-1 ){ glColor3f(1,0 , 0); }
            else glColor3f(0,1 , 0);
                draw_curve(grid[i][j]);
        }
    }


    /**
    * ----------------------------------------------------Exercice 2 ----------------------------------------------------
    */


//    vector<vec3> courbe_castelJau2 = BezierCurveByCasteljau(points2, precision);
//     //Fonction de calcule de la surface réglée
//    vector<vector<vec3>> surface_regle_all = surface_reglee(courbe_castelJau, courbe_castelJau2 ,precision);
//    for (int i = 0; i < surface_regle_all.size() ; ++i) {
//        glColor3f(0, 1, 0);
//        draw_curve(surface_regle_all[i]);
//    }
//
//// Affiche la grille relative à la surface reglée
//    vector<vector<vector<vec3>>> grid =  surface_grid(surface_regle_all);
//    for (int i = 0; i < grid.size() ; ++i) {
//        for (int j = 0; j <grid[i].size() ; ++j) {
//            if (j==0){ glColor3f(0,0 , 1); }
//            else if (j==grid[i].size()-1 ){ glColor3f(1,0 , 0); }
//            else glColor3f(0,1 , 0);
//                draw_curve(grid[i][j]);
//        }
//    }


    /**
   * ----------------------------------------------------Exercice 3 ----------------------------------------------------
   */

//
//
//    vector<vector<vec3>> grilleControlPoint;
//    grilleControlPoint.push_back(points4);
//    grilleControlPoint.push_back(points1);
//    grilleControlPoint.push_back(points2);
//    grilleControlPoint.push_back(points3);
//    //Fonction de calcule de la surface de Bézier par le polynome de Bernstein
//    vector<vector<vec3> > surface = surface_bernstein(grilleControlPoint, precision, precision);
//    for (int i = 0; i <surface.size() ; ++i) {
//        glColor3f(0, 1, 1);
//        draw_curve(surface[i]);
//    }
//
//
// //Affiche la grille relative à la surface de Bernstein
//    vector<vector<vector<vec3>>> grid =  surface_grid(surface);
//    for (int i = 0; i < grid.size() ; ++i) {
//        for (int j = 0; j <grid[i].size() ; ++j) {
//            if (j==0){ glColor3f(0,0 , 1); }
//            else if (j==grid[i].size()-1 ){ glColor3f(1,0 , 0); }
//            else glColor3f(0,1 , 0);
//            draw_curve(grid[i][j]);
//        }
//    }

}
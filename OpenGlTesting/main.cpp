#include<GL/glew.h>
#include <GL/glut.h>
#include <cstdio>
#include <stdlib.h>
#include <stdio.h>



int pos = 0;
int vertInd = 0;
int normInd = 0;
int uvInd = 0;
int faces[125000];
float ver[180000][3];
float uv[180000][2];
float vnormals[180000][3];

GLuint loadBMP_custom(const char* imagepath) {
    unsigned char header[54]; // Each BMP file begins by a 54-bytes header
    unsigned int dataPos;     // Position in the file where the actual data begins
    unsigned int width, height;
    unsigned int imageSize;   // = width*height*3
    // Actual RGB data
    unsigned char* data;

    FILE* file;
    fopen_s(&file, imagepath, "rb");
    if (!file) { printf("Image could not be opened\n"); return 0; }

    if (fread(header, 1, 54, file) != 54) { // If not 54 bytes read : problem
        printf("Not a correct BMP file\n");
        return false;
    }

    if (header[0] != 'B' || header[1] != 'M') {
        printf("Not a correct BMP file\n");
        return 0;
    }

    // Read ints from the byte array
    dataPos = *(int*)&(header[0x0A]);
    imageSize = *(int*)&(header[0x22]);
    width = *(int*)&(header[0x12]);
    height = *(int*)&(header[0x16]);

    if (imageSize == 0)    imageSize = width * height * 3; // 3 : one byte for each Red, Green and Blue component
    if (dataPos == 0)      dataPos = 54; // The BMP header is done that way

    // Create a buffer
    data = (unsigned char*)malloc(sizeof(unsigned char) * imageSize);

    // Read the actual data from the file into the buffer
    fread(data, 1, imageSize, file);

    //Everything is in memory now, the file can be closed
    fclose(file);



    GLuint textureID;
    glGenTextures(1, &textureID);
    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Give the image to OpenGL
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    free(data);
}

void scaleVerts() {
    for (int i = 0; i < sizeof(ver) / (sizeof(float)*3); i++) {
        for (int j = 0; j < 3; j++) {
            ver[i][j] *= 0.01;
        }
            
        
    }
}
void quad(int a, int b, int c, int d) 
{
   
    if (d == -1) 
    {
        glBegin(GL_TRIANGLES);

        glTexCoord2f(uv[a][0], uv[a][1]);
        glNormal3d(vnormals[a][0], vnormals[a][1], vnormals[a][2]); glVertex3fv(ver[a]);
       
        glTexCoord2f(uv[b][0], uv[b][1]);
        glNormal3d(vnormals[b][0], vnormals[b][1], vnormals[b][2]); glVertex3fv(ver[b]);
        
        glTexCoord2f(uv[b][0], uv[b][1]);
        glNormal3d(vnormals[c][0], vnormals[c][1], vnormals[c][2]); glVertex3fv(ver[c]);
        
        
        glEnd();
    }
    else
    {
        glBegin(GL_QUADS);

        glNormal3d(vnormals[a][0], vnormals[a][1], vnormals[a][2]);
        glVertex3fv(ver[a]);

        glNormal3d(vnormals[b][0], vnormals[b][1], vnormals[b][2]);
        glVertex3fv(ver[b]);

        glNormal3d(vnormals[c][0], vnormals[c][1], vnormals[c][2]);
        glVertex3fv(ver[c]);

        glNormal3d(vnormals[d][0], vnormals[d][1], vnormals[d][2]);
        glVertex3fv(ver[d]);


        glEnd();
    }
   
}
void colorcube()
{
    for (int i = 0; i < pos; i+=3) 
    {
        quad(faces[i], faces[i + 1], faces[i + 2],-1);
    }
}

double rotate_y = 0;
double rotate_x = 0;
double rotate_z = 0;
void specialKeys(int key, int x, int y)
{
    if (key == GLUT_KEY_RIGHT)
        rotate_y += 5;
    else if (key == GLUT_KEY_LEFT)
        rotate_y -= 5;
    else if (key == GLUT_KEY_UP)
        rotate_x += 5;
    else if (key == GLUT_KEY_DOWN)
        rotate_x -= 5;
    else if (key == GLUT_KEY_F1)
        rotate_z += 1;
    else if (key == GLUT_KEY_F2)
        rotate_z -= 1;
    glutPostRedisplay();
}
void display()
{
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    int w = glutGet(GLUT_WINDOW_WIDTH);
    int h = glutGet(GLUT_WINDOW_HEIGHT);
    gluPerspective(60, w / h, 0.1, 100);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt
    (
        0, 5 + (rotate_z / 10),3 + (rotate_z / 10),
        0, 0, 0,
        0, 0, 1
    );
    glRotatef(rotate_x, 1.0, 0.0, 0.0);
    glRotatef(rotate_y, 0.0, 0.0, 1.0);
    //glRotatef(rotate_z, 0.0, 1.0, 0.0);
    glEnable(GL_TEXTURE_2D);

    colorcube();

    glFlush();
    glDisable(GL_TEXTURE_2D);


    glutSwapBuffers();
 

}


//MOJE
void displayVerts(float a[][3])
{
    printf("STAMPAMO VERTEKSE\n");
    for (int i = 0; i < vertInd; i++) {
        printf("%f %f %f\n", a[i][0], a[i][1], a[i][2]);
    }
}
void displayFaces()
{
    puts("STAMPAMO FACES");
    for (int i = 0; i < pos; i+=3)
    {
        printf("%d %d %d\n", faces[i], faces[i + 1], faces[i + 2]);
    }
}
void readFaces()
{
    FILE* f;
    fopen_s(&f, "faces.txt", "r");
    char tmp;
    char  str[100];
    int pomm = 0;
    while (!feof(f))
    {
        fscanf_s(f, "%s", str, _countof(str));

        if (str[0] != 'f') {
            int face = atoi(str);
            faces[pos++] = face - 1;


        }
    }
    fclose(f);
}
void readVertices()
{
    FILE* f;
    char  str[100];
    int ind = 0;
    float seks[3];
    bool setMem = true;
    fopen_s(&f, "verts.txt", "r");
    while (!feof(f))
    {
        fscanf_s(f, "%s", str, _countof(str));
        if (str[0] != 'v') {
            float face = atof(str);
            seks[ind++] = face;
            if (ind == 3)
            {
                ind = 0;
                
                
                ver[vertInd][0] = seks[0];
                ver[vertInd][1] = seks[2];
                ver[vertInd][2] = seks[1];
               
                

                vertInd++;

            }

        }
    }
    fclose(f);
}
void readNormals()
{
    FILE* f;
    fopen_s(&f, "normals.txt", "r");

    char  str[100];
    int ind = 0;
    float seks[3];
    bool setMem = true;
    while (!feof(f))
    {
        fscanf_s(f, "%s", str, _countof(str));
        if (str[0] != 'v') {
            float face = atof(str);
            seks[ind++] = face;
            if (ind == 3)
            {
                ind = 0;

                vnormals[normInd][0] = seks[0];
                vnormals[normInd][1] = seks[2];
                vnormals[normInd][2] = seks[1];

                normInd++;

            }

        }
    }
    fclose(f);



}
void readUV()
{
    FILE* f;
    char  str[100];
    int ind = 0;
    float seks[2];
    bool setMem = true;
    fopen_s(&f, "texture.txt", "r");
    while (!feof(f))
    {
        fscanf_s(f, "%s", str, _countof(str));
        if (str[0] != 'v') {
            float face = atof(str);
            seks[ind++] = face;
            if (ind == 2)
            {
                ind = 0;

                uv[uvInd][0] = seks[0];
                uv[uvInd][1] = seks[1];


                uvInd++;

            }

        }
    }
    fclose(f);
}

void init(void)
{
  
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    loadBMP_custom("image.bmp");
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };
    GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0 };
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);


    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
}


int main(int argc, char** argv)
{
    readVertices();
    readFaces();
    readNormals();
    scaleVerts();
    readUV();

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
    glutInitWindowSize(640, 480);
    glutCreateWindow("GLUT");
    init();
    glutDisplayFunc(display);
    glutSpecialFunc(specialKeys);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();

    

    return 0;
}
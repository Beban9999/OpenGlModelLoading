#pragma once
#include <stdlib.h>
#include <stdio.h>
struct Object
{
	int vert_count;
	int norm_count;
	int face_count;
	int uv_count;

	int faces[125000];
	float ver[180000][3];
	float uv[180000][2];
	float normals[180000][3];

    void readFaces(const char* filename = "faces.txt")
    {
        face_count = 0;
        FILE* f;
        fopen_s(&f, filename, "r");
        char tmp;
        char  str[100];
        int pomm = 0;
        while (!feof(f))
        {
            fscanf_s(f, "%s", str, _countof(str));

            if (str[0] != 'f') {
                int face = atoi(str);
                faces[face_count++] = face - 1;


            }
        }
        fclose(f);
    }
    void readVertices(const char* filename = "verts.txt")
    {
        norm_count = 0;
        FILE* f;
        char  str[100];
        int ind = 0;
        float seks[3];
        bool setMem = true;
        fopen_s(&f, filename, "r");
        while (!feof(f))
        {
            fscanf_s(f, "%s", str, _countof(str));
            if (str[0] != 'v') {
                float face = atof(str);
                seks[ind++] = face;
                if (ind == 3)
                {
                    ind = 0;


                    ver[norm_count][0] = seks[0];
                    ver[norm_count][1] = seks[2];
                    ver[norm_count][2] = seks[1];



                    norm_count++;

                }

            }
        }
        fclose(f);
    }
    void readNormals(const char* filename = "normals.txt")
    {
        norm_count = 0;
        FILE* f;
        fopen_s(&f, filename, "r");

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

                    normals[norm_count][0] = seks[0];
                    normals[norm_count][1] = seks[2];
                    normals[norm_count][2] = seks[1];

                    norm_count++;

                }

            }
        }
        fclose(f);



    }
    void readUV(const char* filename = "textures.txt")
    {
        FILE* f;
        uv_count = 0;
        char  str[100];
        int ind = 0;
        float seks[2];
        bool setMem = true;
        fopen_s(&f, filename, "r");
        while (!feof(f))
        {
            fscanf_s(f, "%s", str, _countof(str));
            if (str[0] != 'v') {
                float face = atof(str);
                seks[ind++] = face;
                if (ind == 2)
                {
                    ind = 0;

                    uv[uv_count][0] = seks[0];
                    uv[uv_count][1] = seks[1];


                    uv_count++;

                }

            }
        }
        fclose(f);
    }
};
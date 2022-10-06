#include "glwidget.h"
#include <iostream>
#include <QOpenGLFunctions>
#include <glm/gtc/matrix_transform.hpp>

// Students: ignore this file

using namespace std;

static const int CubeVertexNum = 216;
static const GLfloat CubeData[] = {
    -0.5, 0.5, 0.5, -0, 0, 1,
    -0.5, -0.5, 0.5, -0, 0, 1,
    0.5, -0.5, 0.5, -0, 0, 1,
    0.5, -0.5, 0.5, 0, -0, 1,
    0.5, 0.5, 0.5, 0, -0, 1,
    -0.5, 0.5, 0.5, 0, -0, 1,
    0.5, 0.5, -0.5, -0, -0, -1,
    0.5, -0.5, -0.5, -0, -0, -1,
    -0.5, -0.5, -0.5, -0, -0, -1,
    -0.5, -0.5, -0.5, 0, 0, -1,
    -0.5, 0.5, -0.5, 0, 0, -1,
    0.5, 0.5, -0.5, 0, 0, -1,
    0.5, 0.5, 0.5, 1, 0, 0,
    0.5, -0.5, 0.5, 1, 0, 0,
    0.5, -0.5, -0.5, 1, 0, 0,
    0.5, -0.5, -0.5, 1, 0, 0,
    0.5, 0.5, -0.5, 1, 0, 0,
    0.5, 0.5, 0.5, 1, 0, 0,
    -0.5, 0.5, -0.5, -1, 0, 0,
    -0.5, -0.5, -0.5, -1, 0, 0,
    -0.5, -0.5, 0.5, -1, 0, 0,
    -0.5, -0.5, 0.5, -1, 0, 0,
    -0.5, 0.5, 0.5, -1, 0, 0,
    -0.5, 0.5, -0.5, -1, 0, 0,
    0.5, 0.5, -0.5, 0, 1, -0,
    -0.5, 0.5, -0.5, 0, 1, -0,
    -0.5, 0.5, 0.5, 0, 1, -0,
    -0.5, 0.5, 0.5, -0, 1, 0,
    0.5, 0.5, 0.5, -0, 1, 0,
    0.5, 0.5, -0.5, -0, 1, 0,
    0.5, -0.5, 0.5, -0, -1, -0,
    -0.5, -0.5, 0.5, -0, -1, -0,
    -0.5, -0.5, -0.5, -0, -1, -0,
    -0.5, -0.5, -0.5, 0, -1, 0,
    0.5, -0.5, -0.5, 0, -1, 0,
    0.5, -0.5, 0.5, 0, -1, 0
};

static const int ConeVertexNum = 288;
static const GLfloat ConeData[] = {
    0.353553, -0.5, 0.353553, 0.632455, 0.447214, 0.632456,
    0.5, -0.5, 0, 0.894427, 0.447214, 0,
    0, 0.5, 0, 0.81252, 0.475963, 0.336557,
    0, -0.5, 0, 0, -1, 0,
    0.5, -0.5, 0, 0, -1, 0,
    0.353553, -0.5, 0.353553, 0, -1, 0,
    -2.18557e-08, -0.5, 0.5, -3.90967e-08, 0.447214, 0.894427,
    0.353553, -0.5, 0.353553, 0.632455, 0.447214, 0.632456,
    0, 0.5, 0, 0.336557, 0.475963, 0.81252,
    0, -0.5, 0, 0, -1, 0,
    0.353553, -0.5, 0.353553, 0, -1, 0,
    -2.18557e-08, -0.5, 0.5, 0, -1, 0,
    -0.353553, -0.5, 0.353553, -0.632456, 0.447214, 0.632456,
    -2.18557e-08, -0.5, 0.5, -3.90967e-08, 0.447214, 0.894427,
    -0, 0.5, 0, -0.336557, 0.475963, 0.81252,
    -0, -0.5, 0, 0, -1, 0,
    -2.18557e-08, -0.5, 0.5, 0, -1, 0,
    -0.353553, -0.5, 0.353553, 0, -1, 0,
    -0.5, -0.5, -4.37114e-08, -0.894427, 0.447214, -7.81933e-08,
    -0.353553, -0.5, 0.353553, -0.632456, 0.447214, 0.632456,
    -0, 0.5, 0, -0.81252, 0.475963, 0.336557,
    -0, -0.5, 0, 0, -1, 0,
    -0.353553, -0.5, 0.353553, 0, -1, 0,
    -0.5, -0.5, -4.37114e-08, 0, -1, 0,
    -0.353553, -0.5, -0.353553, -0.632455, 0.447214, -0.632456,
    -0.5, -0.5, -4.37114e-08, -0.894427, 0.447214, -7.81933e-08,
    -0, 0.5, -0, -0.81252, 0.475963, -0.336557,
    -0, -0.5, -0, 0, -1, 0,
    -0.5, -0.5, -4.37114e-08, 0, -1, 0,
    -0.353553, -0.5, -0.353553, 0, -1, 0,
    5.96244e-09, -0.5, -0.5, 1.06659e-08, 0.447214, -0.894427,
    -0.353553, -0.5, -0.353553, -0.632455, 0.447214, -0.632456,
    -0, 0.5, -0, -0.336557, 0.475963, -0.81252,
    -0, -0.5, -0, 0, -1, 0,
    -0.353553, -0.5, -0.353553, 0, -1, 0,
    5.96244e-09, -0.5, -0.5, 0, -1, 0,
    0.353554, -0.5, -0.353553, 0.632456, 0.447214, -0.632455,
    5.96244e-09, -0.5, -0.5, 1.06659e-08, 0.447214, -0.894427,
    0, 0.5, -0, 0.336557, 0.475963, -0.81252,
    0, -0.5, -0, 0, -1, 0,
    5.96244e-09, -0.5, -0.5, 0, -1, 0,
    0.353554, -0.5, -0.353553, 0, -1, 0,
    0.5, -0.5, 8.74228e-08, 0.894427, 0.447214, 1.56387e-07,
    0.353554, -0.5, -0.353553, 0.632456, 0.447214, -0.632455,
    0, 0.5, -0, 0.81252, 0.475963, -0.336557,
    0, -0.5, -0, 0, -1, 0,
    0.353554, -0.5, -0.353553, 0, -1, 0,
    0.5, -0.5, 8.74228e-08, 0, -1, 0
};

static const int CylinderVertexNum = 720;
static const GLfloat CylinderData[] = {
    0, -0.5, 0, 0, -1, 0,
    0.5, -0.5, 0, 0, -1, 0,
    0.404509, -0.5, 0.293893, 0, -1, 0,
    0.404509, 0.5, 0.293893, 0, 1, 0,
    0.5, 0.5, 0, 0, 1, 0,
    0, 0.5, 0, 0, 1, 0,
    0.404509, -0.5, 0.293893, 0.809017, 0, 0.587785,
    0.5, -0.5, 0, 1, 0, 0,
    0.5, 0.5, 0, 1, 0, 0,
    0.404509, 0.5, 0.293893, 0.809017, 0, 0.587785,
    0.404509, -0.5, 0.293893, 0.809017, 0, 0.587785,
    0.5, 0.5, 0, 1, 0, 0,
    0, -0.5, 0, 0, -1, 0,
    0.404509, -0.5, 0.293893, 0, -1, 0,
    0.154508, -0.5, 0.475528, 0, -1, 0,
    0.154508, 0.5, 0.475528, 0, 1, 0,
    0.404509, 0.5, 0.293893, 0, 1, 0,
    0, 0.5, 0, 0, 1, 0,
    0.154508, -0.5, 0.475528, 0.309017, 0, 0.951057,
    0.404509, -0.5, 0.293893, 0.809017, 0, 0.587785,
    0.404509, 0.5, 0.293893, 0.809017, 0, 0.587785,
    0.154508, 0.5, 0.475528, 0.309017, 0, 0.951057,
    0.154508, -0.5, 0.475528, 0.309017, 0, 0.951057,
    0.404509, 0.5, 0.293893, 0.809017, 0, 0.587785,
    0, -0.5, 0, 0, -1, 0,
    0.154508, -0.5, 0.475528, 0, -1, 0,
    -0.154509, -0.5, 0.475528, 0, -1, 0,
    -0.154509, 0.5, 0.475528, 0, 1, 0,
    0.154508, 0.5, 0.475528, 0, 1, 0,
    0, 0.5, 0, 0, 1, 0,
    -0.154509, -0.5, 0.475528, -0.309017, 0, 0.951057,
    0.154508, -0.5, 0.475528, 0.309017, 0, 0.951057,
    0.154508, 0.5, 0.475528, 0.309017, 0, 0.951057,
    -0.154509, 0.5, 0.475528, -0.309017, 0, 0.951057,
    -0.154509, -0.5, 0.475528, -0.309017, 0, 0.951057,
    0.154508, 0.5, 0.475528, 0.309017, 0, 0.951057,
    -0, -0.5, 0, 0, -1, 0,
    -0.154509, -0.5, 0.475528, 0, -1, 0,
    -0.404509, -0.5, 0.293893, 0, -1, 0,
    -0.404509, 0.5, 0.293893, 0, 1, 0,
    -0.154509, 0.5, 0.475528, 0, 1, 0,
    -0, 0.5, 0, 0, 1, 0,
    -0.404509, -0.5, 0.293893, -0.809017, 0, 0.587785,
    -0.154509, -0.5, 0.475528, -0.309017, 0, 0.951057,
    -0.154509, 0.5, 0.475528, -0.309017, 0, 0.951057,
    -0.404509, 0.5, 0.293893, -0.809017, 0, 0.587785,
    -0.404509, -0.5, 0.293893, -0.809017, 0, 0.587785,
    -0.154509, 0.5, 0.475528, -0.309017, 0, 0.951057,
    -0, -0.5, 0, 0, -1, 0,
    -0.404509, -0.5, 0.293893, 0, -1, 0,
    -0.5, -0.5, -4.37114e-08, 0, -1, 0,
    -0.5, 0.5, -4.37114e-08, 0, 1, 0,
    -0.404509, 0.5, 0.293893, 0, 1, 0,
    -0, 0.5, 0, 0, 1, 0,
    -0.5, -0.5, -4.37114e-08, -1, 0, -8.74228e-08,
    -0.404509, -0.5, 0.293893, -0.809017, 0, 0.587785,
    -0.404509, 0.5, 0.293893, -0.809017, 0, 0.587785,
    -0.5, 0.5, -4.37114e-08, -1, 0, -8.74228e-08,
    -0.5, -0.5, -4.37114e-08, -1, 0, -8.74228e-08,
    -0.404509, 0.5, 0.293893, -0.809017, 0, 0.587785,
    -0, -0.5, -0, 0, -1, 0,
    -0.5, -0.5, -4.37114e-08, 0, -1, 0,
    -0.404508, -0.5, -0.293893, 0, -1, 0,
    -0.404508, 0.5, -0.293893, 0, 1, 0,
    -0.5, 0.5, -4.37114e-08, 0, 1, 0,
    -0, 0.5, -0, 0, 1, 0,
    -0.404508, -0.5, -0.293893, -0.809017, 0, -0.587785,
    -0.5, -0.5, -4.37114e-08, -1, 0, -8.74228e-08,
    -0.5, 0.5, -4.37114e-08, -1, 0, -8.74228e-08,
    -0.404508, 0.5, -0.293893, -0.809017, 0, -0.587785,
    -0.404508, -0.5, -0.293893, -0.809017, 0, -0.587785,
    -0.5, 0.5, -4.37114e-08, -1, 0, -8.74228e-08,
    -0, -0.5, -0, 0, -1, 0,
    -0.404508, -0.5, -0.293893, 0, -1, 0,
    -0.154509, -0.5, -0.475528, 0, -1, 0,
    -0.154509, 0.5, -0.475528, 0, 1, 0,
    -0.404508, 0.5, -0.293893, 0, 1, 0,
    -0, 0.5, -0, 0, 1, 0,
    -0.154509, -0.5, -0.475528, -0.309017, 0, -0.951056,
    -0.404508, -0.5, -0.293893, -0.809017, 0, -0.587785,
    -0.404508, 0.5, -0.293893, -0.809017, 0, -0.587785,
    -0.154509, 0.5, -0.475528, -0.309017, 0, -0.951056,
    -0.154509, -0.5, -0.475528, -0.309017, 0, -0.951056,
    -0.404508, 0.5, -0.293893, -0.809017, 0, -0.587785,
    -0, -0.5, -0, 0, -1, 0,
    -0.154509, -0.5, -0.475528, 0, -1, 0,
    0.154509, -0.5, -0.475528, 0, -1, 0,
    0.154509, 0.5, -0.475528, 0, 1, 0,
    -0.154509, 0.5, -0.475528, 0, 1, 0,
    -0, 0.5, -0, 0, 1, 0,
    0.154509, -0.5, -0.475528, 0.309017, 0, -0.951056,
    -0.154509, -0.5, -0.475528, -0.309017, 0, -0.951056,
    -0.154509, 0.5, -0.475528, -0.309017, 0, -0.951056,
    0.154509, 0.5, -0.475528, 0.309017, 0, -0.951056,
    0.154509, -0.5, -0.475528, 0.309017, 0, -0.951056,
    -0.154509, 0.5, -0.475528, -0.309017, 0, -0.951056,
    0, -0.5, -0, 0, -1, 0,
    0.154509, -0.5, -0.475528, 0, -1, 0,
    0.404509, -0.5, -0.293892, 0, -1, 0,
    0.404509, 0.5, -0.293892, 0, 1, 0,
    0.154509, 0.5, -0.475528, 0, 1, 0,
    0, 0.5, -0, 0, 1, 0,
    0.404509, -0.5, -0.293892, 0.809017, 0, -0.587785,
    0.154509, -0.5, -0.475528, 0.309017, 0, -0.951056,
    0.154509, 0.5, -0.475528, 0.309017, 0, -0.951056,
    0.404509, 0.5, -0.293892, 0.809017, 0, -0.587785,
    0.404509, -0.5, -0.293892, 0.809017, 0, -0.587785,
    0.154509, 0.5, -0.475528, 0.309017, 0, -0.951056,
    0, -0.5, -0, 0, -1, 0,
    0.404509, -0.5, -0.293892, 0, -1, 0,
    0.5, -0.5, 8.74228e-08, 0, -1, 0,
    0.5, 0.5, 8.74228e-08, 0, 1, 0,
    0.404509, 0.5, -0.293892, 0, 1, 0,
    0, 0.5, -0, 0, 1, 0,
    0.5, -0.5, 8.74228e-08, 1, 0, 1.74846e-07,
    0.404509, -0.5, -0.293892, 0.809017, 0, -0.587785,
    0.404509, 0.5, -0.293892, 0.809017, 0, -0.587785,
    0.5, 0.5, 8.74228e-08, 1, 0, 1.74846e-07,
    0.5, -0.5, 8.74228e-08, 1, 0, 1.74846e-07,
    0.404509, 0.5, -0.293892, 0.809017, 0, -0.587785
};

static const int SphereVertexNum = 1296;
static const GLfloat SphereData[] = {
    0.25, 0.433013, 0, 0.5, 0.866025, 0,
    0, 0.5, 0, 0, 1, 0,
    0, 0.5, 0, 0, 1, 0,
    0, 0.5, 0, 0, 1, 0,
    0.125, 0.433013, 0.216506, 0.25, 0.866025, 0.433013,
    0.25, 0.433013, 0, 0.5, 0.866025, 0,
    0.433013, 0.25, 0, 0.866025, 0.5, 0,
    0.25, 0.433013, 0, 0.5, 0.866025, 0,
    0.125, 0.433013, 0.216506, 0.25, 0.866025, 0.433013,
    0.125, 0.433013, 0.216506, 0.25, 0.866025, 0.433013,
    0.216506, 0.25, 0.375, 0.433013, 0.5, 0.75,
    0.433013, 0.25, 0, 0.866025, 0.5, 0,
    0.5, -2.18557e-08, 0, 1, -4.37114e-08, 0,
    0.433013, 0.25, 0, 0.866025, 0.5, 0,
    0.216506, 0.25, 0.375, 0.433013, 0.5, 0.75,
    0.216506, 0.25, 0.375, 0.433013, 0.5, 0.75,
    0.25, -2.18557e-08, 0.433013, 0.5, -4.37114e-08, 0.866025,
    0.5, -2.18557e-08, 0, 1, -4.37114e-08, 0,
    0.433013, -0.25, 0, 0.866025, -0.5, 0,
    0.5, -2.18557e-08, 0, 1, -4.37114e-08, 0,
    0.25, -2.18557e-08, 0.433013, 0.5, -4.37114e-08, 0.866025,
    0.25, -2.18557e-08, 0.433013, 0.5, -4.37114e-08, 0.866025,
    0.216506, -0.25, 0.375, 0.433013, -0.5, 0.75,
    0.433013, -0.25, 0, 0.866025, -0.5, 0,
    0.25, -0.433013, 0, 0.5, -0.866025, 0,
    0.433013, -0.25, 0, 0.866025, -0.5, 0,
    0.216506, -0.25, 0.375, 0.433013, -0.5, 0.75,
    0.216506, -0.25, 0.375, 0.433013, -0.5, 0.75,
    0.125, -0.433013, 0.216506, 0.25, -0.866025, 0.433013,
    0.25, -0.433013, 0, 0.5, -0.866025, 0,
    -4.37114e-08, -0.5, -0, -8.74228e-08, -1, -0,
    0.25, -0.433013, 0, 0.5, -0.866025, 0,
    0.125, -0.433013, 0.216506, 0.25, -0.866025, 0.433013,
    0.125, -0.433013, 0.216506, 0.25, -0.866025, 0.433013,
    -2.18557e-08, -0.5, -3.78552e-08, -4.37114e-08, -1, -7.57103e-08,
    -4.37114e-08, -0.5, -0, -8.74228e-08, -1, -0,
    0.125, 0.433013, 0.216506, 0.25, 0.866025, 0.433013,
    0, 0.5, 0, 0, 1, 0,
    -0, 0.5, 0, -0, 1, 0,
    -0, 0.5, 0, -0, 1, 0,
    -0.125, 0.433013, 0.216506, -0.25, 0.866025, 0.433013,
    0.125, 0.433013, 0.216506, 0.25, 0.866025, 0.433013,
    0.216506, 0.25, 0.375, 0.433013, 0.5, 0.75,
    0.125, 0.433013, 0.216506, 0.25, 0.866025, 0.433013,
    -0.125, 0.433013, 0.216506, -0.25, 0.866025, 0.433013,
    -0.125, 0.433013, 0.216506, -0.25, 0.866025, 0.433013,
    -0.216506, 0.25, 0.375, -0.433013, 0.5, 0.75,
    0.216506, 0.25, 0.375, 0.433013, 0.5, 0.75,
    0.25, -2.18557e-08, 0.433013, 0.5, -4.37114e-08, 0.866025,
    0.216506, 0.25, 0.375, 0.433013, 0.5, 0.75,
    -0.216506, 0.25, 0.375, -0.433013, 0.5, 0.75,
    -0.216506, 0.25, 0.375, -0.433013, 0.5, 0.75,
    -0.25, -2.18557e-08, 0.433013, -0.5, -4.37114e-08, 0.866025,
    0.25, -2.18557e-08, 0.433013, 0.5, -4.37114e-08, 0.866025,
    0.216506, -0.25, 0.375, 0.433013, -0.5, 0.75,
    0.25, -2.18557e-08, 0.433013, 0.5, -4.37114e-08, 0.866025,
    -0.25, -2.18557e-08, 0.433013, -0.5, -4.37114e-08, 0.866025,
    -0.25, -2.18557e-08, 0.433013, -0.5, -4.37114e-08, 0.866025,
    -0.216506, -0.25, 0.375, -0.433013, -0.5, 0.75,
    0.216506, -0.25, 0.375, 0.433013, -0.5, 0.75,
    0.125, -0.433013, 0.216506, 0.25, -0.866025, 0.433013,
    0.216506, -0.25, 0.375, 0.433013, -0.5, 0.75,
    -0.216506, -0.25, 0.375, -0.433013, -0.5, 0.75,
    -0.216506, -0.25, 0.375, -0.433013, -0.5, 0.75,
    -0.125, -0.433013, 0.216506, -0.25, -0.866025, 0.433013,
    0.125, -0.433013, 0.216506, 0.25, -0.866025, 0.433013,
    -2.18557e-08, -0.5, -3.78552e-08, -4.37114e-08, -1, -7.57103e-08,
    0.125, -0.433013, 0.216506, 0.25, -0.866025, 0.433013,
    -0.125, -0.433013, 0.216506, -0.25, -0.866025, 0.433013,
    -0.125, -0.433013, 0.216506, -0.25, -0.866025, 0.433013,
    2.18557e-08, -0.5, -3.78552e-08, 4.37114e-08, -1, -7.57103e-08,
    -2.18557e-08, -0.5, -3.78552e-08, -4.37114e-08, -1, -7.57103e-08,
    -0.125, 0.433013, 0.216506, -0.25, 0.866025, 0.433013,
    -0, 0.5, 0, -0, 1, 0,
    -0, 0.5, -0, -0, 1, -0,
    -0, 0.5, -0, -0, 1, -0,
    -0.25, 0.433013, -2.18557e-08, -0.5, 0.866025, -4.37114e-08,
    -0.125, 0.433013, 0.216506, -0.25, 0.866025, 0.433013,
    -0.216506, 0.25, 0.375, -0.433013, 0.5, 0.75,
    -0.125, 0.433013, 0.216506, -0.25, 0.866025, 0.433013,
    -0.25, 0.433013, -2.18557e-08, -0.5, 0.866025, -4.37114e-08,
    -0.25, 0.433013, -2.18557e-08, -0.5, 0.866025, -4.37114e-08,
    -0.433013, 0.25, -3.78552e-08, -0.866025, 0.5, -7.57103e-08,
    -0.216506, 0.25, 0.375, -0.433013, 0.5, 0.75,
    -0.25, -2.18557e-08, 0.433013, -0.5, -4.37114e-08, 0.866025,
    -0.216506, 0.25, 0.375, -0.433013, 0.5, 0.75,
    -0.433013, 0.25, -3.78552e-08, -0.866025, 0.5, -7.57103e-08,
    -0.433013, 0.25, -3.78552e-08, -0.866025, 0.5, -7.57103e-08,
    -0.5, -2.18557e-08, -4.37114e-08, -1, -4.37114e-08, -8.74228e-08,
    -0.25, -2.18557e-08, 0.433013, -0.5, -4.37114e-08, 0.866025,
    -0.216506, -0.25, 0.375, -0.433013, -0.5, 0.75,
    -0.25, -2.18557e-08, 0.433013, -0.5, -4.37114e-08, 0.866025,
    -0.5, -2.18557e-08, -4.37114e-08, -1, -4.37114e-08, -8.74228e-08,
    -0.5, -2.18557e-08, -4.37114e-08, -1, -4.37114e-08, -8.74228e-08,
    -0.433013, -0.25, -3.78552e-08, -0.866025, -0.5, -7.57103e-08,
    -0.216506, -0.25, 0.375, -0.433013, -0.5, 0.75,
    -0.125, -0.433013, 0.216506, -0.25, -0.866025, 0.433013,
    -0.216506, -0.25, 0.375, -0.433013, -0.5, 0.75,
    -0.433013, -0.25, -3.78552e-08, -0.866025, -0.5, -7.57103e-08,
    -0.433013, -0.25, -3.78552e-08, -0.866025, -0.5, -7.57103e-08,
    -0.25, -0.433013, -2.18557e-08, -0.5, -0.866025, -4.37114e-08,
    -0.125, -0.433013, 0.216506, -0.25, -0.866025, 0.433013,
    2.18557e-08, -0.5, -3.78552e-08, 4.37114e-08, -1, -7.57103e-08,
    -0.125, -0.433013, 0.216506, -0.25, -0.866025, 0.433013,
    -0.25, -0.433013, -2.18557e-08, -0.5, -0.866025, -4.37114e-08,
    -0.25, -0.433013, -2.18557e-08, -0.5, -0.866025, -4.37114e-08,
    4.37114e-08, -0.5, 3.82137e-15, 8.74228e-08, -1, 7.64274e-15,
    2.18557e-08, -0.5, -3.78552e-08, 4.37114e-08, -1, -7.57103e-08,
    -0.25, 0.433013, -2.18557e-08, -0.5, 0.866025, -4.37114e-08,
    -0, 0.5, -0, -0, 1, -0,
    -0, 0.5, -0, -0, 1, -0,
    -0, 0.5, -0, -0, 1, -0,
    -0.125, 0.433013, -0.216506, -0.25, 0.866025, -0.433013,
    -0.25, 0.433013, -2.18557e-08, -0.5, 0.866025, -4.37114e-08,
    -0.433013, 0.25, -3.78552e-08, -0.866025, 0.5, -7.57103e-08,
    -0.25, 0.433013, -2.18557e-08, -0.5, 0.866025, -4.37114e-08,
    -0.125, 0.433013, -0.216506, -0.25, 0.866025, -0.433013,
    -0.125, 0.433013, -0.216506, -0.25, 0.866025, -0.433013,
    -0.216506, 0.25, -0.375, -0.433013, 0.5, -0.75,
    -0.433013, 0.25, -3.78552e-08, -0.866025, 0.5, -7.57103e-08,
    -0.5, -2.18557e-08, -4.37114e-08, -1, -4.37114e-08, -8.74228e-08,
    -0.433013, 0.25, -3.78552e-08, -0.866025, 0.5, -7.57103e-08,
    -0.216506, 0.25, -0.375, -0.433013, 0.5, -0.75,
    -0.216506, 0.25, -0.375, -0.433013, 0.5, -0.75,
    -0.25, -2.18557e-08, -0.433013, -0.5, -4.37114e-08, -0.866025,
    -0.5, -2.18557e-08, -4.37114e-08, -1, -4.37114e-08, -8.74228e-08,
    -0.433013, -0.25, -3.78552e-08, -0.866025, -0.5, -7.57103e-08,
    -0.5, -2.18557e-08, -4.37114e-08, -1, -4.37114e-08, -8.74228e-08,
    -0.25, -2.18557e-08, -0.433013, -0.5, -4.37114e-08, -0.866025,
    -0.25, -2.18557e-08, -0.433013, -0.5, -4.37114e-08, -0.866025,
    -0.216506, -0.25, -0.375, -0.433013, -0.5, -0.75,
    -0.433013, -0.25, -3.78552e-08, -0.866025, -0.5, -7.57103e-08,
    -0.25, -0.433013, -2.18557e-08, -0.5, -0.866025, -4.37114e-08,
    -0.433013, -0.25, -3.78552e-08, -0.866025, -0.5, -7.57103e-08,
    -0.216506, -0.25, -0.375, -0.433013, -0.5, -0.75,
    -0.216506, -0.25, -0.375, -0.433013, -0.5, -0.75,
    -0.125, -0.433013, -0.216506, -0.25, -0.866025, -0.433013,
    -0.25, -0.433013, -2.18557e-08, -0.5, -0.866025, -4.37114e-08,
    4.37114e-08, -0.5, 3.82137e-15, 8.74228e-08, -1, 7.64274e-15,
    -0.25, -0.433013, -2.18557e-08, -0.5, -0.866025, -4.37114e-08,
    -0.125, -0.433013, -0.216506, -0.25, -0.866025, -0.433013,
    -0.125, -0.433013, -0.216506, -0.25, -0.866025, -0.433013,
    2.18557e-08, -0.5, 3.78552e-08, 4.37114e-08, -1, 7.57103e-08,
    4.37114e-08, -0.5, 3.82137e-15, 8.74228e-08, -1, 7.64274e-15,
    -0.125, 0.433013, -0.216506, -0.25, 0.866025, -0.433013,
    -0, 0.5, -0, -0, 1, -0,
    0, 0.5, -0, 0, 1, -0,
    0, 0.5, -0, 0, 1, -0,
    0.125, 0.433013, -0.216506, 0.25, 0.866025, -0.433013,
    -0.125, 0.433013, -0.216506, -0.25, 0.866025, -0.433013,
    -0.216506, 0.25, -0.375, -0.433013, 0.5, -0.75,
    -0.125, 0.433013, -0.216506, -0.25, 0.866025, -0.433013,
    0.125, 0.433013, -0.216506, 0.25, 0.866025, -0.433013,
    0.125, 0.433013, -0.216506, 0.25, 0.866025, -0.433013,
    0.216506, 0.25, -0.375, 0.433013, 0.5, -0.75,
    -0.216506, 0.25, -0.375, -0.433013, 0.5, -0.75,
    -0.25, -2.18557e-08, -0.433013, -0.5, -4.37114e-08, -0.866025,
    -0.216506, 0.25, -0.375, -0.433013, 0.5, -0.75,
    0.216506, 0.25, -0.375, 0.433013, 0.5, -0.75,
    0.216506, 0.25, -0.375, 0.433013, 0.5, -0.75,
    0.25, -2.18557e-08, -0.433013, 0.5, -4.37114e-08, -0.866025,
    -0.25, -2.18557e-08, -0.433013, -0.5, -4.37114e-08, -0.866025,
    -0.216506, -0.25, -0.375, -0.433013, -0.5, -0.75,
    -0.25, -2.18557e-08, -0.433013, -0.5, -4.37114e-08, -0.866025,
    0.25, -2.18557e-08, -0.433013, 0.5, -4.37114e-08, -0.866025,
    0.25, -2.18557e-08, -0.433013, 0.5, -4.37114e-08, -0.866025,
    0.216506, -0.25, -0.375, 0.433013, -0.5, -0.75,
    -0.216506, -0.25, -0.375, -0.433013, -0.5, -0.75,
    -0.125, -0.433013, -0.216506, -0.25, -0.866025, -0.433013,
    -0.216506, -0.25, -0.375, -0.433013, -0.5, -0.75,
    0.216506, -0.25, -0.375, 0.433013, -0.5, -0.75,
    0.216506, -0.25, -0.375, 0.433013, -0.5, -0.75,
    0.125, -0.433013, -0.216506, 0.25, -0.866025, -0.433013,
    -0.125, -0.433013, -0.216506, -0.25, -0.866025, -0.433013,
    2.18557e-08, -0.5, 3.78552e-08, 4.37114e-08, -1, 7.57103e-08,
    -0.125, -0.433013, -0.216506, -0.25, -0.866025, -0.433013,
    0.125, -0.433013, -0.216506, 0.25, -0.866025, -0.433013,
    0.125, -0.433013, -0.216506, 0.25, -0.866025, -0.433013,
    -2.18557e-08, -0.5, 3.78552e-08, -4.37114e-08, -1, 7.57103e-08,
    2.18557e-08, -0.5, 3.78552e-08, 4.37114e-08, -1, 7.57103e-08,
    0.125, 0.433013, -0.216506, 0.25, 0.866025, -0.433013,
    0, 0.5, -0, 0, 1, -0,
    0, 0.5, 0, 0, 1, 0,
    0, 0.5, 0, 0, 1, 0,
    0.25, 0.433013, 4.37114e-08, 0.5, 0.866025, 8.74228e-08,
    0.125, 0.433013, -0.216506, 0.25, 0.866025, -0.433013,
    0.216506, 0.25, -0.375, 0.433013, 0.5, -0.75,
    0.125, 0.433013, -0.216506, 0.25, 0.866025, -0.433013,
    0.25, 0.433013, 4.37114e-08, 0.5, 0.866025, 8.74228e-08,
    0.25, 0.433013, 4.37114e-08, 0.5, 0.866025, 8.74228e-08,
    0.433013, 0.25, 7.57103e-08, 0.866025, 0.5, 1.51421e-07,
    0.216506, 0.25, -0.375, 0.433013, 0.5, -0.75,
    0.25, -2.18557e-08, -0.433013, 0.5, -4.37114e-08, -0.866025,
    0.216506, 0.25, -0.375, 0.433013, 0.5, -0.75,
    0.433013, 0.25, 7.57103e-08, 0.866025, 0.5, 1.51421e-07,
    0.433013, 0.25, 7.57103e-08, 0.866025, 0.5, 1.51421e-07,
    0.5, -2.18557e-08, 8.74228e-08, 1, -4.37114e-08, 1.74846e-07,
    0.25, -2.18557e-08, -0.433013, 0.5, -4.37114e-08, -0.866025,
    0.216506, -0.25, -0.375, 0.433013, -0.5, -0.75,
    0.25, -2.18557e-08, -0.433013, 0.5, -4.37114e-08, -0.866025,
    0.5, -2.18557e-08, 8.74228e-08, 1, -4.37114e-08, 1.74846e-07,
    0.5, -2.18557e-08, 8.74228e-08, 1, -4.37114e-08, 1.74846e-07,
    0.433013, -0.25, 7.57103e-08, 0.866025, -0.5, 1.51421e-07,
    0.216506, -0.25, -0.375, 0.433013, -0.5, -0.75,
    0.125, -0.433013, -0.216506, 0.25, -0.866025, -0.433013,
    0.216506, -0.25, -0.375, 0.433013, -0.5, -0.75,
    0.433013, -0.25, 7.57103e-08, 0.866025, -0.5, 1.51421e-07,
    0.433013, -0.25, 7.57103e-08, 0.866025, -0.5, 1.51421e-07,
    0.25, -0.433013, 4.37114e-08, 0.5, -0.866025, 8.74228e-08,
    0.125, -0.433013, -0.216506, 0.25, -0.866025, -0.433013,
    -2.18557e-08, -0.5, 3.78552e-08, -4.37114e-08, -1, 7.57103e-08,
    0.125, -0.433013, -0.216506, 0.25, -0.866025, -0.433013,
    0.25, -0.433013, 4.37114e-08, 0.5, -0.866025, 8.74228e-08,
    0.25, -0.433013, 4.37114e-08, 0.5, -0.866025, 8.74228e-08,
    -4.37114e-08, -0.5, -7.64274e-15, -8.74228e-08, -1, -1.52855e-14,
    -2.18557e-08, -0.5, 3.78552e-08, -4.37114e-08, -1, 7.57103e-08
};


static QMatrix4x4 glmMatToQMat(glm::mat4x4 m) {
    // Note: glm::mat4x4 is column-major order
    //       QMatrix4x4 is row-major order
    QMatrix4x4 qMat(m[0][0], m[1][0], m[2][0], m[3][0],
                    m[0][1], m[1][1], m[2][1], m[3][1],
                    m[0][2], m[1][2], m[2][2], m[3][2],
                    m[0][3], m[1][3], m[2][3], m[3][3]);
    return qMat;
}

/**
 * ==================================================
 *                  Phong Shaders
 * ==================================================
 */
static const char *vertexShaderSourceCore =
    "#version 330 core\n"
    "layout(location = 0) in vec3 position; // Position of the vertex\n"
    "layout(location = 1) in vec3 normal;   // Normal of the vertex\n"
    "out vec4 fragPos;\n"
    "out vec4 fragNormal;\n"
    "uniform mat4 p;\n"
    "uniform mat4 v;\n"
    "uniform mat4 m;\n"
    "void main() {\n"
    "    fragPos = m * vec4(position, 1.f);\n"
    "    fragNormal = vec4(normalize(mat3(transpose(inverse(m))) * normal), 0);\n"
    "    gl_Position = p * v * fragPos;\n"
    "}\n";

static const char *fragmentShaderSourceCore =
    "#version 330 core\n"
    "// fragment shader input in world space\n"
    "in vec4 fragPos;\n"
    "in vec4 fragNormal;\n"
    "// fragment shader output\n"
    "out vec4 fragColor;\n"
    "uniform vec3 lightPos;\n"
    "void main() {\n"
    "   vec3 L = normalize(lightPos - vec3(fragPos));\n"
    "   float NL = max(dot(normalize(vec3(fragNormal)), L), 0.0);\n"
    "   vec3 color = vec3(1.0, 0.78, 0.0);\n"
    "   vec3 col = clamp(color * 0.2 + color * 0.8 * NL, 0.0, 1.0);\n"
    "   fragColor = vec4(col, 1.0);\n"
    "}\n";

GLWidget::~GLWidget() {
    if (m_program) {
        delete m_program;
        m_program = nullptr;
    }

    m_vaoCone.destroy();
    m_vboCone.destroy();
    m_vaoCylinder.destroy();
    m_vboCylinder.destroy();
    m_vaoCube.destroy();
    m_vboCube.destroy();
    m_vaoSphere.destroy();
    m_vboSphere.destroy();
}

void GLWidget::initializeGL() {
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();

    f->glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    f->glEnable(GL_DEPTH_TEST);
    f->glEnable(GL_CULL_FACE);
    f->glCullFace(GL_BACK);
    f->glFrontFace(GL_CCW);

    m_program = new QOpenGLShaderProgram;
    m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSourceCore);
    m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSourceCore);
    m_program->link();
    m_program->bind();

    // Camera
    m_view = glm::lookAt(glm::vec3(8.f, 8.f, 8.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));
    m_fovy = glm::radians(60.f);
    m_proj = glm::perspective(m_fovy, (float)width() / height(), 0.01f, 100.0f);

    // Cone
    m_vaoCone.create();
    m_vaoCone.bind();
    m_vboCone.create();
    m_vboCone.bind();
    m_vboCone.allocate(ConeData, ConeVertexNum * sizeof(GLfloat));
    f->glEnableVertexAttribArray(0);
    f->glEnableVertexAttribArray(1);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), nullptr);
    f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void *>(3 * sizeof(GLfloat)));
    m_vboCone.release();
    m_vaoCone.release();

    // Cube
    m_vaoCube.create();
    m_vaoCube.bind();
    m_vboCube.create();
    m_vboCube.bind();
    m_vboCube.allocate(CubeData, CubeVertexNum * sizeof(GLfloat));
    f->glEnableVertexAttribArray(0);
    f->glEnableVertexAttribArray(1);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), nullptr);
    f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void *>(3 * sizeof(GLfloat)));
    m_vboCube.release();
    m_vaoCube.release();

    // Cylinder
    m_vaoCylinder.create();
    m_vaoCylinder.bind();
    m_vboCylinder.create();
    m_vboCylinder.bind();
    m_vboCylinder.allocate(CylinderData, CylinderVertexNum * sizeof(GLfloat));
    f->glEnableVertexAttribArray(0);
    f->glEnableVertexAttribArray(1);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), nullptr);
    f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void *>(3 * sizeof(GLfloat)));
    m_vboCylinder.release();
    m_vaoCylinder.release();

    // Sphere
    m_vaoSphere.create();
    m_vaoSphere.bind();
    m_vboSphere.create();
    m_vboSphere.bind();
    m_vboSphere.allocate(SphereData, SphereVertexNum * sizeof(GLfloat));
    f->glEnableVertexAttribArray(0);
    f->glEnableVertexAttribArray(1);
    f->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), nullptr);
    f->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), reinterpret_cast<void *>(3 * sizeof(GLfloat)));
    m_vboSphere.release();
    m_vaoSphere.release();
}

void GLWidget::paintGL() {
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();

    f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    m_program->bind();

    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); bad bad line

    m_program->setUniformValue(m_program->uniformLocation("lightPos"), m_lightPos);
    m_program->setUniformValue(m_program->uniformLocation("p"), glmMatToQMat(m_proj));
    m_program->setUniformValue(m_program->uniformLocation("v"), glmMatToQMat(m_view));

    for (auto & shape : m_renderData.shapes) {
        auto &material = shape.primitive.material;
        m_program->setUniformValue(m_program->uniformLocation("m"), glmMatToQMat(shape.ctm));

        switch (shape.primitive.type) {
        case PrimitiveType::PRIMITIVE_CONE:
        {
            m_vaoCone.bind();
            f->glDrawArrays(GL_TRIANGLES, 0, ConeVertexNum);
            m_vaoCone.release();
            break;
        }
        case PrimitiveType::PRIMITIVE_CYLINDER:
        {
            m_vaoCylinder.bind();
            f->glDrawArrays(GL_TRIANGLES, 0, CylinderVertexNum);
            m_vaoCylinder.release();
            break;
        }
        case PrimitiveType::PRIMITIVE_CUBE:
        {
            m_vaoCube.bind();
            f->glDrawArrays(GL_TRIANGLES, 0, CubeVertexNum);
            m_vaoCube.release();
            break;
        }
        case PrimitiveType::PRIMITIVE_SPHERE:
        {
            m_vaoSphere.bind();
            f->glDrawArrays(GL_TRIANGLES, 0, SphereVertexNum);
            m_vaoSphere.release();
            break;
        }
        default:
            break;
        }
    }

    m_program->release();
}

void GLWidget::resizeGL(int w, int h) {
    m_proj = glm::perspective(m_fovy, (float)w / h, 0.01f, 100.0f);
}

void GLWidget::loadScene(const RenderData &renderData) {
    std::cout << "GLWidget [loadScene] begin" << std::endl;

    const auto &cameraData = renderData.cameraData;
    glm::vec3 eye = glm::vec3(cameraData.pos);
    glm::vec3 center = glm::vec3(cameraData.pos + cameraData.look);
    glm::vec3 up = glm::vec3(cameraData.up);

    m_lightPos = QVector3D(eye.x, eye.y, eye.z);

    m_fovy = cameraData.heightAngle;
    m_view = glm::lookAt(eye, center, up);
    m_proj = glm::perspective(m_fovy, (float)width() / height(), 0.01f, 100.0f);

    m_renderData = renderData;

    update();

    std::cout << "GLWidget [loadScene] success" << std::endl;
}

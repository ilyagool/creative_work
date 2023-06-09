#pragma once
#include "glut.h"
#include <stdio.h>
#include <iostream>
#include <vector>
#include <sstream>
using namespace std;

int n;
int** help;
int* result;
int*** mat;

int WinW;
int WinH;



const int maxSize = 20;
int amountVerts;

template<class T>

class Graph
{
	vector<T> vertList;
	vector<T> labelList;
	bool* visitedVerts = new bool[vertList.size()];
public:
	int adjMatrix[maxSize][maxSize] = { 0 };
	Graph();
	~Graph();
	void DrawGraph();
	void InsertEdge(const T& vertex1, const T& vertex2, int weight);
	void InsertVertex(const T& vertex);
	void DeleteVertex();
	int GetVertPos(const T& vertex);
	bool IsEmpty();
	bool IsFull();
	int GetAmountVerts();
	int GetAmountEdges();
	int GetWeight(const T& vertex1, const T& vertex2);
	vector<T> GetNbrs(const T& vertex);
	void Print();
};


int R;

struct vertCoord
{
	int x, y;
};
vertCoord vertC[20];

Graph<int> graph;

void answer(int*** mat, int n, int** help, int* path)
{

	for (int l = 0; l < n; l++)
	{
		for (int i = 0; i < n; i++)
		{
			int min = 1000000;
			for (int j = 0; j < n; j++)
				if (mat[i][j] && min > *mat[i][j])
					min = *mat[i][j];
			for (int j = 0; j < n; j++)
				if (mat[i][j])
					*mat[i][j] -= min;
		}
		for (int j = 0; j < n; j++)
		{
			int min = 1000000;
			for (int i = 0; i < n; i++)
				if (mat[i][j] && min > *mat[i][j])
					min = *mat[i][j];
			for (int i = 0; i < n; i++)
				if (mat[i][j])
					*mat[i][j] -= min;
		}

		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				help[i][j] = 0;

		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
			{
				if (mat[i][j] && !*mat[i][j])
				{
					int hmin = 1000000;
					int vmin = 1000000;

					for (int l = 0; l < n; l++)
						if (l != i && mat[l][j] && hmin > *mat[l][j])
							hmin = *mat[l][j];

					for (int l = 0; l < n; l++)
						if (l != j && mat[i][l] && vmin > *mat[i][l])
							vmin = *mat[i][l];

					help[i][j] = hmin + vmin;
				}
			}

		int mcost = 0, mi = 0, mj = 0;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				if (mat[i][j] && mcost < help[i][j])
				{
					mcost = help[i][j];
					mi = i;
					mj = j;
				}
		path[mi] = mj;

		for (int i = 0; i < n; i++)
			mat[i][mj] = nullptr;

		for (int i = 0; i < n; i++)
			mat[mi][i] = nullptr;

		mat[mj][mi] = nullptr;
	}
}

void preparation(int***& mat, int& n, int**& help, int*& result)
{
	n = amountVerts;

	help = new int* [n];

	result = new int[n];

	mat = new int** [n];

	for (int i = 0; i <= n; i++)
	{
		help[i] = new int[n];
	}

	for (int i = 0; i < n; i++)
	{
		mat[i] = new int* [n];
		for (int j = 0; j < n; j++)
		{
			if (graph.adjMatrix[i][j] == 0) {
				mat[i][j] = nullptr;
				continue;
			}
			mat[i][j] = new int(graph.adjMatrix[i][j]);
		}
	}
}


void tsalesman(int*** mat, int n, int** help, int* result)
{
	preparation(mat, n, help, result);
	int s = 0;
	answer(mat, n, help, result);
	cout << "\n������� �����: ";
	for (int i = 0, j = 0; i < n; i++)
	{
		j = result[i];
		cout << i + 1 << " -> " << j + 1 << '\t';
		s += graph.adjMatrix[i][j];
	}
	cout << endl;
	cout << "\n���������� ����: ";
	int temp = 0;
	for (int l = 0; l < n;)
	{
		for (int i = 0, j = 0; i < n; i++)
		{
			if (temp == 0 || i + 1 == temp)
			{
				if (temp == 0) cout << i + 1;
				j = result[i];
				temp = j + 1;
				if (temp > 0)	cout << " -> " << temp;
				l++;
			}
		}
	}
	cout << "\n����������� ����������: " << s;
	cout << endl;
}


template<class T>
std::vector<T> Graph<T>::GetNbrs(const T& vertex) {
	std::vector<T> nbrsList; // �������� ������ �������� ������
	int vertPos = this->GetVertPos(vertex); // ���������� ������� vertex � ������� ���������
	if (vertPos != (-1)) {

		for (int i = 0, vertListSize = this->vertList.size(); i < vertListSize; ++i) {
			if (this->adjMatrix[vertPos][i] != 0 &&
				this->adjMatrix[i][vertPos] != 0) // ���������� �������� ������

				nbrsList.push_back(this->vertList[i]);

		}
	}
	return nbrsList;
}



template<class T>
void Graph<T>::InsertVertex(const T& vertex) {
	if (!this->IsFull()) {
		this->vertList.push_back(vertex);
	}
	else {
		cout << "���� ���������" << endl;
		return;
	}
}

template<class T>
void Graph<T>::DeleteVertex() {

	this->vertList.pop_back();

}


template<class T>
int Graph<T>::GetAmountEdges() {
	int amount = 0; // �������� ������� ����
	if (!this->IsEmpty()) { // ���� ���� �� ������
		for (int i = 0, vertListSize = this->vertList.size();
			i < vertListSize; ++i) {
			for (int j = 0; j < vertListSize; ++j) {
				if (this->adjMatrix[i][j] ==
					this->adjMatrix[j][i] &&
					this->adjMatrix[i][j] != 0) // ������� ����
					amount += 1; // ����������� ���������� ����
			}
		}
		return (amount / 2); // ���������� �������
	}
	else
		return 0; // ���� �� ���� ������ �� ���������� 0 ����
}

template<class T>
int Graph<T>::GetWeight(const T& vertex1, const T& vertex2) {
	if (!this->IsEmpty()) {
		int vertPos1 = GetVertPos(vertex1);
		int vertPos2 = GetVertPos(vertex2);
		return adjMatrix[vertPos1][vertPos2];
	}
	return 0;
}

template<class T>
int Graph<T>::GetAmountVerts() {
	return this->vertList.size();
}

template<class T>
bool Graph<T>::IsEmpty() {
	if (this->vertList.size() != 0)
		return false;
	else
		return true;
}

template<class T>
bool Graph<T>::IsFull() {
	return (vertList.size() == maxSize);
}

template <class T>
int Graph<T>::GetVertPos(const T& vertex) {
	for (int i = 0; i < this->vertList.size(); ++i) {
		if (this->vertList[i] == vertex)
			return i;
	}
	return -1;
}

template<class T>
Graph<T>::Graph() {
	for (int i = 0; i < maxSize; ++i)
	{
		for (int j = 0; j < maxSize; ++j)
		{
			this->adjMatrix[i][j] = 0;
		}
	}
}

template<class T>
Graph<T>::~Graph() {

}


Graph<int> makeGraph()
{
	Graph<int> graph; // �������� �����
	int amountEdges, sourceVertex, targetVertex, edgeWeight; // �������� ����������� ��� ����� ����� ����������
	cout << "���������� ������ >> "; cin >> amountVerts; cout << endl; // ���� ���������� ������ ����� � ���������� amountVerts
	cout << "���������� ���� >> : "; cin >> amountEdges; cout << endl; // ���� ���������� ���� ����� � ���������� amountEdges
	for (int i = 1; i <= amountVerts; ++i) {
		int* vertPtr = &i; // ���������� ����� �������
		graph.InsertVertex(*vertPtr); //������� ������ �� ������� � ������� InsertVertex; ���������� ������� ������� � ������ ������
	}

	for (int i = 0; i < amountEdges; ++i) {
		cout << "��������� ������� >> "; cin >> sourceVertex; cout << endl; // ���� �������� �������
		int* sourceVertPtr = &sourceVertex; // ���������� ����� �������� �������
		cout << "�������� ������� >> "; cin >> targetVertex; cout << endl; // ���� �������, �� ������� ����� ���� ����� �� �������� �������
		int* targetVertPtr = &targetVertex; // ���������� ����� �������� ������� (�� ������� ����� ���� ����� �� �������� �������)

		cout << "��� >> "; cin >> edgeWeight; cout << endl; // ���� ��������� �������� ���� ����� � ���������� edgeWeight
		graph.InsertEdge(*sourceVertPtr, *targetVertPtr, edgeWeight); // ������� ����� ����� edgeWeight ����� �������� � �������� ���������
	}
	cout << endl;
	return graph;
}

template<class T>
void Graph<T>::InsertEdge(const T& vertex1, const T& vertex2, int weight) {
	if (this->GetVertPos(vertex1) != (-1) && this->GetVertPos(vertex2) != (-1)) {
		int vertPos1 = GetVertPos(vertex1);
		int vertPos2 = GetVertPos(vertex2);
		if (this->adjMatrix[vertPos1][vertPos2] != 0
			&& this->adjMatrix[vertPos2][vertPos1] != 0) {
			cout << "������ ����� ��� ����" << endl;
			return;
		}
		else {
			this->adjMatrix[vertPos1][vertPos2] = weight;
			this->adjMatrix[vertPos2][vertPos1] = weight;
		}
	}
	else {
		cout << "���� ������ ��� � �����" << endl;
		return;
	}
}

template<class T>
void Graph<T>::Print() {
	if (!this->IsEmpty()) {
		cout << "������� ���������: " << endl;
		for (int i = 0, vertListSize = this->vertList.size(); i < vertListSize; ++i) {
			cout << this->vertList[i] << " ";
			for (int j = 0; j < vertListSize; ++j) {
				cout << " " << this->adjMatrix[i][j] << " ";
			}
			cout << endl;
		}

	}

}

void setCoord(int i, int n)
{
	int R_;

	int x0 = WinW / 2;
	int y0 = WinH / 2;
	if (WinW > WinH)
	{
		R = 5 * (WinH / 13) / n;
		R_ = WinH / 2 - R - 10;
	}
	else {
		R = 5 * (WinW / 13) / n;
		R_ = WinW / 2 - R - 10;
	}
	float theta = 2.0f * 3.1415926f * float(i) / float(n);
	float y1 = R_ * cos(theta) + y0;
	float x1 = R_ * sin(theta) + x0;

	vertC[i].x = x1;
	vertC[i].y = y1;
}

void drawCircle(int x, int y, int R) //������ ���� � �������� �����������
{
	glColor3f(1.0, 0.0, 1.0);
	float x1, y1;
	glBegin(GL_POLYGON);
	for (int i = 0; i < 360; i++)
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(360);
		y1 = R * cos(theta) + y;
		x1 = R * sin(theta) + x;;
		glVertex2f(x1, y1);
	}
	glEnd();

	glColor3f(0.0f, 0.0f, 0.0f);
	float x2, y2;
	glBegin(GL_LINE_LOOP);
	for (int i = 0; i < 360; i++)
	{
		float theta = 2.0f * 3.1415926f * float(i) / float(360);
		y2 = R * cos(theta) + y;
		x2 = R * sin(theta) + x;
		glVertex2f(x2, y2);
	}
	glEnd();
}

void drawText(int nom, int x1, int y1)
{
	GLvoid* font = GLUT_BITMAP_HELVETICA_18;
	string s = to_string(nom);
	glRasterPos2i(x1 - 5, y1 - 5);
	for (int j = 0; j < s.length(); j++)
		glutBitmapCharacter(font, s[j]);
}

void drawVertex(int n)
{
	for (int i = 0; i < n; i++) {
		drawCircle(vertC[i].x, vertC[i].y, R);
		drawText(i + 1, vertC[i].x, vertC[i].y);
	}
}

void drawLine(int text, int x0, int y0, int x1, int y1) //����� ����������������� ���������� ����
{
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex2i(x0, y0);
	glVertex2i(x1, y1);
	glEnd();

	drawText(text, (x0 + x1) / 2 + 10, (y0 + y1) / 2 + 10);
}


template<class T>
void Graph<T>::DrawGraph()
{
	int n = vertList.size();
	for (int i = 0; i < n; i++)
	{
		setCoord(i, n);
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			int a = adjMatrix[i][j];
			if (a != 0)
			{
				drawLine(a, vertC[i].x, vertC[i].y, vertC[j].x, vertC[j].y);
			}
		}
	}
	drawVertex(n);
}

void reshape(int w, int h)
{
	WinW = w;
	WinH = h;
	glViewport(0, 0, (GLsizei)WinW, (GLsizei)WinH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, (GLdouble)WinW, 0, (GLdouble)WinH);
	glutPostRedisplay();
}

void drawMenuText(string text, int x1, int y1)
{
	GLvoid* font = GLUT_BITMAP_HELVETICA_18;
	string s = text;
	glRasterPos2i(x1 + 5, y1 - 20);
	for (int j = 0; j < s.length(); j++)
		glutBitmapCharacter(font, s[j]);
}

void drawMenu()
{
	int shift = 60;
	int height = 730;


	glColor3d(1.0, 0.5, 0.0);
	glBegin(GL_QUADS);
	glVertex2i(shift - 10, height - 400);
	glVertex2i(shift + 145, height - 400);
	glVertex2i(shift + 145, height - shift - 570);
	glVertex2i(shift - 10, height - shift - 570);
	glEnd();

	glColor3d(0.2, 0.9, 0.3);
	glBegin(GL_QUADS);
	glVertex2i(shift, height - shift - 390);
	glVertex2i(shift + 135, height - shift - 390);
	glVertex2i(shift + 135, height - shift - 360);
	glVertex2i(shift, height - shift - 360);
	glEnd();
	glColor3d(1, 1, 1);
	drawMenuText("Insert element", shift, height - shift - 360);

	glColor3d(0.2, 0.9, 0.3);
	glBegin(GL_QUADS);
	glVertex2i(shift, height - shift - 430);
	glVertex2i(shift + 135, height - shift - 430);
	glVertex2i(shift + 135, height - shift - 400);
	glVertex2i(shift, height - shift - 400);
	glEnd();
	glColor3d(1, 1, 1);
	drawMenuText("Delete element", shift, height - shift - 400);

	glColor3d(0.2, 0.9, 0.3);
	glBegin(GL_QUADS);
	glVertex2i(shift, height - shift - 470);
	glVertex2i(shift + 135, height - shift - 470);
	glVertex2i(shift + 135, height - shift - 440);
	glVertex2i(shift, height - shift - 440);
	glEnd();
	glColor3d(1, 1, 1);
	drawMenuText("Print matrix", shift, height - shift - 440);

	glColor3d(0.2, 0.9, 0.3);
	glBegin(GL_QUADS);
	glVertex2i(shift, height - shift - 510);
	glVertex2i(shift + 135, height - shift - 510);
	glVertex2i(shift + 135, height - shift - 480);
	glVertex2i(shift, height - shift - 480);
	glEnd();
	glColor3d(1, 1, 1);
	drawMenuText("Answer", shift, height - shift - 480);

	glColor3d(0.2, 0.9, 0.3);
	glBegin(GL_QUADS);
	glVertex2i(shift, height - shift - 550);
	glVertex2i(shift + 135, height - shift - 550);
	glVertex2i(shift + 135, height - shift - 520);
	glVertex2i(shift, height - shift - 520);
	glEnd();
	glColor3d(1, 1, 1);
	drawMenuText("New matrix", shift, height - shift - 520);
}

void mouseClick(int btn, int stat, int x, int y) {
	int shift = 60;
	int height = 730;

	if (stat == GLUT_DOWN) {

		if (x > shift  && x < shift + 135 && y >  shift + 360 && y < shift + 390)
		{
			int sourceVertex;
			int targetVertex;
			int edgeWeight;


			cout << "��������� ������� >> "; cin >> sourceVertex; cout << endl;
			int* sourceVertPtr = &sourceVertex;
			cout << "�������� ������� >> "; cin >> targetVertex; cout << endl;
			int* targetVertPtr = &targetVertex;

			if (sourceVertex > amountVerts || targetVertex > amountVerts) {
				amountVerts++;
				int* vertPtr = &amountVerts;
				graph.InsertVertex(*vertPtr);
			}

			cout << "��� >> "; cin >> edgeWeight; cout << endl;
			graph.InsertEdge(*sourceVertPtr, *targetVertPtr, edgeWeight); // 
		}
		if (x > shift && x < shift + 135 && y > shift + 400 && y < shift + 430)
		{
			int sourceVertex;
			int targetVertex;
			int edgeWeight;

			cout << "������� ������� >> "; cin >> sourceVertex; cout << endl;
			int* sourceVertPtr = &sourceVertex;
			if (sourceVertex == amountVerts)
			{
				amountVerts--;
				graph.DeleteVertex();
			}
			else cout << "����� ������� ���!\n";
		}
		if (x > shift && x < shift + 135 && y >  shift + 440 && y < shift + 470)
		{
			graph.Print();
		}
		if (x > shift && x < shift + 135 && y >  shift + 480 && y < shift + 510)
		{
			tsalesman(mat, n, help, result);
		}
		if (x > shift && x < shift + 135 && y >  shift + 520 && y < shift + 550)
		{
			graph = makeGraph();
		}
	}
	glutPostRedisplay();
}

void display()
{
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, WinW, 0, WinH); //������ ������ ��������� � ����� ������ ����
	glViewport(0, 0, WinW, WinH);
	glClearColor(0.3, 0.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	graph.DrawGraph();
	drawMenu();
	glutSwapBuffers();
}
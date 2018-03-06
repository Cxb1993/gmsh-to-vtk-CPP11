#pragma once
#include <vector>
#include "class_point.h"


unsigned nbfaces;

struct face {
	point p1, p2;
	int bc_typ;
	unsigned idface;
	double area = 0.0;
	point centroid;
};

struct cell_2D : public point {
	unsigned ident = 0;
	point vertex[4];
	face faces[4];
	cell_2D *neighbor1 = nullptr;
	cell_2D *neighbor2 = nullptr;
	cell_2D *neighbor3 = nullptr;
	cell_2D *neighbor4 = nullptr;
	double vol = 0.0;
};

class list_cell_2D : public cell_2D {

public:
	GmshReader msh_reader;
	vector<cell_2D> cells;
	void assign_vextex();
	void assign_faces();
	void assign_boundary_condition();
};

void list_cell_2D::assign_vextex()
{
	for (unsigned i = 0; i < msh_reader.nbelm; i++) {

		cell_2D a_cell;

		a_cell.ident = i;

		int idnode = msh_reader.id_nodes[i].id_node[5];

		for (unsigned j = 0; j < msh_reader.nbnode; j++)
		{
			if (idnode == msh_reader.coord_nodes[j].get_ident())
			{
				double x = msh_reader.coord_nodes[j].get_x();
				double y = msh_reader.coord_nodes[j].get_y();
				double z = msh_reader.coord_nodes[j].get_z();
				a_cell.vertex[0] = point(x, y, z, idnode);
			}
		}

		idnode = msh_reader.id_nodes[i].id_node[6];

		for (unsigned j = 0; j < msh_reader.nbnode; j++)
		{
			if (idnode == msh_reader.coord_nodes[j].get_ident())
			{
				double x = msh_reader.coord_nodes[j].get_x();
				double y = msh_reader.coord_nodes[j].get_y();
				double z = msh_reader.coord_nodes[j].get_z();
				a_cell.vertex[1] = point(x, y, z, idnode);
			}
		}

		idnode = msh_reader.id_nodes[i].id_node[7];

		for (unsigned j = 0; j < msh_reader.nbnode; j++)
		{
			if (idnode == msh_reader.coord_nodes[j].get_ident())
			{
				double x = msh_reader.coord_nodes[j].get_x();
				double y = msh_reader.coord_nodes[j].get_y();
				double z = msh_reader.coord_nodes[j].get_z();
				a_cell.vertex[2] = point(x, y, z, idnode);
			}
		}

		idnode = msh_reader.id_nodes[i].id_node[8];

		for (unsigned j = 0; j < msh_reader.nbnode; j++)
		{
			if (idnode == msh_reader.coord_nodes[j].get_ident())
			{
				double x = msh_reader.coord_nodes[j].get_x();
				double y = msh_reader.coord_nodes[j].get_y();
				double z = msh_reader.coord_nodes[j].get_z();
				a_cell.vertex[3] = point(x, y, z, idnode);
			}
		}

		this->cells.push_back(a_cell);
	}
}

void list_cell_2D::assign_faces()
{
	for (unsigned i = 0; i < msh_reader.nbelm; i++)
	{
		this->cells[i].faces[0].p1 = this->cells[i].vertex[0];
		this->cells[i].faces[0].p2 = this->cells[i].vertex[1];

		this->cells[i].faces[1].p1 = this->cells[i].vertex[1];
		this->cells[i].faces[1].p2 = this->cells[i].vertex[2];

		this->cells[i].faces[2].p1 = this->cells[i].vertex[2];
		this->cells[i].faces[2].p2 = this->cells[i].vertex[3];

		this->cells[i].faces[3].p1 = this->cells[i].vertex[3];
		this->cells[i].faces[3].p2 = this->cells[i].vertex[0];
	}
}

void list_cell_2D::assign_boundary_condition()
{

}
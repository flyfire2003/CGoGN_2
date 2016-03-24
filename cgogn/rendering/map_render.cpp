/*******************************************************************************
* CGoGN: Combinatorial and Geometric modeling with Generic N-dimensional Maps  *
* Copyright (C) 2015, IGG Group, ICube, University of Strasbourg, France       *
*                                                                              *
* This library is free software; you can redistribute it and/or modify it      *
* under the terms of the GNU Lesser General Public License as published by the *
* Free Software Foundation; either version 2.1 of the License, or (at your     *
* option) any later version.                                                   *
*                                                                              *
* This library is distributed in the hope that it will be useful, but WITHOUT  *
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or        *
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License  *
* for more details.                                                            *
*                                                                              *
* You should have received a copy of the GNU Lesser General Public License     *
* along with this library; if not, write to the Free Software Foundation,      *
* Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA.           *
*                                                                              *
* Web site: http://cgogn.unistra.fr/                                           *
* Contact information: cgogn@unistra.fr                                        *
*                                                                              *
*******************************************************************************/

#define CGOGN_RENDERING_DLL_EXPORT

#include <rendering/map_render.h>

namespace cgogn
{

namespace rendering
{

MapRender::MapRender()
{
	for (uint32 i = 0u; i < SIZE_BUFFER; ++i)
	{
		indices_buffers_[i] = new QOpenGLBuffer(QOpenGLBuffer::IndexBuffer);
		indices_buffers_[i]->setUsagePattern(QOpenGLBuffer::StaticDraw);
	}
}

MapRender::~MapRender()
{
	for (uint32 i = 0u; i < SIZE_BUFFER; ++i)
		delete indices_buffers_[i];
}

void MapRender::draw(DrawingType prim)
{
	QOpenGLFunctions *ogl = QOpenGLContext::currentContext()->functions();

	indices_buffers_[prim]->bind();
	switch (prim)
	{
	case POINTS:
		ogl->glDrawElements(GL_POINTS, nb_indices_[POINTS], GL_UNSIGNED_INT, 0);
		break;
	case LINES:
		ogl->glDrawElements(GL_LINES, nb_indices_[LINES], GL_UNSIGNED_INT, 0);
		break;
	case TRIANGLES:
		ogl->glDrawElements(GL_TRIANGLES, nb_indices_[TRIANGLES], GL_UNSIGNED_INT, 0);
		break;
	default:
		break;
	}

	indices_buffers_[prim]->release();
}


} // namespace rendering
} // namespace io

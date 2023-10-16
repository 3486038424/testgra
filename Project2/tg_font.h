#pragma once
#include"Graphics.h"
#include<iostream>

#define STB_TRUETYPE_IMPLEMENTATION

#include "stb_truetype.h"

#include <fstream>

class tg_font {
	stbtt_fontinfo info;
	float scale;
	int wordspace;
	bool line_type = false;
	void tg_set_font_in_graphics(Graphics* gra, float scale_x, float scale_y, int codepoint, int* width, int* height, int& xpos, int& baseline)
	{
		int glyph = stbtt_FindGlyphIndex(&info, codepoint);
		int ix0, iy0, ix1, iy1;
		if (scale_x == 0) scale_x = scale_y;
		if (scale_y == 0) {
			if (scale_x == 0) {
				return;
			}
			scale_y = scale_x;
		}
		stbtt_vertex* vertices;
		int num_verts = stbtt_GetGlyphShape(&info, glyph, &vertices);

		stbtt_GetGlyphBitmapBoxSubpixel(&info, glyph, scale_x, scale_y, 0, 0, &ix0, &iy0, &ix1, &iy1);

		if (width) *width = ix1 - ix0;
		if (height) *height = iy1 - iy0;

		if (*width && *height) {
			float scale = scale_x > scale_y ? scale_y : scale_x;
			int winding_count = 0;
			int* winding_lengths = NULL;
			void* userdata = info.userdata;
			stbtt__point* windings = stbtt_FlattenCurves(vertices, num_verts, 0.35f / scale, &winding_lengths, &winding_count, userdata);
			if (windings) {
				stbtt__edge* e;
				int n, i, j, k, m;

				n = 0;
				for (i = 0; i < winding_count; ++i)
					n += winding_lengths[i];

				e = (stbtt__edge*)STBTT_malloc(sizeof(*e) * (n + 1), userdata); // add an extra one as a sentinel
				n = 0;
				m = 0;
				for (i = 0; i < winding_count; ++i) {
					stbtt__point* p = windings + m;
					m += winding_lengths[i];
					j = winding_lengths[i] - 1;
					for (k = 0; k < winding_lengths[i]; j = k++) {
						if (p[j].y == p[k].y)
							continue;
						int a = k, b = j;
						e[n].invert = 0;
						if (p[j].y > p[k].y) {
							e[n].invert = 1;
							a = j, b = k;
						}
						e[n].x0 = p[a].x * scale_x;
						e[n].y0 = (p[a].y * -scale_y);
						e[n].x1 = p[b].x * scale_x;
						e[n].y1 = (p[b].y * -scale_y);
						++n;
					}
				}

				stbtt__sort_edges(e, n);

				stbtt__hheap hh = { 0, 0, 0 };
				stbtt__active_edge* active = NULL;
				int y;
				j = 0;
				float scanline_data[129], * scanline, * scanline2;

				STBTT__NOTUSED(1);

				if (*width > 64)
					scanline = (float*)STBTT_malloc((*width * 2 + 1) * sizeof(float), userdata);
				else
					scanline = scanline_data;

				scanline2 = scanline + *width;

				y = iy0;
				e[n].y0 = (float)(iy0 + *height) + 1;

				stbtt__edge* te = e;
				while (j < *height) {
					// find center of pixel for this scanline

					float scan_y_bottom = y + 1.0f;
					stbtt__active_edge** step = &active;

					STBTT_memset(scanline, 0, *width * sizeof(scanline[0]));
					STBTT_memset(scanline2, 0, (*width + 1) * sizeof(scanline[0]));

					// update all active edges;
					// remove all active edges that terminate before the top of this scanline
					while (*step) {
						stbtt__active_edge* z = *step;
						if (z->ey <= y) {
							*step = z->next; // delete from list
							STBTT_assert(z->direction);
							z->direction = 0;
							stbtt__hheap_free(&hh, z);
						}
						else {
							step = &((*step)->next); // advance through list
						}
					}

					// insert all edges that start before the bottom of this scanline
					while (e->y0 <= scan_y_bottom) {
						if (e->y0 != e->y1) {
							stbtt__active_edge* z = stbtt__new_active(&hh, e, ix0, y, userdata);
							if (z != NULL) {
								if (j == 0 && iy0 != 0) {
									if (z->ey < y) {
										// this can happen due to subpixel positioning and some kind of fp rounding error i think
										z->ey = y;
									}
								}
								STBTT_assert(z->ey >= y); // if we get really unlucky a tiny bit of an edge can be out of bounds
								// insert at front
								z->next = active;
								active = z;
							}
						}
						++e;
					}

					// now process all active edges
					if (active)stbtt__fill_active_edges_new(scanline, scanline2 + 1, *width, active, y);

					float sum = 0;
					for (i = 0; i < *width; ++i) {
						sum += scanline2[i];
						if ((int)((float)STBTT_fabs(scanline[i] + sum) * 255 + 0.5f) > 0)
							gra->set(xpos + i, baseline - j - iy0);
					}
					step = &active;
					while (*step) {
						stbtt__active_edge* z = *step;
						z->fx += z->fdx; // advance to position for current scanline
						step = &((*step)->next); // advance through list
					}

					++y;
					++j;
				}

				stbtt__hheap_cleanup(&hh, userdata);

				if (scanline != scanline_data)
					STBTT_free(scanline, userdata);

				STBTT_free(te, userdata);
				STBTT_free(winding_lengths, userdata);
				STBTT_free(windings, userdata);
			}
		}
		STBTT_free(vertices, info.userdata);
	}
public:
	tg_font(const char* path = "font/default.ttf") {

		FILE* fontFile = fopen(path, "rb");
		if (fontFile == NULL)
		{
			printf("Can not open font file!\n");
			return;
		}
		std::cout << "true" << std::endl;
		fseek(fontFile, 0, SEEK_END);
		long int size = ftell(fontFile);
		fseek(fontFile, 0, SEEK_SET);

		unsigned char* fontBuffer = (unsigned char*)calloc(size, sizeof(unsigned char));
		fread(fontBuffer, size, 1, fontFile);
		fclose(fontFile);
		if (!stbtt_InitFont(&info, fontBuffer, 0))
		{
			printf("stb init font failed\n");
		}
		set_font_size(24);
		wordspace = 20;
	}
	int set_font_size(int fontSize)
	{
		scale = stbtt_ScaleForPixelHeight(&info, fontSize);
		return 0;
	}
	void active_line() { line_type = true; }
	void unactive_line() { line_type = false; }
	int setWordSpace(int wordSpace) { wordspace = wordSpace; return 0; }
	void render_text(Graphics* gra, std::u16string text, int baseline = 100, int xpos = 0) {
		int t = xpos;
		int ch = 0;
		while (text[ch]) {
			int width, height;
			tg_set_font_in_graphics(gra, scale, scale, text[ch], &width, &height, xpos, baseline);
			xpos += width;
			ch++;
			xpos += wordspace;
		}
		if (line_type)
		{
			while (t <= xpos) {
				gra->set(t, baseline);
				t++;
			}
		}
	}
};

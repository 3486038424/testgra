#include "Graphics.h"
#include <iostream>
#include <cmath>
bool Graphics::set_pixel(int vec, int rgb)
{
	if (vec<0 || vec>len)return false;
	ptr[vec] = rgb;
	return true;
}
void Graphics::drawpic(Image img, int x, int y, int delta_x, int delta_y)
{
	int offset = (h - x + 1) * w;
	int z = x > 0 ? 0 : -x;
	for (int i = y > 0 ? 0 : -y; i < delta_y && i + y < h; i++)
	{
		offset -= w;
		if (offset<0 || offset>len)continue;
		int kt = img.height * i / delta_y * img.width;
		for (int j = z; j < delta_x && j + x < w; j++)
		{
			set_pixel(offset + j + y, img.get_color(kt + (y + j) * img.width / delta_x));
		}
	}
}
int Graphics::init(int width,int height)
{
	frameCount = 0;
	return reset(width,height);
}
int Graphics::reset(int width,int height)
{
	w = width;                 // ����
	h = height;                // �߶�
	len = w * h;
	ptr = (int*)malloc(width * height * 4);  // 4�ֽ�per����
	z_ptr = (int*)malloc(width * height * 4);  // 4�ֽ�per����
	return 0;
}
template<typename T>
void swap(T& a, T& b)
{
	T c = a;
	a = b;
	b = c;
}
tg_vec2d* Graphics::line(tg_vec2d begin, tg_vec2d end, int& l_s)
{
	l_s = 0;
	float d1 = 0, d2 = 0, m = begin.far_2(end);
	float k1 = (end.x - begin.x) / m, k2 = (end.y - begin.y) / m;
	tg_vec2d u(begin);
	tg_vec2d* d = new tg_vec2d[m * 3];
	d[l_s] = u;
	l_s++;
	while (!(u == end))
	{
		bool c = 0;
		d1 += k1; d2 += k2;
		if (d1 <= -1) { u.x--; d1++; c = 1; }
		if (d2 <= -1) { u.y--; d2++; c = 1; }
		if (d1 >= 1) { u.x++; d1--; c = 1; }
		if (d2 >= 1) { u.y++; d2--; c = 1; }
		if (c) { d[l_s] = u; l_s++; }
	}
	return d;
}
tg_vec2d* line_2(tg_vec2d begin, tg_vec2d end, int& l_s)
{
	l_s = 0;
	float d1 = 0, d2 = 0, m = begin.far_2(end);
	float k1 = (end.x - begin.x) / m, k2 = (end.y - begin.y) / m;
	tg_vec2d u(begin);
	tg_vec2d* d = new tg_vec2d[begin.far_with(end) + 3];
	d[l_s] = u;
	l_s++;
	while (!(u.x == end.x && u.y == end.y))
	{
		bool c = 0;
		d1 += k1; d2 += k2;
		if (d1 <= -1) { u.x--; d1++; c = 1; }
		if (d2 <= -1) { u.y--; d2++; c = 1; }
		if (d1 >= 1) { u.x++; d1--; c = 1; }
		if (c) { d[l_s] = u; l_s++; }
	}
	float dz = 0, kz = (end.z - begin.z) / (1.0 * l_s);
	for (int i = 0; i < l_s; i++)
	{
		d[i].z += dz;
		dz += kz;
	}
	return d;
}
tg_vec3d* Graphics::line_3(tg_vec3d begin, tg_vec3d end, int& l_s)
{
	if (begin.y > end.y)swap(begin, end);
	l_s = 0;
	float d1 = 0, d2 = 0, d3 = 0, m = begin.far_3(end);
	float k1 = (end.x - begin.x) / m, k2 = (end.y - begin.y) / m, k3 = (end.z - begin.z) / m;
	tg_vec3d u(begin);
	tg_vec3d* d = new tg_vec3d[m * 3 + 10];
	d[l_s] = u;
	l_s++;
	while (!(u == end))
	{
		bool c = 0;
		d1 += k1; d2 += k2; d3 += k3;
		if (d1 <= -1) { u.x--; d1++; c = 1; }
		if (d2 <= -1) { u.y--; d2++; c = 1; }
		if (d3 <= -1) { u.z--; d3++; c = 1; }
		if (d1 >= 1) { u.x++; d1--; c = 1; }
		if (d2 >= 1) { u.y++; d2--; c = 1; }
		if (d3 >= 1) { u.z++; d3--; c = 1; }
		if (c) { d[l_s] = u; l_s++; }
	}
	return d;
}
int Graphics::tg_DrawLine(tg_vec2d begin, tg_vec2d end)
{
	int l_s = 0;
	tg_vec2d* d = line(begin, end, l_s);
	for (auto it = 0; it != l_s; it++)
	{
		set_pixel(int(d[it].x * w + d[it].y), RGB(255, 0, 0));
	}
	delete d;
	return 0;
};
bool Graphics::get_color(tg_vec3d& b, tg_vec3d& e, tg_vec2d& t, float z, int& rgb)
{
	tg_vec3d k(b);
	k.z += (e.z - b.z) * z;
	if (k.z < 0 || (z_ptr[rgb] != -1 && z_ptr[rgb] < k.z))return 0;
	k.x += (e.x - b.x) * z;
	k.y += (e.y - b.y) * z;
	if (set_pixel(rgb, RGB(255,0,255-k.z)))
	{
		z_ptr[rgb]=k.z;
	}
	return 1;
}

bool Graphics::get_color_2(tg_vec2d& b, tg_vec2d& e, int z, int offset)
{
	tg_vec3d k(b);
	if (e.x == b.x)return 0;
	float d = (z - b.x) / (1.0 * (e.x - b.x));
	k.z += (e.z - b.z) * d;
	if (k.z < 0 || (z_ptr[offset] != -1 && z_ptr[offset] < k.z))return 0;
	k.x += (e.x - b.x) * d;
	k.y += (e.y - b.y) * d;
	if (set_pixel(offset, RGB(255, 0, 255 - k.z)))
	{
		z_ptr[offset] = k.z;
	}
	return 1;
}

double short_distance(tg_vec3d v1, tg_vec3d v2, tg_vec3d v3)
{
	double l1 = v1.far_3(v2), l2 = v2.far_3(v3), l3 = v1.far_3(v3);
	double p = (l1 + l2 + l3) / 2;
	double s = sqrt(p * (p - l1) * (p - l2) * (p - l3));
	return s * 2 / l1;
}

int Graphics::tg_DrawLine3d(tg_vec3d begin, tg_vec3d end)
{
	int l_s = 0;
	tg_vec2d* d = line(begin, end, l_s);
	int rgb;
	for (int it = 0; it != l_s; it++)
	{
		k++;
		rgb = d[it].x * w + d[it].y;
		get_color(begin, end, d[it], it / (l_s * 1.0), rgb);
	}
	if (l_s > 1)delete d;
	return 0;
};
int Graphics::tg_fill(tg_vec2d* l1, tg_vec2d* l2, int l1_s, int l2_s)
{
	if (l1[0].y > l2[0].y) { swap(l2, l1); swap(l1_s, l2_s); }
	int i = 0, j = 0;
	int t1 = 0, t2 = 0, offset, z;
	while (l1[i].x < l2[j].x)
	{
		i++; if (i == l1_s)return 0;
	}
	while (1)
	{
		while (l1[i].x > l2[j].x)
		{
			j++; if (j == l2_s)return 0;
		}
		offset = l1[i].x * w;
		for (z = l1[i].y; z < l2[j].y; z++) {
			if (z == l1[i].y || z + 1 >= l2[j].y)
				set_pixel(offset + z, RGB(0,0,125 ));
		}
		do { i++; if (i == l1_s)return 0; } while (l1[i].x == l1[i - 1].x);
	}
	return 0;
};
int Graphics::tg_DrawTriangle(tg_vec2d v1, tg_vec2d v2, tg_vec2d v3)
{
	int ls1 = 0, ls2 = 0, ls3 = 0;
	tg_vec2d* l1 = line(v1, v2, ls1);
	tg_vec2d* l2 = line(v3, v2, ls2);
	tg_vec2d* l3 = line(v1, v3, ls3);
	tg_fill(l1, l2, ls1, ls2);
	tg_fill(l3, l2, ls3, ls2);
	tg_fill(l1, l3, ls1, ls3);
	delete l1;
	delete l2;
	delete l3;
	return 0;
}
int Graphics::tg_DrawTriangle_3d(tg_vec3d v1, tg_vec3d v2, tg_vec3d v3)
{
	tg_vec2d vec1(v1), vec2(v2), vec3(v3);
	if (vec1.y < vec2.y)swap(vec1, vec2);
	if (vec2.y < vec3.y) { swap(vec2, vec3); if (vec1.y < vec2.y)swap(vec1, vec2); }
	int ls1 = 0, ls2 = 0, ls3 = 0;
	tg_vec2d* l1 = line_2(vec1, vec2, ls1);
	tg_vec2d* l2 = line_2(vec2, vec3, ls2);
	tg_vec2d* l3 = line_2(vec1, vec3, ls3);
	int len1 = 0, len2 = 0, d;
	d = vec3.x + (vec1.x - vec3.x) * (vec2.y - vec3.y) / (vec1.y - vec3.y);
	if (d < vec2.x)d = 1; else d = -1;
	bool t = 0;
	
	while (len1 < ls3)
	{
		int offset = l3[len1].y * w;
		for (int x = l3[len1].x; x != l1[len2].x; x += d)
		{
			get_color_2(l3[len1], l1[len2], x, offset + x);
		}
		do { len1++; } while (len1 < ls3 && l3[len1].y == l3[len1 - 1].y);
		do { len2++; } while (len2 < ls1 && l1[len2].y != l3[len1].y);
		if (len2 == ls1 && t == 0) {
			len2 = 0;
			swap(l1, l2); swap(ls1, ls2);
			while (len2 < ls1 && l1[len2].y != l3[len1].y)len2++;
		}
	}
	/*
	for (auto it = 0; it != ls1; it++)
	{
		ptr[int(l1[it].x * w + l1[it].y)] = RGB(0, 0, 0);
	}
	for (auto it = 0; it != ls2; it++)
	{
		ptr[int(l2[it].x * w + l2[it].y)] = RGB(0, 0, 0);
	}
	for (auto it = 0; it != ls3; it++)
	{
		ptr[int(l3 [it] .x * w + l3[it].y)] = RGB(0, 0, 0);
	}
*/
	delete l1;
	delete l2;
	delete l3;
	return 0;
}
class draw_pic_in_3d
{
	int tx1, tx2;
	int ty1, ty2;
	
	tg_vec3d *l13, *l23;
	float l2; 
	float d1;
	float l_12;
	tg_vec3d *p;
	
public:
	int draw_pic(Graphics *gra,tg_vec3d v1, tg_vec3d v2, tg_vec3d v3, Image& img, tg_vec2d& vc1, tg_vec2d& vc2, tg_vec2d& vc3)
	{
		tg_vec2d vec1(v1), vec2(v2), vec3(v3);
		if (vec1.y < vec2.y) { swap(vec1, vec2); swap(vc1, vc2); swap(v1, v2); }
		if (vec2.y < vec3.y) {
			swap(vec2, vec3); swap(vc2, vc3); swap(v2, v3);
			if (vec1.y < vec2.y) { swap(vec1, vec2); swap(vc1, vc2); swap(v1, v2); }
		}
		
		tx1 = vc2.x - vc1.x;
		tx2 = vc3.x - vc1.x;
		ty1 = vc2.y - vc1.y;
		ty2 = vc3.y - vc1.y;
		l_12 = v1.far_3(v2);
		double l_23 = v2.far_3(v3), l_13 = v1.far_3(v3);
		double p2 = (l_12 + l_23 + l_13) / 2;
		double s = sqrt(p2 * (p2 - l_12) * (p2 - l_23) * (p2 - l_13));
		l2 = s * 2 / l_12;

		l13 = new tg_vec3d(v3.x - v1.x, v3.y - v1.y, v3.z - v1.z);
		l23 = new tg_vec3d(v3.x - v2.x, v3.y - v2.y, v3.z - v2.z);

		int ls1 = 0, ls2 = 0, ls3 = 0;
		tg_vec2d* l1 = line_2(vec1, vec2, ls1);
		tg_vec2d* l2 = line_2(vec2, vec3, ls2);
		tg_vec2d* l3 = line_2(vec1, vec3, ls3);
		int len1 = 0, len2 = 0, d;
		d = vec3.x + (vec1.x - vec3.x) * (vec2.y - vec3.y) / (vec1.y - vec3.y);
		if (d < vec2.x)d = 1; else d = -1;
		bool t = 0;
		while (len1 < ls3)
		{
			int offset = l3[len1].y * gra->w;
			d1 = l1[len2].x - l3[len1].x;
			tg_vec3d k(l3[len1]);
			p = new tg_vec3d(l1[len2]);
			p->x -= k.x; p->y -= k.y; p->z -= k.z;
			for (int x = l3[len1].x; x != l1[len2].x; x += d)
			{
				get_color_3(gra,l3[len1],l1[len2], v1, v2, v3, x, offset + x, img, vc1);
			}
			do { len1++; } while (len1 < ls3 && l3[len1].y == l3[len1 - 1].y);
			do { len2++; } while (len2 < ls1 && l1[len2].y != l3[len1].y);
			if (len2 == ls1 && t == 0) {
				len2 = 0;
				swap(l1, l2); swap(ls1, ls2);
				while (len2 < ls1 && l1[len2].y != l3[len1].y)len2++;
			}
		}
		delete l1;
		delete l2;
		delete l3;
		return 0;
	}
	bool get_color_3(Graphics *gra, tg_vec2d& b, tg_vec2d& e, tg_vec3d v1, tg_vec3d v2, tg_vec3d v3, int x, int offset, Image& img, tg_vec2d& vc1)
	{
		tg_vec3d k(b);
		float d = (x - b.x) / d1;
		k.z += p->z * d;
		if (k.z <= 0 || (gra->z_ptr[offset] != -1 && gra->z_ptr[offset] < k.z))return 0;
		k.x += p->x * d;
		k.y += p->y * d;
		
		double  l_23 = v2.far_3(k), l_13 = v1.far_3(k);
		double p = (l_12 + l_23 + l_13) / 2;
		double s = sqrt(p * (p - l_12) * (p - l_23) * (p - l_13));
		float l1 = s * 2 / l_12;
		float k1 = l1 / l2;
		tg_vec3d line1(v1.x + k1 * l13->x, v1.y + k1 * l13->y, v1.z + k1 * l13->z);
		tg_vec3d line2(v2.x + k1 * l23->x, v2.y + k1 * l23->y, v2.z + k1 * l23->z);
		float k2 = line1.far_3(k) / line1.far_3(line2);
		if (gra->set_pixel(offset, tg_color(k1, k2, img, vc1)))gra->z_ptr[offset] = k.z;
		return 1;
	}
	int tg_color(float k1, float k2, Image& img, tg_vec2d& vec1)
	{
		tg_vec2d p(vec1.x + k1 * tx2 + k2 * (1 - k1) * tx1, vec1.y + k1 * ty2 + k2 * (1 - k1) * ty1);
		//return RGB(p.x/(float)img.width*255,p.y/(float)img.height*255,0);
		//return RGB(k2*255,0,0);
		return img.get_color(int(p.y) * img.width + int(p.x));
	}
};
int Graphics::tg_DrawTriangle_3d_with_image(tg_vec3d v1, tg_vec3d v2, tg_vec3d v3,Image &img,tg_vec2d vc1,tg_vec2d vc2,tg_vec2d vc3)
{
	draw_pic_in_3d d;
	d.draw_pic(this, v1, v2, v3, img, vc1, vc2, vc3);
	return 0;
}


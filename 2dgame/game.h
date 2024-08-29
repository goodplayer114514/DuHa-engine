#include<easyx.h>
#include<vector>
struct pos {
	int dstx;
	int dsty;
};
void addxy(pos& a, pos b, pos c) {
	a.dstx = b.dstx + c.dstx;
	a.dsty = b.dsty + c.dsty;
}
pos plsmidd(pos start, int width, int height) {
	pos tmp = {0,0};
	int srcx = width / 2;
	int srcy = height / 2;
	tmp.dstx += srcx;
	tmp.dsty += srcy;
	return tmp;
}
struct Game_MVP {
	pos start; int width; pos send;
	int height; pos midd; int height2;
	pos estart; int width2; pos end;
};
/*
Game_MVP指的是一个图片相对应的节点
start开始节点 end结束节点
*/
class athor {
public:
	athor(pos start, int width, int height) {
		cube.start = start; cube.width = width; cube.height = height;
		cube.end.dstx = start.dstx + width;
		cube.end.dsty = start.dsty + height;
		cube.midd = plsmidd(start, width, height);
		cube.estart.dstx = start.dstx; cube.estart.dsty = start.dsty + height;
		cube.send.dstx = cube.end.dstx; cube.send.dsty = start.dstx + width;
		cube.height2 = height / 2;
		cube.width2 = width / 2;
	}
	void del() {
		delete this;
	}
	IMAGE pic;Game_MVP cube; 
private:
};
class Game {
public:
	std::vector<athor> list;
	~Game() {
		for (int i = 0; i < list.size(); i++) {
			list[i].del();
		}
	}
	void output() {
		for (int i = 0; i <list.size(); i++) {
			putimage(list[i].cube.start.dstx, list[i].cube.start.dsty, &list[i].pic);
		}
	}
	void update();
	void input();
};
void putpicture(int dstx, int dsty, IMAGE* img, COLORREF color, int alpha) {//0~255 255表示不透明
	DWORD* imgp = GetImageBuffer(img);
	DWORD* bgimgp = GetImageBuffer();
	int w, bw, h, i, j;
	w = img->getwidth();
	bw = getwidth();
	h = img->getheight();
	color += 0xff000000;
	if (alpha < 0)alpha = 0;
	else if (alpha > 255)alpha = 255;
	for (i = 0; i < h; ++i)
		for (j = 0; j < w; ++j)
			if (imgp[i * w + j] != color)
				bgimgp[(i + dsty) * bw + j + dstx] = RGB(
					((int)(alpha / 255.0 * GetRValue(imgp[i * w + j]) + (1 - alpha / 255.0) * GetRValue(bgimgp[(i + dsty) * bw + j + dstx]))),
					((int)(alpha / 255.0 * GetGValue(imgp[i * w + j]) + (1 - alpha / 255.0) * GetGValue(bgimgp[(i + dsty) * bw + j + dstx]))),
					((int)(alpha / 255.0 * GetBValue(imgp[i * w + j]) + (1 - alpha / 255.0) * GetBValue(bgimgp[(i + dsty) * bw + j + dstx])))
				);
}

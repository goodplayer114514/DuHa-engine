#include<graphics.h>
#include<vector>
#include<math.h>
#include<windows.h>
#include<map>
#define M_PI 3.14

double cot(double x) {
	double y = x * M_PI / 180;
	return 1 / tan(y);
}
struct Vector3 {
	double x;
	double y;
	double z;
	int w;
};//三维矢量
struct Vector2 {
	double x;
	double y;
};//二维矢量
class Pos {//顶点位置
public:
	//Vector3 Transform;
	COLORREF MainColor;
	std::vector<int> linePosNum;
	Vector3 CutPos;
	Vector3 WorldNormalPos;
	Vector3 CameraPos;
	Vector2 SrcPos;
	std::vector<Pos> line_pos;
	Pos(double x, double y, double z,int w=1) {
		WorldNormalPos.x = x;
		WorldNormalPos.y = y;
		WorldNormalPos.z = z;
		WorldNormalPos.w = w;
	}
	void RGB_COLOR(int R,int G, int B) {
		MainColor=RGB(R, G, B);
	}
	void SetWorldPos(double a, double b, double c) {
		WorldNormalPos = { a,b,c,1 };
	}
	void MoveWorldNormal (double tx, double ty, double tz,Vector3 *pb) {
		pb->x += tx;
		pb->y += ty;
		pb->z += tz;
	}
	//旋转矩阵
	//以后重构
	void Ro_World_Pos(double Ro,char Call,Vector3 *ad) {
		Vector3 Out;
		switch (Call) {
		case 'x':
			Out = {
				ad->x,
				(cos(Ro) * ad->y) + (-sin(Ro) * ad->z),
				(sin(Ro) * ad->y) + (cos(Ro) * ad->z),
				ad->w
			};
			//Transform.y = (cos(Ro) * Transform.y) + (-sin(Ro) * Transform.z);
			//*ad = Out;
			break;
		case 'y':
			Out = {
				(cos(Ro) * ad->x) + (sin(Ro) * ad->z),
				ad->y,
				(-sin(Ro)* ad->x)+ (cos(Ro)* ad->z),
				ad->w
			};
			//*ad = Out;
			break;
		case 'z':
			Out = {
				(cos(Ro) * ad->x) + (-sin(Ro) * ad->y),
				(sin(Ro) * ad->x) + (cos(Ro) * ad->y),
				ad->z,
				ad->w
			};
			break;
		}
		*ad = Out;
		//return Out;
	}
};
class GameObject {
public:
	std::map<int, int> Mian;
	std::vector<Pos> Poslist;
	void TransLate(double tx, double ty, double tz) {
		for (int i = 0; i < Poslist.size(); i++) {
			Poslist[i].MoveWorldNormal(tx, ty, tz, &Poslist[i].WorldNormalPos);
		}
	}
	void Rotate(double tx, double ty, double tz) {
		for (int i = 0; i < Poslist.size(); i++) {
			Poslist[i].Ro_World_Pos(tx, 'x', &Poslist[i].WorldNormalPos);
			Poslist[i].Ro_World_Pos(ty, 'y', &Poslist[i].WorldNormalPos);
			Poslist[i].Ro_World_Pos(tz, 'z', &Poslist[i].WorldNormalPos);
		}
	}
};
class camera {
private:
	int pixelwidth, pixelheight;
	//int BeCamx, BeCamy, BeCamz;
	void World_Cam_Charge() {//转变坐标系 世界-》摄像
		for (int i = 0; i < list.size(); i++) {
			list[i].CameraPos = list[i].WorldNormalPos;
			list[i].MoveWorldNormal(-Cam_pos.x, -Cam_pos.y, -Cam_pos.z,&list[i].CameraPos);
			if (Cam_ro.x != 0) list[i].Ro_World_Pos(-Cam_ro.x, 'x', &list[i].CameraPos);
			if (Cam_ro.y != 0) list[i].Ro_World_Pos(-Cam_ro.y, 'y', &list[i].CameraPos);
			if (Cam_ro.z != 0) list[i].Ro_World_Pos(-Cam_ro.z, 'z', &list[i].CameraPos);
		}
	}
	void Cam_Cut_Charge() {//转变坐标系 摄像-》裁剪0
		for (int i = 0; i < list.size(); i++) {
			if (Cube_true) {
				list[i].CutPos.x=1.0/mSize*list[i].CameraPos.x;
				list[i].CutPos.y = 1.0 / (mAspect*mSize) * list[i].CameraPos.y;
				list[i].CutPos.z = (- (2.0 / (mFar - mNear)) + -((mFar + mNear) / (mFar - mNear)))* list[i].CameraPos.z;
				list[i].CutPos.w = 1;
			}
			else {
				list[i].CutPos.x = cot(mFov / 2) / mAspect * list[i].CameraPos.x;
				list[i].CutPos.y = cot(mFov / 2) * list[i].CameraPos.y;
				list[i].CutPos.z = -((mFar+mNear)/(mFar-mNear)) * list[i].CameraPos.z-((2*mNear*mFar)/(mFar-mNear));
				list[i].CutPos.w = list[i].CutPos.z;
			}
		}
	}
	void Cut_Src_Charge() {
		for (int i = 0; i < list.size(); i++) {
			if (!Cube_true) {
				list[i].SrcPos.x = (list[i].CutPos.x * pixelwidth) / (2.0 * list[i].CutPos.w) + (pixelwidth / 2.0);
				list[i].SrcPos.y = ((list[i].CutPos.y * pixelheight) / (2.0 * list[i].CutPos.w) + (pixelheight / 2.0));
			}
			else {
				list[i].SrcPos.x = (list[i].CutPos.x * pixelwidth) / (2.0 * list[i].CutPos.w) + (pixelwidth / 2.0);
				list[i].SrcPos.y = pixelheight-((list[i].CutPos.y * pixelheight) / (2.0 * list[i].CutPos.w) + (pixelheight / 2.0));
			}
			/*if (list[i].CutPos.x)*/
		}
	}
public:
	bool Cube_true;
	double mNear, mFar, mSize, mAspect, mNearHeight,mFov;
	Vector3 Cam_pos; Vector3 Cam_ro;
	std::vector<Pos> list;
	void initlist() {
		for (int i = 0; i < list.size(); i++) {
			list[i].CameraPos = list[i].WorldNormalPos;
		}
	}
	camera(double a, double b, double c, double d) {
		mNear = a;
		mFar = b;
		mAspect = c;
		mSize = d;
	}
	camera() {
		mNear = 0;
		mFar = 0;
		mAspect = 0;
		mSize = 0;
		Cam_pos={ 0,0,0,0 };
		mFov = 0;
	}
	void SetCube(double a, double b, double c, double d) {//a=Near b=Far c=Aspect d=Size
		mNear = a;
		mFar = b;
		mAspect = c;
		mSize = d;
	}
	void SetEyes(double a, double b, double c, double d,double e) {//a=Near b=Far c=Aspect d=Size e=Fov
		mNear = a;
		mFar = b;
		mAspect = c;
		mSize = d;
		mFov = e;
	}
	void SeeWorld() {
		for (int i = 0; i < list.size(); i++) {
			setfillcolor(list[i].MainColor);
			fillcircle(list[i].SrcPos.x, list[i].SrcPos.y, 1);
			//if (this->Cam_pos.z < list[i].WorldNormalPos.z) {
				for (int j = 0; j < list[i].linePosNum.size(); j++) {
					line(list[i].SrcPos.x, list[i].SrcPos.y, list[list[i].linePosNum[j]].SrcPos.x, list[list[i].linePosNum[j]].SrcPos.y);
					//floodfill(list[i].SrcPos.x, list[i].SrcPos.y,list[i].MainColor);
				}
			//}
		}
	}
	void Update() {
		World_Cam_Charge();
		Cam_Cut_Charge();
		Cut_Src_Charge();
	}
	void pixel_Ch(int width, int height) {
		pixelwidth = width;
		pixelheight = height;
	}
};
class Game {
private:
	void update();
	void input();
	void Update_Pos() {
		for (int i = 0; i < objectlist.size(); i++) {
			for (int j = 0; j < objectlist[i].Poslist.size(); j++) {
				MainCam.list.push_back(objectlist[i].Poslist[j]);
			}
		}
	}
	void output() {
		BeginBatchDraw();
		clearcliprgn();
		MainCam.Update();
		MainCam.SeeWorld();
		EndBatchDraw();
	}
public:
	camera MainCam;
	std::vector<GameObject> objectlist;
	Game(int Near, int Far, int Aspect, int Size) {
		MainCam.SetCube(Near, Far, Aspect, Size);
		MainCam.Cube_true = true;
	}
	Game(int Near, int Far, int Aspect, int Size, int Fov) {
		MainCam.SetEyes(Near, Far, Aspect, Size,Fov);
		MainCam.Cube_true = false;
	}
	void Running(bool a) {
		Update_Pos();
		while (a) {
			MainCam.initlist();
			input();
			update();
			output();
		}
	}
};
#define Num 0.01
void MIan(GameObject *op,int R,int G,int B) {
	std::map<int, int>::iterator t;
	for (t = op->Mian.begin(); t != op->Mian.end(); t++) {
		if (op->Poslist[t->first].WorldNormalPos.x == op->Poslist[t->second].WorldNormalPos.x) {
			if (op->Poslist[t->first].WorldNormalPos.z < op->Poslist[t->second].WorldNormalPos.z) {//op-》的z小于问题
				for (float i = op->Poslist[t->first].WorldNormalPos.z; i <= op->Poslist[t->second].WorldNormalPos.z; i+=Num) {
					if (op->Poslist[t->first].WorldNormalPos.y > op->Poslist[t->second].WorldNormalPos.y) {
						for (float k = op->Poslist[t->first].WorldNormalPos.y; k <= op->Poslist[t->second].WorldNormalPos.y; k+=Num) {
							Pos pos(op->Poslist[t->first].WorldNormalPos.x, k, i);
							pos.RGB_COLOR(R, G, B);
							op->Poslist.push_back(pos);
						}
					}else{
						for (float k = op->Poslist[t->second].WorldNormalPos.y; k >= op->Poslist[t->first].WorldNormalPos.y; k -= Num) {
							Pos pos(op->Poslist[t->first].WorldNormalPos.x, k, i);
							pos.RGB_COLOR(R, G, B);
							op->Poslist.push_back(pos);
						}
					}
				}
			}
			if (op->Poslist[t->first].WorldNormalPos.z > op->Poslist[t->second].WorldNormalPos.z) {//op-》的z大于问题
				for (float i = op->Poslist[t->first].WorldNormalPos.z; i >= op->Poslist[t->second].WorldNormalPos.z; i-=Num) {
					if (op->Poslist[t->first].WorldNormalPos.y > op->Poslist[t->second].WorldNormalPos.y) {
						for (float k = op->Poslist[t->first].WorldNormalPos.y; k <= op->Poslist[t->second].WorldNormalPos.y; k += Num) {
							Pos pos(op->Poslist[t->first].WorldNormalPos.x, k, i);
							pos.RGB_COLOR(R, G, B);
							op->Poslist.push_back(pos);
						}
					}
					else {
						for (float k = op->Poslist[t->second].WorldNormalPos.y; k >= op->Poslist[t->first].WorldNormalPos.y; k -= Num) {
							Pos pos(op->Poslist[t->first].WorldNormalPos.x, k, i);
							pos.RGB_COLOR(R, G, B);
							op->Poslist.push_back(pos);
						}
					}
				}
			}
		}if (op->Poslist[t->first].WorldNormalPos.z == op->Poslist[t->second].WorldNormalPos.z) {
			if (op->Poslist[t->first].WorldNormalPos.x < op->Poslist[t->second].WorldNormalPos.x) {//op-》的x小于问题
				for (float i = op->Poslist[t->first].WorldNormalPos.x; i <= op->Poslist[t->second].WorldNormalPos.z; i += Num) {
					if (op->Poslist[t->first].WorldNormalPos.y > op->Poslist[t->second].WorldNormalPos.y) {
						for (float k = op->Poslist[t->first].WorldNormalPos.y; k <= op->Poslist[t->second].WorldNormalPos.y; k += Num) {
							Pos pos(op->Poslist[t->first].WorldNormalPos.x, k, i);
							pos.RGB_COLOR(R, G, B);
							op->Poslist.push_back(pos);
						}
					}
					else {
						for (float k = op->Poslist[t->second].WorldNormalPos.y; k >= op->Poslist[t->first].WorldNormalPos.y; k -= Num) {
							Pos pos(op->Poslist[t->first].WorldNormalPos.x, k, i);
							pos.RGB_COLOR(R, G, B);
							op->Poslist.push_back(pos);
						}
					}
				}
			}
			if (op->Poslist[t->first].WorldNormalPos.x > op->Poslist[t->second].WorldNormalPos.x) {//op-》的x大于问题
				for (float i = op->Poslist[t->first].WorldNormalPos.x; i >= op->Poslist[t->second].WorldNormalPos.x; i -= Num) {
					if (op->Poslist[t->first].WorldNormalPos.y > op->Poslist[t->second].WorldNormalPos.y) {
						for (float k = op->Poslist[t->first].WorldNormalPos.y; k <= op->Poslist[t->second].WorldNormalPos.y; k += Num) {
							Pos pos(i, k, op->Poslist[t->first].WorldNormalPos.z);
							pos.RGB_COLOR(R, G, B);
							op->Poslist.push_back(pos);
						}
					}
					else {
						for (float k = op->Poslist[t->second].WorldNormalPos.y; k >= op->Poslist[t->first].WorldNormalPos.y; k -= Num) {
							Pos pos(i, k, op->Poslist[t->first].WorldNormalPos.z);
							pos.RGB_COLOR(R, G, B);
							op->Poslist.push_back(pos);
						}
					}
				}
			}
		}
	}
}
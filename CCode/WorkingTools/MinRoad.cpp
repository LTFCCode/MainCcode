#include "stdafx.h"



#define CITY_NUM 10
#define MAXRADIS 20
#define MINRADIS 5
#define X_LENGTH 100
#define Y_LENGTH 100
#define X_MAX 80
#define X_MIN 20
#define Y_MAX 80
#define Y_MIN 20
#define MIN_EQUAL 0.06
#define MIN_DISTANCE 1.0//建筑物之间最小距离
#define BASEIC_X 50
#define BASEIC_Y 50
#define BASEIC_RADIS 10
#define RANDOMSEED 30
#define PI acos(-1)

typedef struct sAddress
{
	float x;//横坐标
	float y;//纵坐标
	bool operator == (const sAddress& e)
	{
		return fabs(this->x - e.x)< MIN_EQUAL && fabs(this->y - e.y)<MIN_EQUAL;
	}
}sAddress;
typedef struct sRoad
{
	sAddress local;
	sRoad* left;
	sRoad* right;
}sRoad;
typedef struct sTangentline
{
	float k;
	float b;
	bool operator == (const sTangentline& e) 
	{
		return this->k == e.k;
	}
}sTangentline;
typedef struct 
{
	sAddress address;//坐标
	float radis;//半径
}sBuliding;
typedef struct sPoint
{
	sAddress start_point;
	sAddress end_point;
	sBuliding start_bulid;
	sBuliding end_bulid;
	bool operator == (const sPoint& e)
	{
		return this->start_point == e.start_point && this->end_point == e.end_point;
	}
}sPoint;

sAddress Start;
sAddress End;
float GetDistence(sAddress address1, sAddress address2)//两点间距离
{
	return sqrt((address1.x - address2.x)*(address1.x - address2.x) + (address1.y - address2.y)*(address1.y - address2.y));
}
bool IsInCircle(sBuliding buliding, sAddress point)
{
	if (GetDistence(buliding.address, point) <= buliding.radis)
	{
		return true;
	}
	else
	{
		return false;
	}
}
float ToLow(float aim)
{
	stringstream buff;
	buff.precision(2);
	buff.setf(std::ios::fixed);
	buff << aim;
	return atof(buff.str().c_str());
}
//判断建筑初始化时是否在有效范围内
inline bool UnValidCircle(sBuliding aim_buliding)
{
	//建筑超范围或建筑包含起点或终点
	if (aim_buliding.address.x > X_MAX || aim_buliding.address.x <X_MIN || aim_buliding.address.y > Y_MAX || aim_buliding.address.y < Y_MIN 
		|| IsInCircle(aim_buliding, Start) || IsInCircle(aim_buliding, End) || aim_buliding.radis<MINRADIS)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool UnvalidPoint(sAddress point)
{
	return (point.x > X_LENGTH || point.y > Y_LENGTH);
}
bool operator > (sAddress p1, sAddress p2)
{
	if (GetDistence(p1, Start)> GetDistence(p2, Start))
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool operator == (sBuliding b1, sBuliding b2)
{
	return (fabs(b1.address.x - b2.address.x) <0.1 && fabs(b1.address.y - b2.address.y) < 0.1);
}
bool operator < (sBuliding b1, sBuliding b2)
{
	float dis1, dis2;
	dis1 = sqrt((b1.address.x - Start.x)*(b1.address.x - Start.x) + (b1.address.y - Start.y)*(b1.address.y - Start.y));
	dis2 = sqrt((b2.address.x - Start.x)*(b2.address.x - Start.x) + (b2.address.y - Start.y)*(b2.address.y - Start.y));
	if (dis1 < dis2)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool operator > (sBuliding b1, sBuliding b2)
{
	float dis1, dis2;
	dis1 = sqrt((b1.address.x - Start.x)*(b1.address.x - Start.x) + (b1.address.y - Start.y)*(b1.address.y - Start.y));
	dis2 = sqrt((b2.address.x - Start.x)*(b2.address.x - Start.x) + (b2.address.y - Start.y)*(b2.address.y - Start.y));
	if (dis1 > dis2)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool operator != (sBuliding b1, sBuliding b2)
{
	return (fabs(b1.address.x - b2.address.x) > 0.1 && fabs(b1.address.y - b2.address.y) > 0.1);
}
float GetDistence(sBuliding buliding1, sBuliding buliding2)//两圆间距离
{
	return sqrt((buliding1.address.x - buliding2.address.x)*(buliding1.address.x - buliding2.address.x) + (buliding1.address.y - buliding2.address.y)*(buliding1.address.y - buliding2.address.y));
}
bool CircularIntersection(sBuliding buliding1, sBuliding buliding2)
{
	//若两圆相交则返回true，否则返回false
	return GetDistence(buliding1, buliding2) < buliding1.radis + buliding2.radis + MIN_DISTANCE ? true : false;
}
sTangentline getKB(sAddress start, sAddress end)//两点成线
{
	sTangentline line;
	line.k = ToLow((end.y - start.y) / (end.x - start.x));
	line.b = ToLow(start.y - start.x * line.k);
	
	return line;
}
sAddress getintersect(float k1,float b1,float k2,float b2)//两线交点
{
	sAddress result;
	if (fabs(k1 - k2) > MIN_EQUAL)
	{
		result.x = ToLow((b2 - b1) / (k1 - k2));
		result.y = ToLow(k1 * result.x + b1);
	}
	else
	{
		result.x = 0.0;
		result.y = 0.0;
	}
	return result;
}
sAddress getintersect(sTangentline line1,sTangentline line2)
{
	return getintersect(line1.k,line1.b,line2.k,line2.b);
}
bool IsIntersect(sBuliding buliding, sAddress start,sAddress end)//线段与圆是否相交
{
	float k1, b1 = 0.0;
	sTangentline line = getKB(start,end);
	k1 = (-1) / line.k;
	b1 = buliding.address.y - buliding.address.x * k1;
	sAddress intersect = getintersect(k1, b1, line.k, line.b);

	if (GetDistence(intersect, buliding.address) < buliding.radis && intersect > start&& GetDistence(start, buliding.address) > buliding.radis + 9)
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool IsIntersect_noAdd(sBuliding buliding, sAddress start, sAddress end)//线段与圆是否相交
{
	float k1, b1 = 0.0;
	sTangentline line = getKB(start, end);
	k1 = (-1) / line.k;
	b1 = buliding.address.y - buliding.address.x * k1;
	sAddress intersect = getintersect(k1, b1, line.k, line.b);

	if (GetDistence(intersect, buliding.address) < buliding.radis-1 && intersect > start && !(intersect > end))
	{
		return true;
	}
	else
	{
		return false;
	}
}
bool IsIntersect_noAdd(sBuliding buliding, sTangentline line)//线段与圆是否相交
{
	float k1, b1 = 0.0;
	k1 = (-1) / line.k;
	b1 = buliding.address.y - buliding.address.x * k1;
	sAddress intersect = getintersect(k1, b1, line.k, line.b);

	if (GetDistence(intersect, buliding.address) < buliding.radis-1)
	{
		return true;
	}
	else
	{
		return false;
	}
}
float getlength(vector<sAddress> data)
{
	float result = 0.0;
	sAddress point_old(Start);
	for (auto item : data)
	{
		result += GetDistence(point_old,item);
		point_old = item;
	}
	return result;
}
float GetArcLength(sAddress point1, sAddress point2, sBuliding aim_buliding)
{
	sTangentline line1;
	line1 = getKB(point1, aim_buliding.address);
	float k1, b1 = 0.0;
	k1 = (-1) / line1.k;
	b1 = point2.y - point2.x * k1;
	sAddress intersect = getintersect(k1, b1, line1.k, line1.b);

	float a = GetDistence(point2, intersect);
	float b = GetDistence(aim_buliding.address, intersect);

	return atan(a / b)* aim_buliding.radis;
}
bool CompareVector(vector<sAddress>v1,vector<sAddress>v2)
{
	return getlength(v1) < getlength(v2);
}
bool CompareBuliding(sBuliding buliding1, sBuliding buliding2)
{
	return buliding1 < buliding2;
}
bool CompareBuliding_inverted(sBuliding buliding1, sBuliding buliding2)
{
	return buliding1 > buliding2;
}
bool ComparePoint(sPoint p1,sPoint p2)
{
	return p1.start_bulid < p2.start_bulid;
}
bool ComparePoint_saddress(sPoint p1, sPoint p2)
{
	return p1.start_point > p2.start_point;
}
bool CompareLine(sTangentline line1,sTangentline line2)
{
	return line1.k < line2.k;
}
bool ComparePointDis(vector<sPoint> p1, vector<sPoint> p2)
{
	float dis1 = 0.0;
	float dis2 = 0.0;
	sPoint run(p1[0]);
	for (auto item : p1)
	{ 
		if (run.start_bulid != item.start_bulid)
		{
			if (run.end_bulid == item.start_bulid)
			{
				dis1 += GetDistence(run.start_point,run.end_point);
				dis1 += GetArcLength(run.end_point,item.start_point,run.end_bulid);
			}
			run = item;
		}
		else
		{
			continue;
		}
	}
	dis1 += GetDistence(End,(p1.end()-1)->end_point);
	run = (p2[0]);
	for (auto item : p2)
	{
		if (run.start_bulid != item.start_bulid)
		{
			if (run.end_bulid == item.start_bulid)
			{
				dis2 += GetDistence(run.start_point, run.end_point);
				dis2 += GetArcLength(run.end_point, item.start_point, run.end_bulid);
			}
			run = item;
		}
		else
		{
			continue;
		}
	}
	dis2 += GetDistence(End, (p2.end() - 1)->end_point);
	return dis1 < dis2;
}
class cCity
{
public:
	vector<sBuliding> Bulidings;
	vector<sBuliding> goByBuliding;
	vector<sPoint> point_road;
	vector<vector<sPoint>> point_tanLine;
	vector<sPoint> public_tanline;
	sRoad road;
	vector <vector<sAddress>> road_point;
	int road_num;
	cCity(int num);
	sBuliding GetFirst(sAddress start);
	std::tuple<sAddress, sAddress>  GetNext(sAddress start);
	std::tuple<sAddress, sAddress>  cycle(sAddress start);
	std::tuple<sTangentline, sTangentline>  GetTangent(sAddress aim, sBuliding buliding);
	sAddress  GetTangent(sTangentline line, sBuliding buliding);
	std::tuple<sAddress, sAddress>  GetTangentPoint(sAddress aim, sBuliding buliding);
	void  GetPublicTangent(sBuliding buliding1, sBuliding buliding2);
	void  GetPublicTangent(sBuliding buliding1, sBuliding buliding2,vector<sTangentline>* result);
	void cycle(sRoad* road);
	void showroad();
	void getroad();
	void getPublicTangentPoint(sAddress p_start,vector<sPoint>* result);
	void getGoByBuliding(sTangentline line, vector<sBuliding>* result);
	void getPublicRoad();
	void getPublicRoad(sPoint start);
	void showcity();
	void writeRoad(sRoad* road, vector<sAddress> vector_run);
	void writeRoad(sPoint* point, vector<sPoint> vector_run);
	void writeRoad();
	void writeBetterRoad();
	bool No_Inter(sAddress p1, sAddress p2);
	bool No_Inter(sTangentline line1);
};
cCity::cCity(int num)
{
	Start.x = 0;
	Start.y = 0;
	this->road.local = Start;
	this->road.left = NULL;
	this->road.right = NULL;
	End.x = X_LENGTH ;
	End.y = Y_LENGTH ;
	road_num = 0;
	int result = num-1;
	bool Intersection ;//新建筑与已有建筑是否相交标志

	//先添加基础中心建筑
	sBuliding base_buliding;
	base_buliding.address.x = BASEIC_X;
	base_buliding.address.y = BASEIC_Y;
	base_buliding.radis = BASEIC_RADIS;
	this->Bulidings.emplace_back(base_buliding);

	//添加周边建筑

	int seed = RANDOMSEED;
	do
	{
		Intersection = false;
		sBuliding new_buliding;
		std::default_random_engine e;
		std::uniform_int_distribution<int> u(20, 80);
		e.seed(seed);
		seed++;
		new_buliding.address.x = u(e);
		new_buliding.address.y = u(e);
		new_buliding.radis = (u(e) % (MAXRADIS + 1));
		if (UnValidCircle(new_buliding))
		{
			continue;
		}
		else
		{
			for (auto buliding : this->Bulidings)
			{
				if (CircularIntersection(new_buliding,buliding))
				{
					Intersection = true;
					break;
				}
			}
			if (Intersection)
			{
				continue;
			}
			else
			{
				this->Bulidings.emplace_back(new_buliding);
				printf("添加建筑:(%f,%f,%f)\n",new_buliding.address.x,new_buliding.address.y,new_buliding.radis);
				result--;
			}
		}
	} while (result > 0);
	std::sort(this->Bulidings.begin(), this->Bulidings.end(),CompareBuliding);
	this->showcity();
}
void cCity::showcity()
{
	int i = 0;
	string folder = "E:\\CCode\\ServiceDemo\\ReadExcel\\Tools\\Bulidings.txt";
	fstream out(folder, ios::out);
	for (auto buliding : this->Bulidings)
	{
		i++;
		printf("建筑%d:(%0.2f,%0.2f,%0.2f)\n",i,buliding.address.x,buliding.address.y,buliding.radis);
		out  << buliding.address.x<<","<< buliding.address.y<<","<< buliding.radis<< endl;
	}
	out.close();
}
void cCity::getroad()
{
	for (auto buliding : this->Bulidings)
	{
		if (IsIntersect(buliding,Start,End))
		{
			this->goByBuliding.emplace_back(buliding);
		}
	}
	std::sort(this->goByBuliding.begin(), this->goByBuliding.end(), CompareBuliding);

	sBuliding buliding_old;
	sBuliding start_buliding;
	start_buliding.address = Start;
	start_buliding.radis = 0;
	sBuliding end_buliding;
	end_buliding.address = Start;
	end_buliding.radis = 0;
	for (auto buliding : this->goByBuliding)
	{
		if (buliding.address == this->goByBuliding.begin()->address)
		{
			sAddress point1, point2;
			std::tie(point1, point2) = this->GetTangentPoint(Start, buliding);
			sPoint run;
			run.start_point = Start;
			run.end_point = point1;
			run.start_bulid = start_buliding;
			run.end_bulid = buliding;
			this->point_road.emplace_back(run);
			run.end_point = point2;
			this->point_road.emplace_back(run);
			buliding_old = buliding;
			continue;
		}
		else if (buliding.address == (this->goByBuliding.end() - 1)->address)
		{
			sAddress point1, point2;
			std::tie(point1, point2) = this->GetTangentPoint(End, buliding);

			sPoint run;
			run.start_point = point1;
			run.end_point = End;
			run.start_bulid = buliding;
			run.end_bulid = end_buliding;
			this->point_road.emplace_back(run);
			run.start_point = point2;
			this->point_road.emplace_back(run);

			this->GetPublicTangent(buliding_old, buliding);
		}
		else
		{
			this->GetPublicTangent(buliding_old, buliding);
		}
		buliding_old = buliding;
	}
	std::sort(this->point_road.begin(), this->point_road.end(), ComparePoint);
	vector<sPoint> vector_run;
	this->writeRoad(&(this->point_road[0]), vector_run);
	this->writeRoad(&(this->point_road[1]), vector_run);
	std::sort(this->point_tanLine.begin(), this->point_tanLine.end(), ComparePointDis);

	string folder = "E:\\CCode\\ServiceDemo\\ReadExcel\\Tools\\PublicTangent.txt";
	fstream out(folder, ios::out);

	for (auto item : this->point_tanLine[0])
	{
		out << item.start_point.x << "," << item.start_point.y << "," << item.end_point.x << "," << item.end_point.y << "," ;
	}
	out << endl;
	for (auto item : this->point_road)
	{
		out << item.start_point.x << "," << item.start_point.y << "," << item.end_point.x << "," << item.end_point.y << "," << endl;
	}
	out.close();
}
bool cCity::No_Inter(sAddress p1, sAddress p2)
{
	float k1, b1,dis = 0.0;
	sAddress intersect;
	sTangentline line = getKB(p1, p2);
	k1 = (-1) / line.k;
	sAddress p_far, p_near;
	if (p1>p2)
	{
		p_far = p1;
		p_near = p2;
	}
	else
	{
		p_far = p2;
		p_near = p1;
	}
	for (auto buliding : this->Bulidings)
	{
		b1 = buliding.address.y - buliding.address.x * k1;
		intersect = getintersect(k1, b1, line.k, line.b);
		dis = GetDistence(intersect, buliding.address);
		if (dis< buliding.radis  && fabs(dis - buliding.radis) > 0.5  && buliding.address>p_near && !(buliding.address>p_far))
		{
			return false;
		}
	}
	return true;
}
bool cCity::No_Inter(sTangentline line)
{
	float k1, b1,dis = 0.0;
	sAddress intersect;
	k1 = (-1) / line.k;
	for (auto buliding : this->Bulidings)
	{
		b1 = buliding.address.y - buliding.address.x * k1;
		intersect = getintersect(k1, b1, line.k, line.b);
		dis = GetDistence(intersect, buliding.address);
		if (dis< buliding.radis  && fabs(dis - buliding.radis) > 0.5)
		{
			return false;
		}
	}
	return true;
}
void cCity::getPublicTangentPoint(sAddress p_start, vector<sPoint>* result)
{
	sPoint p_run;
	sBuliding near_buliding;
	float near_dis = X_LENGTH + Y_LENGTH;
	vector<sBuliding> GBBuliding;
	sTangentline line = getKB(p_start,End);
	for (auto item : this->Bulidings)
	{
		if (GetDistence(p_start,item.address) - item.radis< near_dis)
		{
			p_run.start_bulid = item;
			near_buliding = item;
		}
	}
	this->getGoByBuliding(line, &GBBuliding);
	if (GBBuliding.size() == 0)
	{
		return;
	}
	for (auto item : GBBuliding)
	{
		if (item == near_buliding)
		{
			continue;
		}
		vector<sTangentline> v_lines;
		this->GetPublicTangent(item, near_buliding, &v_lines);
		for (auto line : v_lines)
		{
			if (this->No_Inter(line))
			{
				p_run.end_bulid = item;
				p_run.end_point = this->GetTangent(line, item);
				p_run.start_point = this->GetTangent(line, near_buliding);
				p_run.start_bulid = near_buliding;
				result->emplace_back(p_run);
			}
		}
	}
	return;
}
void cCity::getGoByBuliding(sTangentline line, vector<sBuliding>* result)
{
	for (auto item : this->Bulidings)
	{
		if (IsIntersect_noAdd(item,line))
		{
			result->emplace_back(item);
		}
	}
	return;
}
void cCity::getPublicRoad()
{
	sPoint start;
	start.start_point = Start;
	start.end_point = Start;
	this->getPublicRoad(start);
}
void cCity::getPublicRoad(sPoint start)
{
	vector<sPoint> result;
	printf("计算起点(%f,%f)\n", start.end_point.x, start.end_point.y);
	if (start.end_point == Start)
	{
		sTangentline line = getKB(start.end_point, End);
		vector<sBuliding> GBBuliding;
		sPoint p_run(start);
		this->getGoByBuliding(line, &GBBuliding);
		if (GBBuliding.size() == 0)
		{
			printf("建筑物(%.0f,.0%f)可直线到达终点\n", start.start_bulid.address.x, start.start_bulid.address.y);
			return;
		}	
		sAddress p_left, p_right;
		for (auto item : GBBuliding)
		{
			std::tie(p_left, p_right) = this->GetTangentPoint(Start, item);
			if (this->No_Inter(Start,p_left))
			{
				p_run.end_point = p_left;
				p_run.end_bulid = item;
				this->public_tanline.emplace_back(p_run);
				this->getPublicRoad(p_run);
			}
			if (this->No_Inter(Start, p_right))
			{
				p_run.end_point = p_right;
				p_run.end_bulid = item;
				this->public_tanline.emplace_back(p_run);
				this->getPublicRoad(p_run);
			}
		}	
		return;
	}
	else
	{
		sAddress p_left, p_right;
		std::tie(p_left, p_right) = this->GetTangentPoint(End, start.end_bulid);

		sTangentline line_left = getKB(p_left, End);
		vector<sBuliding> GBBuliding_left;
		this->getGoByBuliding(line_left, &GBBuliding_left);
		if (GBBuliding_left.size() == 0)
		{
			sPoint p_run;
			p_run.start_point = p_left;
			p_run.start_bulid = start.end_bulid;
			p_run.end_point = End;
			p_run.end_bulid.address = End;
			p_run.end_bulid.radis = 0.0;
			printf("建筑物(%.0f,%.0f)经左侧到达终点\n", start.start_bulid.address.x, start.start_bulid.address.y);
			this->public_tanline.emplace_back(p_run);
			return;
		}
		else
		{
			this->getPublicTangentPoint(p_left, &result);
		}

		sTangentline line_right = getKB(p_right, End);
		vector<sBuliding> GBBuliding_right;
		this->getGoByBuliding(line_right, &GBBuliding_right);
		if (GBBuliding_right.size() == 0)
		{
			sPoint p_run;
			p_run.start_point = p_right;
			p_run.start_bulid = start.end_bulid;
			p_run.end_point = End;
			p_run.end_bulid.address = End;
			p_run.end_bulid.radis = 0.0;
			printf("建筑物(%.0f,%.0f)经右侧到达终点\n", start.start_bulid.address.x, start.start_bulid.address.y);
			this->public_tanline.emplace_back(p_run);
			return;
		}
		else
		{
			this->getPublicTangentPoint(p_right, &result);
		}

		if (result.size() == 0)
		{
			printf("错误起点(%f,%f)未得到结果\n", start.start_point.x, start.start_point.y);
		}
		else
		{
			std::sort(result.begin(), result.end(), ComparePoint_saddress);
			result.erase(unique(result.begin(), result.end()), result.end());
			for (auto item : result)
			{
				this->public_tanline.emplace_back(item);
				this->getPublicRoad(item);
			}
		}
	}
	return;
}

void cCity::GetPublicTangent(sBuliding buliding1, sBuliding buliding2)
{
	float x1 = buliding1.address.x;
	float y1 = buliding1.address.y;
	float x2 = buliding2.address.x;
	float y2 = buliding2.address.y;
	float r1 = buliding1.radis;
	float r2 = buliding2.radis;
	float x = x1-x2;
	float y = y1-y2;
	float r = r1-r2;
	float r_add = r1 + r2;
	sTangentline line[4];
	for (int i = 0; i < 4;i++)
	{
		if (i==0)
		{
			line[i].k = (x*y + r*sqrt(x*x + y*y - r*r)) / (x*x - r*r);
			line[i].b = ((x1*r2 - x2*r1)*line[i].k + (r1*y2 - r2*y1))/r;
		}
		if (i == 1)
		{
			line[i].k = (x*y - r*sqrt(x*x + y*y - r*r)) / (x*x - r*r);
			line[i].b = ((x1*r2 - x2*r1)*line[i].k + (r1*y2 - r2*y1))/r;
		}
		if (i == 2)
		{
			line[i].k = (x*y + r_add*sqrt(x*x + y*y - r_add*r_add)) / (x*x - r_add*r_add);
			line[i].b = (-(x1*r2 + x2*r1)*line[i].k + (r1*y2 + r2*y1))/r_add;
		}
		if (i == 3)
		{
			line[i].k = (x*y - r_add*sqrt(x*x + y*y - r_add*r_add)) / (x*x - r_add*r_add);
			line[i].b = (-(x1*r2 + x2*r1)*line[i].k + (r1*y2 + r2*y1))/r_add;
		}
	}
	sPoint run;
	run.start_bulid = buliding1;
	run.end_bulid = buliding2;
	for (auto item : line)
	{
		run.start_point = this->GetTangent(item, buliding1);
		run.end_point = this->GetTangent(item, buliding2);
		this->point_road.emplace_back(run);
	}
}
void cCity::GetPublicTangent(sBuliding buliding1, sBuliding buliding2, vector<sTangentline>* result)
{
	float x1 = buliding1.address.x;
	float y1 = buliding1.address.y;
	float x2 = buliding2.address.x;
	float y2 = buliding2.address.y;
	float r1 = buliding1.radis;
	float r2 = buliding2.radis;
	float x = x1 - x2;
	float y = y1 - y2;
	float r = r1 - r2;
	float r_add = r1 + r2;
	sTangentline line[4];
	for (int i = 0; i < 4; i++)
	{
		if (i == 0)
		{
			line[i].k = (x*y + r*sqrt(x*x + y*y - r*r)) / (x*x - r*r);
			line[i].b = ((x1*r2 - x2*r1)*line[i].k + (r1*y2 - r2*y1)) / r;
		}
		if (i == 1)
		{
			line[i].k = (x*y - r*sqrt(x*x + y*y - r*r)) / (x*x - r*r);
			line[i].b = ((x1*r2 - x2*r1)*line[i].k + (r1*y2 - r2*y1)) / r;
		}
		if (i == 2)
		{
			line[i].k = (x*y + r_add*sqrt(x*x + y*y - r_add*r_add)) / (x*x - r_add*r_add);
			line[i].b = (-(x1*r2 + x2*r1)*line[i].k + (r1*y2 + r2*y1)) / r_add;
		}
		if (i == 3)
		{
			line[i].k = (x*y - r_add*sqrt(x*x + y*y - r_add*r_add)) / (x*x - r_add*r_add);
			line[i].b = (-(x1*r2 + x2*r1)*line[i].k + (r1*y2 + r2*y1)) / r_add;
		}
		result->emplace_back(line[i]);
	}
	return;
}
std::tuple<sAddress, sAddress>  cCity::GetTangentPoint(sAddress aim, sBuliding buliding)
{
	sTangentline line1, line2;
	std::tie(line1, line2) = this->GetTangent(aim, buliding);
	float k1, b1 = 0.0;
	k1 = (-1) / line1.k;
	b1 = buliding.address.y - buliding.address.x * k1;
	sAddress intersect1 = getintersect(k1, b1, line1.k, line1.b);
	float k2, b2 = 0.0;
	k2 = (-1) / line2.k;
	b2 = buliding.address.y - buliding.address.x * k2;
	sAddress intersect2 = getintersect(k2, b2, line2.k, line2.b);
	printf("从点(%.0f,%.0f)得到两切点(%.0f,%.0f)(%.0f,%.0f)\n", aim.x, aim.y, intersect1.x, intersect1.y, intersect2.x, intersect2.y);
	return std::make_tuple(std::move(intersect1), std::move(intersect2));
}
sAddress cCity::GetTangent(sTangentline line , sBuliding buliding)
{
	float k1, b1 = 0.0;
	k1 = (-1) / line.k;
	b1 = buliding.address.y - buliding.address.x * k1;
	return getintersect(k1, b1, line.k, line.b);
}

sBuliding cCity::GetFirst(sAddress start)
{
	//todo:返回线段经过的第一个建筑坐标不经过建筑返回终点坐标
	sBuliding buliding_result;
	buliding_result.address.x = X_LENGTH;
	buliding_result.address.y = Y_LENGTH;
	buliding_result.radis = 0.0;

	float min = X_LENGTH + Y_LENGTH;
	float dis = 0.0;
	for (auto item :this->Bulidings)
	{
		if (IsIntersect(item, start, End))
		{
			if (item < buliding_result)
			{
				buliding_result = item;
			}
		}
	}
	return buliding_result;
}
std::tuple<sTangentline, sTangentline>  cCity::GetTangent(sAddress aim, sBuliding buliding)
{
	sTangentline line1, line2;
	float x = buliding.address.x - aim.x;
	float y = buliding.address.y - aim.y;
	float r = buliding.radis;
	line1.k = (x*y + r * sqrt(x*x + y*y - r*r)) / (x*x - r*r);
	line1.b = aim.y - aim.x * line1.k;
	line2.k = (x*y - r * sqrt(x*x + y*y - r*r)) / (x*x - r*r);
	line2.b = aim.y - aim.x * line2.k;
	if (line1.k > line2.k)
	{
		return std::make_tuple(std::move(line1), std::move(line2));
	}
	else
	{
		return std::make_tuple(std::move(line2), std::move(line1));
	}
}
std::tuple<sAddress, sAddress> cCity::GetNext(sAddress start)
{
	sBuliding aim_buliding = this->GetFirst(start);
	sAddress result1, result2;
	if (aim_buliding.radis >1)
	{
		printf("经过建筑:(%f,%f,%f)\n", aim_buliding.address.x, aim_buliding.address.y, aim_buliding.radis);
		sTangentline line1, line2, line3, line4;
		std::tie(line1, line2) = GetTangent(start, aim_buliding);
		std::tie(line3, line4) = GetTangent(End, aim_buliding);
		if (GetDistence(start, aim_buliding.address) <aim_buliding.radis)
		{
			printf("起点(%0.2f,%0.2f)在建筑(%0.2f,%0.2f,%0.2f)内\n", start.x, start.y, aim_buliding.address.x, aim_buliding.address.y, aim_buliding.radis);
			system("pause");
		}
		result1 = getintersect(line1, line4);
		result2 = getintersect(line2, line3);
		if (UnvalidPoint(result1) || UnvalidPoint(result2))
		{
			printf("point1(%f,%f) point2(%f,%f) 超出范围\n",result1.x,result1.y,result2.x,result2.y);
		}
	}
	else
	{
		printf("到达终点\n");
		result1 = End;
		result2 = End;
	}

	return std::make_tuple(std::move(result1), std::move(result2));
}
std::tuple<sAddress, sAddress> cCity::cycle(sAddress start)
{
	sAddress point1, point2;
	std::tie(point1, point2) = this->GetNext(start);
	return std::make_tuple(std::move(point1), std::move(point2));;
}
void cCity::cycle(sRoad* road)
{
	road->left = new sRoad;
	road->right = new sRoad;
	std::tie(road->left->local, road->right->local) = this->cycle(road->local);
	if (road->left->local == End)
	{
		road->left->left = nullptr;
		road->left->right = nullptr;
	}
	if (road->right->local == End)
	{
		road->right->left = nullptr;
		road->right->right = nullptr;
	}
	if (road->right->local == End && road->left->local == End)
	{
		return;
	}

	this->cycle(road->left);
	this->cycle(road->right);

}
void cCity::showroad()
{
	this->cycle(&this->road);
}
void cCity::writeRoad(sPoint* point, vector<sPoint> vector_run)
{
	vector_run.emplace_back(*point);
	if (point->end_point == End)
	{
		this->point_tanLine.emplace_back(vector_run);
		return;
	}
	for (auto item : this->point_road)
	{
		if (item.start_bulid == point->end_bulid)
		{
			this->writeRoad(&item, vector_run);
		}
	}
}
void cCity::writeRoad(sRoad* road, vector<sAddress> vector_run)
{
	vector_run.emplace_back(road->local);
	if (road->left->local == End && road->right->local ==End)
	{
		vector_run.emplace_back(End);
		this->road_point.emplace_back(vector_run);
		return;
	}
	if (road->left != NULL)
	{
		this->writeRoad(road->left, vector_run);
	}
	if (road->right != NULL)
	{
		this->writeRoad(road->right, vector_run);
	}
}
void cCity::writeRoad()
{
	vector<sAddress> vector_run;
	this->writeRoad(&this->road, vector_run);
	int i = 0;
	string folder = "E:\\CCode\\ServiceDemo\\ReadExcel\\Tools\\SimpleRoad.txt";
	fstream out(folder, ios::out);
	std::sort(this->road_point.begin(),this->road_point.end(),CompareVector);
	for (auto road_vector : this->road_point)
	{
		for (auto item : road_vector)
		{
			out << item.x << "," << item.y << ",";
		}
		i++;
		out << endl;
	}
	out.close();
}
void cCity::writeBetterRoad()
{
	string folder = "E:\\CCode\\ServiceDemo\\ReadExcel\\Tools\\BetterRoad.txt";
	fstream out(folder, ios::out);
	for (auto road : this->road_point)
	{
		stack<sAddress> stack_run;
		for (auto point : road)
		{
			if (stack_run.size() == 0)
			{
				stack_run.push(point);
			}
			else
			{
				for (auto buliding:this->Bulidings)
				{
					sTangentline line1 = getKB(stack_run.top(),point);
					sTangentline line2;
					line2.k = (-1) / line1.k;
					line2.b = buliding.address.y - buliding.address.x * line2.k;
					sAddress insert = getintersect(line1,line2);
					if (GetDistence(buliding.address,insert)<buliding.radis)
					{

					}
				}
			}
		}
	}
	out.close();
}
void MinRoad()
{
	cCity City(CITY_NUM);
	City.showroad();
	City.getroad();
	City.getPublicRoad();
	City.writeRoad();
	//City.writeBetterRoad();
}
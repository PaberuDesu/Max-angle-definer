#include <iostream>
using namespace std;

class Point {
public:
	float x;
	float y;
	bool exists;

	Point() {
		x = 0;
		y = 0;
		exists = false;
	}
	Point(float _x, float _y) {
		this->x = _x;
		this->y = _y;
		this->exists = true;
	}
};

class Quadrangle {
	float angle(Point PointCoord[3])
	{
		float X1 = PointCoord[0].x - PointCoord[1].x, Y1 = PointCoord[0].y - PointCoord[1].y;//���������� ������� �� ������ ����� � ������
		float X2 = PointCoord[2].x - PointCoord[1].x, Y2 = PointCoord[2].y - PointCoord[1].y;//���������� ������� �� ������ ����� � ������

		float Scalyar = X1 * X2 + Y1 * Y2;//��������� ������������ ��������

		float Abs1 = sqrt(float(pow(X1, 2) + pow(Y1, 2))), Abs2 = sqrt(float(pow(X2, 2) + pow(Y2, 2)));//����� �������� ����� ������� ��������

		float Cos = Scalyar / (Abs1 * Abs2);//������� �������� ����

		float Pi = 3.1415926535;//������������ �������� ����� ��

		float VectorAngle = acos(Cos) * 180 / Pi;//������� ���� ����� ���������
		return VectorAngle;
	}

public:
	Point PointsArray[4];

	Quadrangle() {}

	void create_point(float x, float y) {
		for (int pointNum = 0; pointNum < 4; pointNum++) {
			if (!PointsArray[pointNum].exists) {
				PointsArray[pointNum] = Point(x, y);
				return;
			}
		}
		cout << "Error. Tried to make an extra point";
	}

	float define_max_angle() {
		if (this->not_collinear()) {
			float MinimalX = PointsArray[0].x;

			for (int pointNum = 1; pointNum < 4; pointNum++) {
				if (PointsArray[pointNum].x < MinimalX) {
					MinimalX = PointsArray[pointNum].x;
					swap(PointsArray[pointNum], PointsArray[0]);
				}
			}//������ ����� � ����� ��������� � � ������ ������ (����� 0).
			float MinimalY = PointsArray[0].y;

			for (Point point : PointsArray) {
				point.x -= MinimalX;
				point.y -= MinimalY;
			}

			Point TestAngle1[3] = {PointsArray[1], PointsArray[0], PointsArray[2]};
			Point TestAngle2[3] = {PointsArray[1], PointsArray[0], PointsArray[3]};
			Point TestAngle3[3] = {PointsArray[2], PointsArray[0], PointsArray[3]};

			float TestAngle1Velocity = angle(TestAngle1), TestAngle2Velocity = angle(TestAngle2), TestAngle3Velocity = angle(TestAngle3);
			float MaxTestAngle = max(TestAngle1Velocity, TestAngle2Velocity);
			MaxTestAngle = max(MaxTestAngle, TestAngle3Velocity);

			if (MaxTestAngle == TestAngle1Velocity)
				swap(PointsArray[2], PointsArray[3]);

			else if (MaxTestAngle == TestAngle3Velocity)
				swap(PointsArray[2], PointsArray[1]);
			/*���������� � ������ ����� >= X ����� 0, � �� ����� ������ ����� �� ����� ���� �����, ������� �������, ������������ ��������� �������,
			���������� ���������� ���� � ����� 0 �� ���� ���������, ����� �������� ��������� ��������� ��������������, � ������� �� ����������� �������.
			������� ������ ������� ������ � ������, ���������� ����������� ������� ������ 2.*/

			float deltax = PointsArray[1].x - PointsArray[3].x;

			if (deltax) {
				float deltay = PointsArray[1].y - PointsArray[3].y;
				float k = deltay / deltax;
				float b = PointsArray[1].y - (PointsArray[1].x * k);

				if ((k * PointsArray[2].x + b > PointsArray[2].y) == (k * PointsArray[0].x + b > PointsArray[0].y)) {
					return 0;
				}
			}//�������� ��������� ������ y = kx + b. ���� ��������� 02 � 13 �� ������������, ��������������� ����������
			else if (PointsArray[1].x > PointsArray[2].x) {
				return 0;
			}//���� ���������� � ����� 1 � 3 ��������� � ��������� ���������� � ����� 2, �� ��������� 02 � 13 �� ������������, � ������, ��������������� ����������

			float maxAngle = 0;

			for (int pointNum = 0; pointNum < 4; pointNum++) {
				Point AnglePoints[3] = {
					PointsArray[pointNum],
					PointsArray[(pointNum + 1) % 4],
					PointsArray[(pointNum + 2) % 4]};

				float AngleVelocity = angle(AnglePoints);

				maxAngle = max(AngleVelocity, maxAngle);
			}//������� ���������� ����
			return maxAngle;
		}
		return 0;
	}

	bool not_collinear() {
		for (int pointNum1 = 0; pointNum1 < 2; pointNum1++) {
			for (int pointNum2 = pointNum1 + 1; pointNum2 < 3; pointNum2++) {
				for (int pointNum3 = pointNum2 + 1; pointNum3 < 4; pointNum3++) {
					float X1 = PointsArray[pointNum1].x - PointsArray[pointNum2].x, Y1 = PointsArray[pointNum1].y - PointsArray[pointNum2].y;

					float X2 = PointsArray[pointNum3].x - PointsArray[pointNum2].x, Y2 = PointsArray[pointNum3].y - PointsArray[pointNum2].y;

					if ((X1 && X2 && Y1 / X1 == Y2 / X2) || (Y1 && Y2 && X1 / Y1 == X2 / Y2) || (!X1 && !Y1) || (!X2 && !Y2)) {
						return false;
					}
				}
			}
		}
		return true;
		/*��������: ���� ���� �� ��� ����� �� ������� ����� �� ����� ������, �� ��� ����� �� ����� ���� ������ ������ � ���� �� ����������������.
		��� ������������� ���������������� ���� ��������� ����� �� ���� ����� ���������� �����������, ��� ������������� ����� ��� �������, �������
		����� ������ � ����� �� ����� � ��������������� � ���� ������ ������ �� ���� ����������. ��� ����� ����� �����������, ��� ��� ������� ���������
		� ��� ��������� X1/Y1 = X2/Y2 �������.*/
	}
};

int main() {
	const float max_limit = 3.4 * pow(10,38);

	Quadrangle quad;

	for (int pointNum = 0; pointNum < 4; pointNum++) {
		float point_coords[2];

		for (int coordinate = 0; coordinate < 2; coordinate++) {
			while (true) {
				char CoordChar = !coordinate ? 'X' : 'Y';
				/*��������� ������ PointsArray ������������ ��� ���������� ��������� � � Y ���� ���� �����. ���������� � ������������ � ������ PointsArray[pointNum][coordinate],
				��� coordinate = 0. ���������� ��� ��������� Y coordinate = 1. ����� �������, � ������� ���������� ��������� !coordinate ? 'X' : 'Y' �� �����������
				CoordChar ���������� ��������, ���������� ����������, ������� ��������� ������ �� ������������ (X ��� Y)*/

				cout << "Enter the " << CoordChar << " coordinate of point number " << pointNum + 1 << ":" << endl;
				string UserInput;
				cin >> UserInput;//���� ��������� �����

				point_coords[coordinate] = strtof(UserInput.c_str(), NULL);
				if (point_coords[coordinate] || UserInput == "0") {
					if (abs(point_coords[coordinate]) <= max_limit) break;
					cout << "You have to print a number from -3.4*10^38 to 3.4*10^38." << endl;
				}/*��������, �������� �� ��������� ������������� ����� ������. �� ��������� ��������� ����� � �����. ���� ���������� ������� �����, ��� �� ���������,
				���� �� ������� �� �����, PointsArray[pointNum][coordinate] ������ �������� false ��� ������� ������ � �������� ������� ����������. ��� ����� ����������
				��� �������� ����� 0, ������� ��� ����� ��������� ��������.*/
				else cout << "You have to print a number." << endl;
			}
		}
		quad.create_point(point_coords[0], point_coords[1]);
	}

	float max_angle = quad.define_max_angle();
	if (!max_angle) {
		cout << "Quadrangle isn't convex";
		return 0;
	}
	cout << endl << max_angle << " degrees" << endl;//������� ������������ ���� ����������������
}
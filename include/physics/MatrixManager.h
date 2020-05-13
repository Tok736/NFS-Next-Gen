#ifndef PHYSICS_MATRIXMANAGER_H
#define PHYSICS_MATRIXMANAGER_H

class MatrixManager{
public:
	void rotatePart(int *matrixA, float angle);//поворот объектной матрицы
	void matrixOverlay(int *matrixA, int *matrixB);//наложение объектных матриц друг на друга, клетки наложения помечаются маркером с определенным весом для расчетов
	void makeBordersCurves(int *matrixA, float coefficient);//деформация объектной матрицы(новые коэффициенты)
};

#endif //PHYSICS_MATRIXMANAGER_H

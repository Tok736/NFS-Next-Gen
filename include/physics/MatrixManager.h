#ifndef PHYSICS_MATRIXMANAGER_H
#define PHYSICS_MATRIXMANAGER_H

class MatrixManager{
public:
	void rotatePart(int[][] &matrixA, float angle);
	void overlayByDepth(int[][] &matrixA, int[][] &matrixB, float depth);
	int[][] &multiplication(int[][] &matrixA, int[][] &matrixB);
	void transporense(int[][]& matrixA);
	void makeBordersCurves(int[][] &matrixA, float coefficient);
};

#endif //PHYSICS_MATRIXMANAGER_H

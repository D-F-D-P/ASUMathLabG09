//Multiply
int** multiply_matrix(int** A, int** B, int rows, int columns)
{
	int** result = createEmptyMatrix(rows, columns);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			for (int k = 0; k < columns; k++)
			result[i][j] += A[k][j] * B[i][k];
		}
	}

	return result;
}

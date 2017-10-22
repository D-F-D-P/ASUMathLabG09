int** sum_matrix(int** A, int** B, int rows, int columns)
{
	int** result = createEmptyMatrix(rows, columns);

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			result[i][j] = A[i][j] + B[i][j];
		}
	}

	return result;
}
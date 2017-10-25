double** fill_matrix(double** A, int rows, int columns)
{
	cout << "Please fill the matrix with its elements" << endl;
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			cin >> A[i][j];
			cout << "\t";
		}
		cout << endl;
	}

	return A;
}

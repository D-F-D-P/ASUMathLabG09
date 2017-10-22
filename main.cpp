void destroy_matrix(int** matrix, int rows)
{
	for (int i = 0; i < rows; i++)
	{
		delete[] matrix[i]; //deletes an inner array of integer;
	}
  
	delete[] matrix; //delete pointer holding array of pointers;
}

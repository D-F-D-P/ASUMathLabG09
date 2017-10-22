//print matrix

void print_matrix(int**A,int rows,int columns){
	for(int i=0;i<rows;i++){
		for(int j=0;j<columns;j++){
			cout<<A[i][j]<<"\t";
		}
		cout<<endl;
	}
}

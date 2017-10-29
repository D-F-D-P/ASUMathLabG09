
matrix matrix::operator * (matrix& m){
    if (this->columns!=m.rows)
      //Or whatever the doctor says
	    cout << "error columns of first is not equal rows of the second" << endl;
    matrix r(this->rows,m.columns);

    //initializing elements of matrix r=0
    for (int i=0;i<this->rows;i++){
        for (int j=0;j<m.columns;j++){
            r.elements[rows][columns]=0;
        }
    }

    // Multiplying and store in r
     for (int i=0;i<this->rows;i++){
        for (int j=0;j<m.columns;j++){
            for (int k=0;k<this->columns;k++){
                r.elements[rows][columns] += this->elements[rows][k]*m.elements[k][columns];
            }
        }
    }
    return r;
}

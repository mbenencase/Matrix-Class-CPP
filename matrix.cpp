#include <iostream>
#include <stdexcept>

template< typename T >
class matrix{	
	public:
		int rows;
		int cols;
		T **Mat;
	
	public:
		//constructor
		matrix(int rows, int cols);

		//destructor
		~matrix();
		
		//operators overloading
		matrix< T >& operator=(const matrix< T >& );
		matrix< T >& operator+=(const matrix< T >& );
		matrix< T >& operator-=(const matrix< T >& );
		matrix< T > operator+(const matrix< T >& ) const;
		matrix< T > operator-(const matrix< T >& ) const;
		matrix< T > operator*(const matrix< T >& ) const; //Matrix product
		T const* operator[](int const i) const{
			return &Mat[0][i];		
		}
		T* operator[](int const i){
			return &Mat[0][i];
		}

		//methods------------------------------------------------------------		
		void insert(int row, int column, T value){
			//Insert values at the given row and given column
			this->Mat[row][column] = value;
		}
		
		matrix< T > tranpose(){
			//Returns the tranposed array or matrix
			matrix< T > aux(cols, rows);
			
			for(int j = 0 ; j < cols ; j++)
				for(int i = 0 ; i < rows ; i++)
					aux.Mat[j][i] = this->Mat[i][j];
			
			int rows_ = rows;
			
			rows = cols;
			cols = rows_;			
			
			return aux; 
		}
		
		void show(){
			//Print method to array or matrix visualization
			for(int i = 0 ; i < rows ; i++){
				for(int j = 0 ; j < cols ; j++)
					std::cout << Mat[i][j] << " ";
				
				std::cout << std::endl;
			}
		}
		//end methods--------------------------------------------------------
};

//------------Constructor------------------------
template< typename T >
matrix< T >::matrix(int rows_, int cols_){
	rows = rows_;
	cols = cols_;
	
	Mat = new T*[rows];
	
	for(int i = 0 ; i < rows ; i++){
		Mat[i] = new T[cols];
	}
	
	for(int i = 0 ; i < rows ; i++)
		for(int j = 0 ; j < cols ; j++)
			Mat[i][j] = 0;
}

//------------Destructor------------------------
template< typename T >
matrix< T >::~matrix(){
	for(int i = 0 ; i < rows ; i++)
		delete Mat[i];
	
	delete Mat;
}

//------------Operators-Overloading--------------
template< class T >
matrix< T >& matrix< T >::operator=(const matrix< T >& m1){
	if(m1.rows != rows && m1.cols != cols)
		throw std::domain_error("matrix op= not of same order");
	
	for(int i = 0 ; i < rows ; i++)
		for(int j = 0 ; j < cols ; j++)
			Mat[i][j] = m1.Mat[i][j];
	
	return *this;
}

template< class T >
matrix< T >& matrix< T >::operator+=(const matrix< T >& m1){
	if(m1.rows != rows && m1.cols != cols)
		throw std::domain_error("matrix op+ not of same order");
	
	for(int i = 0 ; i < rows ; i++)
		for(int j = 0 ; j < cols ; j++)
			Mat[i][j] += m1.Mat[i][j];
	
	return *this;	
}

template< class T >
matrix< T >& matrix< T >::operator-=(const matrix< T >& m1){
	if(m1.rows != rows && m1.cols != cols)
		throw std::domain_error("matrix op+ not of same order");
	
	for(int i = 0 ; i < rows ; i++)
		for(int j = 0 ; j < cols ; j++)
			Mat[i][j] -= m1.Mat[i][j];
	
	return *this;	
}

template< class T >
matrix< T > matrix< T >::operator+(const matrix< T >& m1) const{
	matrix< T > result(rows, cols);
	
	for(int i = 0 ; i < rows ; i++)
		for(int j = 0 ; j < cols ; j++)
			result.Mat[i][j] = this->Mat[i][j] + m1.Mat[i][j];
	
	return result;
}

template< class T >
matrix< T > matrix< T >::operator-(const matrix< T >& m1) const{
	matrix< T > result(rows, cols);
	
	for(int i = 0 ; i < rows ; i++)
		for(int j = 0 ; j < cols ; j++)
			result.Mat[i][j] = this->Mat[i][j] - m1.Mat[i][j];
	
	return result;
}

template< class T >
matrix< T > matrix< T >::operator*(const matrix< T >& m1) const{
	if(cols != m1.rows)
		throw std::domain_error("matrix dimensions does not match");
		
	matrix< T > result(rows, cols);
	
	for(int i = 0 ; i < rows ; i++)
		for(int j = 0 ; j < m1.cols ; j++)
			for(int k = 0 ; k < cols ; k++)
				result.Mat[i][j] += this->Mat[i][k] * m1.Mat[k][j];
	
	return result;
}

#include "assignment1.h"

double ** choleskyDecomp(double ** A, int n, int i)
{
	double **L;
	initMatrix(&L, n);
	int a,b;
	double divisor = A[i][i];
	
	for (a = 0; a < n; a++)
	{
		for (b = 0; b < n; b++)
		{
			if (a==b)
			{
				L[a][b] = 1;
			}
			
			else
			{
				L[a][b] = 0;
			}
		}
	}
	L[i][i] = pow(A[i][i], 0.5);
		
	
	for (a = i+1; a < n; a++)
	{
		L[a][i] = A[a][i]/(pow(A[i][i], 0.5));
	}	
	
	double v[n-1-i];

	for (a=0; a<n-1-i; a++)
	{
		v[a] = A[i][a+1+i];
	}	
	
	for (a = i; a < n; a++)
	{
		A[i][a] = 0;
		A[a][i] = 0;
	}
	A[i][i] = 1;	
	
	if (identity(A,n) == 1)
	{
		freeMatrix(A,n);
		return L;
	}

	double **B;
	initMatrix(&B, n);
	
	for (a = 1 + i; a < n; a++)
	{
		for (b=1 + i; b<n;b++)
		{
			B[a][b] = v[a-1-i]*v[b-1-i];
		}
	}
	
	for (a = 0; a <n; a++)
	{
		for (b = 0; b<n; b++)
		{
			A[a][b] = A[a][b] - ((B[a][b])/divisor);
		}
	}
	freeMatrix(B,n);
	return mult(L, choleskyDecomp(A, n, i+1), n);
}

double ** mult(double ** L1,double ** L2, int n)
{
	int i,j,k,dotprod = 0;
	double **matrix;
	initMatrix(&matrix, n);

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			for (k = 0; k < n; k++)
			{
				dotprod += L1[i][k] * L2[k][j];
			}
			matrix[i][j] = dotprod;
			dotprod = 0;		
		}
	}
	if (L1 == L2)
	{
		freeMatrix(L1, n);
	}
	else
	{
		freeMatrix(L1, n);
		freeMatrix(L2, n);
	}		
	return matrix;
}

int identity(double ** A, int n)
{
	int i,j, check = 1;
	double **identity;
	initMatrix(&identity, n);
	
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (i == j)
			{
				identity[i][j] = 1;
			}
			
			else
			{
				identity[i][j] = 0;
			}
		}
	}
	
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (A[i][j] != identity[i][j])
			{
				check = 0;
			}	
		}
	}
	freeMatrix(identity, n);
	return check; 
}


void initMatrix(double ***mat,int n)
{
	int i,j;
	double **matrix = (double **)malloc(sizeof(double*)*n);
	for (i = 0; i < n; i++)
	{
		matrix[i] = (double *)malloc(sizeof(double)*n);
		for (j = 0; j < n; j++)
		{
			matrix[i][j] = 0;
		}	
	}	
	*mat = matrix;
}

double **readMatrix(char * filename)
{
	FILE *fp = fopen(filename,"r");
	double ** matrix;
	initMatrix(&matrix, MATSIZE);
	int i,j;
	
	for (i = 0; i < MATSIZE; i++)
	{
		for (j = 0; j < MATSIZE; j++)
			{			
				fscanf(fp, "%lf",&(matrix[i][j]));
			}
	}
	
	fclose(fp);
	return matrix; 
	
}

void freeMatrix(double ** matrix, int n)
{
	int i,j;
	for (i = 0; i < n; i++)
	{
		free(matrix[i]);
		matrix[i] = NULL;
	}
	free(matrix);
	matrix = NULL;	
}

void printMatrix(double ** A, int n)
{
	int i,j;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			printf("%f ", A[i][j]);		
		}
		printf("\n");
	}	
}
